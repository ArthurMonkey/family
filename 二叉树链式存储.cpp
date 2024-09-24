#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//������
	struct BiTnode* lchild, * rchild;//���Һ���ָ��
}BiTnode,*BiTree;
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

//��������ĵݹ��㷨
// 
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
//��������ķǵݹ��㷨
//
//��������

/*
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
		DeQueue(Q, &p);
		visit(p);
		if (p->lchild != NULL) EnQueue(Q, p->lchild);
		if (p->rchild != NULL) EnQueue(Q, p->rchild);
	}
}
*/
//�������д���������
void CreateTreePreOrder(BiTree* T) {//����ָ��
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
	if (root == NULL) return 0;//���ڵ�δ����return0
	if (root != NULL && k == 1) return 1;//ֻ�и��ڵ㷵��1��
	return BinaryTreeLevelSize(root->lchild, k - 1) + BinaryTreeLevelSize(root->rchild, k - 1);
}
int BinaryTreeHeight(BiTnode* root) {//��������ĸ߶�
	if (root == NULL) return 0;
	int left = 1 + BinaryTreeHeight(root->lchild);
	int right = 1 + BinaryTreeHeight(root->rchild);
	return left > right ? left : right;
}
bool BinaryTreeSearch(BiTnode* root, Elemtype e) {//�ڶ������в���ֵΪe�Ľڵ�,���ز��ҽ��
	if (root == NULL) return false;
	if (root->data == e) return true;
	return BinaryTreeSearch(root->lchild, e) || BinaryTreeSearch(root->rchild, e);
}
void DestoryBinaryTree(BiTnode* T) {//���ٶ�����
	if (T == NULL) return;
	DestoryBinaryTree(T->lchild);
	DestoryBinaryTree(T->rchild);
	free(T);
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
	printf("%d\n", root->lchild->data);
	//�����������������
	//1 2 9 3 9 9 4 9 9  ����˳��
	//�����������������
	//9 2 9 3 9 1 9 4 9
	BiTnode* root1 = (BiTnode*)malloc(sizeof(BiTnode));
	CreateTreePreOrder(&root1);
	printf("\n������������\n");
	PreOrder(root1);
	printf("\n������������\n");
	InOrder(root1);
	printf("\n������������\n");
	PostOrder(root1);
	printf("�������ڵ��ܸ���:%d\n", BinaryTreeSize(root1));
	printf("�������ڵ��ܸ���:%d\n", BinaryTreeSizePreOrder(root1));//�ݹ����ʱҲ���Լ�������num++����visit֮�󼴿�
	printf("������Ҷ�ӽڵ��ܸ���:%d\n", BinaryTreeLeafnum(root1));//3, 4��Ҷ�ӽڵ�
	printf("�������ڶ���ڵ����:%d\n", BinaryTreeLevelSize(root1, 2));
	printf("���������߶�:%d\n", BinaryTreeHeight(root1));
	printf("�������в���ֵΪ5�ĵ㣬�������Ϊ1��������Ϊ0�������:%d\n", BinaryTreeSearch(root1,5));
//	DestoryBinaryTree(root);

	return 0;


}