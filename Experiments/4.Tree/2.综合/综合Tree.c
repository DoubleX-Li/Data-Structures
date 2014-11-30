//Author: Double X Li
//Date: 2014-11-27 

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Stack_Post.h"

int zero = 0, one = 0, two = 0;

int Creat(Tree *T)
{
	char c;
	c = getchar();
	if(c == '*')
	{
		*T = NULL;
	}
	else
	{
		*T = (TNode *)malloc(sizeof(TNode));
		(*T)->key = c;
		Creat(&((*T)->lchild));
		Creat(&((*T)->rchild));
	}
	return 0;
}

int Pre(Tree T)
{
	if(NULL != T)
	{
		printf("%c ",T->key);
		Pre(T->lchild);
		Pre(T->rchild);
	}
	return 0;
}

int Pre_NonRec(Tree T)
{
	Stack S;
	InitStack(&S);
	Tree p = NULL;
	if(NULL != T)
	{
		Push(&S,T);
		while(!IsEmpty(S)) 
		{
			Pop(&S, &p);
			printf("%c ",p->key);
			if(NULL != p->rchild)
				Push(&S,p->rchild);
			if(NULL != p->lchild)
				Push(&S, p->lchild);
		}
	}
	return 0;
}

int Mid(Tree T)
{
	if(NULL != T)
	{
		Mid(T->lchild);
		printf("%c ",T->key);
		Mid(T->rchild);
	}
	return 0;
}

int Mid_NonRec(Tree T)
{
	Stack S;
	InitStack(&S);
	Tree p = T;
	while(NULL != p || !IsEmpty(S))
	{
		while(NULL != p)
		{
			Push(&S,p);
			p = p->lchild;
		}
		Pop(&S,&p);
		printf("%c ",p->key);
		p = p->rchild;
	}
	return 0;
}

int Post(Tree T)
{
	if(NULL != T)
	{
		Post(T->lchild);
		Post(T->rchild);
		printf("%c ",T->key);
	}
	return 0;
}

int Post_NonRec(Tree T)
{
	Stack_Post S;
	Tree p = T;
	Elem elem;
	InitStack_Post(&S);

	while(NULL != p || !IsEmpty_Post(S))
	{
		while(NULL != p)
		{
			elem.ptr = p;
			elem.tag = 1; 
			Push_Post(&S,elem); 
			p = p -> lchild;
		}
		Pop_Post(&S,&elem);
		if(1 == elem.tag)
		{
			elem.tag = 2;
			Push_Post(&S,elem); 
			p = elem.ptr -> rchild;
		}
		else if(2 == elem.tag)
		{
			p = elem.ptr;
			printf("%c ", p->key);
			p = NULL; 
		}
	}
	return 0;
}

int CountDegree(Tree T)
{
	if(NULL != T)
	{
		CountDegree(T->lchild);
		CountDegree(T->rchild);
		
		if(T->lchild != NULL && T->rchild != NULL)
			two++;
		else if(T->lchild != NULL || T->rchild != NULL)
			one++;
		else
			zero++;
	}
	return 0;
}

int GetHeight(Tree T)
{
	int left, right;
	if(NULL != T)
	{
		left = GetHeight(T->lchild);
		right = GetHeight(T->rchild);
		if(left > right)
			return left + 1;
		else
			return right + 1;
	}
}

int main()
{
	Tree T;
	int height;
	system("color F0");
	
	Creat(&T);
	
	printf("Pre:\n");
	Pre(T);
	printf("\nPre_NonRec:\n");
	Pre_NonRec(T);
	
	printf("\n\nMid:\n");
	Mid(T);
	printf("\nMid_NonRec:\n");
	Mid_NonRec(T);
	
	printf("\n\nPost:\n");
	Post(T);
	printf("\nPost_NonRec:\n");
	Post_NonRec(T);
	
	printf("\n\n各类节点:\n");
	CountDegree(T);
	printf("zero = %d  one = %d  two = %d\n",zero, one, two);
	
	height = GetHeight(T);
	printf("\n高度:\nHeight = %d\n", height);
	
	return 0;
}
