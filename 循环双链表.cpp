#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Ok 1
#define Error 0
typedef int Elemtype;
typedef int Status;
typedef struct DNode {
	Elemtype data;
	struct DNode* prior, * next;
}DNode,*DLinkList;
DNode* Create() {//����ͷ�ڵ�
	DNode* L = (DNode*)malloc(sizeof(DNode));
	if (L = NULL) return NULL;
	L->prior = L;
	L->next = L;
	return L;
}
bool Empty(DNode* p) {
	if (p->next == p) return true;
	else return false;
}
bool isTail(DNode* L, DNode* p) {
	if (p->next == L) return true;
	else return false;
}
bool InsertNextDNode(DNode* p, DNode* s) {//��ָ���ڵ�p�Ͳ���ڵ�s
	s->next = p->next;
	p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}
bool DeletDNode(DNode* p, DNode* s) {//ɾ��ָ���ڵ�p�ĺ�̽ڵ�s
	p->next = s->next;
	s->next->prior = p;
	free(s);
}