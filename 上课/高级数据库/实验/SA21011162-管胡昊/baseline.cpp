#include<bits/stdc++.h>
using namespace std;
#define DEFBUFSIZE 1024
map<int,int> mp;
int op,id;
vector<int> v,nxt;
struct cmp{
    bool operator()(int a,int b){
        return nxt[a]<nxt[b];
    }
};
class CLOCK{
public:
    int ring[DEFBUFSIZE];
    int cur;
    CLOCK(){
        cur = 0;
        for(int i=0;i<DEFBUFSIZE;i++) ring[i]=1;
    };
  
    void adjust(int id){
        return;
    }
    
    int get(){
        while(1){
            if(ring[cur]==0){
                cur = (cur+1)%DEFBUFSIZE;
                return cur;
            }else{
                ring[cur] = 0;
                cur = (cur+1)%DEFBUFSIZE;
            }
        }
    }
};
int main(){
    freopen("data-5w-50w-zipf.txt","r",stdin);
    while(scanf("%d,%d",&op,&id)!=EOF) {
        v.push_back(id);
        nxt.push_back(mp[id]);
        mp[id]=v.size();
    }
    priority_queue<int,vector<int>,cmp> que;
    map<int,int> hit;
    int cnt = 0;
    for(int i=0;i<v.size();i++){
        if(hit[v[i]]==1) {
            cnt++;
            continue;
        }
        if(que.size()<1024){
            que.push(v[i]);
        }else {
            int p = que.top();
            que.pop();
            hit[p]=0;
        }
        hit[v[i]] = 1;
    }
    cout<<"Hit Rate:"<<100.0*cnt/500000<<"%"<<endl;

    
}