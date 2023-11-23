#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

class Mnemonic
{
public:
    string m_class;
    int opcode;
    Mnemonic() {}
    Mnemonic(string m_class, int opcode)
    {
        this->m_class = m_class;
        this->opcode = opcode;
    }
    string get_class()
    {
        if (m_class == "IS")
        {
            return "IS";
        }
        else if (m_class == "AD")
        {
            return "AD";
        }
        else if (m_class == "DL")
        {
            return "DL";
        }
        else
        {
            return "";
        }
    }
    friend class Lookup;
};

class Lookup
{
public:
    map<string, Mnemonic> lookup = {
        {"START", Mnemonic("AD", 1)},
        {"END", Mnemonic("AD", 2)},
        {"ORIGIN", Mnemonic("AD", 3)},
        {"EQU", Mnemonic("AD", 4)},
        {"LTORG", Mnemonic("AD", 5)},

        {"DC", Mnemonic("DL", 1)},
        {"DS", Mnemonic("DL", 2)},

        {"STOP", Mnemonic("IS", 0)},
        {"ADD", Mnemonic("IS", 1)},
        {"SUB", Mnemonic("IS", 2)},
        {"MULT", Mnemonic("IS", 3)},
        {"MOVER", Mnemonic("IS", 4)},
        {"MOVEM", Mnemonic("IS", 5)},
        {"COMP", Mnemonic("IS", 6)},
        {"BC", Mnemonic("IS", 7)},
        {"DIV", Mnemonic("IS", 8)},
        {"READ", Mnemonic("IS", 9)},
        {"PRINT", Mnemonic("IS", 10)},
    };

    Mnemonic get_mnemonic(string name)
    {
        return lookup[name];
    }
    bool is_mnemonic(string name)
    {
        return lookup.find(name) != lookup.end();
    }
    friend class Tokenizer;
    friend class Pass1;
};

class Tokenizer
{
    Lookup table;
    vector<string> get_tokens(string is)
    {
        stringstream ss(is);
        string token;
        vector<string> tokens;
        while (getline(ss, token, '\t'))
        {
            tokens.push_back(token);
        }
        string label, mnemonic, op1, op2;
        if (table.is_mnemonic(tokens[0]))
        {
            mnemonic = tokens[0];
            if (tokens.size() == 2)
            {
                op1 = tokens[1];
            }
            else if (tokens.size() == 3)
            {
                op1 = tokens[1];
                op2 = tokens[2];
            }
        }
        else if (table.is_mnemonic(tokens[1]))
        {
            label = tokens[0];
            mnemonic = tokens[1];
            if (tokens.size() == 3)
            {
                op1 = tokens[2];
            }
            else if (tokens.size() == 4)
            {
                op1 = tokens[2];
                op2 = tokens[3];
            }
        }
        return {label, mnemonic, op1, op2};
    }
    friend class Pass1;
};

class SymbolTable
{
    vector<pair<string, int>> symtab;
    SymbolTable() {}
    bool present(string &s)
    {
        for (auto itr = symtab.begin(); itr != symtab.end(); ++itr)
        {
            if (itr->first == s)
            {
                return true;
            }
        }
        return false;
    }
    int get_index(string &s)
    {
        for (int i = 0; i < symtab.size(); i++)
        {
            if (symtab[i].first == s)
            {
                return i;
            }
        }
    }
    void make_entry(string s, int addr)
    {
        for (auto itr = symtab.begin(); itr != symtab.end(); ++itr)
        {
            if (itr->first == s)
            {
                itr->second = addr;
                return;
            }
        }
        symtab.push_back({s, addr});
    }
    void display_symtab()
    {
        for (int i = 0; i < symtab.size(); i++)
        {
            cout << i << "\t" << symtab[i].first << "\t" << symtab[i].second << endl;
        }
    }
    void write_symtab()
    {
        ofstream sym_tab;
        sym_tab.open("/home/pict/Documents/31173_LP1/test_cases/symtab_c1.txt", ios::trunc);
        for (int i = 0; i < symtab.size(); i++)
        {
            sym_tab << i << "\t" << symtab[i].first << "\t" << symtab[i].second << endl;
        }
        sym_tab.close();
    }
    friend class Pass1;
};

