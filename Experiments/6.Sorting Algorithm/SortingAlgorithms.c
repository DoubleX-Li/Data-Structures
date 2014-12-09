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

void Show(int array[], int i)
{
	while(i--)
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
	static int x = 0;
	if (first < last)
	{
		int mid = (first + last) / 2;
		MergeSort(a, first, mid, temp);
		MergeSort(a, mid+1, last, temp);
		MergeArray(a, first, mid, last, temp);
	}
	printf("No.%2d:          ",++x);
	Show(temp, 10);
}

int main()
{
	int array[10];
	int temp[10] = {0};
	
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
	printf("\nMergeSort\n");
	MergeSort(array, 0 , 9, temp);

	return 0;
}
