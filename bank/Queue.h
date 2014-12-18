#define MAX 100
//�ṹ�塪���ͻ� 
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

//�ṹ�塪���ͻ����� 
typedef struct
{
    Person data[MAX];
    int front,rear;
    int sum;
}Queue;
 
//��ʼ������ 
void InitQueue(Queue &Q)
{
    Q.front = 0;
    Q.rear = 0;
    Q.sum = 0;
}

//�п� 
int IsEmpty(Queue Q)
{
    return Q.front == Q.rear;
}

//���� 
int IsFull(Queue Q)
{
    return (Q.rear + 1) % MAX == Q.front;
}

//�󳤶� 
int QLength(Queue Q)
{
    return (Q.rear - Q.front + MAX) % MAX;
}

//���� 
int EnQueue(Queue &Q, Person e)
{
    if(IsFull(Q))
        return -1;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX;
}

//���� 
int DeQueue(Queue &Q, Person &e)
{
    if(IsEmpty(Q))
        return -1;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX;
}
