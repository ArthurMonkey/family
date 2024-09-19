#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct LinkNode {//队列节点
	struct LinkNode* next;
	Elemtype data;
}LinkNode;
typedef struct {//队列指针，就是队列节点但是不赋值
	LinkNode* front, * rear;
}LinkQueue;
//初始化
void InitQueue(LinkQueue& Q) {//带头节点
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));//front rear均指向头结点
	Q.front->next = NULL;//不对rear操作
}
//判空
bool IsEmpty(LinkQueue Q) {
	if (Q.rear = Q.front) return true;
	else return false;
}
//入队操作
void EnQueue(LinkQueue& Q, Elemtype e) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;//s作为最后一个节点指向NULL
	if (Q.front = NULL) {//第一个元素入队时需要特别处理
		Q.front = s;//
		Q.rear = s;
	}
	else {
		Q.rear->next = s;//新节点插入rear后，移动rear
		Q.rear = s;
	}
}
//出队操作,队头元素出队
bool DeQueue(LinkQueue& Q, Elemtype& e) {
	if (Q.front = Q.rear) return false;//空队
	LinkNode* p = Q.front->next;//p指向头结点的下一个节点,永远带头结点，则front->next永远指向队的第一个节点
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear = p) {//如果是最后一个节点出队，要单独修改front=rear
		Q.rear = Q.front;
	}
	free(p);
	return true;
}

int main() {
	LinkQueue Q;
	InitQueue(Q);
	int e = 3;
	DeQueue(Q, e);
	printf("%d ", IsEmpty(Q));

	return 0;
}