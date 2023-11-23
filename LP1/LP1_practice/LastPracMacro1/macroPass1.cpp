#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<unordered_map>
using namespace std;

class MacroProcesser{
    public:
    
    map<string,vector<int>>MNT;
    map<int,vector<string>>MDT;
    map<string,string>KPDTAB;
    map<string,map<string,int>>ALLPNTABS;
    fstream file;
    MacroProcesser(){
        file.open("macroInput.txt");
        if(!file.is_open()){
            cout<<"Error in opening main input file "<<endl;
        }
    }

    int typeOfParameter(string para){
        if(para[para.length()-1]=='='){
            return 2;
        }
        else{
            for(int i = 0;i<para.length();i++){
                if(para[i]=='='){
                    return 3;
                }
            }
        }
        return 1;
    }

    void PerformPass1(){

        if(file.is_open()){
            string line;
            vector<string>words;
            bool firstLine = false;
            bool inMacro = false;
            string macroName="";
            while (!file.eof())
            {
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
                words.push_back(w);
                
                if(words[0]=="MACRO"){
                    inMacro =true;
                    firstLine = true;
                }
                else if(firstLine){
                    firstLine = false;
                    macroName = words[0];
                    int noOfPP = 0;
                    int noOfKP = 0;
                    map<string,int>currPNTAB;
                    for(int k = 1;k<words.size();k++){
                        if(typeOfParameter(words[k]) == 1){
                            currPNTAB[words[k]]=k;
                            noOfPP++;
                        }
                        else if(typeOfParameter(words[k]) == 2){
                            string paraName = words[k].substr(0,words[k].length()-1);
                            currPNTAB[paraName] = k;
                            KPDTAB[paraName]="-";
                            noOfKP++;
                        }
                        else if(typeOfParameter(words[k]) == 3){
                            int indOfEqu = 0;
                            for(int l = 0;l<words[k].length();l++){
                                if(words[k][l]=='='){
                                    indOfEqu = l;
                                    break;
                                }
                            }
                            string paraName = words[k].substr(0,indOfEqu);
                            string value = words[k].substr(indOfEqu+1,words[k].length()-(indOfEqu+1));
                            currPNTAB[paraName]=k;
                            KPDTAB[paraName]=value;
                            noOfKP++;
                        }
                        else{
                            cout<<"It should be a parameter but its not "<<endl;
                        }
                        ALLPNTABS[macroName] = currPNTAB;
                        
                    }
                    MNT[macroName].push_back(noOfPP);
                    MNT[macroName].push_back(noOfKP);
                    MNT[macroName].push_back(MDT.size()+1);
                    MNT[macroName].push_back(KPDTAB.size()+1-noOfKP);
                }
                else{
                    if(words[0]=="MEND"){
                        inMacro = false;
                        string currLine = "MEND";
                        MDT[MDT.size()+1].push_back(currLine);
                    }
                    else{
                        vector<string>currLine;
                        
                        currLine.push_back(words[0]);
                        
                        if(words[1][0]=='&'){
                            int ind = ALLPNTABS[macroName][words[1]];
                            string temp = "(P,"+to_string(ind)+")";
                            currLine.push_back(temp);
                        }
                        else{
                            currLine.push_back(words[1]); 
                        }
                        if(words[2][0]=='&'){
                            int ind = ALLPNTABS[macroName][words[2]];
                            string temp = "(P,"+to_string(ind)+")";
                            currLine.push_back(temp);
                        }
                        else{
                            currLine.push_back(words[2]); 
                        }
                        MDT[MDT.size()+1] = currLine;
                    }
                }
                words.clear();
            }
            
            
        }
        else{
            cout<<"Error in opening input file "<<endl;
        }
    }

    void display(){
        cout<<"Print MNT "<<endl;
        for(auto itr:MNT){
            cout<<"Macro : "<<itr.first<<endl;
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
        cout<<"Print MDT "<<endl;
        for(auto itr:MDT){
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"Print KPDTAB "<<endl;
        for(auto itr:KPDTAB){
            cout<<itr.first<<" "<<itr.second<<endl;
        }
        cout<<endl;
        cout<<endl;
        cout<<"Print ALLPNTABS "<<endl;
        for(auto itr:ALLPNTABS){
            cout<<"Macro : "<<itr.first<<endl;
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<endl;
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;

    }
};
int main(){
    MacroProcesser obj;
    obj.PerformPass1();
    obj.display();
}