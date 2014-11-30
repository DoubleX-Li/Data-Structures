//Author: Double X Li
//Date:2014-11-20
 
#include <iostream>
#include <iomanip>
#define ElemType int
using namespace std;

//结构体——三元 
typedef struct
{
    int row, column;
    ElemType value;
}Three;

//结构体——三元组及相关信息 
typedef struct
{
    Three data[500];
    int rown;
    int coln;
    int valn;
}Matrix;

//初始化 
int InitMatrix(Matrix &M)
{
    M.rown = 0;
    M.coln = 0;
    M.valn = 0;
    
    for(int i = 0; i < 500; i++)
    {
        M.data[i].row = 0;
        M.data[i].column = 0;
        M.data[i].value = 0;
    }
    return 0;
}

//创建稀疏矩阵 
int CreatMatrix(Matrix &M)
{
    cout << "请输入矩阵的行数列数以及非零元的个数(a b c)：";
    cin >> M.rown >> M.coln >> M.valn;
    for(int i = 0; i < M.valn; i++)
    {
        cout << "请输入第" << i + 1 << "个非零元的行、列、值(a b c)：";
        cin >> M.data[i].row >> M.data[i].column >> M.data[i].value;
    }
    return 0;
}

//打印稀疏矩阵 
int ShowMatrix(Matrix M)
{
    int temp = 0;
    
    for(int k = 0; k < M.valn; k++)
    {
        for(int i = 0; i < M.rown; i++)
        {
            for(int j = 0; j < M.coln; j++)
            {
                if(i == M.data[k].row && j == M.data[k].column)
        	{
        		cout <<  setw(4) << M.data[k++].value;
		}
		else
			cout << setw(4) << temp;
	    }
	    cout << endl;
	}
    }
    cout << endl;
    return 0;
}

//函数重载——相加矩阵置于C 
int AddMatrix(Matrix A, Matrix B, Matrix &C)
{
    int i = 0, j = 0;
    C.rown = A.rown;
    C.coln = A.coln;

    while(i < A.valn && j < B.valn)
    {
        if(A.data[i].row < B.data[j].row)
        {
            C.data[C.valn].row = A.data[i].row;
            C.data[C.valn].column = A.data[i].column;
            C.data[C.valn].value = A.data[i].value;
            C.valn++;
            i++;
        }
        if(A.data[i].row == B.data[j].row)
        {
            if(A.data[i].column < B.data[j].column)
            {
                C.data[C.valn].row = A.data[i].row;
                C.data[C.valn].column = A.data[i].column;
                C.data[C.valn].value = A.data[i].value;
                C.valn++;
                i++;
            }
            if(A.data[i].column == B.data[j].column)
            {
                C.data[C.valn].row = A.data[i].row;
                C.data[C.valn].column = A.data[i].column;
                C.data[C.valn].value = A.data[i].value + B.data[j].value;
                C.valn++;
                i++;
                j++;
            }
            if(A.data[i].column > B.data[j].column)
            {
                C.data[C.valn].row = B.data[j].row;
                C.data[C.valn].column = B.data[j].column;
                C.data[C.valn].value = B.data[j].value;
                C.valn++;
                j++;
            }
        }
        if(A.data[i].row > B.data[j].row)
        {
            C.data[C.valn].row = B.data[j].row;
            C.data[C.valn].column = B.data[j].column;
            C.data[C.valn].value = B.data[j].value;
            C.valn++;
            j++;
        }
    }
    if(i == A.valn)
    {
        while(j < B.valn)
        {
            C.data[C.valn].row = B.data[j].row;
            C.data[C.valn].column = B.data[j].column;
            C.data[C.valn].value = B.data[j].value;
            C.valn++;
            j++;
        }
    }
    if(j == B.valn)
    {
        while(i < A.valn)
        {
            C.data[C.valn].row = A.data[i].row;
            C.data[C.valn].column = A.data[i].column;
            C.data[C.valn].value = A.data[i].value;
            C.valn++;
            i++;
        }
    }
    return 0;
}

//函数重载——相加矩阵置于A 
int AddMatrix(Matrix &A, Matrix B)
{
	int i = 0, j = 0;
	
	while(i < A.valn && j < B.valn)
    {
        if(A.data[i].row < B.data[j].row)
        {
            i++;
        }
        if(A.data[i].row == B.data[j].row)
        {
            if(A.data[i].column < B.data[j].column)
            {
                i++;
            }
            if(A.data[i].column == B.data[j].column)
            {
				A.data[i].value += B.data[j].value;
				i++;
				j++;
            }
            if(A.data[i].column > B.data[j].column)
            {
                for(int n = A.valn; n > i; n--)
                {
                	A.data[n].row = A.data[n - 1].row;
                	A.data[n].column = A.data[n - 1].column;
                	A.data[n].value = A.data[n - 1].value;
		}
		A.data[i].row = B.data[j].row;
		A.data[i].column = B.data[j].column;
		A.data[i].value = B.data[j].value;
		j++;
		A.valn++;
            }
        }
        if(A.data[i].row > B.data[j].row)
        {
            for(int n = A.valn; n > i; n--)
            {
                A.data[n].row = A.data[n - 1].row;
                A.data[n].column = A.data[n - 1].column;
                A.data[n].value = A.data[n - 1].value;
	    }
	    A.data[i].row = B.data[j].row;
	    A.data[i].column = B.data[j].column;
	    A.data[i].value = B.data[j].value;
	    j++;
	    A.valn++;
        }
    }
    if(i == A.valn)
    {
        while(j < B.valn)
        {
            A.data[i].row = B.data[j].row;
            A.data[i].column = B.data[j].column;
            A.data[i].value = B.data[j].value;
            i++;
            j++;
        }
    }
    if(j == B.valn)
    {
        //Do nothing!
    }
    return 0;
} 

int main()
{
    Matrix A,B,C;
	
    system("color F0");
	
    InitMatrix(A);
    InitMatrix(B);
    InitMatrix(C);
    
    CreatMatrix(A);
    CreatMatrix(B);
	
    cout << "矩阵A：" << endl;
    ShowMatrix(A);
    cout << "矩阵B：" << endl;
    ShowMatrix(B);
	
    AddMatrix(A,B,C);
    cout << "和置于矩阵C：" << endl;
    ShowMatrix(C);
    
    AddMatrix(A,B);
    cout << "和置于矩阵A：" << endl;
    ShowMatrix(A);
    
    cout << "感谢使用稀疏矩阵相加程序！" << endl;
    return 0;
}
