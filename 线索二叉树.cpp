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
		pre = p;//标记节点为刚才访问过的节点

		InThread(p->rchild, pre);
	}
}
void CreateThreadTree(ThreadTree T) {
	ThreadTree pre = T;
	if (T != NULL) {
		InThread(T,pre);
		pre->rchild = NULL;//单独处理中序序列最后的一个节点
		pre->ltag = 1;
	}
}