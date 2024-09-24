#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//数据域
	struct BiTnode* lchild, * rchild;//左右孩子指针
}BiTnode,*BiTree;
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

//三序遍历的递归算法
// 
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
//三序遍历的非递归算法
//
//先序序列

/*
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
		DeQueue(Q, &p);
		visit(p);
		if (p->lchild != NULL) EnQueue(Q, p->lchild);
		if (p->rchild != NULL) EnQueue(Q, p->rchild);
	}
}
*/
//先序序列创建二叉树
void CreateTreePreOrder(BiTree* T) {//二级指针
	int temp;
	scanf_s("%d", &temp);
	if (temp == 9) {
		*T = NULL;
	}
	else {
		*T = (BiTnode*)malloc(sizeof(BiTnode));
		(*T)->data = temp;
		CreateTreePreOrder(&(*T)->lchild);
		CreateTreePreOrder(&(*T)->rchild);
	}
}
void CreateTreeInOrder(BiTree* T) {
	int temp;
	scanf_s("%d", &temp);
	if (temp == 9) {
		*T = NULL;
	}
	else {
		*T = (BiTnode*)malloc(sizeof(BiTnode));
		CreateTreeInOrder(&(*T)->lchild);
		(*T)->data = temp;
		CreateTreeInOrder(&(*T)->rchild);
	}
}
int BinaryTreeSize(BiTnode* root) {
	if (root == NULL) return 0;
	return BinaryTreeSize(root->lchild)+BinaryTreeSize(root->rchild) + 1;
}
void PreOrder1(BiTnode* root, int* num) {
	if (root != NULL) {
		visit(root);
		(*num)++;
		PreOrder1(root->lchild, num);
		PreOrder1(root->rchild, num);
	}
}
int BinaryTreeSizePreOrder(BiTnode* root) {
	int num = 0;
	if (root == NULL) return num;
	else {
		PreOrder1(root, &num);
	}
	return num;
}
int BinaryTreeLeafnum(BiTnode* root) {
	if (root == NULL) return 0;
	else if (root->lchild == NULL && root->rchild == NULL) return 1;
	else return BinaryTreeLeafnum(root->lchild) + BinaryTreeLeafnum(root->rchild);
}
int BinaryTreeLevelSize(BiTnode* root, int k) {
	if (root == NULL) return 0;//根节点未空则return0
	if (root != NULL && k == 1) return 1;//只有根节点返回1层
	return BinaryTreeLevelSize(root->lchild, k - 1) + BinaryTreeLevelSize(root->rchild, k - 1);
}
int BinaryTreeHeight(BiTnode* root) {//求二叉树的高度
	if (root == NULL) return 0;
	int left = 1 + BinaryTreeHeight(root->lchild);
	int right = 1 + BinaryTreeHeight(root->rchild);
	return left > right ? left : right;
}
bool BinaryTreeSearch(BiTnode* root, Elemtype e) {//在二叉树中查找值为e的节点,返回查找结果
	if (root == NULL) return false;
	if (root->data == e) return true;
	return BinaryTreeSearch(root->lchild, e) || BinaryTreeSearch(root->rchild, e);
}
void DestoryBinaryTree(BiTnode* T) {//销毁二叉树
	if (T == NULL) return;
	DestoryBinaryTree(T->lchild);
	DestoryBinaryTree(T->rchild);
	free(T);
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
	printf("%d\n", root->lchild->data);
	//先序遍历创建二叉树
	//1 2 9 3 9 9 4 9 9  输入顺序
	//中序遍历建立二叉树
	//9 2 9 3 9 1 9 4 9
	BiTnode* root1 = (BiTnode*)malloc(sizeof(BiTnode));
	CreateTreePreOrder(&root1);
	printf("\n先序遍历结果：\n");
	PreOrder(root1);
	printf("\n中序遍历结果：\n");
	InOrder(root1);
	printf("\n后序遍历结果：\n");
	PostOrder(root1);
	printf("二叉树节点总个数:%d\n", BinaryTreeSize(root1));
	printf("二叉树节点总个数:%d\n", BinaryTreeSizePreOrder(root1));//递归遍历时也可以计数，把num++放在visit之后即可
	printf("二叉树叶子节点总个数:%d\n", BinaryTreeLeafnum(root1));//3, 4是叶子节点
	printf("二叉树第二层节点个数:%d\n", BinaryTreeLevelSize(root1, 2));
	printf("二叉树最大高度:%d\n", BinaryTreeHeight(root1));
	printf("二叉树中查找值为5的点，如果存在为1，不存在为0，结果是:%d\n", BinaryTreeSearch(root1,5));
//	DestoryBinaryTree(root);

	return 0;


}