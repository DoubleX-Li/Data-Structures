#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

#define  GRAPH  30
#define  UNDIGRA       GRAPH + 0    //创建无向图
#define  DIGRA          GRAPH + 1    //创建有向图
#define  DIGRA_REV     GRAPH + 2    //创建邻接表时用，表示创建有向图的逆邻接表

typedef  char  VertexType;
typedef  int  EdgeType;

//邻接矩阵的定义
typedef struct
{
	VertexType vexs[MAX];
	EdgeType edges[MAX][MAX];
	int vexnum, arcnum;  //记录图的顶点数和边或弧的条数
}AdjMatrix;

typedef  enum{ FALSE, TRUE }  VisitFlag;
VisitFlag visited_DFS_M[MAX];  //设置全局向量，用来标识顶点是否已被访问过
VisitFlag visited_BFS_M[MAX];  //设置全局向量，用来标识顶点是否已被访问过

SqQueue Q;  //设置全局队列

/*创建图的邻接矩阵*/
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
	for (i = 1; i <= G.vexnum; i++)  //初始化矩阵
	{
		for (j = 1; j <= G.vexnum; j++)
			G.edges[i][j] = 0;
	}
	for (k = 1; k <= G.arcnum; k++)  //根据输入的边的信息设置邻接矩阵
	{
		printf("Please input NO.%d edge's start and end:", k);
		scanf("%d,%d", &start, &end);
		G.edges[start][end] = 1;
		if (UNDIGRA == graphtype)
			G.edges[end][start] = 1;
	}

	return(G);
}

/*输出图的邻接矩阵*/
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


/*=============深度优先搜索遍历的实现算法===============*/
/*基于邻接矩阵的从指定顶点开始的深度优先搜索算法*/
void DFS_Matrix(AdjMatrix G, int k)
{
	int j;

	printf("Visit vertex: %c \n", G.vexs[k]);  //访问编号为k的顶点
	visited_DFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++)  //查找顶点k的一个尚未被访问过的邻接顶点
	{
		if (1 == G.edges[k][j] && FALSE == visited_DFS_M[j])  //若编号为j的顶点尚未被访问过
			DFS_Matrix(G, j);
	}
}

/*基于邻接矩阵的深度优先搜索算法*/
void DFSTraverse_Matrix(AdjMatrix G)
{
	int k;

	for (k = 1; k <= G.vexnum; k++)
		visited_DFS_M[k] = FALSE;  //初始化标识向量
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_DFS_M[k])  //若编号为k的顶点未被访问过，则以该顶点为出发顶点
			DFS_Matrix(G, k);
	}
}

/*==============广度优先搜索遍历的实现算法==============*/
/*基于邻接矩阵的从指定顶点开始的广度优先搜索算法*/
void BFS_Matrix(AdjMatrix G, int k)
{
	int j;
	int t;

	printf("Visit vertex: %c \n", G.vexs[k]);  //访问编号为k的顶点
	visited_BFS_M[k] = TRUE;
	for (j = 1; j <= G.vexnum; j++)  //访问顶点k的所有尚未被访问过的邻接顶点
	{
		if (1 == G.edges[k][j] && FALSE == visited_BFS_M[j])  //若编号为j的顶点尚未被访问过
		{
			printf("Visit vertex: %c \n", G.vexs[j]);
			visited_BFS_M[j] = TRUE;
			EnQueue_sq(&Q, j);  //按访问顺序依次入列
		}
	}
	while (!QueueEmpty_sq(Q))
	{
		DeQueue_sq(&Q, &t);
		for (j = 1; j <= G.vexnum; j++)  //访问顶点t的所有尚未被访问过的邻接顶点
		{
			if (1 == G.edges[t][j] && FALSE == visited_BFS_M[j])
			{
				printf("Visit vertex: %c \n", G.vexs[j]);
				visited_BFS_M[j] = TRUE;
				EnQueue_sq(&Q, j);  //按访问顺序依次入列
			}
		}
	}
}

/*基于邻接矩阵的广度优先搜索算法*/
void BFSTraverse_Matrix(AdjMatrix G)
{
	int k;
	for (k = 1; k <= G.vexnum; k++)
		visited_BFS_M[k] = FALSE;  //初始化标识向量
	for (k = 1; k <= G.vexnum; k++)
	{
		if (FALSE == visited_BFS_M[k])  //若编号为k的顶点未被访问过，则以该顶点为出发顶点
			BFS_Matrix(G, k);
	}
}

int main(void)
{
	//以课本中的无向图G13和有向图G14为测试用例
	AdjMatrix G13_M, G14_M;

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