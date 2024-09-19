#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Error 0
#define Ok 1
typedef int Elemtype;
typedef int Status;
typedef struct Node {
	Elemtype data;
	struct Node* next;
}Node;
//初始化一个单链表
Node* Create(Node* L) {//创建头节点时，指向自身
	L = (Node*)malloc(sizeof(Node));
	if (L == NULL) return NULL;
	L->next = L;
	return L;
}
//判空
bool Empty(Node* L) {
	if (L->next == L) return true;
	else return false;
}
//判断节点p是否为循环单链表的表尾节点
bool isTail(Node* L, Node* p) {
	if (p->next == L) return true;
	else return false;
}