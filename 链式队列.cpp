#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct LinkNode {//���нڵ�
	struct LinkNode* next;
	Elemtype data;
}LinkNode;
typedef struct {//����ָ�룬���Ƕ��нڵ㵫�ǲ���ֵ
	LinkNode* front, * rear;
}LinkQueue;
//��ʼ��
void InitQueue(LinkQueue& Q) {//��ͷ�ڵ�
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));//front rear��ָ��ͷ���
	Q.front->next = NULL;//����rear����
}
//�п�
bool IsEmpty(LinkQueue Q) {
	if (Q.rear = Q.front) return true;
	else return false;
}
//��Ӳ���
void EnQueue(LinkQueue& Q, Elemtype e) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = NULL;//s��Ϊ���һ���ڵ�ָ��NULL
	if (Q.front = NULL) {//��һ��Ԫ�����ʱ��Ҫ�ر���
		Q.front = s;//
		Q.rear = s;
	}
	else {
		Q.rear->next = s;//�½ڵ����rear���ƶ�rear
		Q.rear = s;
	}
}
//���Ӳ���,��ͷԪ�س���
bool DeQueue(LinkQueue& Q, Elemtype& e) {
	if (Q.front = Q.rear) return false;//�ն�
	LinkNode* p = Q.front->next;//pָ��ͷ������һ���ڵ�,��Զ��ͷ��㣬��front->next��Զָ��ӵĵ�һ���ڵ�
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear = p) {//��������һ���ڵ���ӣ�Ҫ�����޸�front=rear
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