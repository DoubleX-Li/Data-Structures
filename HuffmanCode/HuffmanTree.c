//Author: Double X Li
//Date: 2014-11-30 

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

FILE *fp;
void Init(Tree *t, int x, char y)
{
	*t = (TNode *)malloc(sizeof(TNode));
	(*t)->key = x;
	(*t)->value = y;
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

void Print(Tree T, int n)
{
	int i;
	if(T == NULL)
		return;
	Print(T->rchild,n+1);
	for(i = 0; i < n; i++)
		printf("    ");
	printf("%4d\n",T->key);
	Print(T->lchild,n+1);
}

void Pre(Tree T)
{
	if(T != NULL)
	{
		printf("%4d %4c\n",T->key,T->value);
		fwrite(T,1,sizeof(Tree),fp);
		Pre(T->lchild);
		Pre(T->rchild);
	}
}

int main()
{
	int i,j,temp;
	int flag = 1;
	char c;
	int weight[27] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
	char ch[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int n = 27;
	Stack S, K;
	Tree x;
	Tree one, two;
	Tree temp1, temp2;
	
	InitStack(&S);
	InitStack(&K);
	
	for(i = 0;i < n; i++)
	{
		for(j = 1; j < n - i; j++)
		{
			if(weight[j-1] < weight[j])
			{
				temp = weight[j];
				c = ch[j];
				weight[j] = weight[j-1];
				ch[j] = ch[j-1];
				weight[j-1] = temp;
				ch[j-1] = c;
			}
		}
	}
	for(i = 0; i < 27; i++)
	{
		Init(&x,weight[i],ch[i]);
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
	printf("\n\n");
	fp = fopen("data",'w');
	Pre(temp1);
	fclose(fp);
	return 0;
}
