#define MAX 50
typedef struct Post_Elem
{
	Tree ptr;
	int tag;
}Elem;

typedef struct                    //定义结构体 
{
	Elem data[MAX];
	int top;
}Stack_Post;

int InitStack_Post(Stack_Post *S)           //初始化栈 
{
	(*S).top = -1;
	return 0;
}

int IsEmpty_Post(Stack_Post S)              //判空 
{
	return -1 == S.top;
}

int IsFull_Post(Stack_Post S)               //判满 
{
	return MAX - 1 == S.top;
}

int Push_Post(Stack_Post *S, Elem e)        //入栈 
{
	if(IsFull_Post(*S))
		return -1;
	(*S).top += 1;
	(*S).data[(*S).top] = e;
	return 0; 
}

int Pop_Post(Stack_Post *S, Elem *e)        //出栈
{
	if(IsEmpty_Post(*S))
		return -1;
	*e = (*S).data[(*S).top];
	(*S).top -= 1;
	return 0;
}
