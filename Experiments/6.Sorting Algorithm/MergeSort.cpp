//Author: Double X Li
//Date: 2014-08-25

#include <iostream>
using namespace std;

void merge_array(int a[], int first, int mid, int last, int temp[])
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

void merge_sort(int a[], int first, int last, int temp[])
{
	if (first < last)
	{
		int mid = (first + last) / 2;
		merge_sort(a, first, mid, temp);
		merge_sort(a, mid+1, last, temp);
		merge_array(a, first, mid, last, temp);
	}
}

int main()
{
	int a[10]={7, 3, 4, 5, 0, 6, 2, 9, 1, 8};
	int *p = new int[10];
	merge_sort(a,0,9,p);
	cout << "MergeSort:";
	for (int i = 0; i < 10 ; i++)
		cout << a[i] << " ";
	cout << endl; 
	return 0;
}
