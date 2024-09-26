#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int	Elemtype;
typedef struct AVLnode {
	Elemtype data;
	int heigh;//�߶�
	struct AVLnode* lchild;
	struct AVLnode* rchild;
}AVLnode, *AVLtree;

//��ȡ�߶�
int height(AVLnode* T) {
	if (T == NULL) return 0;
	else return T->heigh;
}

//����ֵ
int abs(int a, int b) {
	return a - b > 0 ? a - b : b - a;
}
//����һ���ڵ�
AVLnode* Createnode(Elemtype data) {
	AVLnode* s = (AVLnode*)malloc(sizeof(AVLnode));
	if (s == NULL) return NULL;
	s->data = data;
	s->heigh = 0;
	s->lchild = NULL;
	s->rchild = NULL;
	return s;
}
//����ƽ�������---���򲹳�


//�������ݽڵ�
AVLnode* Searchnode(AVLnode* T, Elemtype e) {
	if (T == NULL) return NULL;
	if (e == T->data) return T;
	else if (e < T->data) Searchnode(T->lchild, e);
	else Searchnode(T->rchild, e);
}

//�ж�һ�����ǲ���ƽ�������
//˼·1���ݹ鷨,�жϸ߶Ȳ�
bool JudgeAVL(AVLnode* T) {
	if (T == NULL) exit(0);
	if (T->lchild->data > T->data || T->rchild->data < T->data) return false;
	if (abs(height(T->lchild) - height(T->rchild)) > 1) return false;
	else return true;
	return JudgeAVL(T->lchild) && JudgeAVL(T->rchild);
}
//˼·2����balance��Ϊƽ���ǣ�ƽ�ⷵ��1��ƽ�ⷵ��0��hΪ�߶ȣ��жϸ߶�
void JudgeAVL1(AVLtree T, int& balance, int& h) {
	int bl = 0, br = 0, hl = 0, hr = 0;//����������ƽ���Ǻ͸߶�
	if (T == NULL) {//�п���
		h = 0;
		balance = 1;
	}
	else if (T->lchild == NULL && T->rchild == NULL) {//��ֻ�и��ڵ�
		h = 1;
		balance = 1;
	}
	else {
		JudgeAVL1(T->lchild, bl, hl);
		JudgeAVL1(T->rchild, br, hr);
		h = (hl > hr ? hl : hr) + 1;
		if (abs(hl - hr) < 2) {//������������߶Ȳ�С��2�������������Ƿ�ƽ��
			balance = bl && br;//�߼��룬������������ƽ��ʱ������ƽ��
		}
		else {
			balance = 0;
		}
	}
}