//Author: Double X Li
//Date: 2014-12-14

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

int count = 0;;
int cmp[7][5] = {0};
int mov[7][5] = {0};
FILE *fp;

void InitArray(int array[], int n)
{
	int i;
	
	srand(time(NULL));
	for(i = 0; i < n; i++)
	{
		array[i] = rand() % n;
	}
}

void Copy(int array[], int t[], int n)
{
	int i;
	
	for(i = 0; i < n; i++)
	{
		t[i] = array[i];
	}
}

void Show(int array[], int n)
{
	int i = 0;
	
	while(i < n)
	{
		fprintf(fp,"%3d ",array[i++]);
		if(i != 0 && i % 20 == 0)
			fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
}

void BubleSort(int array[], int n)
{
	int i, j;
	int temp;
	
	fprintf(fp,"\nBubleSort\n");
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (array[j] < array[j-1])
			{
				temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
				cmp[0][count]++;
				mov[0][count] += 3;
			}
		}
	}
	Show(array,n);
	fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[0][count],mov[0][count]);
}

void InsertionSort(int array[], int n)
{
	int i,j;
	int temp;

	fprintf(fp,"\nInsertionSort\n");
	for(i = 1; i < n; i++)
	{
		temp = array[i];
		mov[1][count]++;
		j = i - 1;
		while((j >= 0) && array[j] > temp)
		{
			array[j + 1] = array[j];
			j--;
			cmp[1][count]++;
			mov[1][count]++;
		}
		array[j + 1] = temp;
		mov[1][count]++;
		
	}
	Show(array,n);
	fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[1][count],mov[1][count]);
}

void SelectionSort(int array[],int n)
{
	int i,j;
	int temp;
	int min;

	fprintf(fp,"\nSelectionSort\n");
	for(i = 0; i < n - 1; i++)
	{
		min = i;
		for(j = i + 1; j < n; j++)
		{
			if (array[j] < array[min])
			{
				min = j;
				cmp[2][count]++;
			}
		}
		if (array[min] != array[i])
		{
			temp = array[i];
			array[i] = array[min];
			array[min] = temp;
			cmp[2][count]++;
			mov[2][count] += 3;
		}
	}
	Show(array, n);
	fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[2][count],mov[2][count]);
}

void ShellSort(int array[], int n)
{
	int i, j, gap;
	int k, temp;

	fprintf(fp,"\nShellSort\n");
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		for(i = 0; i < gap; i++)
		{
			for (j = i + gap; j < n; j += gap)
			{
				if (array[j] < array[j - gap])
				{
					temp = array[j];
					k = j - gap;
					cmp[3][count]++;
					mov[3][count]++;
					while(k >= 0 && array[k] > temp)
					{
						array[k + gap] = array[k];
						k -= gap;
						cmp[3][count]++;
						mov[3][count]++;
					}
					array[k + gap] = temp;
					mov[3][count]++;
				}
			}
		}
	}
	Show(array, n);
	fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[3][count],mov[3][count]);
}

void QuickSort(int array[], int left, int right)
{
	int p = (left + right) / 2;
	int pivot = array[p];
	int i = left, j = right;
	
	mov[4][count]++;
	for(; i < j;)
	{
		while(i < p && pivot >= array[i])
		{
			++i;
			cmp[4][count]++;
		}
		if(i < p)
		{
			array[p] = array[i];
			p = i;
			mov[4][count]++;
		}
		while(j > p && pivot <= array[j])
		{
			--j;
			cmp[4][count]++;
		}
		if(j > p)
		{
			array[p] = array[j];
			p = j;
			mov[4][count]++;
		}
	}
	array[p] = pivot;
	if(p - left > 1)
		QuickSort(array, left, p - 1);
	if(right - p > 1)
		QuickSort(array, p + 1, right);
}

void MergeArray(int a[], int first, int mid, int last, int temp[])
{
	int i = first, j = mid + 1;
	int m = mid, n = last;
	int k = 0;
	
	while(i <= m && j <= n )
	{
		if (a[i] < a[j] )
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
		cmp[5][count]++;
		mov[5][count]++;
	}
	while(i <= m)
	{
		temp[k++] = a[i++];
		mov[5][count]++;
	}
		
	while(j <= n)
	{
		temp[k++] = a[j++];
		mov[5][count]++;
	}
	for (i = 0; i < k; i++)
	{
		a[first+i] = temp[i];
		mov[5][count]++;
	}
		
}

void MergeSort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		MergeSort(a, first, mid, temp);
		MergeSort(a, mid+1, last, temp);
		MergeArray(a, first, mid, last, temp);
	}
}

