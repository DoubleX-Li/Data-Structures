#define MAX 50
#define NAMELEN 9

typedef  int  ElemType;

typedef struct
{
	ElemType data[MAX];
	int front, rear;
} SqQueue;

//初始化
int InitQueue_sq(SqQueue *Q)
{
	(*Q).front = 0;
	(*Q).rear = 0;
	return 0;
}
//判空
int QueueEmpty_sq(SqQueue Q)
{
	return Q.front == Q.rear;
}
//判满
int QueueFull_sq(SqQueue Q)
{
	return (Q.rear + 1) % MAX == Q.front;
}
//求长度
int QueueLength_sq(SqQueue Q)
{
	return (Q.rear - Q.front + MAX) % MAX;
}
//访问队首
int GetHead_sq(SqQueue Q, ElemType *e)
{
	if (QueueEmpty_sq(Q))
		return -1;
	*e = Q.data[Q.front];
	return 0;
}
//入列
int EnQueue_sq(SqQueue *Q, ElemType e)
{
	if (QueueFull_sq(*Q))
		return -1;
	(*Q).data[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAX;
	return 0;
}
//出列
int DeQueue_sq(SqQueue *Q, ElemType *e)
{
	if (QueueEmpty_sq(*Q))
		return -1;
	*e = (*Q).data[(*Q).front];
	(*Q).front = ((*Q).front + 1) % MAX;
	return 0;  //出列操作成功
}