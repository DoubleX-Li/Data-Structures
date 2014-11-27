//Author: Double X Li
//2014-11-26
 
#include <stdio.h>
#include <stdlib.h>
#define ElemType char

int zero = 0, one = 0, two = 0;
 
typedef struct TNode
{
	ElemType key;
	struct TNode *lchild, *rchild;
}TNode, *Tree;

void Creat(Tree *T)
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
		Creat(&(*T)->lchild);
		Creat(&(*T)->rchild);
	}
}

void Pre(Tree T)
{
	if(NULL != T)
	{
		printf("%c ", T->key);
		Pre(T->lchild);
		Pre(T->rchild);
	}
}

void Mid(Tree T)
{
	if(NULL != T)
	{
		Mid(T->lchild);
		printf("%c ",T->key);
		Mid(T->rchild);
	}
}

void Post(Tree T)
{
	if(NULL != T)
	{
		Post(T->lchild);
		Post(T->rchild);
		printf("%c ", T->key);
	}
}

void CountDegree(Tree T)
{
	if(NULL != T)
	{
		if(T->lchild != NULL && T->rchild != NULL)
			two++;
		else if(T->lchild != NULL || T->rchild)
			one++;
		else
			zero++;
		
		CountDegree(T->lchild);
		CountDegree(T->rchild);
	}
}

int GetHeight(Tree T)
{
	int left, right;
	if(T == NULL)
		return 0;
	left = GetHeight(T->lchild);
	right = GetHeight(T->rchild);
	if(left > right)
		return left + 1;
	else
		return right + 1;
}

int main()
{
	Tree T;
	int height;
	system("color F0");
	Creat(&T);
	printf("Pre:\n");
	Pre(T);
	printf("\n\nMid:\n");
	Mid(T);
	printf("\n\nPost:\n");
	Post(T);
	CountDegree(T);
	printf("\n\nzero = %d  one = %d  two = %d\n",zero, one, two);
	height = GetHeight(T);
	printf("\nHeight = %d\n",height);
	return 0;
}
