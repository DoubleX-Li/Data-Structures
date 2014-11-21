//Author: Double X Li
//Date: 2014-11-17

#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX 15
using namespace std;

//结构体——个人 
typedef struct
{
     char name[9];
}Person;

//结构体——同性队列 
typedef struct
{
    Person data[MAX];
    int front,rear;
}Queue;

//结构体——舞伴 
typedef struct
{
    Person female;
    Person male;
}Pair;

//初始化队列 
int InitQueue(Queue &Q)
{
    Q.front = 0;
    Q.rear = 0;
    return 0;
}

//判空 
int IsEmpty(Queue Q)
{
    return Q.front == Q.rear;
}

//判满 
int IsFull(Queue Q)
{
    return (Q.rear + 1) % MAX == Q.front;
}

//求长度 
int QLength(Queue Q)
{
    return (Q.rear - Q.front + MAX) % MAX;
}

//入列 
int EnQueue(Queue &Q, Person e)
{
    if(IsFull(Q))
        return -1;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX;
    return 0;
}

//出列 
int DeQueue(Queue &Q, Person &e)
{
    if(IsEmpty(Q))
        return -1;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX;
    return 0;
}

//输出队列 
int ShowQueue(Queue Q)
{
    int temp = Q.front;
    while(temp != Q.rear)
    {
        cout << Q.data[temp].name << "  ";
        temp = (temp + 1) % MAX;
    }
    return 0;
}

//从文件读取舞会名单 
int InputTwoQueue(Queue &fq, Queue &mq)
{
    FILE *fp;
    char buffer[255];
    
    //读取数据 
    fp = fopen("data.txt","r");
    if(fp == NULL)
        return -1;
    fgets(buffer,255,fp);
    fclose(fp);
    
    int tnum = 0;
    Person temp;
    
    //处理字符 
    int i = 0;
    while(buffer[i] != '@')
    {
        //若遇到'&'，做标记以区分当前是女士队列 or  男士队列 
        if(buffer[i] == '&')
        {
            i++;
            tnum++;
            i++;
            continue;
        }
        
        //每逢遇到'|'，将之前的字符作为一个人的名字入列 
        int j = 0;
        while(buffer[i] != '|')
        {
            temp.name[j++] = buffer[i++];
        }
        if(buffer[i] == '|')
        {
            temp.name[j] = '\0';
            if(tnum == 1)
                EnQueue(fq,temp);
            if(tnum == 2)
                EnQueue(mq,temp);
            i++;
        }
    }
    return 0; 
}

//循环队列——配对
int MakePair(Queue &fq, Queue &mq)
{
    Person temp;
    Pair array[MAX];
    int pnum = 0;
    
    //若两队列均不为空，则从队首取两人配对 
    while(!IsEmpty(fq) && !IsEmpty(mq))
    {
        pnum++;
        DeQueue(fq,temp);
        array[pnum].female = temp;
        DeQueue(mq,temp);
        array[pnum].male = temp;
    }
    
    //输出此配对，并将两人分别从队尾插入 
    for(int i = 1; i <= pnum; i++)
    {
        cout << "(" << array[i].female.name << "," << array[i].male.name << ")  ";
        EnQueue(fq, array[i].female);
		EnQueue(mq,array[i].male);
    }
    cout << endl;
    return 0;
}

int main()
{
    Queue fq,mq;
    int rnum;
    
    system("color F0");
    
    //处理工作 
    InitQueue(fq);
    InitQueue(mq);
    InputTwoQueue(fq,mq);
    cout << "参与舞会的女士：";
    ShowQueue(fq);
    cout << "\n参与舞会的男士：";
    ShowQueue(mq);
    
    //获得舞会轮数 
    while(true)
    {
        cout << "\n\n请输入舞会轮数：";
        cin >> rnum;
        if(rnum <= 0)
            cout << "不能小于零，重新输入：";
        else
            break;
    }
    
    //调用配对函数，得到配对方案 
    for(int i = 1; i <= rnum; i++)
    {
        cout << "\n第" << i << "轮配对如下：" << endl;
        MakePair(fq,mq);
    }
    
    cout << "\n任意键退出。";
    getchar();
    getchar();
    return 0;
}