//Author: Double X Li
//Date: 2014-11-27 

#include <stdio.h>
#include <stdlib.h>

typedef struct TNode
{
	char key;
	struct TNode *lchild, *rchild;
}TNode, *Tree;

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

	printf("\n\nMid:\n");
	Mid(T);
	
	printf("\n\nPost:\n");
	Post(T);
	
	printf("\n\n各类节点数:\n");
	CountDegree(T);
	
	printf("zero = %d  one = %d  two = %d\n",zero, one, two);
	height = GetHeight(T);
	printf("\n高度:\nHeight = %d\n", height);
	
	return 0;
}
