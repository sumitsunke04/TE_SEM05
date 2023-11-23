
#include <iostream>
#include <map>
#include <vector>
#include<fstream>
using namespace std;

class LitTabEntry{
    public:
    int id;
    string literal;
    int address;

    LitTabEntry(int id,string literal,int address){
        this->id = id;
        this->literal = literal;
        this->address = address;
    }
};

class SymTabEntry{
    public:
    int id;
    string symbol;
    int address;

    SymTabEntry(int id,string symbol,int address){
        this->id = id;
        this->symbol = symbol;
        this->address = address;
    }
};
class ICGenerator
{
    // DEFINE ALL OPCODES
    map<string, string> AD;
    map<string, string> IS;
    map<string, string> DL;
    map<string, string> R;

public:
    ICGenerator()
    {
        AD["START"] = "01";
        AD["END"] = "02";
        AD["ORIGIN"] = "03";
        AD["EQU"] = "04";
        AD["LTORG"] = "05";

        IS["STOP"] = "00";
        IS["ADD"] = "01";
        IS["SUB"] = "02";
        IS["MULT"] = "03";
        IS["MOVER"] = "04";
        IS["MOVEM"] = "05";
        IS["COMP"] = "06";
        IS["BC"] = "07";
        IS["DIV"] = "08";
        IS["READ"] = "09";
        IS["PRINT"] = "10";

        DL["DC"] = "01";
        DL["DS"] = "02";

        R["AREG"] = "01";
        R["BREG"] = "02";
        R["CREG"] = "03";
        R["DREG"] = "04";
        R["ANY"] = "06";
    }

private:

    // ??????????????????
    bool isStrNum(string strNum){
        int len = strNum.length();
        for(int i = 0;i<len;i++){
            if(strNum[i]-'0' > 9){
                return false;
            }
        }
        return true;
    }
    //String to Number
    int strToNum(string str){
        int num = 0;
        for(int i = 0;i<str.length();i++){
            num = num*10 + (str[i]-'0');
        }
        return num;
    }

    // Number to string
    string numToStr(int num){
        string ans = "";
        int x = num;
        while(x){
            int digit = x%10;
            char dg =(char)( digit+'0');
            ans = dg+ans;
            x/=10;
        }
        if(!num){
            return "0";
        }
        return ans;
    }
    // FUNCTION FOR SPLITING A STRING AND ACCESSING ALL ITS WORDS
    vector<string> getWords(string line)
    {
        vector<string> ans;
        int n = line.length();
        int i = 0;
        string word = "";
        while (i < n)
        {
            if (line[i] != ' ')
            {
                word += line[i];
            }
            else
            {
                ans.push_back(word);
                word = "";
            }
            i++;
        }
        if (word != "")
        {
            ans.push_back(word);
        }
        return ans;
    }

    //Read each line from file
    vector<string> readFile(string fileName){
        ifstream fin;
        fin.open(fileName);
        vector<string>codeLines;
        while (!fin.eof())
        {
            string line;
            getline(fin,line);
            codeLines.push_back(line);
        }
        fin.close();
        return codeLines;
        
    }

    // CHECK FOR LABEL
    bool checkForLabel(string word)
    {
        if (AD[word] !="" && IS[word] !="" && DL[word]!="")
        {
            return false;
        }
        
        return true;
    }

    
    //Create object of each line
    Instruction seggregateToken(vector<string>words ){

        int len = words.size();
        int i = 0;
        Instruction instr;
        bool isLabel = false;
        if(checkForLabel(words[0])){
            isLabel = true;
            instr.label = words[0];
        }
        if(isLabel){
            i++;
        }
        if(i<len){
            instr.opcode = words[i];
            i++;
        }
        if(i<len){
            instr.operand1 = words[i];
            i++;
        }
        if(i<len){
            instr.operand2 = words[i];
            i++;
        }
        return instr;
    }

    vector<Instruction> getPreprocessedInstructions(vector<string>codeLines){
        int noOfLines = codeLines.size();
        vector<Instruction> ans;
        for(int i = 0;i<noOfLines;i++){
            vector<string> words = getWords(codeLines[i]);
            Instruction instr = seggregateToken(words);
            ans.push_back(instr);
        }
        return ans;
    }


