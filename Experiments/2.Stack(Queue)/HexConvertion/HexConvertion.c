//Author: Double X Li
//Date: 2014-10-05

#include <stdio.h>
#define MAX 50
typedef struct                    //定义结构体 
{
	char data[MAX];
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

int Push(Stack *S, char e)        //入栈 
{
	if(IsFull(*S))
		return -1;
	(*S).top += 1;
	(*S).data[(*S).top] = e;
	return 0; 
}

int Pop(Stack *S, char *e)        //出栈
{
	if(IsEmpty(*S))
		return -1;
	*e = (*S).data[(*S).top];
	(*S).top -= 1;
	return 0;
} 

int HexConvertion(int N, int B)   //进制转换 
{
	int temp;
	char e;
	Stack S;
	
	InitStack(&S);
	if(N == 0)
	    Push(&S,(char)(N + '0'));
	else
	{
        while(N > 0)
	    {
		    temp = N % B;
		    if(temp < 10)
		        Push(&S,(char)(temp + '0'));
		    else
		        Push(&S,(char)(temp + 55));
		    N = N / B;
	    }
    }
    
	while(!IsEmpty(S))
	{
		e = -1;
		Pop(&S,&e);
		printf("%c",e);
	}
	printf("\n");
	return 0;
}

int main()
{
	int N, B;
	system("color F0");
	Begin:
	printf("请输入要转换的十进制数N及期望进制B(N,B):");
	scanf("%d,%d",&N,&B);
	if(B > 16 || B < 2)
		printf("期望进制超出范围！\n");
	else
		HexConvertion(N, B);
	goto Begin;
}
