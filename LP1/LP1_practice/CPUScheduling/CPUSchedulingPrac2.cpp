#include<iostream>
#include<vector>
#include<limits.h>
#include<queue>
using namespace std;

class Process{
    public:
    int arr,bur,comp,tat,prio,proc,wt;
    
    Process(){
        this->proc = -1;
        this->arr = -1;
        this->bur=-1;
        this->comp = -1;
        this->tat = -1;
        this->wt = -1;
        this->prio = -1;
    }
    Process(int proc,int arr,int bur,int comp,int tat,int wt,int prio){
        this->proc = proc;
        this->arr = arr;
        this->bur=bur;
        this->comp = comp;
        this->tat = tat;
        this->wt = wt;
        this->prio = prio;
    }
};

class Schedular{
    public:
    void display(vector<Process*>processes,int n){
        for(int i = 0;i<n;i++){
            cout<<processes[i]->proc<<" "<<processes[i]->arr<<" "<<processes[i]->bur<<" "<<processes[i]->comp<<" "<<processes[i]->tat<<" "<<processes[i]->wt<<" "<<processes[i]->prio<<endl;
        }
    }
    void FCFS(vector<Process*>processes,int n){
        //Sort according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(processes[j]->arr > processes[j+1]->arr){
                    swap(processes[j],processes[j+1]);
                }
            }
        }

        int currTime = 0;
        for(int i = 0;i<n;i++){
            if(processes[i]->arr > currTime){
                currTime = processes[i]->arr;
            }
            processes[i]->comp = currTime+processes[i]->bur;
            processes[i]->tat = processes[i]->comp-processes[i]->arr;
            processes[i]->wt = processes[i]->tat-processes[i]->bur;
            currTime = processes[i]->comp;
        }
        display(processes,n);
    }

    void PriorityNonPreemptive(vector<Process*>processes,int n){
        //Sort according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(processes[j]->arr > processes[j+1]->arr){
                    swap(processes[j],processes[j+1]);
                }
            }
        }

        int currTime = 0;
        bool isExecuted[n+1] = {false};
        for(int i =0;i<n;i++){
            int maxPriority = INT_MAX;
            int maxprioIndex = -1;

            int minArrivalTime = INT_MAX;
            int minArrTimeIndex = -1;
            for(int j = 0;j<n;j++){
                //if current process id is not executed
                if(!isExecuted[processes[j]->proc]){
                    if(processes[j]->arr <= currTime){
                        if(maxPriority > processes[j]->prio){
                            maxprioIndex = j;
                            maxPriority = processes[j]->prio;
                        }

                        if(processes[j]->arr < minArrivalTime){
                            minArrivalTime = processes[j]->arr;
                            minArrTimeIndex = j;
                        }
                    }
                }
            }
            if(minArrivalTime<=currTime){
                processes[maxprioIndex]->comp = currTime+processes[maxprioIndex]->bur;
                processes[maxprioIndex]->tat = processes[maxprioIndex]->comp-processes[maxprioIndex]->arr;
                processes[maxprioIndex]->wt = processes[maxprioIndex]->tat-processes[maxprioIndex]->bur;
                currTime = processes[maxprioIndex]->comp;
                isExecuted[processes[maxprioIndex]->proc] = true;
            }
            else{
                
                if(minArrivalTime!=INT_MAX){
                    currTime = minArrivalTime;
                }
                else{
                    currTime++;
                }
                i--;
            }
        }
        display(processes,n);
    }

    void SJF(vector<Process*>processes,int n){
        //Sort according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(processes[j]->arr > processes[j+1]->arr){
                    swap(processes[j],processes[j+1]);
                }
            }
        }

        int remTime[n];
        for(int i = 0;i<n;i++){
            remTime[i] = processes[i]->bur;
        }
        int currTime = 0;
        bool isExecuted[n+1] = {false};
        for(int i = 0;i<n;i++){
            int shortJobTime = INT_MAX;
            int shortJobIndex = -1;

            int minArrivalTime = INT_MAX;
            int minArrTimeIndex = -1;

            for(int j = 0;j<n;j++){
                if(!isExecuted[processes[j]->proc]){
                    if(processes[j]->arr <= currTime){
                        if(shortJobTime > remTime[j]){
                            shortJobIndex = j;
                            shortJobTime = remTime[j];
                        }

                        if(minArrivalTime > processes[j]->arr){
                            minArrivalTime = processes[j]->arr;
                            minArrTimeIndex = j;
                        }
                    }
                }
            }

            if(minArrivalTime <= currTime){
                if(remTime[shortJobIndex]==1){
                    remTime[shortJobIndex] = 0;
                    isExecuted[processes[shortJobIndex]->proc] = true;
                    processes[shortJobIndex]->comp = currTime+1;
                    processes[shortJobIndex]->tat =processes[shortJobIndex]->comp - processes[shortJobIndex]->arr; 
                    processes[shortJobIndex]->wt = processes[shortJobIndex]->tat - processes[shortJobIndex]->bur;  
                }
                else{
                    remTime[shortJobIndex]--;
                    i--;
                }
                 currTime++;
            }
            else{
                if(minArrivalTime==INT_MAX){
                    currTime++;
                }
                else{
                    currTime = minArrivalTime;
                }
                i--;
            }
        }
        display(processes,n);
    }

    void RoundRobin(vector<Process*>processes,int n){
        //Sort according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(processes[j]->arr > processes[j+1]->arr){
                    swap(processes[j],processes[j+1]);
                }
            }
        }
        int tempBur[n];
        for(int i = 0;i<n;i++){
            tempBur[i]=processes[i]->bur;
        }
        cout<<"Enter value of Time Quantam "<<endl;
        int tq;
        cin>>tq;
        queue<Process*>readyQueue;
        readyQueue.push(processes[0]);
        int currTime = 0;
        bool isExecuted[n+1] = {false};
        while (!readyQueue.empty())
        {
            Process *currProcess = readyQueue.front();
            int tempTQ = tq;
            int remTimeIndex = -1;
            for(int i = 0;i<n;i++){
                if(processes[i]==currProcess){
                    remTimeIndex = i;
                    break;
                }
            }
            cout<<"processing"<<currProcess->proc<<endl;
            cout<<readyQueue.size()<<endl;
            while (tempTQ && tempBur[remTimeIndex])
            {
                cout<<"tempTQ"<<tempTQ<<endl;
                tempTQ--;
                tempBur[remTimeIndex]--;
                currTime++;
                for(int j = 0;j<n;j++){
                    if((processes[j]->arr == currTime) && tempBur[j]>0){
                        readyQueue.push(processes[j]);
                    }
                }
                if(tempBur[remTimeIndex]==0){
                    isExecuted[remTimeIndex]=true;
                    currProcess->comp = currTime;
                    currProcess->tat = currProcess->comp - currProcess->arr;
                    currProcess->wt = currProcess->tat - currProcess->bur ;
                }
            }
            readyQueue.pop();
            if(tempBur[remTimeIndex]){
                readyQueue.push(currProcess);
            }  
        }
        display(processes,n);
        
    }
};
int main(){

    // Process *processes[5];
    vector<Process*>processes;
    int n;
    cout<<"Enter number of proceses"<<endl;
    cin>>n;
    for(int i = 0;i<n;i++){
        int proc,arr,bur,comp,tat,wt,prio;
        cout<<"Enter process id "<<endl;
        cin>>proc;
        cout<<"Enter process arrival time "<<endl;
        cin>>arr;
        cout<<"Enter process burst Time "<<endl;
        cin>>bur;
        cout<<"Enter process priority "<<endl;
        cin>>prio;
        Process *obj = new Process(proc,arr,bur,-1,-1,-1,prio);
        // processes[i] = obj;
        processes.push_back(obj);
    }

    for(int i = 0;i<n;i++){
        cout<<processes[i]->proc<<" "<<processes[i]->arr<<" "<<processes[i]->bur<<" "<<processes[i]->comp<<" "<<processes[i]->tat<<" "<<processes[i]->wt<<" "<<processes[i]->prio<<endl;
    }
    cout<<"--------------------------------------------"<<endl;
    Schedular op;
    op.RoundRobin(processes,n);
}