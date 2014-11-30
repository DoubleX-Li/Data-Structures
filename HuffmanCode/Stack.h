#define MAX 50

typedef struct TNode
{
	int key;
	struct TNode *lchild, *rchild;
}TNode, *Tree;

typedef struct                    //����ṹ�� 
{
	Tree data[MAX];
	int top;
}Stack;

int InitStack(Stack *S)           //��ʼ��ջ 
{
	(*S).top = -1;
	return 0;
}

int IsEmpty(Stack S)              //�п� 
{
	return -1 == S.top;
}

int IsFull(Stack S)               //���� 
{
	return MAX - 1 == S.top;
}

int Push(Stack *S, Tree e)        //��ջ 
{
	if(IsFull(*S))
		return -1;
	(*S).top += 1;
	(*S).data[(*S).top] = e;
	return 0; 
}

int Pop(Stack *S, Tree *e)        //��ջ
{
	if(IsEmpty(*S))
		return -1;
	*e = (*S).data[(*S).top];
	(*S).top -= 1;
	return 0;
}
