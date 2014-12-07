#define MAX 50
#define NAMELEN 9

typedef  int  ElemType;

typedef struct
{
	ElemType data[MAX];
	int front, rear;
} SqQueue;

//��ʼ��
int InitQueue_sq(SqQueue *Q)
{
	(*Q).front = 0;
	(*Q).rear = 0;
	return 0;
}
//�п�
int QueueEmpty_sq(SqQueue Q)
{
	return Q.front == Q.rear;
}
//����
int QueueFull_sq(SqQueue Q)
{
	return (Q.rear + 1) % MAX == Q.front;
}
//�󳤶�
int QueueLength_sq(SqQueue Q)
{
	return (Q.rear - Q.front + MAX) % MAX;
}
//���ʶ���
int GetHead_sq(SqQueue Q, ElemType *e)
{
	if (QueueEmpty_sq(Q))
		return -1;
	*e = Q.data[Q.front];
	return 0;
}
//����
int EnQueue_sq(SqQueue *Q, ElemType e)
{
	if (QueueFull_sq(*Q))
		return -1;
	(*Q).data[(*Q).rear] = e;
	(*Q).rear = ((*Q).rear + 1) % MAX;
	return 0;
}
//����
int DeQueue_sq(SqQueue *Q, ElemType *e)
{
	if (QueueEmpty_sq(*Q))
		return -1;
	*e = (*Q).data[(*Q).front];
	(*Q).front = ((*Q).front + 1) % MAX;
	return 0;  //���в����ɹ�
}