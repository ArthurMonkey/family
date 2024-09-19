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
Node* CreatHeadInsert() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	for (int i = 0; i < 10; i++) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i;
		p->next = head->next;
		head->next = p;
	}
	return head->next;
}
void showList(Node* head) {
	Node* p=head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
Node* CreatTailInsert() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	Node* r = head;
	for (int i = 0; i < 10; i++) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	return head->next;
}
bool ListInsert(Node* L, int i, Elemtype e) {//按位序插入：在给定i前插入节点
	if (i < 1) return false;
	if (i == 1) {
		Node* s = (Node*)malloc(sizeof(Node));
		s->data = e;
		s->next = L;
		L=s;
		return true;
	}
	Node* p = L;
	int j = 1;//初始节点，指向第1个节点（不带头结点）
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool InsertNextNode(Node* p, Elemtype e) {//在给定节点后插入新节点
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL) return false;//某些情况下分配失败，比如内存不足
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListInsert1(Node* L, int i, Elemtype e) {//按位序插入：在给定i前插入节点,有后插操作后可以对第i-1节点实现后插
	if (i < 1) return false;
	Node* p = L;
	int j = 1;//初始节点，指向第1个节点（不带头结点）
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	return InsertNextNode(p, e);
}
bool InsertPriorNode(Node* p, Elemtype e) {//指定节点前插，可以在指定节点后插，然后交换两个节点数据即可
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL) return false;
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;
	return true;
}
bool ListDelete(Node* L, int i, Elemtype* e) {//删除指定位序的节点,返还元素值
	if (i < 1) return false;
	Node* p;
	int j = 1;//不带头结点，指向1， 带头结点指向0
	p = L;
	while (p != NULL && j < i - 1) {//p移动同时需要j来计数
		p = p->next;
		j++;
	}
	if (p == NULL) return false;//p空
	if (p->next == NULL) return false;//p-1空
	//此时p指向第i-1个节点
	Node* q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return true;
}
bool DeleteNode(Node* p) {//删除指定节点
	if (p == NULL) return false;
	Node* q = p->next;//q在p后
	p->data = q->data;//先交换p和q的data，再删除p的后继节点，从而完成对指定节点p的删除
	p->next = q->next;
	free(q);
	return true;
}
Node* GetElem(Node* L, int i) {//按位序查找，返回第i个节点
	if (i < 0) return NULL;//如果是节点类型，但是找不到节点，则返回一个NULL指针等价于空节点
	Node* p;
	int j = 1;//不带头结点，从下标1开始
	p = L;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}
Node* LocateElem(Node* L, Elemtype e) {//按值查找，在表L中找到具有给定关键字的元素，返回节点
	Node* p = L;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;
}
int Length(Node* L) {//求链表长度
	int len = 0;
	Node* p = L;
	while (p != NULL) {
		p = p->next;
		len++;
	}
	return len;
}
Node* Reverse(Node* L) {//逆置链表，不带头结点.
	Node* p, * q;//如果不初始化就是指针，初始化就代表节点
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	p = L;//p指向第一个节点
	while (p!= NULL) {
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
	return head->next ;
}
int main() {
	Node* L = CreatHeadInsert();
	showList(L);
	Node* H = CreatTailInsert();
	showList(H);
	ListInsert(L, 3, 9);
	showList(L);
	ListInsert1(H, 3, 9);
	showList(H);
	printf("%d\n", Length(L));
	Node* K = Reverse(H);
	showList(K);
	return 0;
}