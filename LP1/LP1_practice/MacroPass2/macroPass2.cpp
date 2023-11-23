#include<iostream>
#include<map>
#include<vector>
#include<fstream>
using namespace std;

class MacroProcesser{
    public:
    vector<string>mainFile;
    vector<string>output;
    map<int,map<string,string>>KPDTAB;
    map<string,map<int,string>>ALLPNTABS;
    map<string,vector<int>>MNT;
    map<int,vector<string>>MDT;
    map<string,map<int,string>>ALLAPTABS;
    fstream file,kptab,pntab,mnt,mdt;
    
    MacroProcesser(){
        file.open("macroInput.txt");
        if(!file.is_open()){
            cout<<"Error in opening mainFile file "<<endl;
        }
        else{
            string line;
            while (!file.eof())
            {
                getline(file,line);
                mainFile.push_back(line);
            }
        }

        kptab.open("kptab.txt");
        if(!kptab.is_open()){
            cout<<"Error in opening kptab file "<<endl;
        }
        else{
            string line;
            while (!kptab.eof())
            {
                vector<string>v;
                getline(kptab,line);
                
                string w="";
                for(int i = 0;i<line.length();i++){
                    if(line[i]!=' '){
                        w+=line[i];
                    }
                    else{
                        v.push_back(w);
                        w="";
                    }
                }
                v.push_back(w);
                map<string,string>temp;
                temp[v[1]]=v[2];
                KPDTAB[stoi(v[0])]=temp;
            }
            
        }
        pntab.open("pntab.txt");
        if(!pntab.is_open()){
            cout<<"Error in opening pntab file "<<endl;
        }
        else{
            string line;
            vector<string>allLines;
            while (!pntab.eof())
            {
                getline(pntab,line);
                allLines.push_back(line);
            }
            map<int,string>tempPNTAB;
            string macroName="";
            int cntInd = 0;
            for(int itr = 0;itr<allLines.size();itr++){
                if(allLines[itr][0]!='&'){
                    macroName = allLines[itr];
                    ALLPNTABS[macroName]=tempPNTAB;
                    cntInd=0;
                    tempPNTAB.clear();
                }
                else{
                    cntInd++;
                    vector<string>tempVec;
                    string w="";
                    for(int p = 0;p<allLines[itr].length();p++){
                        if(allLines[itr][p]!=' '){
                            w+=allLines[itr][p];
                        }
                        else{
                            tempVec.push_back(w);
                            w="";
                        }
                    }
                    tempVec.push_back(w);
                    tempPNTAB[cntInd]=tempVec[0];
                }
            }    
        }
        mdt.open("mdt.txt");
        if(!mdt.is_open()){
            cout<<"Error in opening mdt file "<<endl;
        }
        else{
            string line;
            int ind = 1;
            while (!mdt.eof())
            {
                getline(mdt,line);
                vector<string>words;
                string w="";
                for(int k = 0;k<line.length();k++){
                    if(line[k]!=' '){
                        w+=line[k];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }
                words.push_back(w);
                MDT[ind]=words;
                ind++;
            }
            
        }
        mnt.open("mnt.txt");
        if(!mnt.is_open()){
            cout<<"Error in opening mnt file "<<endl;
        }
        else{
            string line;
            while (!mnt.eof())
            {
                getline(mnt,line);
                vector<string>words;
                string w="";
                for(int k = 0;k<line.length();k++){
                    if(line[k]!=' '){
                        w+=line[k];
                    }
                    else{
                        words.push_back(w);
                        w="";
                    }
                }
                words.push_back(w);
                string macroName = words[0];
                vector<int>otherFields;
                for(int k = 1;k<words.size();k++){
                    otherFields.push_back(stoi(words[k]));
                }
                MNT[macroName]=otherFields;
            }
            
        }
    }

    void display(){
        ofstream fout;
        fout.open("myMDT.txt");
        for(auto itr:MDT){
            fout<<itr.first<<" ";
            for(auto itr2:itr.second){
                fout<<itr2<<" ";
            }
            fout<<endl;
        }  
        fout.close();

        cout<<"Display MDT"<<endl;
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
            cout<<itr.first<<" ";
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<" ";
            }
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
        cout<<endl;
        cout<<"Display ALLAPTABS"<<endl;
        for(auto itr:ALLAPTABS){
            cout<<"Macro Name : "<<itr.first<<" "<<endl;
            for(auto itr2:itr.second){
                cout<<itr2.first<<" "<<itr2.second<<endl;
            }
            cout<<endl;
        }

        cout<<endl;
        cout<<"Display output File"<<endl;
        for(auto itr:output){
            cout<<itr<<" "<<endl;
        }
    }
    void PerfromPass2(){
        int macrosEncountered = 0 ;
        //split single line into words and then do operation
        for(int i = 0;i<mainFile.size();i++){
            
            vector<string>splittedLine;
            string currLine = mainFile[i];
            string w="";
            for(int k = 0;k<currLine.length();k++){
                if(currLine[k]!=' '){
                    w+=currLine[k];
                }
                else{
                    splittedLine.push_back(w);
                    w="";
                }
            }
            splittedLine.push_back(w);

            if(splittedLine[0] == "MEND")
            {
                macrosEncountered++;
            }

            //check if the firstword is macro name
            string firstWord = splittedLine[0];
            if(MNT.find(firstWord)!=MNT.end() && macrosEncountered == MNT.size()){
                string macroName = firstWord;
                int noOfPP = MNT[macroName][0];
                int noOfKP = MNT[macroName][1];
                map<int,string>currAPTAB;

                //add all positional parameters
                for(int num=1;num<=noOfPP;num++){
                    currAPTAB[num]=splittedLine[num];
                }

                //iterate on kpdtab using kpdptr and write whatever value is there.
                int kpdtptr = MNT[macroName][3];
                int tempCnt = 0;
                for(auto tempItr:KPDTAB){
                    if(tempCnt < noOfKP){
                        if(tempItr.first >= kpdtptr){
                            for(auto tpItr2:tempItr.second){
                                currAPTAB[noOfPP+tempCnt+1]=tpItr2.second;
                                tempCnt++;
                            }
                        }
                    }
                    else{
                        break;
                    }
                }
                //now check any KP values given in Macro Call
                for(int num = noOfPP+1;num<splittedLine.size();num++){
                    string completeWord = splittedLine[num];
                    int indOfEqu = 0;
                    for(int l = 0;l<completeWord.length();l++){
                        if(completeWord[l]=='='){
                            indOfEqu=l;
                            break;
                        }
                    }
                    //find seperate key and value given in call
                    string keywordParaName = completeWord.substr(0,indOfEqu);
                    string value=completeWord.substr(indOfEqu+1,completeWord.size()-(indOfEqu+1));
                    int indexForAPTAB;
                    //now find what will be the index of given parameter in APTAB
                    for(auto itr:KPDTAB){
                        for(auto itr2:itr.second){
                            if(itr2.first==keywordParaName){
                                indexForAPTAB=itr.first;
                                break;
                            }
                        }
                    }
                    //add value to that index
                    currAPTAB[noOfPP+indexForAPTAB]=value;
                }
                ALLAPTABS[macroName]=currAPTAB;


                //EXPANDING THE MACRO CALL
                int mdtptr = MNT[macroName][2];
                //iterate over mdt
                for(auto itr:MDT){
                    if(itr.first>=mdtptr){
                        if(itr.second[0]=="MEND"){
                            break;
                        }
                        else{
                            string tempAns = "";
                            tempAns+="+ ";
                            tempAns+=itr.second[0];
                            tempAns+=" ";
                            if(itr.second[1][0]=='('){
                                int index =itr.second[1][3]-'0';
                                tempAns+=ALLAPTABS[macroName][index];
                                tempAns+=" ";
                            }
                            else{
                                tempAns+=itr.second[1];     
                                tempAns+=" ";
                            }
                            if(itr.second[2][0]=='('){
                                int index =itr.second[2][3]-'0';
                                tempAns+=ALLAPTABS[macroName][index];
                                tempAns+=" ";
                            }
                            else{
                                tempAns+=itr.second[2];
                                tempAns+=" ";
                            }
                            output.push_back(tempAns);
                            
                        }
                    }
                }
            }
            else{
                output.push_back(currLine);
            }
        }
    }
};

int main(){
    MacroProcesser obj;
    obj.PerfromPass2();
    obj.display();
}