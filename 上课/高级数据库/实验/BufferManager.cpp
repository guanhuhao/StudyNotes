#include <bits/stdc++.h>
#include <malloc.h>
using namespace std;
#define FRAMESIZE 4096
#define MAXPAGES 50000
#define DEFBUFSIZE 1024
#define GHH(...) printf(__VA_ARGS__)
// #define GHH(...) 
int hit=0;
int miss=0;

struct bFrame 
{
    char field [FRAMESIZE];
};
bFrame buf[DEFBUFSIZE];
struct Newpage
{
    int frame_id;
    int page_id;
};
struct BCB
{
    BCB();          //构造函数
    int page_id;    //物理页id
    int frame_id;   //内存页id
    int latch;      //是否加锁
    int count;      //是否占用
    int dirty;      //是否写回
    BCB * next;     //链表形式
    void print(){
        printf("page_id:%6d   frame_id:%6d   bucket_id:%6d\n",this->page_id,this->frame_id,this->page_id%DEFBUFSIZE);
    }
};
class LRU_List{
public:
    int nxt[DEFBUFSIZE+2],pre[DEFBUFSIZE+2];
    int head,cnt,tail;
    LRU_List(){
        cnt=0;
        head=0;
        tail=DEFBUFSIZE+1;
        for(int i=1;i<=DEFBUFSIZE;i++){
            nxt[i]=i+1;
            pre[i]=i-1;
        }
        nxt[head]=1;
        pre[tail]=DEFBUFSIZE;
    };
  
    void adjust(int id){
        id++;
        int id_pre = pre[id];
        int id_nxt = nxt[id];
        pre[id_nxt]=id_pre;
        nxt[id_pre]=id_nxt;
        int back = pre[tail];
        nxt[back] = id;
        pre[id] = back;

        pre[tail] = id;
        nxt[id] = tail;
    }

    // int replace(){
    //     int ret = nxt[head];
    //     this->adjust(ret);
    //     return ret-1;
    // }

    void delet(int id){
        int id_pre = pre[id];
        int id_nxt = nxt[id];
        pre[id_nxt]=id_pre;
        nxt[id_pre]=id_nxt;

        int front = nxt[head];
        pre[front] = id;
        nxt[id] = front;

        pre[id] = head;
        nxt[head] = id;
    }

    void print(){
        GHH("LRU:");
        for(int i=head;i!=tail;i=nxt[i]){
            GHH("%d->",i);
        }
        GHH("%d\n",tail);
    }
};
class DSMgr
{
public:
    DSMgr();    //构造函数
    int OpenFile(string filename);  //打开指定数据文件,返回错误码
    int CloseFile();                //在关闭数据库时调用
    bFrame ReadPage(int page_id);   //从磁盘中读取某页到内存中,被FixPage调用,使用fseek,以及fread获取指定内容
    int WritePage(int page_id, bFrame frm);    //将内存中某页写回到磁盘,在任意写回时刻被调用,返回值表示写了多少字节,使用fseek以及fwrite进行定向书写,此处原先为frame_id,但感觉不太对
    int Seek(int offset, int pos);  //将文件指针移动到指定位置
    FILE * GetFile();               //返回当前文件指针
    void IncNumPages();             //计数当前使用Page页+1
    int GetNumPages();              //获得当前内存中页数目
    void SetUse(int index, int use_bit);    //使用位图来表示当前页是否被占用,
    int GetUse(int index);                  //获取位图
    void RandData();
private:
    FILE *currFile;                         //文件指针用于表示当前文件
    int numPages;                           //当前使用页数目
    int pages[MAXPAGES];                    //目录式堆文件
}DS;

class BMgr
{
public:
    BMgr();     //构造函数
    // Interface functions
    int FixPage(int page_id, int prot=0); //查找给定page_id是否存在内存中,如果不在则选择某页替换,并返回对应frame_id
    Newpage FixNewPage();               //申请一个空页,因此需要分别提供空闲的frame以及page,因此将<frame_id,page_id>作为返回值
    int UnfixPage(int page_id);         //解除对应page_id的一次占用,当对应占用为0时可以将其进行替换或者其他操作
    int NumFreeFrames();                //返回当前内存中还空闲的页个数
    // Internal Functions
    int SelectVictim();                 //返回一个可以替换的页
    int Hash(int page_id);              //实现将page_id到frame_id的映射
    void RemoveBCB(int page_id);        //将page_id对应的BCB删除
    void RemoveLRUEle(int frame_id);        //在LRU列表中移除对应frid
    void AddBCB(int page_id,int frame_id);
    void SetDirty(int frame_id);            //将对应frame_id脏标记置1,1表示需写回,0表示不用写回
    void UnsetDirty(int frame_id);          //将对应frame_id脏标记置0
    void WriteDirtys();                     //当系统结束运行时,对于脏标记为1的frame需要调用,保证数据一致性
    void PrintFrame(int frame_id);          //打印对应帧消息,用于调试(?)
    void Read(int page_id);
    void Write(int page_id);
    void print();
private:
    // Hash Table
    int ftop[DEFBUFSIZE];                   //frame到page的hash映射
    BCB* ptof[DEFBUFSIZE];                  //page到frame的映射
    LRU_List LRU;

    BCB* PagefindBCB(int page_id);
    BCB* PagefindBCB_Pre(int page_id);

}BM;

