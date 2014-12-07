#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define  GRAPH  30
#define  UNDIGRA       GRAPH + 0    //��������ͼ
#define  DIGRA          GRAPH + 1    //��������ͼ
#define  DIGRA_REV     GRAPH + 2    //�����ڽӱ�ʱ�ã���ʾ��������ͼ�����ڽӱ�

typedef  char  VertexType;
typedef  int  EdgeType;

//�ڽӾ���Ķ���
typedef struct
{
	VertexType vexs[MAX];
	EdgeType edges[MAX][MAX];
	int vexnum, arcnum;  //��¼ͼ�Ķ������ͱ߻򻡵�����
}AdjMatrix;

typedef  enum{ FALSE, TRUE }  VisitFlag;
VisitFlag visited_DFS_M[MAX];  //����ȫ��������������ʶ�����Ƿ��ѱ����ʹ�
VisitFlag visited_BFS_M[MAX];  //����ȫ��������������ʶ�����Ƿ��ѱ����ʹ�

SqQueue Q;  //����ȫ�ֶ���

/*����ͼ���ڽӾ���*/
AdjMatrix CreateGraph_Matrix(int graphtype)
{
	AdjMatrix G;
	int i, j, k, start, end;

	printf("Please input graph's vexnum and arcnum:");
	scanf("%d,%d", &G.vexnum, &G.arcnum);
	getchar();
	for (i = 1; i <= G.vexnum; i++)
	{
		G.vexs[i] = getchar();
	}
	getchar();
	for (i = 1; i <= G.vexnum; i++)  //��ʼ������
	{
		for (j = 1; j <= G.vexnum; j++)
			G.edges[i][j] = 0;
	}
	for (k = 1; k <= G.arcnum; k++)  //��������ıߵ���Ϣ�����ڽӾ���
	{
		printf("Please input NO.%d edge's start and end:", k);
		scanf("%d,%d", &start, &end);
		G.edges[start][end] = 1;
		if (UNDIGRA == graphtype)
			G.edges[end][start] = 1;
	}

	return(G);
}

/*���ͼ���ڽӾ���*/
void ShowGraph_Matrix(AdjMatrix G)
{
	int i, j;

	printf("   ");
	for (i = 1; i <= G.vexnum; i++)
	{
		printf("%3c", G.vexs[i]);
	}
	printf("\n");
	for (i = 1; i <= G.vexnum; i++)
	{
		printf("%2c ", G.vexs[i]);
		for (j = 1; j <= G.vexnum; j++)
		{
			printf("%3d", G.edges[i][j]);
		}
		printf("\n");
	}
}


/*=============�����������������ʵ���㷨===============*/
/*�����ڽӾ���Ĵ�ָ�����㿪ʼ��������������㷨*/
void DFS_Matrix(AdjMatrix G, int k)
{
	int j;

	printf("Visit vertex: %c \n", G.vexs[k]);  //���ʱ��Ϊk�Ķ���
	visited_DFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++)  //���Ҷ���k��һ����δ�����ʹ����ڽӶ���
	{
		if (1 == G.edges[k][j] && FALSE == visited_DFS_M[j])  //�����Ϊj�Ķ�����δ�����ʹ�
			DFS_Matrix(G, j);
	}
}

/*�����ڽӾ����������������㷨*/
void DFSTraverse_Matrix(AdjMatrix G)
{
	int k;

	for (k = 1; k <= G.vexnum; k++)
		visited_DFS_M[k] = FALSE;  //��ʼ����ʶ����
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_DFS_M[k])  //�����Ϊk�Ķ���δ�����ʹ������Ըö���Ϊ��������
			DFS_Matrix(G, k);
	}
}

/*==============�����������������ʵ���㷨==============*/
/*�����ڽӾ���Ĵ�ָ�����㿪ʼ�Ĺ�����������㷨*/
void BFS_Matrix(AdjMatrix G, int k)
{
	int j;
	int t;

	printf("Visit vertex: %c \n", G.vexs[k]);  //���ʱ��Ϊk�Ķ���
	visited_BFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++)  //���ʶ���k��������δ�����ʹ����ڽӶ���
	{
		if (1 == G.edges[k][j] && FALSE == visited_BFS_M[j])  //�����Ϊj�Ķ�����δ�����ʹ�
		{
			printf("Visit vertex: %c \n", G.vexs[j]);
			visited_BFS_M[j] = TRUE;
			EnQueue_sq(&Q, j);  //������˳����������
		}
	}
	while (!QueueEmpty_sq(Q))
	{
		DeQueue_sq(&Q, &t);
		for (j = 1; j <= G.vexnum; j++)  //���ʶ���t��������δ�����ʹ����ڽӶ���
		{
			if (1 == G.edges[t][j] && FALSE == visited_BFS_M[j])
			{
				printf("Visit vertex: %c \n", G.vexs[j]);
				visited_BFS_M[j] = TRUE;
				EnQueue_sq(&Q, j);  //������˳����������
			}
		}
	}
}

/*�����ڽӾ���Ĺ�����������㷨*/
void BFSTraverse_Matrix(AdjMatrix G)
{
	int k;
	for (k = 1; k <= G.vexnum; k++)
		visited_BFS_M[k] = FALSE;  //��ʼ����ʶ����
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_BFS_M[k])  //�����Ϊk�Ķ���δ�����ʹ������Ըö���Ϊ��������
			BFS_Matrix(G, k);
	}
}

int main(void)
{
	//�Կα��е�����ͼG13������ͼG14Ϊ��������
	AdjMatrix G13_M, G14_M;

	InitQueue_sq(&Q);
	printf("=====�������ϵ�����ͼG13���ڽӾ���=====\n");
	G13_M = CreateGraph_Matrix(UNDIGRA);
	printf("G13���ڽӾ���������ʾ:\n");
	ShowGraph_Matrix(G13_M);

	printf("=====�������ϵ�����ͼG14���ڽӾ���=====\n");
	G14_M = CreateGraph_Matrix(DIGRA);
	printf("G14���ڽӾ���������ʾ:\n");
	ShowGraph_Matrix(G14_M);

	printf("=====G13�����ڽӾ���õ����������������������(�Ӷ���1��ʼ)=====\n");
	DFSTraverse_Matrix(G13_M);

	printf("=====G13�����ڽӾ���õ��Ĺ������������������(�Ӷ���1��ʼ)=====\n");
	BFSTraverse_Matrix(G13_M);
	system("pause");
	return 0;
}