class LiteralTable
{
    vector<pair<string, int>> littab;
    int lit_ptr = 0;
    vector<int> pooltab;
    int s_ind = 0;
    LiteralTable() {}
    bool present(string &s)
    {
        for (auto itr = littab.begin(); itr != littab.end(); ++itr)
        {
            if (itr->first == s)
            {
                return true;
            }
        }
        return false;
    }
    int get_index(string &s)
    {
        for (int i = 0; i < littab.size(); i++)
        {
            if (littab[i].first == s)
            {
                return i;
            }
        }
    }
    void make_entry(string s, int addr)
    {
        for (auto itr = littab.begin(); itr != littab.end(); ++itr)
        {
            if (itr->first == s)
            {
                itr->second = addr;
                return;
            }
        }
        littab.push_back({s, addr});
        lit_ptr++;
    }
    void init(int &lc)
    {
        for (int i = 0; i < littab.size(); i++)
        {
            if (littab[i].second == -1)
            {
                littab[i].second = lc;
                lc++;
            }
        }
    }
    void new_pool()
    {
        s_ind = pooltab.size();
        pooltab.push_back(lit_ptr);
    }
    void write_littab()
    {
        ofstream lit_tab;
        lit_tab.open("/home/pict/Documents/31173_LP1/test_cases/littab_c1.txt", ios::trunc);
        for (int i = 0; i < littab.size(); i++)
        {
            lit_tab << i << "\t" << littab[i].first << "\t" << littab[i].second << endl;
        }
        lit_tab.close();
    }
    friend class Pass1;
};

