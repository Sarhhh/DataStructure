#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;


int PrintNodes(Node *p) //打印链表
{
    while (p)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

int CreatNodesReverse(Node * L,int count)   //逆序创建链表
{
    for (int i = 1;i <= count;i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        scanf("%d", &p->data);
        p->next = L->next;
        L ->next = p;
    }
    return 0;
}

int CreatNodes(Node * L,int count)   //顺序创建链表
{
    Node * tail =L;
    for (int i = 1;i <= count;i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        p->data = i;
        p->next = tail->next;
        tail->next = p;
        tail = p;
    }
    return 0;
}


int main()
{
    /*
    Node * L1 =(Node *)malloc(sizeof(Node));
    L1->data =0;
    L1->next =NULL;

    CreatNodes(L1,10);
    PrintNodes(L1->next);
    */

    Node * L2 =(Node *)malloc(sizeof(Node));
    L2->data =0;
    L2->next =NULL;
    printf("请输入10个整数：\n");
    CreatNodesReverse(L2,10);
    PrintNodes(L2->next);

    return 0;
}