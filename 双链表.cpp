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
}DNode;
DNode* Create(DNode* L) {
	DNode* head = (DNode*)malloc(sizeof(DNode));
	if (head == NULL) return NULL;
	head->next = NULL;
	head->prior = NULL;
	return head;
}
bool Empty(DNode* head) {//判断双链表是否为空
	if (head->next == NULL) return true;
	else return false;
}
bool InsertNextDNode(DNode* p, DNode* s) {//在节点p后插入节点s
	if (p == NULL || s == NULL) return false;//如果两个节点为空，则为非法参数
	s->next = p->next;
	if (p->next != NULL) p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}
//按位序插入操作：从头结点开始找到第i-1个节点后插
// 
//前插操作：找到给定节点的前驱结点，对前驱结点进行后插

//删除p节点的后继节点
bool DeletNextDNode(DNode* p) {
	if (p == NULL) return false;
	DNode* q = p->next;
	if (q == NULL) return false;
	p->next = q->next;
	if (q->next != NULL) q->next->prior = p;
	free(q);
	return true;
}

bool DestoryList(DNode* L) {//带头结点
	//循环释放各个数据结点
	while (L->next != NULL) {
		DeletNextDNode(L);  //删除头结点的后继结点
		free(L); //释放头结点
		L = NULL;  //头指针指向NULL

	}
	return true;
}

void showList(DNode* head) {
	DNode* p = head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int main() {
	DNode* L=(DNode*)malloc(sizeof(DNode));
	L = Create(L);
	if (L == NULL) printf("0\n");
	else printf("1\n");
	//显示1， 创建成功

	return 0;
}