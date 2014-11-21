//Arthur: Double X Li
//Date: 2014-09-25

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int coefficient;
	int exponent;
}Monomial;

typedef struct LNode
{
	Monomial data;
	struct LNode *next;
}LNode,*ListNode;

//初始化链表
int InitList(ListNode *head)
{
	*head = (LNode *)malloc(sizeof(LNode));
	(*head)->next = NULL;
	return 0;
}

//逐个输入，创建链表
int CreateList(ListNode head)
{
	LNode *p = NULL,*q = head;
	int n,i;
	static int x = 1; 
	printf("How many monoment you want to put in the No.%d list?\n",x);
	scanf("%d",&n);
	for(i = 0; i < n; i++)
	{
		p = (LNode *)malloc(sizeof(LNode));
		printf("\nPlease input the coefficient of the No.%d monoment:", i + 1);
		scanf("%d",&p->data.coefficient);
		printf("Please input the exponent of the NO.%d monoment", i + 1);
		scanf("%d",&p->data.exponent);
		p->next = NULL;
		q->next = p;
		q = p;
	}
	printf("\nSuccessfully created a list!\n");
	x++;
	return 0;
}

//插入，将结点q插到结点p之后
ListNode InsertNode(ListNode p, ListNode q)
{
	LNode *i;
	i = (LNode *)malloc(sizeof(LNode));
	i->data.coefficient = q->data.coefficient;
	i->data.exponent = q->data.exponent;
	i->next = p->next;
	p->next = i;
	return p;
}

//删除，删除p->next
int DelNode(ListNode p)
{
	LNode *q;
	q = p->next;
	p->next = q->next;
	free(q);
	return 0;
}

//比较，比较q与q->next的指数大小并交换
int CompareNode(ListNode q)
{
	int temp1,temp2;
	if (q->next->data.exponent < q->data.exponent)
	{
		temp1 = q->data.exponent;
		temp2 = q->data.coefficient;
		q->data.exponent = q->next->data.exponent;
		q->data.coefficient = q->next->data.coefficient;
		q->next->data.exponent = temp1;
		q->next->data.coefficient = temp2;
	}
	return 0;
}

//两个一元多项式相加
int AddList(ListNode head1, ListNode head2)
{
	LNode *p1 = head1, *p2 = head2;
	while(p1->next != NULL && p2->next != NULL)
	{
		if (p1->next->data.exponent < p2->next->data.exponent)
		{
			p1= p1->next;
		}
		else if (p1->next->data.exponent == p2->next->data.exponent)
		{
			p1->next->data.coefficient += p2->next->data.coefficient;
			DelNode(p2);
			if (p1->next->data.coefficient == 0)
				DelNode(p1);
		}
		else if(p1->next->data.exponent > p2->next->data.exponent)
		{
			p1 = InsertNode(p1,p2->next); 
			DelNode(p2);
		}
	}
	if (p1->next == NULL)
	{
		p1->next = p2->next;
	}
	if (p2->next == NULL)
	{
		//Do nothing.
	}
	printf("\nSuccessfully added!\n");
	return 0;
}

//冒泡排序
int SortList(ListNode head)
{
	LNode *p = head->next, *q = NULL;
	int temp1,temp2;
	int i, j;
	int count = 0;
	while(p != NULL)
	{
		count++;
		p = p->next;
	}
	p = head->next;
	for(i = 0; i < count; i++)
	{
		q = p;
		for(j = 1; j < count - i; j++)
		{
			CompareNode(q);
			q = q->next;
		}
	}
	printf("\n\nList sorted!\n\n");
	return 0;
}

//f(x)输出
int ShowList(ListNode head)
{
	LNode *p = head->next;
	printf("f(x)=");
	while(p != NULL)
	{
        if(p->data.exponent == 0)
        {
            if(p->data.coefficient < 0)
            {
                printf("%d",p->data.coefficient);
            }
            else if(p->data.coefficient >= 1)
            {
                if(p == head->next)
                    printf("%d",p->data.coefficient);
                else
                    printf("+%d",p->data.coefficient);
            }
        }
        else if(p->data.exponent == 1)
        {
            if(p->data.coefficient < -1)
            {
                printf("%dx",p->data.coefficient);
            }
            else if(p->data.coefficient == -1)
            {
                printf("-x");
            }
            else if(p->data.coefficient == 1)
            {
                if(p == head->next)
                    printf("x",p->data.coefficient);
                else
                    printf("+x",p->data.coefficient);
            }
            else if(p->data.coefficient > 1)
            {
                if(p == head->next)
                    printf("%dx",p->data.coefficient);
                else
                    printf("+%dx",p->data.coefficient);
            }
        }
        else
        {
            if(p->data.coefficient < -1)
            {
                printf("%dx^%d",p->data.coefficient,p->data.exponent);
            }
            else if(p->data.coefficient == -1)
            {
                printf("-x^%d",p->data.exponent);
            }
            else if(p->data.coefficient == 1)
            {
                if(p == head->next)
                    printf("x^%d",p->data.exponent);
                else
                    printf("+x^%d",p->data.exponent);
            }
            else if(p->data.coefficient > 1)
            {
                if(p == head->next)
                    printf("%dx^%d",p->data.coefficient,p->data.exponent);
                else
                    printf("+%dx^%d",p->data.coefficient,p->data.exponent);
            }
        }
		p = p->next;
	}
	printf("\n");
	return 0;
}

int main()
{
	ListNode *head1 = NULL,*head2 = NULL;
	int x;
	system("color F0");
	Begin:
    printf("\n欢迎使用一元多项式相加程序~~~~~~~~~~~~~~~~\n");
	printf("------------------------------------------\n");
	printf("0.输入一元多项式\n");
	printf("1.显示一元多项式\n");
	printf("2.一元多项式相加\n");  
	printf("3.退出\n");
	printf("------------------------------------------\n");
	printf("请输入序号：");
	scanf("%d",&x);
	switch(x)
	{
         case 0:InitList(&head1);
	            CreateList(head1);
	            SortList(head1);
	            InitList(&head2);
	            CreateList(head2);
	            SortList(head2);
	            break;
         case 1:printf("\nThe first list:");
                ShowList(head1);
                printf("The second list:");
                ShowList(head2);
                break;
         case 2:printf("\nLoading plus function~~~~~~~~\n");
	            AddList(head1,head2);
	            printf("\nAfter calculating\n");
	            ShowList(head1);
	            break;
         case 3:printf("感谢使用一元多项式相加程序！任意键退出。\n");
                getchar();
                return 0;
         default: ;
    }
	goto Begin;
}
