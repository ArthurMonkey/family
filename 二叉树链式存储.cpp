#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//数据域
	struct BiTnode* lchild, * rchild;//左右孩子指针
}BiTnode;
//层序遍历需要辅助队列
typedef struct LinkNode {//队列节点
	struct LinkNode* next;
	BiTnode* data;//此处为 BiTnode节点
}LinkNode;
typedef struct {//队列指针，就是队列节点但是不赋值
	LinkNode* front, * rear;
}LinkQueue;


BiTnode* Create(BiTnode* root) {//插入根节点
	root = (BiTnode*)malloc(sizeof(BiTnode));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;
	return root;
}
BiTnode* newnode(int v) {//生成一个新节点，节点值为v
	BiTnode* p = (BiTnode*)malloc(sizeof(BiTnode));
	p->data = v;
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}
void visit(BiTnode* p) {//访问节点，打印出data
	printf("%d ", p->data);
}
//先序，中序，后序遍历子树
void PreOrder(BiTnode* root) {
	if (root != NULL) {//root=NULL代表子树为空，如果存了data和lchild，rchild则代表子树不空
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

//层序遍历需要辅助队列和EnQueue和DeQueue
//
//
//初始化
void InitQueue(LinkQueue& Q) {//带头节点
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));//front rear均指向头结点
	Q.front->next = NULL;//不对rear操作
}
void EnQueue(LinkQueue& Q, BiTnode* e) {
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
bool DeQueue(LinkQueue& Q, BiTnode* e) {
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
bool IsEmpty(LinkQueue Q) {
	if (Q.rear = Q.front) return true;
	else return false;
}
void LevelOrder(BiTnode* T) {//层序遍历
	LinkQueue Q;
	InitQueue(Q);
	BiTnode* p;
	EnQueue(Q, T);//根节点入队
	while (IsEmpty(Q) !=false) {
		DeQueue(Q, p);
		visit(p);
		if (p->lchild != NULL) EnQueue(Q, p->lchild);
		if (p->rchild != NULL) EnQueue(Q, p->rchild);
	}
}
int main() {
	//定义一个根节点==定义一颗空树
	BiTnode* root = NULL;
	//插入根节点（把数，左右指针插入）
	root = (BiTnode*)malloc(sizeof(BiTnode));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;
	//插入新节点
	root->lchild = newnode(2);
	printf("%d", root->lchild->data);
	//
	return 0;
}