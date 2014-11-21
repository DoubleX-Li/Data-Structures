//Author: Double X Li
//Date: 2014-11-17

#include <iostream>
#include <cstdio>
#include <cstdlib>
#define MAX 15
using namespace std;

//�ṹ�塪������ 
typedef struct
{
     char name[9];
}Person;

//�ṹ�塪��ͬ�Զ��� 
typedef struct
{
    Person data[MAX];
    int front,rear;
}Queue;

//�ṹ�塪����� 
typedef struct
{
    Person female;
    Person male;
}Pair;

//��ʼ������ 
int InitQueue(Queue &Q)
{
    Q.front = 0;
    Q.rear = 0;
    return 0;
}

//�п� 
int IsEmpty(Queue Q)
{
    return Q.front == Q.rear;
}

//���� 
int IsFull(Queue Q)
{
    return (Q.rear + 1) % MAX == Q.front;
}

//�󳤶� 
int QLength(Queue Q)
{
    return (Q.rear - Q.front + MAX) % MAX;
}

//���� 
int EnQueue(Queue &Q, Person e)
{
    if(IsFull(Q))
        return -1;
    Q.data[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAX;
    return 0;
}

//���� 
int DeQueue(Queue &Q, Person &e)
{
    if(IsEmpty(Q))
        return -1;
    e = Q.data[Q.front];
    Q.front = (Q.front + 1) % MAX;
    return 0;
}

//������� 
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

//���ļ���ȡ������� 
int InputTwoQueue(Queue &fq, Queue &mq)
{
    FILE *fp;
    char buffer[255];
    
    //��ȡ���� 
    fp = fopen("data.txt","r");
    if(fp == NULL)
        return -1;
    fgets(buffer,255,fp);
    fclose(fp);
    
    int tnum = 0;
    Person temp;
    
    //�����ַ� 
    int i = 0;
    while(buffer[i] != '@')
    {
        //������'&'������������ֵ�ǰ��Ůʿ���� or  ��ʿ���� 
        if(buffer[i] == '&')
        {
            i++;
            tnum++;
            i++;
            continue;
        }
        
        //ÿ������'|'����֮ǰ���ַ���Ϊһ���˵��������� 
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

//ѭ�����С������
int MakePair(Queue &fq, Queue &mq)
{
    Person temp;
    Pair array[MAX];
    int pnum = 0;
    
    //�������о���Ϊ�գ���Ӷ���ȡ������� 
    while(!IsEmpty(fq) && !IsEmpty(mq))
    {
        pnum++;
        DeQueue(fq,temp);
        array[pnum].female = temp;
        DeQueue(mq,temp);
        array[pnum].male = temp;
    }
    
    //�������ԣ��������˷ֱ�Ӷ�β���� 
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
    
    //������ 
    InitQueue(fq);
    InitQueue(mq);
    InputTwoQueue(fq,mq);
    cout << "��������Ůʿ��";
    ShowQueue(fq);
    cout << "\n����������ʿ��";
    ShowQueue(mq);
    
    //���������� 
    while(true)
    {
        cout << "\n\n���������������";
        cin >> rnum;
        if(rnum <= 0)
            cout << "����С���㣬�������룺";
        else
            break;
    }
    
    //������Ժ������õ���Է��� 
    for(int i = 1; i <= rnum; i++)
    {
        cout << "\n��" << i << "��������£�" << endl;
        MakePair(fq,mq);
    }
    
    cout << "\n������˳���";
    getchar();
    getchar();
    return 0;
}