int main(){
    freopen("data-5w-50w-zipf.txt","r",stdin);
    // freopen("in.txt","r",stdin);

    DS.OpenFile("data.dbf");
    // DS.RandData();
    int op,id;
    while(scanf("%d,%d",&op,&id)!=EOF){
        BM.Read(id);
        // if(op==0){
        //     BM.Read(id);
        // }else {
        //     BM.Write(id);
        // }
    }
    // BM.print();
    cout<<"hit rate:"<<1.0*hit/(hit+miss)<<endl;
    return 0;
}
void DSMgr::RandData(){
    this->currFile=fopen("data.dbf","w+");
    for(int i=0;i<MAXPAGES;i++){
        bFrame tmp;
        memset(tmp.field,0,sizeof(tmp.field));
        sprintf(tmp.field,"%d\n",i);
        this->WritePage(i,tmp);
        // printf("%s",tmp.field);
    }
}
BCB* BMgr::PagefindBCB(int page_id){
    int hash = this->Hash(page_id);
    BCB * p = this->ptof[hash];
    while(p->next != NULL){
        p = p->next;
        if(p->page_id==page_id) return p;
    }
    return NULL;
}
BCB* BMgr::PagefindBCB_Pre(int page_id){
    int hash = this->Hash(page_id);
    BCB * p = this->ptof[hash];
    while(p->next != NULL){
        if(p->next->page_id == page_id) return p;
        p = p->next;
    }
    return NULL;
}

BMgr::BMgr(){
    for(int i=0;i<DEFBUFSIZE;i++){
        this->ptof[i]=(BCB*)malloc(sizeof(BCB));
        this->ptof[i]->next=NULL;         
    }
};
void BMgr::print(){
    for(int i=0;i<DEFBUFSIZE;i++){
        BCB* p= ptof[i]->next;
        while(p!=NULL){
            p->print();
            p=p->next;
        }
    }
}
int BMgr::FixPage(int page_id, int prot){
    BCB* p = this->PagefindBCB(page_id);
    if(p!=NULL) {
        hit++;
        return p->frame_id;
    }

    int vic = this->SelectVictim();
    this->RemoveBCB(this->ftop[vic]);
    this->ftop[vic] = page_id;
    this->AddBCB(page_id,vic);
    this->LRU.adjust(vic);
    miss++;
    return vic-DEFBUFSIZE;

}  
void BMgr::RemoveBCB(int page_id){
    BCB* pre =  this->PagefindBCB_Pre(page_id);
    if(pre == NULL) return;
    BCB* cur = pre->next;
    if(cur->dirty) DS.WritePage(cur->page_id,buf[cur->frame_id]);
    pre->next = cur->next;
    free(cur);

}  
void BMgr::AddBCB(int page_id,int frame_id){
    // cerr<<"Add page_id:"<<page_id<<" frame_id:"<<frame_id<<endl;
    int hash = this->Hash(page_id);
    BCB *p = this->ptof[hash];   
    while(p->next!=NULL){  p = p->next;   }
    BCB *newBCB = (BCB*)malloc(sizeof(BCB));

    newBCB->page_id=page_id;
    newBCB->frame_id = frame_id;
    newBCB->next=NULL;
    p->next = newBCB;
}    


int BMgr::SelectVictim(){
    return (this->LRU.nxt[0])-1;
}

int BMgr::Hash(int page_id){
    return page_id%DEFBUFSIZE;
}

int BMgr::NumFreeFrames(){
    return DEFBUFSIZE-DS.GetNumPages();
}

DSMgr::DSMgr(){    //构造函数

};

int DSMgr::OpenFile(string filename){
    this->currFile=fopen(filename.c_str(),"a+");
    if(this->currFile==NULL) return 1;
    return 0;
}

int DSMgr::CloseFile(){
    return 0;
}

int DSMgr::Seek(int offset, int pos=0){
    fseek(this->currFile,offset,SEEK_SET);
    return offset;
}

FILE * DSMgr::GetFile(){
    return this->currFile;
}

void DSMgr::IncNumPages(){             //计数当前使用Page页+1
    this->numPages++;
}

int DSMgr::GetNumPages(){              //获得当前内存中页数目
    return this->numPages;
}

bFrame DSMgr::ReadPage(int page_id){
    bFrame data;    
    
    this->Seek(page_id*FRAMESIZE);

    fread(data.field,FRAMESIZE,1,this->currFile);

    return data;
}

int DSMgr::WritePage(int page_id, bFrame frm){
    this->Seek(page_id*FRAMESIZE);
    fwrite(frm.field,sizeof(char),FRAMESIZE,this->currFile);

    return strlen(frm.field);
}

void BMgr::Read(int page_id){
    int frame_id = this->FixPage(page_id);

    GHH("Read page_id:%d return:%d\n",page_id,frame_id);
    if(frame_id<0){
        frame_id = frame_id+DEFBUFSIZE;
        this->ftop[frame_id]=page_id;
        int hash = this->Hash(page_id);
        strcpy(buf[frame_id].field,DS.ReadPage(page_id).field);
    }
    this->LRU.adjust(frame_id);
}

void BMgr::Write(int page_id){
    int frame_id = this->FixPage(page_id);
    if(frame_id<0) {
        cerr<<"write error!"<<endl;
    }
    this->LRU.adjust(frame_id);
}
//! int DSMgr::WritePage(int page_id, bFrame frm); 该函数应该为page_id而不是frame_id
//! int DSMgr::Seek(int offset, int pos=0) pos没用
//! 位图获取长度不够
//! FixPage prot意义不明
//! 数据中存在没读就写