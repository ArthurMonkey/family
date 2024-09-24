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
递归查找二叉排序树T中是否存在key
指针f指向T的双亲，其初始调用值为NULL
若查找成功，则指针p指向该数据元素结点，并返回TRUE
否则指针p指向查找路径上访问的最后一个结点并返回FALSE
*/
bool SearchBST(BSTree T, int key, BSTree f, BSTree* p) {
	if (T == NULL) {
		*p = f;
		return false;
	}
	else if (T->data == key) {//查找成功
		*p = T;
		return true;
	}
	else if (key < T->data) {
		return SearchBST(T->lchild, key, T, p);//往左子树查找
	}
	else {
		return SearchBST(T->rchild, key, T, p);
	}
}

bool InsertBST(BSTree* T, int key) {
	BSTree p, s;
	if (SearchBST(*T, key, NULL, &p) == NULL) {//查找失败，key不存在BST中
		s = (BSTnode*)malloc(sizeof(BSTnode));
		s->data = key;
		s->lchild = NULL;
		s->rchild = NULL;
		if (p == NULL) {//如果查到p节点为空
			*T = s;//插入s为新的根节点
		}
		else if (key < p->data) {//左子树插入节点s
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
void visit(BSTnode* p) {//访问节点，打印出data
	printf("%d ", p->data);
}
void PreOrder(BSTnode* root) {
	if (root != NULL) {//root=NULL代表子树为空，如果存了data和lchild，rchild则代表子树不空
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
若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点，
并返回TRUE;否则返回FALSE
*/
/*从二叉排序树中删除结点p，并重接它的左或右子树。*/
//删除节点暂存，有问题
bool Delete(BSTnode* p) {
	//在二叉排序树中删除结点p, 并重新连接它的左右子树
	BSTnode* q, * s;
	//1.p为叶子结点
	if (p->lchild == NULL && p->rchild == NULL) {
		free(p);
	}
	//2.1 p左子树为空, 重接右子树
	else if (p->lchild == NULL) {
		q = p;
		p = p->rchild; 
		free(q);
	}
	//2.2 p右子树为空, 重接左子树
	else if (p->rchild == NULL) {
		q = p;
		p = p->lchild;
		free(q);
	}
	//3. p左右子树均不为空
	else {
		q = p;
		s = p->rchild; //找到p的右子树的最左端（中序直接后继）
		while (s->lchild != NULL) {
			q = s;
			s = s->lchild;
		}
		p->data = s->data;

		if (q != p) //判断是否执行上述while循环
			q->lchild = s->rchild; //执行上述while循环，重接*q的左子树
		else
			q->rchild = s->rchild; //未执行上述while循环，重接*q的右子树，对于这个情况，可以参考代码后给出的示例图
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
	printf("%d\n", SearchBST(T, 47, NULL, &p));//查找成功
	InOrder(T);
	printf("\n%d\n", DeleteBST(T, 47));//47可以成功删除，其他暂时有问题
	InOrder(T);
	return 0;
}