void SiftDown(int array[ ], int s, int m)
{  	
	int j; 
	int r = array[s];
	mov[6][count]++;
	for(j = 2 * s; j < m; j = j * 2)
	{
		if(j <m && array[j] < array[j+1])
		{
			j = j +1;
			cmp[6][count]++;
		}
		if(r < array[j])
		{
			array[s] = array[j]; 
			s = j;
			cmp[6][count]++;
			mov[6][count]++;
		}
	}
	array[s] = r;
	mov[6][count]++;
}

void HeapSort(int H[], int n)
{ 
	int i; 
	int r;
	int array[201];
	
	for(i = 0; i < n; i++)
	{
		array[i+1] = H[i];
	}
	for(i = n/2; i >= 1; i--)
	{
		SiftDown(array, i, n);
	} 
	for(i = n; i > 2; i--)
	{
		r = array[i]; 
		array[i] = array[1]; 
		array[1] = r;
		mov[6][count] += 3;
		SiftDown(array, 1, i - 1);
	}
	for(i = 0; i < n; i++)
	{
		array[i] = array[i+1];
	}
	Show(array,n);
	fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[6][count],mov[6][count]);
}

void Conclusion()
{
	int ave[7][2] = {0};
	int var[7][2] = {0};
	int i,j;
	
	for(i = 0; i < 7; i++)
	{
		for(j = 0; j < 5; j++)
		{
			ave[i][0] += cmp[i][j];
			ave[i][1] += mov[i][j]; 
		}
		ave[i][0] /= 5;
		ave[i][1] /= 5;
	}
	for(i = 0; i < 7; i++)
	{
		for(j = 0; j < 5; j++)
		{
			var[i][0] += pow(cmp[i][j] - ave[i][0], 2);
			var[i][1] += pow(mov[i][j] - ave[i][1], 2);
		}
		var[i][0] /= 5;
		var[i][1] /= 5;
	}
	fprintf(fp,"\n总结：\n");
	fprintf(fp,"平均比较次数:\n");
	fprintf(fp,"BubleSort:    %d	方差：%d\n",ave[0][0],var[0][0]);
	fprintf(fp,"InsertionSort:%d	方差：%d\n",ave[1][0],var[1][0]);
	fprintf(fp,"SelectionSort:%d	方差：%d\n",ave[2][0],var[2][0]);
	fprintf(fp,"ShellSort:    %d	方差：%d\n",ave[3][0],var[3][0]);
	fprintf(fp,"QuickSort:    %d	方差：%d\n",ave[4][0],var[4][0]);
	fprintf(fp,"MergeSort:    %d	方差：%d\n",ave[5][0],var[5][0]);
	fprintf(fp,"HeapSort:     %d	方差：%d\n",ave[6][0],var[6][0]);
	fprintf(fp,"\n平均移动次数:\n");
	fprintf(fp,"BubleSort:    %d	方差：%d\n",ave[0][1],var[0][1]);
	fprintf(fp,"InsertionSort:%d	方差：%d\n",ave[1][1],var[1][1]);
	fprintf(fp,"SelectionSort:%d	方差：%d\n",ave[2][1],var[2][1]);
	fprintf(fp,"ShellSort:    %d	方差：%d\n",ave[3][1],var[3][1]);
	fprintf(fp,"QuickSort:    %d	方差：%d\n",ave[4][1],var[4][1]);
	fprintf(fp,"MergeSort:    %d	方差：%d\n",ave[5][1],var[5][1]);
	fprintf(fp,"HeapSort:     %d	方差：%d\n",ave[6][1],var[6][1]);
}

int main()
{
	int n = 200;
	int array[200];
	int temp[200] = {0};
	int t[200];
	
	printf("静候5s\n");
	fp = fopen("data.txt","w");
	fprintf(fp,"测试过程如下：\n");
	while(count < 5)
	{
		fprintf(fp,"\n第%d组测试\n", count+1);
		InitArray(array,n);
		fprintf(fp,"Origin\n");
		Show(array,n);
		
		Copy(array, t, n);
		BubleSort(t,n);
		
		Copy(array, t, n);	
		InsertionSort(t,n);
	
		Copy(array, t, n);	
		SelectionSort(t,n);
		
		Copy(array, t, n);
		ShellSort(t,n);
	
		Copy(array, t, n);	
		fprintf(fp,"\nQuickSort\n");
		QuickSort(t, 0, n-1);
		Show(t, n);
		fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[4][count],mov[4][count]);
	
		Copy(array, t, n);	
		fprintf(fp,"\nMergeSort\n");
		MergeSort(t, 0 , n-1, temp);
		Show(t, n);
		fprintf(fp,"比较次数:%d\n移动次数:%d\n",cmp[5][count],mov[5][count]);
		
		Copy(array, t, n);
		fprintf(fp,"\nHeapSort\n");
		HeapSort(t, n);
		
		count++;
		Sleep(1000);
	}
	
	Conclusion();
	fclose(fp);
	system("data.txt");
	return 0;
}
