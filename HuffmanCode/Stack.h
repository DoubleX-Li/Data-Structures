#define MAX 50

typedef struct TNode
{
	int key;
	struct TNode *lchild, *rchild;
}TNode, *Tree;

typedef struct                    //定义结构体 
{
	Tree data[MAX];
	int top;
}Stack;

int InitStack(Stack *S)           //初始化栈 
{
	(*S).top = -1;
	return 0;
}

int IsEmpty(Stack S)              //判空 
{
	return -1 == S.top;
}

int IsFull(Stack S)               //判满 
{
	return MAX - 1 == S.top;
}

int Push(Stack *S, Tree e)        //入栈 
{
	if(IsFull(*S))
		return -1;
	(*S).top += 1;
	(*S).data[(*S).top] = e;
	return 0; 
}

int Pop(Stack *S, Tree *e)        //出栈
{
	if(IsEmpty(*S))
		return -1;
	*e = (*S).data[(*S).top];
	(*S).top -= 1;
	return 0;
}
