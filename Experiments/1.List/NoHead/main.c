//Arthur: Double X Li
//Date: 2014-09-23 

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode
{
	int age;
	struct LNode *next;
}LNode,*ListNode;

void InitList(ListNode *head)
{
	*head = NULL; 
}

int CreateList(ListNode *head)
{
	int i,n,age;
	LNode *p = NULL, *q = head; // q始终指向尾结点 
	printf("Please input the number of students:");
	scanf("%d",&n);
	for(i = 0; i < n; i++)
	{
		printf("\nPlease input the age of the No.%d student's age:",i + 1);
		scanf("%d",&age);
		p = (LNode *)malloc(sizeof(LNode));
		if(p == NULL)
		{
			printf("Error!\n");
			return -1;
		}
		p->next = NULL;   //尾元结点的下一个为空 
		p->age = age;
		if (NULL == *head)
			*head = p;
		else
			q->next = p;		//尾元结点挂到表尾 
		q = p;		//q始终指向尾元结点 
	}
	printf("\nSuccessfully created a list.\n\n");
	return 0; 
}

int LocateList(ListNode *head)
{
	LNode *p = *head;
	int count = 1,n;
	printf("Which age do you want to locate?\n");
	scanf("%d",&n);
	while(NULL != p)
	{
		if(n == p->age)
			return count;
		count++;
		p = p->next;
	}
	return -1;
}

int FindList(ListNode *head)
{
	LNode *p = *head;
	int count = 1,i;
	printf("\nPlease input the number of the element you want to find:");
	scanf("%d",&i);
	while(p != NULL && count < i)
	{
		count++;
		p = p->next;
	}
	if(p == NULL)
		return -2;
	if(count > i)
		return -1;
	return p->age;
}

int DelList(ListNode *head)
{
	LNode *p = *head, *q = NULL;
	int count = 1,i;
	printf("\nPlease input the number of the element you want to delete:");
	scanf("%d",&i);
	if (i == 1)
	{
		*head = p->next;
		return 0;
	}
	while(p != NULL && count < i)
	{
		count++;
		q = p;
		p= p->next;
	}
	if(p == NULL)
		return -2;
	if(count > i)
		return -1;
	q->next = p->next;
	free(p);
	return 0;
}

int ShowList(ListNode *head)
{
	LNode *p = *head;
	int i = 0; 
	while(p!= NULL)
	{
		printf("\nNo.%d student's age are %d",++i,p->age);
		p = p->next;
	}
	return 0;
}

int main()
{
	ListNode *head = NULL;
	InitList(&head);
	CreateList(&head);
	printf("Locate:No.%d\n",LocateList(&head));
	printf("Find:%d\n",FindList(&head));
	ShowList(&head);
	DelList(&head);
	ShowList(&head);
	return 0;
}
