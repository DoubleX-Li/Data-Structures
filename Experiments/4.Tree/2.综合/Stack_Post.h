#define MAX 50
typedef struct Post_Elem
{
	Tree ptr;
	int tag;
}Elem;

typedef struct                    //����ṹ�� 
{
	Elem data[MAX];
	int top;
}Stack_Post;

int InitStack_Post(Stack_Post *S)           //��ʼ��ջ 
{
	(*S).top = -1;
	return 0;
}

int IsEmpty_Post(Stack_Post S)              //�п� 
{
	return -1 == S.top;
}

int IsFull_Post(Stack_Post S)               //���� 
{
	return MAX - 1 == S.top;
}

int Push_Post(Stack_Post *S, Elem e)        //��ջ 
{
	if(IsFull_Post(*S))
		return -1;
	(*S).top += 1;
	(*S).data[(*S).top] = e;
	return 0; 
}

int Pop_Post(Stack_Post *S, Elem *e)        //��ջ
{
	if(IsEmpty_Post(*S))
		return -1;
	*e = (*S).data[(*S).top];
	(*S).top -= 1;
	return 0;
}
