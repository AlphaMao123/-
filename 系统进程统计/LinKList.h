#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#define MAX_NAME_LENGTH 50
#include<stdlib.h>

typedef struct Process
{
    int memory=0;
    int runtime=0;
    char name[MAX_NAME_LENGTH];
    Process* next,* pre;
}Process,*ListPtr;

typedef struct LinkList
{
    int Length;
    ListPtr head=NULL;
}LinkList;

void InitList(LinkList& L)
{
    L.head=(ListPtr)malloc(sizeof(Process));
    if(!L.head) exit(-2);
    L.head->next=NULL;
    L.head->name[0]='head';
    L.Length=0;
}

void DestoryList(LinkList& L)
{
    ListPtr p=L.head,q=L.head->next;
    if(p!=NULL)
    {
        if (q!=NULL)
        {
            while (q!=NULL)
            {
                free(p);
                p=q;
                q=q->next;   
            }
        }
        free(p);
    }
}

bool MatchName(ListPtr p,ListPtr q)
{
    bool judge=true;
    int i;
    for(i=0;p->name[i]!='\0'&&q->name!='\0';++i)
    {
        if(p->name[i]!=q->name[i])
        {
            judge=false;
            break;
        }
    }
    if(judge&&p->name[i]==q->name[i])
        ;
    else 
        judge=false;
    return judge;
}

void ListInsert(LinkList& L,ListPtr p,ListPtr value)
{
    ListPtr q=L.head;
    for(;!MatchName(p,q);q=q->next);
    value->next=q->next;
    q->next=value;
    ++L.Length;
}

void ListDelete(LinkList& L,ListPtr p)
{
    ListPtr pre=L.head,q=L.head->next;
    for(;!MatchName(q,p);pre=pre->next,q=q->next);
    pre->next=p->next;
    --L.Length;
}

void Listpush_front(LinkList& L,ListPtr p)
{
    ListInsert(L,L.head,p);
}

#endif