//Author: Double X Li
//Date:2014-11-20
 
#include <iostream>
#include <iomanip>
#define ElemType int
using namespace std;

//�ṹ�塪����Ԫ 
typedef struct
{
	int row, column;
	ElemType value;
}Three;

class Matrix
{
private:
    Three data[500];
    int rown;
    int coln;
    int valn;
public:
	//���캯��
	Matrix()
	{
		rown = 0;
		coln = 0;
		valn = 0;
		
		for(int i = 0; i < 500; i++)
    	{
        	data[i].row = 0;
        	data[i].column = 0;
        	data[i].value = 0;
    	}
	}
	
	friend istream &operator>>(istream &input, Matrix &M);
	friend ostream &operator<<(ostream &output, const Matrix &M);
	
	//�������ء�����Ӿ�������C 
	int AddMatrix(Matrix A, Matrix B)
	{
    	int i = 0, j = 0;
    	
		rown = A.rown;
    	coln = A.coln;

    	while(i < A.valn && j < B.valn)
    	{
        	if(A.data[i].row < B.data[j].row)
        	{
            	data[valn].row = A.data[i].row;
            	data[valn].column = A.data[i].column;
            	data[valn].value = A.data[i].value;
            	valn++;
            	i++;
        	}
        	if(A.data[i].row == B.data[j].row)
        	{
            	if(A.data[i].column < B.data[j].column)
            	{
                	data[valn].row = A.data[i].row;
                	data[valn].column = A.data[i].column;
                	data[valn].value = A.data[i].value;
                	valn++;
                	i++;
            	}
            	if(A.data[i].column == B.data[j].column)
            	{
                	data[valn].row = A.data[i].row;
                	data[valn].column = A.data[i].column;
                	data[valn].value = A.data[i].value + B.data[j].value;
                	valn++;
                	i++;
                	j++;
            	}
            	if(A.data[i].column > B.data[j].column)
            	{
                	data[valn].row = B.data[j].row;
                	data[valn].column = B.data[j].column;
                	data[valn].value = B.data[j].value;
                	valn++;
                	j++;
            	}
        	}
        	if(A.data[i].row > B.data[j].row)
        	{
            	data[valn].row = B.data[j].row;
            	data[valn].column = B.data[j].column;
            	data[valn].value = B.data[j].value;
            	valn++;
            	j++;
        	}
    	}
    	if(i == A.valn)
    	{
        	while(j < B.valn)
        	{
            	data[valn].row = B.data[j].row;
            	data[valn].column = B.data[j].column;
            	data[valn].value = B.data[j].value;
            	valn++;
            	j++;
        	}
    	}
    	if(j == B.valn)
    	{
        	while(i < A.valn)
       		{
            	data[valn].row = A.data[i].row;
            	data[valn].column = A.data[i].column;
            	data[valn].value = A.data[i].value;
            	valn++;
            	i++;
        	}
    	}
    	return 0;
	}
	
	//�������ء�����Ӿ�������A 
	int AddMatrix(Matrix B)
	{
		int i = 0, j = 0;
		
		while(i < valn && j < B.valn)
	    {
	        if(data[i].row < B.data[j].row)
	        {
	            i++;
	        }
	        if(data[i].row == B.data[j].row)
	        {
	            if(data[i].column < B.data[j].column)
	            {
	                i++;
	            }
	            if(data[i].column == B.data[j].column)
	            {
					data[i].value += B.data[j].value;
					i++;
					j++;
            	}
            	if(data[i].column > B.data[j].column)
            	{
                	for(int n = valn; n > i; n--)
                	{
                		data[n].row = data[n - 1].row;
                		data[n].column = data[n - 1].column;
                		data[n].value = data[n - 1].value;
					}
					data[i].row = B.data[j].row;
					data[i].column = B.data[j].column;
					data[i].value = B.data[j].value;
					j++;
					valn++;
            	}
        	}
        	if(data[i].row > B.data[j].row)
        	{
            	for(int n = valn; n > i; n--)
            	{
                	data[n].row = data[n - 1].row;
                	data[n].column = data[n - 1].column;
                	data[n].value = data[n - 1].value;
				}
				data[i].row = B.data[j].row;
				data[i].column = B.data[j].column;
				data[i].value = B.data[j].value;
				j++;
				valn++;
        	}
    	}
    	if(i == valn)
    	{
        	while(j < B.valn)
        	{
            	data[i].row = B.data[j].row;
            	data[i].column = B.data[j].column;
            	data[i].value = B.data[j].value;
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
};

//��������ء���>>(ִ�д�������)  
istream &operator>>(istream &input, Matrix &M)
{
	cout << "�������������������Լ�����Ԫ�ĸ���(a b c)��";
    input >> M.rown >> M.coln >> M.valn;
    for(int i = 0; i < M.valn; i++)
    {
        cout << "�������" << i + 1 << "������Ԫ���С��С�ֵ(a b c)��";
        input >> M.data[i].row >> M.data[i].column >> M.data[i].value;
    }
    return input;
}

//��������ء���<<(ִ�д�ӡ����) 
ostream &operator<<(ostream &output, const Matrix &M)
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
        			output <<  setw(4) << M.data[k++].value;
				}
				else
					output << setw(4) << temp;
			}
			output << endl;
		}
    }
    output << endl;
    return output;
}

int main()
{
    Matrix A,B,C;
	
	system("color F0");
	
    cin >> A;
    cin >> B;
	
	cout << "����A��" << endl;
	cout << A;
	cout << "����B��" << endl;
	cout << B;
	
    C.AddMatrix(A,B);
    cout << "�����ھ���C��" << endl;
    cout << C;
    
    A.AddMatrix(B);
    cout << "�����ھ���A��" << endl;
    cout << A;
    
    cout << "��лʹ��ϡ�������ӳ���" << endl;
    return 0;
}
