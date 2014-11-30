//Author: Double X Li
//Date: 2014-11-30 

#include <stdio.h>
#include <stdlib.h>
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

void Init(Tree *t, int x)
{
	*t = (TNode *)malloc(sizeof(TNode));
	(*t)->key = x;
	(*t)->lchild = NULL;
	(*t)->rchild = NULL;
}

void Make(Tree one, Tree two, Tree *temp1)
{
	(*temp1) = (TNode *)malloc(sizeof(TNode));
	(*temp1)->key = one->key + two->key;
	(*temp1)->lchild = one;
	(*temp1)->rchild = two;
}

void Pre(Tree T)
{
	if(NULL != T)
	{
		printf("%d ",T->key);
		Pre(T->lchild);
		Pre(T->rchild);
	}
}

void Print(Tree T, int n)
{
	int i;
	if(T == NULL)
		return;
	Print(T->rchild,n+1);
	for(i = 0; i < n; i++)
		printf("    ");
	printf("%d\n",T->key);
	Print(T->lchild,n+1);
}

int main()
{
	int i;
	int flag = 1;
	int depth;
	int str[20] = {19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0};
	Stack S;
	Stack K;
	Tree x;
	Tree one;
	Tree two;
	Tree temp1;
	Tree temp2;
	
	InitStack(&S);
	InitStack(&K);
	
	for(i = 0; i < 20; i++)
	{
		Init(&x,str[i]);
		Push(&S,x);
	}
	
	while(flag)
	{
		Pop(&S, &one);
		Pop(&S,&two);
		
		Make(one, two, &temp1);
		
		if(IsEmpty(S))
			break;
		temp2 = (TNode *)malloc(sizeof(TNode));
		Pop(&S,&temp2);
		while(temp1->key > temp2->key && !IsEmpty(S))
		{
			Push(&K,temp2);
			Pop(&S,&temp2);
		}
		if(temp1->key > temp2->key)
		{
			Push(&S,temp1);
			Push(&S,temp2);
		}
		else
		{
			Push(&S,temp2);
			Push(&S,temp1);
		}
		
		while(!IsEmpty(K))
		{
			Pop(&K,&temp2);
			Push(&S,temp2);
		}
		if(temp1->key == 190)
			flag = 0;
	}
	printf("\n\n");
	Print(temp1,1);
	return 0;
}
