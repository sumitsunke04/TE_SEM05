#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<limits.h>
using namespace std;


class PageReplacement{
    public:
    void FIFO(vector<int>arr,int n,int frames){
        queue<int>q;
        map<int,int>mp;
        vector<queue<int>> states;
        int pageFault = 0;
        for(int i = 0;i<n;i++){
            if(mp.find(arr[i])!=mp.end()){
                
            }
            else if(q.size()==frames){
                int toDel = q.front();
                q.pop();
                mp.erase(toDel);
                q.push(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            else{
                q.push(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            states.push_back(q);
        }
        for(auto i:states){
            queue<int>temp = i;
            while (!temp.empty())
            {
                cout<<temp.front()<<" ";
                temp.pop();
            }
            cout<<endl;
        }
        cout<<"Page Fault : "<<pageFault<<endl;
    }

    void LRU(vector<int>arr,int n,int frames){
        vector<vector<int>>states;
        vector<int>v;
        map<int,int>mp;
        int pageFault =0;
        for(int i = 0;i<n;i++){
            if(mp.find(arr[i])!=mp.end()){

            }
            else if(v.size()==frames){
                int lr = v[0];
                int lri = INT_MAX;
                for(auto itr:v){
                    for(int j = i-1;j>=0;j--){
                        if(arr[j]==itr){
                            if(j<lri){
                                lri=j;
                                lr=itr;
                            }
                            break;
                        }
                    }
                }

                for(int j = 0;j<v.size();j++){
                    if(v[j]==lr){
                        mp.erase(lr);
                        v.erase(v.begin()+j,v.begin()+j+1);
                    }
                    

                }
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            else{
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            states.push_back(v);
        }
        for(auto i:states){
            for(auto j:i){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<"Page Fault : "<<pageFault<<endl;
    }

    void MRU(vector<int>arr,int n,int frames){
        vector<vector<int>>states;
        vector<int>v;
        map<int,int>mp;
        int pageFault =0;

        for(int i = 0;i<n;i++){
            if(mp.find(arr[i])!=mp.end()){

            }
            else if(v.size()==frames){
                int mri = INT_MIN;
                int mr=v[0];
                for(auto itr:v){
                    for(int j = i-1;j>=0;j--){
                        if(arr[j]==itr){
                            if(j>mri){
                                mri=j;
                                mr=itr;
                            }
                            break;
                        }
                    }
                }
                for(int k = 0;k<v.size();k++){
                    if(v[k]==mr){
                        mp.erase(mr);
                        v.erase(v.begin()+k,v.begin()+k+1);
                    }
                }
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
                
            }
            else{
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            states.push_back(v);
        }
        for(auto i:states){
            for(auto j:i){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<"Page Fault : "<<pageFault<<endl;
    }

    void OptimalPageReplacement(vector<int>arr,int n,int frames){
        vector<vector<int>>states;
        vector<int>v;
        map<int,int>mp;
        int pageFault =0;

        for(int i = 0;i<n;i++){
            if(mp.find(arr[i])!=mp.end()){

            }
            else if(v.size()==frames){
                int lu = v[0];
                int lui = INT_MIN;
                for(auto itr:v){
                    bool flag = false;
                    for(int p = i+1;p<n;p++){
                        if(arr[p]==itr){
                            flag = true;
                            if(p>lui){
                                lu=arr[p];
                                lui=p;
                            }
                            break;
                        }
                    }
                    if(!flag){
                        lu = itr;
                        break;
                    }
                }
                for(int p = 0;p<v.size();p++){
                    if(v[p]==lu){
                        v.erase(v.begin()+p,v.begin()+p+1);
                        mp.erase(lu);
                        break;
                    }
                }
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            else{
                v.push_back(arr[i]);
                mp[arr[i]]++;
                pageFault++;
            }
            states.push_back(v);
        }
        for(auto i:states){
            for(auto j:i){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<"Page Fault : "<<pageFault<<endl;
    }
};
int main(){
    vector<int> v ={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    PageReplacement obj;
    obj.OptimalPageReplacement(v,v.size(),4);
}