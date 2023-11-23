#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<limits.h>
using namespace std;


void Input(){
    int sz;
    int *arr;
    int frames;

    cout<<"Enter total number of pages"<<endl;
    cin>>sz;
    cout<<"Enter frame size"<<endl;
    cin>>frames;
    arr = new int[sz];
    cout<<"Start entering all the page numbers"<<endl;
    for(int i = 0;i<sz;i++){
        cin>>arr[sz];
    }
}

class PageReplacementAlgo{
    public:
    
    
    void displayState(vector<vector<int>>state,int sz,int frames){
        cout<<"Displaying the states"<<endl;
        for(int i = 0;i<sz;i++){
            for(int j = 0;j<frames;j++){
                cout<<state[i][j];
            }
        }
    }

    void FIFO(int arr[],int sz,int frames){
       
        queue<int>q;
        map<int,int>mp;
        vector<queue<int>> states;
        for(int i = 0;i<sz;i++){
            if(mp.find(arr[i])!=mp.end()){

            }
            else if(q.size()==frames){
                int tp = q.front();
                q.pop();
                mp.erase(tp);
                q.push(arr[i]);
            }
            else{
                mp[arr[i]]++;
                q.push(arr[i]);
            }
            states.push_back(q);
        }

        cout<<"All States : "<<endl;
        for(int i = 0;i<states.size();i++){
            queue<int> temp = states[i];
            while (!temp.empty())
            {
                int t = temp.front();
                temp.pop();
                cout<<t<<" ";
            }
            cout<<endl; 
        }
    }

    void MostRecentlyUsed(int arr[],int sz,int frames){
        int mr = -1;
        vector<vector<int>>states;
        map<int,int>mp;
        vector<int>v;
        for(int i = 0;i<sz;i++){
            if(mp.find(arr[i])!=mp.end()){
                mr = arr[i];
            }
            else if(v.size()==frames){
                for(int j = 0;j<v.size();j++){
                    if(v[j]==mr){
                        
                        mp.erase(mr);
                        v.erase(v.begin()+j,v.begin()+j+1);
                        v.push_back(arr[i]);
                        mr = arr[i];
                        mp[arr[i]]++;
                    }
                }
            }
            else{
                v.push_back(arr[i]);
                mr = arr[i];
                mp[arr[i]]++;
            }
            states.push_back(v);
        }

        for(int i = 0;i<states.size();i++){
            for(int j = 0;j<states[i].size();j++){
                cout<<states[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void OptimalPageReplacement(int arr[],int sz,int frames){
        vector<vector<int>>states;
        map<int,int>mp;
        vector<int>v;
        for(int i = 0;i<sz;i++){
            cout<<"Inserting "<<arr[i]<<endl;
            if(mp.find(arr[i])!=mp.end()){

            }
            else if(v.size()==frames){
                // cout<<"Need to delete" <<endl;
                int maxInd = INT_MIN;
                int toDel = v[0];
                for(int j = 0;j<v.size();j++){
                    int num = v[j];
                    bool flag = false;
                    for(int k = i+1;k<sz;k++){
                        if(arr[k]==num){
                            flag = true;
                            if(maxInd < k){
                                maxInd = k;
                                toDel = num;
                            }
                            break;
                        }
                    }
                    if(!flag){
                        toDel = v[j];
                        break;
                    }
                }
                // cout<<"Delete otem"<<toDel<<endl;
                for(int j = 0;j<v.size();j++){
                    if(v[j]==toDel){
                        mp.erase(v[j]);
                        v.erase(v.begin()+j,v.begin()+j+1);
                        
                        v.push_back(arr[i]);
                        mp[arr[i]]++;
                    }
                }
            }
            else{
                v.push_back(arr[i]);
                mp[arr[i]]++;
            }
            states.push_back(v);
            // for(int p = 0;p<v.size();p++){
            //     cout<<v[p]<<" ";
            // }
            cout<<endl;
        }
        for(int i = 0;i<states.size();i++){
            for(int j = 0;j<states[i].size();j++){
                cout<<states[i][j]<<" ";
            }
            cout<<endl;
        }
    }

};

int main(){
    int arr[7] = {1,3,0,3,5,6,3};
    PageReplacementAlgo obj;
    // obj.FIFO(arr,7,3);
    int arr2[14] = {7,0,1,2,0,3,0,4,2,3,0,3,2,3};
    // obj.MostRecentlyUsed(arr2,14,4);
    cout<<"--------"<<endl;
    obj.OptimalPageReplacement(arr2,14,4);
    return 0;
}


