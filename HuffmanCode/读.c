#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	int i;
	int weight[30];
	char ch[30];
	fp = fopen("f.txt","r");
	for(i = 0; i < 27; i++)
	{
		fread(&ch[i],sizeof(char),1,fp);
		fread(&weight[i],sizeof(int),1,fp);
	}
	for(i = 0; i < 27; i++)
	{
		printf("%c %d\n",ch[i],weight[i]);
	}
	return 0;
}
