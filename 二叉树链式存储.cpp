#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//������
	struct BiTnode* lchild, * rchild;//���Һ���ָ��
}BiTnode;
//���������Ҫ��������
typedef struct LinkNode {//���нڵ�
	struct LinkNode* next;
	BiTnode* data;//�˴�Ϊ BiTnode�ڵ�
}LinkNode;
typedef struct {//����ָ�룬���Ƕ��нڵ㵫�ǲ���ֵ
	LinkNode* front, * rear;
}LinkQueue;


BiTnode* Create(BiTnode* root) {//������ڵ�
	root = (BiTnode*)malloc(sizeof(BiTnode));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;
	return root;
}
BiTnode* newnode(int v) {//����һ���½ڵ㣬�ڵ�ֵΪv
	BiTnode* p = (BiTnode*)malloc(sizeof(BiTnode));
	p->data = v;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}
void visit(BiTnode* p) {//���ʽڵ㣬��ӡ��data
	printf("%d ", p->data);
}
//�������򣬺����������
void PreOrder(BiTnode* root) {
	if (root != NULL) {//root=NULL��������Ϊ�գ��������data��lchild��rchild�������������
		visit(root);
		PreOrder(root->lchild);
		PreOrder(root->rchild);
	}
}
void InOrder(BiTnode* root) {
	if (root != NULL) {
		InOrder(root->lchild);
		visit(root);
		InOrder(root->rchild);
	}
}
void PostOrder(BiTnode* root) {
	if (root != NULL) {
		PostOrder(root->lchild);
		PostOrder(root->rchild);
		visit(root);
	}
}

//���������Ҫ�������к�EnQueue��DeQueue
//
//
//��ʼ��
void InitQueue(LinkQueue& Q) {//��ͷ�ڵ�
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));//front rear��ָ��ͷ���
	Q.front->next = NULL;//����rear����
}
void EnQueue(LinkQueue& Q, BiTnode* e) {
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
bool DeQueue(LinkQueue& Q, BiTnode* e) {
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
bool IsEmpty(LinkQueue Q) {
	if (Q.rear = Q.front) return true;
	else return false;
}
void LevelOrder(BiTnode* T) {//�������
	LinkQueue Q;
	InitQueue(Q);
	BiTnode* p;
	EnQueue(Q, T);//���ڵ����
	while (IsEmpty(Q) !=false) {
		DeQueue(Q, p);
		visit(p);
		if (p->lchild != NULL) EnQueue(Q, p->lchild);
		if (p->rchild != NULL) EnQueue(Q, p->rchild);
	}
}
int main() {
	//����һ�����ڵ�==����һ�ſ���
	BiTnode* root = NULL;
	//������ڵ㣨����������ָ����룩
	root = (BiTnode*)malloc(sizeof(BiTnode));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;
	//�����½ڵ�
	root->lchild = newnode(2);
	printf("%d", root->lchild->data);
	//
	return 0;
}