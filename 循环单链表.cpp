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
//��ʼ��һ��������
Node* Create(Node* L) {//����ͷ�ڵ�ʱ��ָ������
	L = (Node*)malloc(sizeof(Node));
	if (L == NULL) return NULL;
	L->next = L;
	return L;
}
//�п�
bool Empty(Node* L) {
	if (L->next == L) return true;
	else return false;
}
//�жϽڵ�p�Ƿ�Ϊѭ��������ı�β�ڵ�
bool isTail(Node* L, Node* p) {
	if (p->next == L) return true;
	else return false;
}