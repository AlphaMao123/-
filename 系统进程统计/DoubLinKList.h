#ifndef _DOUBLINKLIST_H_
#define _DOUBLINKLIST_H_
#define MAX_NAME_LENGTH 50
#include<stdlib.h>
#include"LinKList.h"

typedef struct DoubLinkList
{
    int Length;
    ListPtr head=NULL;
}DoubLinkList;

void InitDList(DoubLinkList& DL)
{
    DL.head=(ListPtr)malloc(sizeof(Process));
    if(!DL.head) exit(-2);
    DL.Length=0;
    DL.head->name[0]='head';
    DL.head->next=DL.head->pre=NULL;
}

void ClearDList(DoubLinkList& DL)
{
	ListPtr p = DL.head->next;
	if (p == NULL)
	{
		return;
	}
	if (p->next != NULL)
	{
		ListPtr q = p->next;
		if (q != NULL)
		{
			while (q != NULL)
			{
				free(p);  
				p = q;
				q = q->next;
			}
		}
		free(p);
	}
	DL.head->next = NULL;
	DL.Length = 0;
}

void DestoryDList(DoubLinkList& DL)
{
    ListPtr p=DL.head,q=DL.head->next;
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

ListPtr LocateElem(DoubLinkList DL,int i)
{
    ListPtr p=DL.head;
    if(i>DL.Length)
    {
        return NULL;
    }
    for(int j=0;j<i;++j)
    {
        p=p->next;
    }
    return p;
}

void DListInsert(DoubLinkList& DL,int i,ListPtr value)
{
    ListPtr p=LocateElem(DL,i);
    if(p==DL.head&&p->next==NULL)
    {
        value->pre=p;
        value->next=p->next;
        p->next=value;
    }
	else if (p==DL.head)
	{
		value->pre = p;
		value->next = p->next;
		p->next->pre = value;
		p->next = value;
	}
    else
    {
        p->pre->next=value;
        value->pre=p->pre;
        value->next=p;
        p->pre=value;
    }
    ++DL.Length;
}

void DListDelete(DoubLinkList& DL,int i,ListPtr value)
{
    ListPtr p=LocateElem(DL,i);
    value=p;
    if(i!=0)
    {
        if(p->next==NULL)
        {
            p->pre->next=NULL;
        }
        else
        {
            p->pre->next=p->next;
            p->next->pre=p->pre;
        }
    }
	--DL.Length;
}


void DListSort(DoubLinkList& DL)
{
    ListPtr max;
    int maxindex,j;
    if (DL.head->next)
    {
        for(int i=1;i<=DL.Length;++i)
        {
            max=LocateElem(DL,i);
			for( j=i;j<=DL.Length;++j)
            {
                ListPtr p=LocateElem(DL,j);
                if (p->memory<=max->memory)
                {
                    maxindex=j;
                    max=p;
                }
            }
            DListDelete(DL,maxindex,max);
            DListInsert(DL,0,max);
        }
    }
}
#endif