class Pass1
{
public:
    vector<vector<string>> tokenised_lines;
    Tokenizer tok;
    SymbolTable ST;
    LiteralTable LT;
    Lookup lookup_table;
    int lc, sym_ptr;
    map<string, int> regs = {
        {"AREG", 1},
        {"BREG", 2},
        {"CREG", 3},
        {"DREG", 4}};
    map<string, int> conditionals = {
        {"LT", 1},
        {"LE", 2},
        {"EQ", 3},
        {"GT", 4},
        {"GE", 5},
        {"ANY", 6}};
    Pass1()
    {
        lc = 0;
        get_lines();
    }
    void get_lines()
    {
        ifstream src_code;
        src_code.open("/home/pict/Documents/31173_LP1/test_cases/testcase1.txt");
        string line;
        while (getline(src_code, line))
        {
            tokenised_lines.push_back(tok.get_tokens(line));
        }
        src_code.close();
    }
    void parser()
    {
        ofstream ic_code;
        LT.new_pool();
        ic_code.open("/home/pict/Documents/31173_LP1/test_cases/ic_c1.txt", ios::trunc);
        for (int i = 0; i < tokenised_lines.size(); i++)
        {
            vector<string> line = tokenised_lines[i];
            string instruction = line[1];
            Mnemonic is_mn = lookup_table.get_mnemonic(instruction);
            if (is_mn.m_class != "DL" && line[0] != "")
            {
                ST.make_entry(line[0], lc);
            }
            if (instruction == "START")
            {
                lc = stoi(line[2]);
                ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                        << "C," << line[2] << endl;
            }
            if (instruction == "LTORG")
            {
                LT.new_pool();
                LT.init(lc);
                ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << endl;
            }
            if (instruction == "ORIGIN")
            {
                if (check_sign(line[2]))
                {
                    lc = eval_offset(line[2]).second;
                    ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                            << "S," << eval_offset(line[2]).first << endl;
                }
                else
                {
                    if (ST.present(line[2]))
                    {
                        int s_index = ST.get_index(line[2]);
                        lc = ST.symtab[s_index].second;
                        ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                                << "S," << s_index << endl;
                    }
                    else
                    {
                        lc = stoi(line[2]);
                        ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                                << "C," << lc << endl;
                    }
                }
            }
            if (instruction == "END")
            {
                LT.init(lc);
                ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << endl;
            }
            if (instruction == "EQU")
            {
                if (check_sign(line[2]))
                {
                    int addr = eval_offset(line[2]).second;
                    ST.make_entry(line[0], addr);
                    string temp = eval_offset(line[2]).first;
                    ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                            << "S," << temp << endl;
                }
                else
                {
                    if (ST.present(line[2]))
                    {
                        int s_index = ST.get_index(line[2]);
                        int addr = ST.symtab[s_index].second;
                        ST.make_entry(line[0], addr);
                        ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                                << "S," << s_index << endl;
                    }
                    else
                    {
                        int s_index = ST.get_index(line[2]);
                        int addr = ST.symtab[s_index].second;
                        ST.make_entry(line[0], addr);
                        ic_code << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                                << "C," << lc << endl;
                    }
                }
            }
            if (is_mn.m_class == "IS")
            {
                if (instruction == "READ" || instruction == "PRINT")
                {
                    if (!ST.present(line[2]))
                    {
                        cout << "here" << endl;
                        ST.make_entry(line[2], -1);
                    }
                    int s_index = ST.get_index(line[2]);
                    ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                            << "S," << s_index << endl;
                }
                else if (instruction == "BC")
                {
                    if (!ST.present(line[3]))
                    {
                        ST.make_entry(line[3], -1);
                    }
                    int s_index = ST.get_index(line[3]);
                    ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t" << conditionals[line[2]] << "\t"
                            << "S," << s_index << endl;
                }
                else if (instruction == "STOP")
                {
                    ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << endl;
                }
                else
                {
                    if (line[3][0] == '=')
                    {
                        line[3] = regex_replace(line[3], regex("="), "");
                        line[3] = regex_replace(line[3], regex("'"), "");
                        // line[3].erase(remove(line[3].begin(), line[3].end(), '='), line[3].end());
                        // line[3].erase(remove(line[3].begin(), line[3].end(), '\''), line[3].end());
                        LT.make_entry(line[3], -1);
                        int l_index = LT.get_index(line[3]);
                        ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t" << regs[line[2]] << "\t"
                                << "L," << l_index << endl;
                    }
                    else
                    {
                        if (!ST.present(line[3]))
                        {
                            ST.make_entry(line[3], -1);
                        }
                        int s_index = ST.get_index(line[3]);
                        ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t" << regs[line[2]] << "\t"
                                << "S," << s_index << endl;
                    }
                }
                lc++;
            }
            else if (instruction == "DC" || instruction == "DS")
            {
                ST.make_entry(line[0], lc);
                sym_ptr++;
                ic_code << lc << "\t" << is_mn.get_class() << "," << is_mn.opcode << "\t"
                        << "C," << line[2] << endl;
                if (instruction == "DS")
                {
                    lc += stoi(line[2]);
                }
                else
                {
                    lc += 1;
                }
            }
        }
        ic_code.close();
        ST.write_symtab();
        LT.write_littab();
    }
    bool check_sign(string op)
    {
        return op.find('+') != string::npos || op.find('-') != string::npos;
    }
    pair<string, int> eval_offset(string op)
    {
        if (op.find('+') != string::npos)
        {
            string symbol = op.substr(0, op.find('+'));
            int offset = stoi(op.substr(op.find('+'), op.length()));
            int s_index = ST.get_index(symbol);
            int addr = ST.symtab[s_index].second + offset;
            string out = to_string(s_index) + " +" + to_string(offset);
            return {out, addr};
        }
        else
        {
            string symbol = op.substr(0, op.find('-'));
            int s_index = ST.get_index(symbol);
            int offset = stoi(op.substr(op.find('-'), op.length()));
            int addr = ST.symtab[s_index].second + offset;
            string out = to_string(s_index) + " " + to_string(offset);
            return {out, addr};
        }
    }
};

int main()
{
    Pass1 p1;
    p1.parser();
    return 0;
}
