#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<stack>
#include<math.h>
#include"LinKList.h"
#include"DoubLinKList.h"

void PrintList(LinkList L)
{
    ListPtr p=L.head->next;
    if (p)
    {
        for (;p;p=p->next)
        {
            printf("%s ",p->name);
        }
        printf("\n");
    }
}

void PrintDList(DoubLinkList DL)
{
    ListPtr p=DL.head->next;
    if (p)
    {
        for (;p;p=p->next)
        {
            printf("%d ",p->memory);
        }
        printf("\n");
    }
}

void getProcess()
{
    FILE* fp;
    char names[1000];
    if((fp=_popen("tasklist","r"))==NULL)
    {
        exit(-1);
    }
    FILE* ptr=fopen("process_test.txt","w"); 
	int i = 0;
	int j = 0;
    while(fgets(names,sizeof(names),fp))
    {
		if (i<=2)
        {
            ++i;
            continue;
        }
		++j;
		if (j == 21)
		{
			break;
		}
        fputs(names,ptr);
    }
    _pclose(fp);
    fclose(ptr);
}

void DealData(DoubLinkList& DL)//暂时命名
{   
    FILE* fp;
    fp=fopen("process_test.txt","r");
    char names[1000];
    int j=0;
    std::stack<char> S;
    while (fgets(names,sizeof(names),fp))
    {
        ListPtr p=(ListPtr)malloc(sizeof(Process));
		p->memory = 0;
		p->runtime = 0;
		j = 0;
        for(int i=0;names[i]!='\0';++i)
        {
            if(((names[i]>'A'&&names[i]<'Z')||(names[i]>'a'&&names[i]<'z')||names[i]=='.')&&p->name[j]!='\0')
            {
                p->name[j]=names[i];
                ++j;
                continue;
            }
            if(names[i]==' '&&names[i+1]==' ')
            {
                p->name[j]='\0';
                continue;
            }
			else
			{
				if(p->name[j]!='\0')
                {
                    p->name[j] = names[i];
                    ++j;
					continue;
                }
			}
            if(names[i]==',')
            {
                continue;
            }
            if(names[i]>='0'&&names[i]<='9')
            {
                S.push(names[i]);
                if(names[i+2]=='S'||names[i+2]=='C')
                {
                    while(!S.empty())
                    {
                        S.pop();
                    }
                }
                if(!S.empty())
                {
                    if(S.top()=='0'||S.top()=='1')
                    {
                        if(names[i+1]==' '&&names[i+2]==' '&&names[i+3]==' ')
                        {
                            S.pop();
                        }
                    }
                }
                if(names[i+2]=='K')
                    {
                        for (int k=0;!S.empty();++k)
                        {
                            p->memory=p->memory+(S.top()-48)*pow(10,k);
                            S.pop();
                        }
                    }
            }
        }
		DListInsert(DL,0,p);
    }
}

void Show(DoubLinkList DL,LinkList L)
{
	while (true)
	{
		getProcess();
		DealData(DL);
		DListSort(DL);
		printf("进程名\t\t\t运行时间\t\t使用内存\n");
		static int time = 0;
		for (int i = 1; i <= 20; ++i)
		{
			ListPtr p = LocateElem(DL, i);
			printf("%-25s%7d%\t\t%7d K\n", p->name,time, p->memory);
		}
		++time;
		ClearDList(DL);
		Sleep(1000);
		system("cls");
	}
	
}

int main()
{
    LinkList L;
    DoubLinkList DL;
    InitList(L);
    InitDList(DL);
	/*
    ListPtr p=L.head;
    int num;
    for(int i=0;i<20;++i)
    {
        scanf("%d",&num);
        p=(ListPtr)malloc(sizeof(Process));
        p->memory=num;
        DListInsert(DL,0,p);
    }
	DListSort(DL);
    PrintDList(DL);
    DestoryDList(DL);
    DestoryList(L);
    return 0;*/
    //getProcess();
	//DealData(DL);
	//DListSort(DL);
	Show(DL, L);
    return 0;
}