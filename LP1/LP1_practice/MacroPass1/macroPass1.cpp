#include<iostream>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

class MNTValues{
    public:
    int pp,kp,mdt,kpdt,kpdtptr;
    MNTValues(){
        pp=0;
        kp=0;
        mdt=0;
        kpdt=0;
        kpdtptr=0;
    }
};

class MacroProcesser{
    public:
    fstream file;
    // fstream macro_name_table;
    // fstream macro_definition_table;
    // fstream parameter_name_table;
    // fstream keyword_parameter_table;

    map<string,vector<int>>MNT;
    map<int,vector<string>>MDT;
    map<string,map<string,int>>ALLPNTABS;
    map<string,string>KPDTAB;

    MacroProcesser(){
        file.open("macroTest.txt");
        if(!file.is_open()){
            cout<<"Error in opening input file "<<endl;
        }
        // macro_definition_table.open("macro_definition_tabel.txt");
        // if(!macro_definition_table.is_open()){
        //     cout<<"Error in opening mdt file "<<endl;
        // }

        // macro_name_table.open("macro_name_table.txt");
        // if(!macro_name_table.is_open()){
        //     cout<<"Error in opening mnt file "<<endl;
        // }

        // keyword_parameter_table.open("keyword_parameter_table.txt");
        // if(!keyword_parameter_table.is_open()){
        //     cout<<"Error in opening kpdtab file "<<endl;
        // }

        // parameter_name_table.open("parameter_name_table.txt");
        // if(!parameter_name_table.is_open()){
        //     cout<<"Error in opening pntab file "<<endl;
        // }
    }

    int typeOfParameter(string para){
        if(para[para.length()-1]=='='){
            return 2;
        }
        else{
            for(int k = 0;k<para.length();k++){
                if(para[k]=='=') return 3;
            }
        }
        return 1;
    }

    void performpass1(){
        string line;
        vector<string>words;
        if(file.is_open()){
            //read file into strings
            bool inMacro = false;
            bool firstLine = false;
            string macroName;
            while (!file.eof())
            {
                //read one line into "line"
                getline(file,line);
                string w="";
                for(int i = 0;i<line.length();i++){
                    if(line[i]!=' '){
                        w+=line[i];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }

                //Below words vector contains all splitted words
                words.push_back(w);

                
                if(words[0]=="MACRO"){
                    // cout<<"Found your macro "<<endl;
                    inMacro = true;
                    firstLine = true;
                }
                else if(inMacro && firstLine){
                    firstLine = false;
                    macroName = words[0];
                    // cout<<"Reading your macro name "<<macroName<<endl;
                    int cntPP = 0;
                    int cntKP = 0;

                    //New PNTAB for this Macro
                    map<string,int>PNTAB;
                    for(int i = 1;i<words.size();i++){
                        if(typeOfParameter(words[i])==1){   //if its a positional parameter
                            string paraName = words[i].substr(1,words[i].length()-1);
                            PNTAB[paraName] = i;  //Add to PNTAB
                            cntPP++;
                        }
                        else if(typeOfParameter(words[i])==2){  //if its a keyword parameter
                            string paraName = words[i].substr(1,words[i].length()-2);
                            PNTAB[paraName] = i;
                            KPDTAB[paraName] = "-";
                            cntKP++;
                        }
                        else if(typeOfParameter(words[i])==3){
                            int indexOfEqu = 0;
                            for(int k = 0;k<words[i].length();k++){
                                if(words[i][k]=='='){
                                    indexOfEqu = k;
                                    break;
                                }
                            }
                            string paraName = words[i].substr(1,indexOfEqu-1);
                            string value = words[i].substr(indexOfEqu+1,words[i].length()-indexOfEqu);
                            KPDTAB[paraName] = value;
                            PNTAB[paraName] = i;
                            cout<<"Value "<<value<<endl;
                            cntKP++;
                        }
                        else{
                            cout<<"It should be a parameter but its not."<<endl;
                        }
                    }
                    MNT[macroName].push_back(cntPP);
                    MNT[macroName].push_back(cntKP);
                    MNT[macroName].push_back(MDT.size()+1);
                    MNT[macroName].push_back(KPDTAB.size()+1-cntKP);

                    ALLPNTABS[macroName]=PNTAB;
                }
                else{
                    if(words[0]=="MEND"){
                        MDT[MDT.size()+1].push_back(words[0]);
                    }
                    else{
                        vector<string>oprnds;
                        //push the first opcode
                        oprnds.push_back(words[0]);
                        //check for next two operands
                        for(int k = 1;k<words.size();k++){
                            // if its parameter then do IF
                            if(words[k].at(0)=='&'){
                                string pName = words[k].substr(1,words[k].length()-1);
                                int ind = ALLPNTABS[macroName][pName];
                                string temp = "(P,"+to_string(ind)+") ";
                                oprnds.push_back(temp);
                            }
                            else{
                                oprnds.push_back(words[k]);
                            }
                        }
                        MDT[MDT.size()+1] = oprnds;
                    }
                }
                words.clear();
            }
        }
        else{
            cout<<"Error in opening file "<<endl;
        }
    }

    void display(){
        cout<<"Display MDT"<<endl;
        for(auto itr:MDT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }
        ofstream fout ; 
        fout.open("MDT.txt");
        for(auto itr:MDT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }
        
        cout<<endl;
        cout<<"Display MNT"<<endl;
        for(auto itr:MNT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }

        cout<<endl;
        cout<<"Display KPDTAB"<<endl;
        for(auto itr:KPDTAB){
            cout<<itr.first<<" "<<itr.second;
            cout<<endl;
        }

        cout<<endl;
        cout<<"Display AllPNTABS"<<endl;
        for(auto itr:ALLPNTABS){
            cout<<"Macro Name : "<<itr.first<<" "<<endl;
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<endl;
            }
            cout<<endl;
        }
    }
};
int main(){
    MacroProcesser obj;
    obj.performpass1();
    obj.display();
}