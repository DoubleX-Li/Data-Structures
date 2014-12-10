//Author: Double X Li
//Date: 2014-12-8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

FILE *fp;
char save[27][15];
char codestr[500];

int IsLeaf(Tree T)
{
	if(T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return 0;
}
 
void InitNode(Tree *t, int x, char y)
{
	*t = (TNode *)malloc(sizeof(TNode));
	(*t)-> weight = x;
	(*t)->ch = y;
	(*t)->lchild = NULL;
	(*t)->rchild = NULL;
}

void Make(Tree one, Tree two, Tree *temp1)
{
	(*temp1) = (TNode *)malloc(sizeof(TNode));
	(*temp1)->weight = one->weight + two->weight;
	(*temp1)->ch = '#';
	(*temp1)->lchild = one;
	(*temp1)->rchild = two;
}

void ReadTree(Tree *T)
{
	int flag;
	*T = (TNode *)malloc(sizeof(TNode));
	fscanf(fp,"%c %d %d\n",&((*T)->ch), &((*T)->weight), &flag);
	
	if(!flag)
	{
		ReadTree(&((*T)->lchild));
		ReadTree(&((*T)->rchild));
	}
}

void SaveTree(Tree T)
{
	fprintf(fp,"%c %d %d\n",T->ch, T->weight, IsLeaf(T));
	if(!IsLeaf(T))
	{
		SaveTree(T->lchild);
		SaveTree(T->rchild);
	}	
}

Tree Init()
{
	int i,j,temp;
	char c;
	int n = 27;
	int flag = 1;
	int weight[27];//��������Ȩ�� 
	char ch[27];//���������ַ� 
	Stack S, K;
	Tree x;
	Tree one, two;
	Tree temp1, temp2;
	
	InitStack(&S);
	InitStack(&K);
	
	if((fp = fopen("character.txt","r")) != NULL)//������� 
	{
		for(i = 0; i < n; i++)
		{
			fscanf(fp,"%c %d\n",&ch[i],&weight[i]);
		}
		fclose(fp);
	}
	else//�������벢�洢 
	{
		for(i = 0; i < n; i++)
		{
			printf("�������%d����ĸ:\n",i + 1);
			if(( ch[i] = getchar() ) == ' ')
				ch[i] = '*';
			getchar();
			printf("������Ȩֵ:\n");
			scanf("%d",&weight[i]);
			getchar();
		}
		fp = fopen("character.txt","w");
		for(i = 0; i < n; i++)
		{
			fprintf(fp,"%c %d\n",ch[i],weight[i]); 
		}
		fclose(fp);
	}
	
	//���ַ���Ȩֵ���� 
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
	
	//��ÿ���ַ�����Ȩֵ�����һ����������ջ 
	for(i = 0; i < 27; i++)
	{
		InitNode(&x,weight[i],ch[i]);
		Push(&S,x);
	}
	
	//���ն��幹��������� 
	while(flag)
	{
		Pop(&S, &one);
		Pop(&S,&two);
		Make(one, two, &temp1);
		if(IsEmpty(S))
			break;
		temp2 = (TNode *)malloc(sizeof(TNode));
		Pop(&S,&temp2);
		while(temp1->weight > temp2->weight && !IsEmpty(S))
		{
			Push(&K,temp2);
			Pop(&S,&temp2);
		}
		if(temp1->weight > temp2->weight)
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
		if(temp1->weight == 1000)
			flag = 0;
	}
	fp = fopen("hfmTree.txt","w");
	SaveTree(temp1);
	fclose(fp);
	printf("��ʼ����ϣ�\n");
	return temp1;
}

Tree HuffmanCoding(Tree T)
{
	if(NULL != T)
	{
		if(IsLeaf(T))
		{
			printf("%c:%4d   %s\n",T->ch,T->weight,T->code);
			if(isalpha(T->ch))
			{
				strcpy(save[(int)(T->ch - 64)],T->code);
			}
			else if('*' == T->ch)
			{
				strcpy(save[0],T->code);
			}
			
		}
		if(T->lchild)
        {
            strcpy(T->lchild->code,T->code);
            strcat(T->lchild->code,"0");
    	}
        if(T->rchild)
        {
            strcpy(T->rchild->code,T->code);
            strcat(T->rchild->code,"1");
        }
        HuffmanCoding(T->lchild);
        HuffmanCoding(T->rchild);
	}
	return T;
}

Tree Encoding(Tree T)
{
	int i = 0;
	char str[30];
	
	if(T == NULL)
	{
		fp = fopen("hfmTree.txt","r");
		ReadTree(&T);
		fclose(fp);
	}
	printf("���й���������\n");
	T = HuffmanCoding(T);

	printf("\n");
	if((fp = fopen("ToBeTran.txt","r")) != NULL)
	{
		fgets(str,30,fp);
		fclose(fp);
	}
	else
	{
		printf("������Ҫ������ļ���\n");
		gets(str);
		fp = fopen("ToBeTran.txt","w");
		fprintf(fp,"%s",str);
		fclose(fp);
	}
	
	while(str[i] != '\0')
	{
		if(isalpha(str[i]))
		{
			//printf("%c %s\n",str[i], save[(int)(str[i] - 64)]);
			if(i == 0)
				strcpy(codestr,save[(int)(str[i] - 64)]);
			else
				strcat(codestr,save[(int)(str[i] - 64)]);
		}
		else if(' ' == str[i])
		{
			//printf("  %s\n",save[0]);
			if(i == 0)
				strcpy(codestr,save[0]);
			else
				strcat(codestr,save[0]);
		}
		i++;
	}
	if((fp = fopen("CodeFile.txt","w")) == NULL)
	{
		printf("���벻��д���ļ���");
	} 
	else
	{
		fprintf(fp,"%s",codestr);
		fclose(fp);
	}
	printf("\n������ϣ�\n");
	return T;
}

void Decoding(Tree T)
{
	char ch;
	Tree temp = T;
	FILE *fq;

	fq = fopen("TextFile.txt","w");
	
	if((fp = fopen("CodeFile.txt","r")) == NULL)
	{
		printf("�޷����룡\n");
		fclose(fp);
		return;
	}
	else
	{
		while(1)
		{
			while(!IsLeaf(temp))
			{
				if((ch = fgetc(fp)) == EOF)
				{
					printf("\n");
					fclose(fp);
					fclose(fq);
					printf("�������ѱ���\n");
					return;
				}
				if(ch == '0')
					temp = temp->lchild;
				if(ch == '1')
					temp = temp->rchild;
			}
			if(temp->ch == '*')
				temp->ch = ' ';
			printf("%c",temp->ch);
			fprintf(fq,"%c",temp->ch);
			temp = T;
		}
	}
}

void PrintCode()
{
	int i;
	
	fp = fopen("CodePrint.txt","w");
	
	for(i = 0; codestr[i] != '\0'; i++)
	{
		if( i != 0 && i % 50 == 0)
		{
			printf("\n");
			fprintf(fp,"%c",'\n');
		}
		printf("%c",codestr[i]);
		fprintf(fp,"%c",codestr[i]);
	}
	fclose(fp);
	printf("\n\n��ӡ������ϣ�\n");
}

void PrintTree(Tree T, int n)
{
	int i;
	if(T == NULL)
		return;
	PrintTree(T->rchild,n+1);
	for(i = 0; i < n; i++)
	{
		printf("    ");
		fprintf(fp,"%s","    ");
	}	
	if(T->ch == '#')
	{
		printf("%4d\n",T->weight);
		fprintf(fp,"%4d\n",T->weight);
	}	
	else if(T->ch == ' ')
	{
		printf("%4c\n",'*');
		fprintf(fp,"%4c\n",'*');
	}
	else
	{
		printf("%4c\n",T->ch);
		fprintf(fp,"%4c\n",T->ch);
	}
	PrintTree(T->lchild,n+1);
}



int main(void)
{
	int x;
	Tree T = NULL;
	
	system("color F0");
	Begin:
	printf("��ӭʹ�ù������������\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("0.��ʼ��\n");
	printf("1.����\n");
	printf("2.����\n");
	printf("3.��ӡ����\n");
	printf("4.��ӡ��������\n");
	printf("5.�˳��������������\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("���������ѡ����:");
	scanf("%d",&x);
	getchar();
	switch(x)
	{
		case 0: T = Init();
				system("pause");
				system("cls");
				goto Begin;//�����ַ���Ȩֵ�������������������� 
		case 1: T = Encoding(T); 
				system("pause");
				system("cls");
				goto Begin;//���й���������
		case 2: Decoding(T);
				system("pause");
				system("cls");
				goto Begin;//���й��������� 
		case 3: PrintCode();
				system("pause");
				system("cls");
				goto Begin;
		case 4: fp = fopen("TreePrint.txt","w");
				PrintTree(T,1);
				fclose(fp);
				printf("\n���������ѱ��棡\n");
				system("pause");
				system("cls");
				goto Begin;
		case 5: printf("��лʹ�ù�����������ϵͳ��\n");
				 return 0;
		default: printf("There must be something wrong, please check!\n");
				 system("pause");
				 system("cls");
				 goto Begin;
	}
}
