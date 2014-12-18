#define MAX 100
//结构体——客户 
typedef struct
{
     int arrive;
     int consult;
     int curr;
     int wait;
     int begin;
     int flag;
     int num;
}Person;

//结构体——客户队列 
typedef struct
{
    Person data[MAX];
    int front,rear;
    int sum;
}Queue;
 
//初始化队列 
void InitQueue(Queue &Q)
{
    Q.front = 0;
    Q.rear = 0;
    Q.sum = 0;
}

//判空 
int IsEmpty(Queue Q)
{
    return Q.front == Q.rear;
}

//判满 
int IsFull(Queue Q)
{
    return (Q.rear + 1) % MAX == Q.front;
}

//求长度 
int QLength(Queue Q)
{
    return (Q.rear - Q.front + MAX) % MAX;
}

//入列 
int EnQueue(Queue &Q, Person e)
{
    if(IsFull(Q))
        return -1;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX;
}

//出列 
int DeQueue(Queue &Q, Person &e)
{
    if(IsEmpty(Q))
        return -1;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX;
}
