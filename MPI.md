# MPI编程
## MPI 基本说明
### MPI_Datatype
MPI数值枚举表，可用类型如下表：
```c++
typedef enum _MPI_Datatype { 
  MPI_DATATYPE_NULL          = 0x0c000000,
  MPI_CHAR                   = 0x4c000101, // char字符型
  MPI_UNSIGNED_CHAR          = 0x4c000102, 
  MPI_SHORT                  = 0x4c000203,
  MPI_UNSIGNED_SHORT         = 0x4c000204,
  MPI_INT                    = 0x4c000405, // 32位int型
  MPI_UNSIGNED               = 0x4c000406,
  MPI_LONG                   = 0x4c000407,
  MPI_UNSIGNED_LONG          = 0x4c000408,
  MPI_LONG_LONG_INT          = 0x4c000809, // 64位int型 
  MPI_LONG_LONG              = MPI_LONG_LONG_INT,
  MPI_FLOAT                  = 0x4c00040a, // 单浮点类型
  MPI_DOUBLE                 = 0x4c00080b, // 双浮点类型
  MPI_LONG_DOUBLE            = 0x4c00080c,
  MPI_BYTE                   = 0x4c00010d,
  MPI_WCHAR                  = 0x4c00020e,
  MPI_PACKED                 = 0x4c00010f,
  MPI_LB                     = 0x4c000010,
  MPI_UB                     = 0x4c000011,
  MPI_C_COMPLEX              = 0x4c000812,
  MPI_C_FLOAT_COMPLEX        = 0x4c000813,
  MPI_C_DOUBLE_COMPLEX       = 0x4c001614,
  MPI_C_LONG_DOUBLE_COMPLEX  = 0x4c001615,
  MPI_2INT                   = 0x4c000816,
  MPI_C_BOOL                 = 0x4c000117,
  MPI_SIGNED_CHAR            = 0x4c000118,
  MPI_UNSIGNED_LONG_LONG     = 0x4c000819,
  MPI_CHARACTER              = 0x4c00011a,
  MPI_INTEGER                = 0x4c00041b,
  MPI_REAL                   = 0x4c00041c,
  MPI_LOGICAL                = 0x4c00041d,
  MPI_COMPLEX                = 0x4c00081e,
  MPI_DOUBLE_PRECISION       = 0x4c00081f,
  MPI_2INTEGER               = 0x4c000820,
  MPI_2REAL                  = 0x4c000821,
  MPI_DOUBLE_COMPLEX         = 0x4c001022,
  MPI_2DOUBLE_PRECISION      = 0x4c001023,
  MPI_2COMPLEX               = 0x4c001024,
  MPI_2DOUBLE_COMPLEX        = 0x4c002025,
  MPI_REAL2                  = MPI_DATATYPE_NULL,
  MPI_REAL4                  = 0x4c000427,
  MPI_COMPLEX8               = 0x4c000828,
  MPI_REAL8                  = 0x4c000829,
  MPI_COMPLEX16              = 0x4c00102a,
  MPI_REAL16                 = MPI_DATATYPE_NULL, MPI_Op
  MPI_INTEGER2               = 0x4c00022f,
  MPI_INTEGER4               = 0x4c000430,
  MPI_INTEGER8               = 0x4c000831,
  MPI_INTEGER16              = MPI_DATATYPE_NULL,
  MPI_INT8_T                 = 0x4c000133,
  MPI_INT16_T                = 0x4c000234,
  MPI_INT32_T                = 0x4c000435,
  MPI_INT64_T                = 0x4c000836,
  MPI_UINT8_T                = 0x4c000137,
  MPI_UINT16_T               = 0x4c000238,
  MPI_UINT32_T               = 0x4c000439,
  MPI_UINT64_T               = 0x4c00083a,
  MPI_AINT                   = 0x4c00083b (_WIN64), 0x4c00043b,
  MPI_OFFSET                 = 0x4c00083c,
  MPI_FLOAT_INT              = 0x8c000000,
  MPI_DOUBLE_INT             = 0x8c000001,
  MPI_LONG_INT               = 0x8c000002,
  MPI_SHORT_INT              = 0x8c000003,
  MPI_LONG_DOUBLE_INT        = 0x8c000004
} MPI_Datatype;
```

###  MPI_Op
MPI指定操作类型，可用类型如下表
```c++
typedef enum _MPI_Op { 
  MPI_OP_NULL  = 0x18000000,
  MPI_MAX      = 0x58000001, 
  MPI_MIN      = 0x58000003,
  MPI_SUM      = 0x58000003,
  MPI_PROD     = 0x58000004,
  MPI_LAND     = 0x58000005,
  MPI_BAND     = 0x58000006,
  MPI_LOR      = 0x58000007,
  MPI_BOR      = 0x58000008,
  MPI_LXOR     = 0x58000009,
  MPI_BXOR     = 0x5800000a,
  MPI_MINLOC   = 0x5800000b,
  MPI_MAXLOC   = 0x5800000c,
  MPI_REPLACE  = 0x5800000d
} MPI_Op;
```
## 常用函数参数说明

```c++
int MPI_Send(
    void* data,             //数据指针,表示数据存哪
    int count,              //表示存多少个数据,配合上面这个指针使用
    MPI_Datatype datatype,  //接受数据类型,如果为int 则为MPI_INT,接受数据为char 则为MPI_CHAR
    int destination,        //目标id
    int tag,                //接受节点的标记需一致才能接受
    MPI_Comm communicator)  //通信交流,暂不明确目前设置为MPI_COMM_WORLD

MPI_Recv(
    void* data,             //数据指针,表示数据存哪
    int count,              //表示存多少个数据,配合上面这个指针使用
    MPI_Datatype datatype,  //接受数据类型,如果为int 则为MPI_INT,接受数据为char 则为MPI_CHAR
    int source,             //表示谁接受
    int tag,                //接受节点的标记需一致才能接受
    MPI_Comm communicator,  //通信交流,暂不明确目前设置为MPI_COMM_WORLD
    MPI_Status* status)     //提供接受msg的信息

int MPI_Allreduce(
    const void *sendbuf,    //数据指针，表示发送数据起始地址
    void *recvbuf,          //数据指针，表示接受数据起始地址
    int count,              //接受/发送数据数目
    MPI_Datatype datatype,  //接受/发送数据类型
    MPI_Op op, 
    MPI_Comm comm)

``` 
