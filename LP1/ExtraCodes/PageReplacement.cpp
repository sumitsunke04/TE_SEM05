#include<iostream>
#include<queue>
#include<map>
using namespace std;

void FIFO(int arr[],int n,int frames){
    queue<int>q;
    map<int,int>mp;
    int fault = 0; 
    vector<queue<int>>states;
    
    for(int i = 0;i<n;i++){
        if(mp.find(arr[i]) != mp.end()){

        }
        else if(q.size() == frames){
            int temp = q.front();
            q.pop();
            mp.erase(temp);
            q.push(arr[i]);
            mp[arr[i]]++;
            fault++;
        }
        else{
            q.push(arr[i]);
            mp[arr[i]]++;
            fault++;
        }
        states.push_back(q); 
    }

    for(int i = 0;i<states.size();i++){
        cout<<"state "<<i<<" ::  ";
        queue<int>tp = states[i];
        while (!tp.empty())
        {
            cout<<tp.front()<<" ";
            tp.pop();
        }
        cout<<endl;
    }
    cout<<"Total Page Faults : "<<fault<<endl;
}


void MostRecentlyUsed(int arr[],int n,int frames){
    queue<int> q;
    vector<queue<int>>states;
    map<int,int>mp;
    int fault = 0;
    int mostRecent = -1;
    for(int i = 0;i<n;i++){
        if(mp.find(arr[i])!=mp.end()){
            mostRecent = arr[i];
        }
        else if(q.size() == frames){
            queue<int>temp;
            while (!q.empty())
            {
                int top = q.front();
                if(top==mostRecent){
                    q.pop();
                    mp.erase(top);
                    break;
                }
                temp.push(top);
                q.pop();
            }
            temp.push(arr[i]);
            while (!q.empty())
            {
                int top = q.front();
                temp.push(top);
                q.pop();
            }
            while (!temp.empty())
            {
                int top = temp.front();
                q.push(top);
                temp.pop();
            } 
            mostRecent = arr[i];  
            fault++;
        }
        else{
            q.push(arr[i]);
            mostRecent = arr[i];
            mp[arr[i]]++;
            fault++;
        }
        states.push_back(q);
    }
    for(int i = 0;i<states.size();i++){
        cout<<"state "<<i<<" ::  ";
        queue<int>tp = states[i];
        while (!tp.empty())
        {
            cout<<tp.front()<<" ";
            tp.pop();
        }
        cout<<endl;
    }
    cout<<"Total Page Faults : "<<fault<<endl;
}


void optimalReplacementAlgorithm(int arr[],int n,int frames){
    
    vector<int> v(frames,-1);
    vector<vector<int>>states;
    map<int,int>mp;
    int fault = 0;

    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if(mp.find(arr[i])!=mp.end()){

        }
        else if(index == frames){
            int maxind = -1;
            int maxval = -1;
            for(int k = 0;k<v.size();k++){
                bool found = false;
                for(int j = i+1;j<n;j++){
                    if(arr[j] == v[k]){
                        found = true;
                        if(j > maxind){
                            maxind = j;
                            maxval = arr[j];
                        }
                        break;
                    }
                }
                if(!found && maxind!=(n+1)){
                    maxind = n+1;
                    maxval = v[k];
                }
            }
            for(int k = 0;k<v.size();k++){
                if(v[k] == maxval){
                    v[k] = arr[i];
                    mp[arr[i]++];
                    fault++;
                }
            }
        }
        else{
            v[index] = arr[i];
            index++;
            mp[arr[i]]++;
            fault++;
        }
        states.push_back(v);
    }

    for(int i = 0;i<states.size();i++){
        cout<<"State "<<i<<" : "<<" ";
        for(int j = 0;j<states[i].size();j++){
            cout<<states[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<"Total Page Faults : "<<fault<<endl;
    
}
int main(){
    int arr[14] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3};
    int brr[7] = {1,3,0,3,5,6,3};
    int crr[14] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3};

    cout<<"Calling FIFO Algorithm"<<endl;
    FIFO(brr,7,3);
    cout<<"Calling MostRecentlyUsed Algorithm"<<endl;
    MostRecentlyUsed(arr,14,4);
    cout<<"Calling optimalReplacementAlgorithm Algorithm"<<endl;
    optimalReplacementAlgorithm(arr,14,4);


}