//Author: Double X Li
//Date: 2014-09-29

#include <stdio.h>

void InitArray(int array[])
{
	array[0] = 7;
	array[1] = 3;
	array[2] = 4;
	array[3] = 5;
	array[4] = 0; 
	array[5] = 6;
	array[6] = 2;
	array[7] = 9;
	array[8] = 1;
	array[9] = 8;
}

void Show(int array[], int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}

void InsertionSort(int array[], int n)
{
	int i,j;
	int temp;
	static int x = 0;
	printf("\nInsertionSort\n");
	for(i = 1; i < n; i++)
	{
		temp = array[i];
		j = i - 1;
		while((j >= 0) && array[j] < temp)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = temp;
		printf("No.%2d:          ",++x);
		Show(array,10);
	}
	
}

void SelectionSort(int array[],int n)
{
	int i,j;
	int temp;
	int min;
	static int x = 0;
	printf("\nSelectionSort\n");
	for(i = 0; i < n - 1; i++)
	{
		min = i;
		for(j = i + 1; j < n; j++)
		{
			if (array[j] > array[min])
			{
				min = j;
			}
		}
		if (array[min] != array[i])
		{
			temp = array[i];
			array[i] = array[min];
			array[min] = temp;
		}
		printf("No.%2d:          ",++x);
		Show(array, 10);
	}
}

void QuickSort(int array[], int left, int right)
{
	int p = (left + right) / 2;
	int pivot = array[p];
	int i = left, j = right;
	static int x = 0;
	for(; i < j;)
	{
		while(i < p && pivot <= array[i])
		{
			++i;
		}
		if(i < p)
		{
			array[p] = array[i];
			p = i;
		}
		while(j > p && pivot >= array[j])
		{
			--j;
		}
		if(j > p)
		{
			array[p] = array[j];
			p = j;
		}
	}
	array[p] = pivot;
	printf("No.%2d:          ",++x);
	Show(array, 10);
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
	}
	while(i <= m)
		temp[k++] = a[i++];
	while(j <= n)
		temp[k++] = a[j++];
	for (i = 0; i < k; i++)
		a[first+i] = temp[i];
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
	for(j = 2 * s; j < m; j = j * 2)
	{
		if(j <m && array[j] < array[j+1])
		{
			j = j +1;
		}
		if(r < array[j])
		{
			array[s] = array[j]; 
			s = j;
		}
	}
	array[s] = r;
}

void HeapSort(int H[])
{ 
	int i; 
	int j;
	int r;
	int array[11];
	static int x = 0;
	
	printf("\nHeapSort\n");
	for(i = 0; i < 10; i++)
	{
		array[i+1] = H[i];
	}
	for(i = 10/2; i >= 1; i--)
	{
		SiftDown(array, i, 10);
	} 
	for(i = 10; i > 2; i--)
	{
		r = array[i]; 
		array[i] = array[1]; 
		array[1] = r;
		SiftDown(array, 1, i - 1);
		printf("No.%2d:          ",++x);
		for(j = 1; j < 11; j++)
		{
			printf("%d ",array[j]);
		}
		printf("\n");
	}
}

int main()
{
	int array[10];
	int temp[10] = {0};
	
	system("color F0");
	InitArray(array);
	printf("Origin:        ");
	Show(array,10);
	
	InitArray(array);
	InsertionSort(array,10);
	
	InitArray(array);
	SelectionSort(array,10);
	
	InitArray(array);
	printf("\nQuickSort\n");
	QuickSort(array, 0, 9);
	
	InitArray(array);
	printf("\nMergeSort       ");
	MergeSort(array, 0 , 9, temp);
	Show(temp, 10);
	
	InitArray(array);
	HeapSort(array);

	return 0;
}
