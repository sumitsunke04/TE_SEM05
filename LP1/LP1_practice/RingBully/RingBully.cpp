#include<iostream>
#include<vector>
using namespace std;

class Process{
    public:
    int id;
    bool isActive;
    Process(){
        this->id = 0;
        this->isActive = true;
    }
    Process(int id){
        this->id = id;
        this->isActive = true;
    }
};

class BullyElection{
    public:
    vector<Process*>processes;
    BullyElection(vector<Process*>processes){
        this->processes = processes;
    }
    void BullyAlgo(int deactivatedID,int initiator){
        //make the id as deactivated
        int winnerID = -1;
        processes[deactivatedID]->isActive = false;
        int n = processes.size();
        for(int i = initiator;i<n;i++){
            if(processes[i]->isActive){
                for(int j = i+1;j<n;j++){
                    cout<<"Process : "<<processes[i]->id<<" has sent election msg to"<<processes[j]->id<<endl;
                }
                bool hasGotResponse = false;
                for(int j = i+1;j<n;j++){
                    if(processes[j]->isActive){
                        cout<<"Process : "<<processes[i]->id<<" receives response from"<<processes[j]->id<<endl;
                        hasGotResponse = true;
                    }
                }
                if(!hasGotResponse){
                    winnerID = i;
                    cout<<"Winner of this election is Process : "<<i<<endl;
                }
            } 
        }
        for(int i = 0;i<n;i++){
            cout<<winnerID<<" sends victory message to process : "<<processes[i]->id<<endl;
        }
    }
};

class RingElection{
    public:
    vector<Process*>processes;
    RingElection(vector<Process*>processes){
        this->processes = processes;
    }
    void RingAlgo(int deactivatedID,int initiator){
        vector<int>activeProcess;
        int winnerID = -1;
        processes[deactivatedID]->isActive = false;

        int currID = initiator;
        int n = processes.size();
        activeProcess.push_back(currID);
        currID++;
        while (true)
        {
            if(currID == initiator){
                winnerID = activeProcess[0];
                for(int k = 0;k<activeProcess.size();k++){
                    winnerID = max(winnerID,activeProcess[k]);
                }
                break;
            }
            if(processes[currID]->isActive){
                activeProcess.push_back(currID);
            }
            currID++;
            currID = currID%n;
        }
        cout<<"Winner of this election is "<<winnerID<<endl;
        for(int i = 0;i<n;i++){
            cout<<winnerID<<" sends victory message to process : "<<processes[i]->id<<endl;
        }
        
    }
};
int main(){
    vector<Process*>processes(7);
    for(int i = 0;i<7;i++){
        processes[i] = new Process(i);
    }
    
    // BullyElection obj(processes);
    // obj.BullyAlgo(5,2);
    RingElection obj(processes);
    obj.RingAlgo(5,2);
}