    //Update Symbol Table
    void updateSymTab(string label,int address,vector<SymTabEntry>&symTab){
        int len = symTab.size();
        for(int i = 0;i<len;i++){
            if(symTab[i].symbol == label){
                if(symTab[i].address == -1){
                    symTab[i].address = address;
                }
                return;
            }
        }
        SymTabEntry newEntry(symTab.size()+1,label,address);
        symTab.push_back(newEntry);
        return;
    }

    // ?????????????????????????????????????????????????????????
    //update Literal Table
    void updateLitTab(string literal,vector<LitTabEntry>&litTab,vector<int>&poolTab){
        int i = 0;
        int startId = poolTab.back();
        int litTablen = litTab.size();

        while (i<litTablen && litTab[i].id != startId)
        {
            i++;
        }
        if(i == litTablen){
            LitTabEntry newLitTabEntry(startId,literal,-1);
            litTab.push_back(newLitTabEntry);
            return ;
        }
        while (i<litTablen && litTab[i].literal != literal)
        {
            i++;
        }
        if(i == litTablen){
            LitTabEntry newEntry(litTab.back().id+1,literal,-1);
            litTab.push_back(newEntry);
            return;
        }
        

        
    }

    int getSymTabIndex(string symbol,vector<SymTabEntry>&symTab){
        for(int i = 0;i<symTab.size();i++){
            if(symTab[i].symbol == symbol){
                return symTab[i].id;
            }
        }
        return -1;
    }

    int getLitTabIndex(string literal,vector<LitTabEntry>&litTab){
        for(int i = 0;i<litTab.size();i++){
            if(litTab[i].literal == literal){
                return litTab[i].id;
            }
        }
        return -1;
    }

    //Add Opcode
    void addOpcode(string &procStr,string opcode){
        if(opcode=="STOP"){
            procStr+="(IS,0)";
            return ;
        }
        if(AD[opcode]!=""){
            procStr = procStr + "(AD,"+AD[opcode]+")";
        }
        else if(IS[opcode]!=""){
            procStr = procStr + "(IS,"+IS[opcode]+")";
        }
        else if(DL[opcode]!=""){
            procStr = procStr + "(DL,"+DL[opcode]+")";
        }
        else{
            cout<<"Invalid Opcode"<<endl;
        }
    }

    // ??????????????????????????????????
    //Add Operand
    void addOperand(string operand,string &procStr,vector<LitTabEntry>&LitTab,vector<SymTabEntry>&SymTab,vector<int>&poolTab){
        // when the constant is there e.g:'3'
        // operand can be '3',AREG,="3",3,ANYSYMBOL
        if(operand[0] == '\''){
            operand = operand.substr(1,operand.length()-2);
        }
        if(R[operand]!=""){
            procStr = procStr+"("+R[operand]+")";
            return ;
        }
        else if(operand[0] == '='){
            updateLitTab(operand,LitTab,poolTab);
            int index = getLitTabIndex(operand,LitTab);
            procStr = procStr + "(L,"+numToStr(index)+")";
        }
        else if(isStrNum(operand)){
            procStr = procStr + "(C,"+operand+")";
        }
        else{
            int index = getSymTabIndex(operand,SymTab);
            int addres = -1;
            if(index == -1){
                updateSymTab(operand,-1,SymTab);
            }
            index = getSymTabIndex(operand,SymTab);
            procStr = procStr + "(S,"+numToStr(index)+")";
        }
        return ;
    }

    void drawline(){
        cout<<"------------------------------------------------------------------"<<endl;
        
    }
};

class Instruction
{
    string label, opcode, operand1, operand2;

public:
    Instruction()
    {
        this->label = "";
        this->opcode = "";
        this->operand1 = "";
        this->operand2 = "";
    }
    Instruction(string label, string opcode, string operand1, string operand2)
    {
        this->label = label;
        this->opcode = opcode;
        this->operand1 = operand1;
        this->operand2 = operand2;
    }
    friend class ICGenerator;
};

int main()
{

}