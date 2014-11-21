//Arthur: Double X Li
//Date: 2014-09-28

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

int InitList(ListNode *head)
{
	*head = (LNode *)malloc(sizeof(LNode));
	(*head)->next = NULL;
	return 0;
}

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
		printf("Please imput the exponent of the NO.%d monoment", i + 1);
		scanf("%d",&p->data.exponent);
		p->next = NULL;
		q->next = p;
		q = p;
	}
	printf("\nSuccessfully created a list!\n");
	x++;
	return 0;
}

int InsertNode(ListNode p, ListNode q)
{
	q->next = p->next;
	p->next = q;
	return 0;
}

int DelNode(ListNode p)
{
	LNode *q;
	q = p->next;
	p->next = q->next;
	free(q);
	return 0;
}

/*int CompareNode(ListNode q)
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
}*/

int ExchangeNode(ListNode p)
{
	LNode *q = p->next;
	LNode *temp = q->next;
	if (q->data.exponent > q->next->data.exponent)
	{
		 p->next = temp;
		 q->next = temp->next;
		 temp->next = q;
	}
	return 0;
} 

int AddList(ListNode head1, ListNode head2)
{
	LNode *p1 = head1, *p2 = head2;
	while(p1->next != NULL && p2->next != NULL)
	{
		if (p1->next->data.exponent < p2->next->data.exponent)
		{
			p1= p1->next;
			continue; 
		}
		else if (p1->next->data.exponent == p2->next->data.exponent)
		{
			p1->next->data.coefficient += p2->next->data.coefficient;
			if (p1->next->data.coefficient == 0)
				DelNode(p1);
		}
		else
		{
			InsertNode(p1,p2->next); 
			DelNode(p2);
		}
		p2 = p2->next;
	}
	if (p1->next == NULL)
	{
		p1->next = p2->next;
	}
	if (p2->next == NULL)
	{
		//Do nothing.
	}
	printf("\nSuccessfully Adding!\n");
	return 0;
}

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
	p = head;
	for(i = 0; i < count; i++)
	{
		q = p;
		for(j = 1; j < count - i; j++)
		{
			ExchangeNode(q);
			q = q->next;
		}
	}
	printf("\n\nList sorted!\n\n");
	return 0;
}

int ShowList(ListNode head)
{
	LNode *p = head->next;
	while(p != NULL)
	{
		printf("\n(%d,%d)",p->data.coefficient,p->data.exponent);
		p = p->next;
	}
	return 0;
}

int main()
{
	ListNode *head1 = NULL,*head2 = NULL;
	InitList(&head1);
	CreateList(head1);
	ShowList(head1);
	SortList(head1);
	InitList(&head2);
	CreateList(head2);
	ShowList(head2);
	SortList(head2);
	printf("\nLoading plus function~~~~~~~~\n");
	AddList(head1,head2);
	printf("\nAfter calculating\n");
	ShowList(head1);
	return 0;
}
