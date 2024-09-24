#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BSTnode {
	Elemtype data;
	struct BSTnode* lchild, * rchild;
}BSTnode,*BSTree;

/*
�ݹ���Ҷ���������T���Ƿ����key
ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
�����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE
����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE
*/
bool SearchBST(BSTree T, int key, BSTree f, BSTree* p) {
	if (T == NULL) {
		*p = f;
		return false;
	}
	else if (T->data == key) {//���ҳɹ�
		*p = T;
		return true;
	}
	else if (key < T->data) {
		return SearchBST(T->lchild, key, T, p);//������������
	}
	else {
		return SearchBST(T->rchild, key, T, p);
	}
}

bool InsertBST(BSTree* T, int key) {
	BSTree p, s;
	if (SearchBST(*T, key, NULL, &p) == NULL) {//����ʧ�ܣ�key������BST��
		s = (BSTnode*)malloc(sizeof(BSTnode));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (p == NULL) {//����鵽p�ڵ�Ϊ��
			*T = s;//����sΪ�µĸ��ڵ�
		}
		else if (key < p->data) {//����������ڵ�s
			p->lchild = s;
		}
		else {
			p->rchild = s;
		}
		return true;
	}
	else {
		return false;
	}
}
void visit(BSTnode* p) {//���ʽڵ㣬��ӡ��data
	printf("%d ", p->data);
}
void PreOrder(BSTnode* root) {
	if (root != NULL) {//root=NULL��������Ϊ�գ��������data��lchild��rchild�������������
		visit(root);
		PreOrder(root->lchild);
		PreOrder(root->rchild);
	}
}
void InOrder(BSTnode* root) {
	if (root != NULL) {
		InOrder(root->lchild);
		visit(root);
		InOrder(root->rchild);
	}
}
/*
������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬
������TRUE;���򷵻�FALSE
*/
/*�Ӷ�����������ɾ�����p�����ؽ����������������*/
//ɾ���ڵ��ݴ棬������
bool Delete(BSTnode* p) {
	//�ڶ�����������ɾ�����p, ����������������������
	BSTnode* q, * s;
	//1.pΪҶ�ӽ��
	if (p->lchild == NULL && p->rchild == NULL) {
		free(p);
	}
	//2.1 p������Ϊ��, �ؽ�������
	else if (p->lchild == NULL) {
		q = p;
		p = p->rchild; 
		free(q);
	}
	//2.2 p������Ϊ��, �ؽ�������
	else if (p->rchild == NULL) {
		q = p;
		p = p->lchild;
		free(q);
	}
	//3. p������������Ϊ��
	else {
		q = p;
		s = p->rchild; //�ҵ�p��������������ˣ�����ֱ�Ӻ�̣�
		while (s->lchild != NULL) {
			q = s;
			s = s->lchild;
		}
		p->data = s->data;

		if (q != p) //�ж��Ƿ�ִ������whileѭ��
			q->lchild = s->rchild; //ִ������whileѭ�����ؽ�*q��������
		else
			q->rchild = s->rchild; //δִ������whileѭ�����ؽ�*q�������������������������Բο�����������ʾ��ͼ
		free(s);
	}
	return true;
}
bool DeleteBST(BSTnode* root, int x) {
	if (root == NULL) {
		return false;
	}
	else {
		if (x == root->data)
			return Delete(root);
		else if (x < root->data)
			return DeleteBST(root->lchild, x);
		else
			return DeleteBST(root->rchild, x);
	}
}

int main() {
	int i;
	int a[10] = { 62, 88, 58, 47, 35, 73, 51, 99, 37, 93 };
	BSTree T = NULL;
	for (i = 0; i < 10; i++) {
		InsertBST(&T, a[i]);
	}
	BSTree p;
	printf("%d\n", SearchBST(T, 47, NULL, &p));//���ҳɹ�
	InOrder(T);
	printf("\n%d\n", DeleteBST(T, 47));//47���Գɹ�ɾ����������ʱ������
	InOrder(T);
	return 0;
}
