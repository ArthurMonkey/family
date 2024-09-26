#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int	Elemtype;
typedef struct AVLnode {
	Elemtype data;
	int heigh;//高度
	struct AVLnode* lchild;
	struct AVLnode* rchild;
}AVLnode, *AVLtree;

//获取高度
int height(AVLnode* T) {
	if (T == NULL) return 0;
	else return T->heigh;
}

//绝对值
int abs(int a, int b) {
	return a - b > 0 ? a - b : b - a;
}
//创建一个节点
AVLnode* Createnode(Elemtype data) {
	AVLnode* s = (AVLnode*)malloc(sizeof(AVLnode));
	if (s == NULL) return NULL;
	s->data = data;
	s->heigh = 0;
	s->lchild = NULL;
	s->rchild = NULL;
	return s;
}
//创建平衡二叉树---后序补充


//查找数据节点
AVLnode* Searchnode(AVLnode* T, Elemtype e) {
	if (T == NULL) return NULL;
	if (e == T->data) return T;
	else if (e < T->data) Searchnode(T->lchild, e);
	else Searchnode(T->rchild, e);
}

//判断一棵树是不是平衡二叉树
//思路1：递归法,判断高度差
bool JudgeAVL(AVLnode* T) {
	if (T == NULL) exit(0);
	if (T->lchild->data > T->data || T->rchild->data < T->data) return false;
	if (abs(height(T->lchild) - height(T->rchild)) > 1) return false;
	else return true;
	return JudgeAVL(T->lchild) && JudgeAVL(T->rchild);
}
//思路2：用balance作为平衡标记，平衡返回1不平衡返回0，h为高度，判断高度
void JudgeAVL1(AVLtree T, int& balance, int& h) {
	int bl = 0, br = 0, hl = 0, hr = 0;//左右子树的平衡标记和高度
	if (T == NULL) {//判空树
		h = 0;
		balance = 1;
	}
	else if (T->lchild == NULL && T->rchild == NULL) {//判只有根节点
		h = 1;
		balance = 1;
	}
	else {
		JudgeAVL1(T->lchild, bl, hl);
		JudgeAVL1(T->rchild, br, hr);
		h = (hl > hr ? hl : hr) + 1;
		if (abs(hl - hr) < 2) {//如果左右子树高度差小于2，则看左右子树是否都平衡
			balance = bl && br;//逻辑与，当两个子树都平衡时二叉树平衡
		}
		else {
			balance = 0;
		}
	}
}