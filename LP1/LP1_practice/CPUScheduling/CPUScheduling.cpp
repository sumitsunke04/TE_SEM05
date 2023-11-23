#include<iostream>
#include<limits.h>
#include<queue>
using namespace std;


class Scheduling{

    public:
    int *proc,*arr,*bur,*comp,*tat,*wt,*prio;
    int n;
    Scheduling(){
        cout<<"Enter total number of processes"<<endl;
        cin>>n;
        proc = new int[n];
        arr = new int[n];
        bur = new int[n];
        comp = new int[n];
        tat = new int[n];
        wt = new int[n];
        for(int i = 0;i<n;i++){
            cout<<"Enter process ID"<<endl;
            cin>>proc[i];
            cout<<"Enter Arrival Time"<<endl;
            cin>>arr[i];
            cout<<"Enter Burst Time"<<endl;
            cin>>bur[i];
        }
    }
    void FCFS(){
        //Sorting according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swap(proc[j],proc[j+1]);
                    swap(bur[j],bur[j+1]);
                }
            }
        }
        int currTime = 0;
        for(int i = 0;i<n;i++){
            int compTime = max(currTime,arr[i])+bur[i];
            currTime = compTime;
            comp[i] = compTime;
            tat[i] = comp[i]-arr[i];
            wt[i] = tat[i]-bur[i];
        }
        for(int i = 0;i<n;i++){
            cout<<proc[i]<<" "<<arr[i]<<" "<<bur[i]<<" "<<comp[i]<<" "<<tat[i]<<" "<<wt[i]<<endl;
        }
    }
    void Priority(){
        prio = new int[n];

        //Take input of all priorities
        cout<<"Enter priorities"<<endl;
        for(int i = 0;i<n;i++){
            cin>>prio[i];
        }

        //Sorting according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swap(proc[j],proc[j+1]);
                    swap(bur[j],bur[j+1]);
                    swap(prio[j],prio[j+1]);
                }
            }
        }

        //set current time
        int currTime = 0;
        //check whether a process is executed or not
        bool isExecuted[n] = {false};

        //process all process ids one by one
        for(int p = 0;p<n;p++){

            int maxPriority = INT_MAX;
            int maxInd = -1;

            int minArrivalTime = INT_MAX;
            int minArrInd = -1;
            
            //iterate over all processes to get the process with max priority
            for(int i = 0;i<n;i++){
                //if it is not executed then only check for the further processes.
                if(!isExecuted[i]){
                    if(arr[i]<=currTime){
                        if(prio[i]<maxPriority){
                            maxPriority = prio[i];
                            maxInd = i;
                        }
                    }
                    if(arr[i]<minArrivalTime){
                        minArrivalTime = arr[i];
                        minArrInd = i;
                    }
                }
            }
            //if no processes are arrived before current time 
            if(minArrivalTime > currTime ){
                currTime = minArrivalTime;
                p--;
            }
            else{
                comp[maxInd] = currTime+bur[maxInd];
                currTime = comp[maxInd];
                tat[maxInd] = comp[maxInd]-arr[maxInd];
                wt[maxInd] = tat[maxInd]-bur[maxInd];
                isExecuted[maxInd] = true;
            }
        }

        for(int i = 0;i<n;i++){
            cout<<proc[i]<<" "<<prio[i]<<" "<<arr[i]<<" "<<bur[i]<<" "<<comp[i]<<" "<<tat[i]<<" "<<wt[i]<<endl;
        }
        
    }
    void SJF(){
        
        // Taking a temporary array for burst Time.
        int tempBur[n];
        for(int i = 0;i<n;i++){
            tempBur[i] = bur[i];
        }
        //Sorting according to arrival time
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swap(proc[j],proc[j+1]);
                    swap(bur[j],bur[j+1]);
                    swap(tempBur[j],tempBur[j+1]);
                }
            }
        }
        
        int currTime = 0;
        bool isExecuted[n] = {false};
        int p = n;
        //Process untill all processes complete
        while(p){
            int shortestJobTime = INT_MAX;
            int shortestIndex = -1;
            for(int i = 0;i<n;i++){
                if(!isExecuted[i] && arr[i]<=currTime){
                    if(shortestJobTime > tempBur[i] && tempBur[i]>0){
                        shortestJobTime = tempBur[i];
                        shortestIndex = i;
                    }
                }
            }
            if(shortestJobTime!=INT_MAX){
                if(tempBur[shortestIndex]==1){
                    tempBur[shortestIndex] = 0;
                    comp[shortestIndex] = currTime+1;
                    tat[shortestIndex] = comp[shortestIndex]-arr[shortestIndex];
                    wt[shortestIndex] = tat[shortestIndex]-bur[shortestIndex];
                    isExecuted[shortestIndex] = true;
                    p--;
                }
                else{
                    tempBur[shortestIndex]--;
                }
            }
            currTime++;
        }
        for(int i = 0;i<n;i++){
            cout<<proc[i]<<" "<<arr[i]<<" "<<bur[i]<<" "<<comp[i]<<" "<<tat[i]<<" "<<wt[i]<<endl;
        }
    }
    void RoundRobin(){
        cout<<"Enter Time Quantam "<<endl;
        int tq;
        cin>>tq;
        

        //Sorting according to arrival time
        int tempBur[n];
        for(int i = 0;i<n;i++){
            tempBur[i] = bur[i];
        }
        
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n-i-1;j++){
                if(arr[j]>arr[j+1]){
                    swap(arr[j],arr[j+1]);
                    swap(proc[j],proc[j+1]);
                    swap(bur[j],bur[j+1]);
                    swap(tempBur[j],tempBur[j+1]);
                }
            }
        }
        
        queue<int>readyQueue,ansQueue;

        readyQueue.push(0);
        ansQueue.push(0);
        int currTime = arr[0];
        int totalProcessed = 0;
        while (!readyQueue.empty())
        {
            int ind = readyQueue.front();
            int tmqt = tq;
            while (tmqt && tempBur[ind])
            {
                tmqt--;
                tempBur[ind]--;
                currTime++;
                for(int i = 0;i<n;i++){
                    if(arr[i]==currTime && tempBur[i]>0){
                        readyQueue.push(i);
                        ansQueue.push(i);
                    }
                }
                if(tempBur[ind]==0){
                    comp[ind] = currTime;
                    tat[ind] = comp[ind]-arr[ind];
                    wt[ind] = tat[ind]-bur[ind];
                    totalProcessed++;
                }
            }
            if(tempBur[ind]){
                readyQueue.push(ind);
            }
            readyQueue.pop();
            if(readyQueue.empty() && totalProcessed<n){
                for(int i = 0;i<n;i++){
                    if(tempBur[i] > 0){
                        readyQueue.push(i);
                        currTime = arr[i];
                        break;
                    }
                }
            }
        }

        for(int i = 0;i<n;i++){
            cout<<proc[i]<<" "<<arr[i]<<" "<<bur[i]<<" "<<comp[i]<<" "<<tat[i]<<" "<<wt[i]<<endl;
        }
        
    }
};
int main(){
    Scheduling obj;
    // obj.FCFS();
    obj.Priority();
    // obj.SJF();
    // obj.RoundRobin();
}