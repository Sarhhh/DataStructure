#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

int PrintNodes(Node *p) // 打印链表
{
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

int CreatNodesReverse(Node *L, int count) // 逆序创建链表
{
    for (int i = 1; i <= count; i++)
    {
        Node *p = (Node *)malloc(sizeof(Node));
        scanf("%d", &p->data);
        p->next = L->next;
        L->next = p;
    }
    return 0;
}

int main()
{
    Node *L = (Node *)malloc(sizeof(Node));
    L->data = 0;
    L->next = NULL;
    printf("请输入10个整数：\n");
    CreatNodesReverse(L, 10);
    printf("链表中的整数为：\n");
    PrintNodes(L->next);

    return 0;
}