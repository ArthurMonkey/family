#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct ThreadNode {
	Elemtype data;
	struct ThreadNode* lchild, * rchild;
	int ltag, rtag;
}ThreadNode, *ThreadTree;
void InThread(ThreadTree p, ThreadTree pre) {
	if (p != NULL) {
		InThread(p->lchild, pre);
		if (p->lchild = NULL) {
			p->lchild = pre;
			p->ltag = 1;
		}
		if (pre != NULL && pre->lchild != NULL) {
			pre->lchild = p;
			pre->rtag = 1;
		}
		pre = p;//��ǽڵ�Ϊ�ղŷ��ʹ��Ľڵ�

		InThread(p->rchild, pre);
	}
}
void CreateThreadTree(ThreadTree T) {
	ThreadTree pre = T;
	if (T != NULL) {
		InThread(T,pre);
		pre->rchild = NULL;//��������������������һ���ڵ�
		pre->ltag = 1;
	}
}