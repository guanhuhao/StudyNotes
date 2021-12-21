#include<bits/stdc++.h>
using namespace std;
const int n = 1000000;
const int R = 10;
int cnt[n+10];  
struct Hot{
    int l,r;
    int sum;
    void print(){
        printf("l:%8d  r:%8d  sum:%8d\n",l,r,sum);
    }
    Hot(){

    }
    Hot(int ll,int rr,int ssum){
        l=ll;
        r=rr;
        sum=ssum;
    }
};
class Baseline{
public:
    int cnt[n+10];  
    int flag[n+10];
    vector<Hot> get_topk(int k){
        vector<Hot> topk;
        memset(flag,0,sizeof flag);
        while(k--){
            int l = 0;
            int r = 0;
            int sum = 0;
            Hot tmp(-1,-1,-1);
            for(int i=0;i<n;i++){
                sum+=cnt[i];
                r = i;
                if(flag[i]) {       //检查是否该区间已被包含
                    l = i + 1;
                    sum = 0;
                }
                if(r-l+1==R){       //
                    if(tmp.sum<sum){
                        tmp.sum = sum;
                        tmp.l = l;
                        tmp.r = r;
                    }
                    sum -= cnt[l];
                    l++;
                } 
            }
            if(tmp.l==-1){      //check1
                cerr<<"error: have no topk range!"<<endl;
                break;
            }

            for (int i=tmp.l;i<=tmp.r;i++)  flag[i]++; //打标记
            topk.push_back(tmp);
            
        }

        for(int i=0;i<n;i++){   //check2
            if(flag[i]>=2)
                cerr<<"error: topk have overlap!"<<endl;
        }
        return topk;
    }
}baseline;

class segmentTree{
private:
    struct Node{
        int k;
        int l,r;
        int ans_L,ans_R;
        int sum;
        Node(int ll,int rr,int al,int ar,int ssum){
            k = 0;
            l = ll;
            ans_L = al;
            r = rr;
            ans_R = ar;
            sum = ssum;
        }
        Node(int ll,int rr,int ssum){
            k = 0;
            l = ans_L = ll;
            r = ans_R = rr;
            sum = ssum;
        }
        Node(){
            k = l = r = ans_R = ans_L = sum =  -1;
        };
        void print(){
            printf("l:%8d  r:%8d  ansl:%8d  ansr:%8d  sum:%8d\n",l,r,ans_L,ans_R,sum);
        }
    };
    struct cmp{
        bool operator()(Node a,Node b){
            return a.sum < b.sum;
        }
    };
    Node node[n*4/R];
public:
    int cnt[n];

    void build(int k,int l,int r,int len=R){
        node[k].l=l;
        node[k].r=r;
        if(r-l+1<len*2){
            node[k].ans_L=l;
            node[k].ans_R=l+len-1;
            int sum = 0;
            for(int i=node[k].ans_L;i<=node[k].ans_R;i++)   sum += cnt[i];
            node[k].sum=sum;

            for(int i=node[k].ans_R+1;i<=r;i++){
                sum -= cnt[i-len];
                sum += cnt[i];
                if(sum>node[k].sum){
                    node[k].sum = sum;
                    node[k].ans_L = i-len+1;
                    node[k].ans_R = i;
                }
            }
            return;
        }
        int mid = (l+r)/2;
        build(2*k,l,mid,len);
        build(2*k+1,mid+1,r,len);

        int flag=node[2*k].sum>node[2*k+1].sum?2*k:2*k+1;
        node[k].sum=node[flag].sum;
        node[k].ans_L=node[flag].ans_L;
        node[k].ans_R=node[flag].ans_R;

        int sum = 0;
        for(int i = mid-len+1;i<=mid;i++) sum+=cnt[i];
        for(int i = mid+1;i<mid+len;i++){
            sum-=cnt[i-len];
            sum+=cnt[i];
            if(sum>node[k].sum){
                node[k].sum = sum;
                node[k].ans_L = i-len+1;
                node[k].ans_R = i;
            }
        }
        // if(k==1124) cerr<<"k==1124 sum is "<<sum<<endl;
    }

    Hot ask(int k,int l,int r,int len=R){
        if(l<=node[k].l&&r>=node[k].r) return Hot(node[k].ans_L,node[k].ans_R,node[k].sum);
        if(node[k].r<l||node[k].l>r) return Hot(-1,-1,-1);
        int mid = (node[k].l+node[k].r)/2;
        Hot nodeL = ask(2*k,l,r,len);
        Hot nodeR = ask(2*k+1,l,r,len);
        Hot ans(-1,-1,-1);
        if(nodeL.sum>nodeR.sum) ans = nodeL;
        else ans = nodeR;

        int sum = 0;
        for(int i = mid-len+1;i<=mid;i++) sum+=cnt[i];
        for(int i = mid+1;i<mid+len;i++){
            sum-=cnt[i-len];
            sum+=cnt[i];
            if(sum>ans.sum&&i<=r&&i-len+1>=l){
                ans.sum = sum;
                ans.l = i-len+1;
                ans.r = i;
            }
        }
        return ans;
    }
    vector<Hot> gettopk(int k){
        build(1,1,n);
        priority_queue<Node,vector<Node>,cmp> que;
        vector<Hot> topk;
        Hot tmp = ask(1,1,n);
        que.push(Node(1,n,tmp.l,tmp.r,tmp.sum));
        while(topk.size()<k){
            Node p = que.top();
            que.pop();
            topk.push_back(Hot(p.ans_L,p.ans_R,p.sum));

            if(p.ans_L-p.l>=R){
                tmp = ask(1,p.l,p.ans_L-1);
                que.push(Node(p.l,p.ans_L-1,tmp.l,tmp.r,tmp.sum));
            }

            if(p.r-p.ans_R>=R){
                tmp = ask(1,p.ans_R+1,p.r);
                que.push(Node(p.ans_R+1,p.r,tmp.l,tmp.r,tmp.sum));
            }

        }
        return topk;
    }
}seg;

void randData(){
    for(int i=1;i<n;i++) {
        cnt[i]=rand()%10000;
        baseline.cnt[i] = cnt[i];
        seg.cnt[i] = cnt[i];
    }
}

int main(){
    vector<Hot> topk1,topk2;
    int k = 200;
    printf("实验相关参数说明:\n数据范围n:%8d  topk个数k:%8d  区间长度r:%8d\n",n,k,R);
    randData();
    clock_t begin = clock();
    topk1 = baseline.get_topk(k);
    clock_t end = clock();
    printf("baseline 运行时间:%lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    begin = clock();
    topk2 = seg.gettopk(k);
    end = clock();
    printf("segmentTree 运行时间:%lf(ms)\n",1000.0*(end-begin)/CLOCKS_PER_SEC);

    for(int i=0;i<topk2.size();i++){
        if(topk2[i].sum!=topk1[i].sum){
            cerr<<"error: not equle when i = "<<i<<endl;
            topk1[i].print();
            topk2[i].print();
        }
    }
    cerr<<"check same"<<endl;   
    return 0;
}