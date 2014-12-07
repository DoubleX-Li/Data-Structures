#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	int weight[27] = {186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1};
	char ch[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int i;
	if(!(fp = fopen("f.txt","w")))
		return -1;
	for(i = 0; i < 27; i++)
	{
		fwrite(&ch[i],sizeof(char),1,fp);
		fwrite(&weight[i],sizeof(int),1,fp);
	}
	fclose(fp);
	return 0;
}
