#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define  GRAPH  30
#define  UNDIGRA       GRAPH + 0    
#define  DIGRA          GRAPH + 1   
#define  DIGRA_REV     GRAPH + 2   

typedef  char  VertexType;
typedef  int  EdgeType;


typedef struct
{
	VertexType vexs[MAX];
	EdgeType edges[MAX][MAX];
	int vexnum, arcnum;  
}AdjMatrix;

typedef  enum{ FALSE, TRUE }  VisitFlag;
VisitFlag visited_DFS_M[MAX]; 
VisitFlag visited_BFS_M[MAX];  

SqQueue Q; 

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
	for (i = 1; i <= G.vexnum; i++)  
	{
		for (j = 1; j <= G.vexnum; j++)
			G.edges[i][j] = 0;
	}
	for (k = 1; k <= G.arcnum; k++)  
	{
		printf("Please input NO.%d edge's start and end:", k);
		scanf("%d,%d", &start, &end);
		G.edges[start][end] = 1;
		if (UNDIGRA == graphtype)
			G.edges[end][start] = 1;
	}

	return(G);
}

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


void DFS_Matrix(AdjMatrix G, int k)
{
	int j;

	printf("Visit vertex: %c \n", G.vexs[k]);  
	visited_DFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++)  
	{
		if (1 == G.edges[k][j] && FALSE == visited_DFS_M[j])  
			DFS_Matrix(G, j);
	}
}

void DFSTraverse_Matrix(AdjMatrix G)
{
	int k;

	for (k = 1; k <= G.vexnum; k++)
		visited_DFS_M[k] = FALSE;  
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_DFS_M[k])  
			DFS_Matrix(G, k);
	}
}

void BFS_Matrix(AdjMatrix G, int k)
{
	int j;
	int t;

	printf("Visit vertex: %c \n", G.vexs[k]);  
	visited_BFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++) 
	{
		if (1 == G.edges[k][j] && FALSE == visited_BFS_M[j])
		{
			printf("Visit vertex: %c \n", G.vexs[j]);
			visited_BFS_M[j] = TRUE;
			EnQueue_sq(&Q, j);
		}
	}
	while (!QueueEmpty_sq(Q))
	{
		DeQueue_sq(&Q, &t);
		for (j = 1; j <= G.vexnum; j++)
		{
			if (1 == G.edges[t][j] && FALSE == visited_BFS_M[j])
			{
				printf("Visit vertex: %c \n", G.vexs[j]);
				visited_BFS_M[j] = TRUE;
				EnQueue_sq(&Q, j);
			}
		}
	}
}

void BFSTraverse_Matrix(AdjMatrix G)
{
	int k;
	for (k = 1; k <= G.vexnum; k++)
		visited_BFS_M[k] = FALSE; 
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_BFS_M[k]) 
			BFS_Matrix(G, k);
	}
}

int main(void)
{
	AdjMatrix G13_M, G14_M;
	
	system("color F0");
	InitQueue_sq(&Q);
	printf("=====创建书上的无向图G13的邻接矩阵=====\n");
	G13_M = CreateGraph_Matrix(UNDIGRA);
	printf("G13的邻接矩阵如下所示:\n");
	ShowGraph_Matrix(G13_M);

	printf("=====创建书上的有向图G14的邻接矩阵=====\n");
	G14_M = CreateGraph_Matrix(DIGRA);
	printf("G14的邻接矩阵如下所示:\n");
	ShowGraph_Matrix(G14_M);

	printf("=====G13基于邻接矩阵得到的深度优先搜索遍历序列(从顶点1开始)=====\n");
	DFSTraverse_Matrix(G13_M);

	printf("=====G13基于邻接矩阵得到的广度优先搜索遍历序列(从顶点1开始)=====\n");
	BFSTraverse_Matrix(G13_M);
	system("pause"); 
	return 0;
}
