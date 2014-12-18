#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "Queue.h"
#include "InitArrive.h"
#include "InitConsult.h"
using namespace std;

FILE *fp;
int Time;
 
void InQueue(Queue &Q)
{
	int n;
	Person Top;
	if(Q.front != Q.rear)
	{
		if(Q.data[Q.front].flag == 0)
		{
			Q.data[Q.front].begin = Time;
			fprintf(fp,"%02d:%02d:第%03d位客人开始咨询\n",Q.data[Q.front].begin / 60 + 9, Q.data[Q.front].begin % 60,Q.data[Q.front].num,Q.data[Q.front].arrive / 60 + 9, Q.data[Q.front].arrive % 60);
			Q.data[Q.front].flag = 1;
		}
		if(Q.data[Q.front].curr == Q.data[Q.front].consult)
		{
			fprintf(fp,"%02d:%02d:第%03d位客人离开，等候%d分钟,办理业务%d分钟\n",9+Time/60,Time%60,Q.data[Q.front].num,Q.data[Q.front].begin-Q.data[Q.front].arrive,Q.data[Q.front].consult);
			Top = Q.data[Q.front];
			Q.front++;
			Q.sum++;
			InQueue(Q);
		}
		if(Q.front != Q.rear)
		{
			Q.data[Q.front].curr = Time - Q.data[Q.front].begin;
		}
	}
}

int main()
{
	int i;
	/*
	int rarrive[MAX] = {3,7,3,3,0,1,4,1,3,0,
					    1,7,1,0,2,0,3,1,0,8,
						4,0,0,7,0,20,6,3,5,1,
						0,6,2,3,1,4,10,4,1,5,
						6,1,12,10,1,0,1,1,1,10,
						3,4,8,7,7,12,16,7,10,0,
						18,6,1,12,1,2,16,6,0,1,
						3,5,4,7,8,3,4,0,2,0,
						9,6,8,12,0,0,1,1,1,0,
						2,0,1,0,0,2,1,0,1,1};
	int rconsult[MAX] = {8,10,5,6,20,8,8,14,8,7,
	                     10,5,9,5,8,7,5,8,11,9,
						 9,6,7,23,5,8,11,9,7,11,
						 8,13,6,6,11,9,7,7,9,17,
						 5,8,16,12,10,5,6,9,7,9,
						 6,6,15,5,5,6,7,11,8,6,
						 12,13,8,9,29,13,10,7,21,12,
						 12,7,17,8,6,10,9,21,8,5,
						 7,16,13,20,13,11,10,10,5,12,
						 5,8,15,21,7,13,15,20,14,6}; 
	*/
	int rarrive[MAX];
	int rconsult[MAX];
	int t[5];
	Queue all;
	Queue one;
	Queue two;
	Queue three;
	Queue four;
	Person T;
	
	fp = fopen("data.txt","w");
	InitArrive(rarrive);
	InitConsult(rconsult);
	InitQueue(one);
	InitQueue(two);
	InitQueue(three);
	InitQueue(four);
	//ShowArrive(rarrive);
	//ShowConsult(rconsult);
	
	for(i = 0; i < MAX; i++)
	{
		if(i == 0)
		{
			all.data[i].arrive = rarrive[i];
		}
		else
		{
			all.data[i].arrive = all.data[i-1].arrive + rarrive[i];
		}
		all.data[i].consult = rconsult[i];
		all.data[i].curr = 0;
		all.data[i].num = i + 1;
		all.data[i].flag = 0;
	}
	
	for(Time = 0; Time <= 480; Time++)
	{
		L1:
		InQueue(one);
		InQueue(two);
		InQueue(three);
		InQueue(four);
		
		if(all.sum < 100 && all.data[all.front].arrive == Time)
		{
			T = all.data[all.front];
			all.front++;
			all.sum++;
			
			t[1] = QLength(one);
			t[2] = QLength(two);
			t[3] = QLength(three);
			t[4] = QLength(four);

			int flag = 1;
			for(int j = 1; j < 5; j++)
			{
				if(t[flag] > t[j])
					flag = j;
			}
			if(flag == 1)
			{
				one.data[one.rear] = T;
				one.rear++;
			}
			else if(flag == 2)
			{
				two.data[two.rear] = T;
				two.rear++;
			}
			else if(flag == 3)
			{
				three.data[three.rear] = T;
				three.rear++;
			}
			else if(flag == 4)
			{
				four.data[four.rear] = T;
				four.rear++;
			}
			fprintf(fp,"%02d:%02d:第%03d位客人到达\n",T.arrive/60+9,T.arrive%60,T.num);
			goto L1;
		}
		else
			continue;
		
	}
	fprintf(fp,"\n窗口一办理业务总人数：%d\n",one.sum);
	fprintf(fp,"窗口二办理业务总人数：%d\n",two.sum);
	fprintf(fp,"窗口三办理业务总人数：%d\n",three.sum);
	fprintf(fp,"窗口四办理业务总人数：%d\n",four.sum);
	fclose(fp);
	system("data.txt");

	return 0;
}
