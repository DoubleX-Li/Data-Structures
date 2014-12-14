#define MAX 50

typedef struct TNode
{
	int weight;
	char ch;
	char code[20];//每个结点自带一个字符数组存储当前结点的哈夫曼编码 
	struct TNode *lchild, *rchild;
}TNode, *Tree;

typedef struct
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
