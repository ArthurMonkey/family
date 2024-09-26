#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//������
	struct BiTnode* lchild, * rchild;//���Һ���ָ��
}BiTnode, * BiTree;
#define ERROR 0
#define OK 1
#define maxsize 20
typedef int Elemtype;
typedef int Status;

void visit(BiTnode* p) {//���ʽڵ㣬��ӡ��data
	printf("%d ", p->data);
}
//ջ�Ķ���ͻ�������
typedef struct {
	Elemtype data[maxsize];
	int top;    //����ջ��ָ��
}SqStack;

void InitStack(SqStack* S) {
	S->top = -1;    //��ʼ��ջ��ָ��
}

bool StackEmpty(SqStack S) {
	if (S.top == -1) {
		return true;    //ջ��
	}
	else {
		return false;   //����
	}
}

/*����Ԫ��eΪ�µ�ջ��Ԫ��*/
Status Push(SqStack* S, Elemtype e) {
	//��ջ
	if (S->top == maxsize - 1) {
		return ERROR;
	}
	S->top++;   //ջ��ָ������һ
	S->data[S->top] = e;    //���²���Ԫ�ظ�ֵ��ջ���ռ�
	return OK;
}
Status Push1(SqStack* S, BiTnode* e) {
	//��ջ
	if (S->top == maxsize - 1) {
		return ERROR;
	}
	S->top++;   //ջ��ָ������һ
	S->data[S->top] = (*e).data;    //���²���Ԫ�ظ�ֵ��ջ���ռ�
	return OK;
}

/*��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR*/
Status Pop(SqStack* S, Elemtype* e) {
	if (S->top == -1) {
		return ERROR;
	}
	*e = S->data[S->top];   //��Ҫɾ����ջ��Ԫ�ظ�ֵ��e
	S->top--;   //ջ��ָ���һ
	return OK;
}
Status Pop1(SqStack* S, BiTnode* e) {
	if (S->top == -1) {
		return ERROR;
	}
	(*e).data = S->data[S->top];   //��Ҫɾ����ջ��Ԫ�ظ�ֵ��e
	S->top--;   //ջ��ָ���һ
	return OK;
}
/*��ջ��Ԫ��*/
Status GetTop(SqStack S, Elemtype* e) {
	if (S.top == -1) {   //ջ��
		return ERROR;
	}
	*e = S.data[S.top];   //��¼ջ��Ԫ��
	return OK;
}
Status GetTop1(SqStack S, BiTnode* e) {
	if (S.top == -1) {   //ջ��
		return ERROR;
	}
	(*e).data = S.data[S.top];   //��¼ջ��Ԫ��
	return OK;
}
//
// 
// 
// 
//��ʮ����
//��д��������������ķǵݹ��㷨
//gettop1��push1��pop1���ȶ���Ϊ�˷��ϵ����﷨Ҫ����д��
void PostOrderStack(BiTree T) {
	SqStack* S;
	InitStack(S);
	BiTnode* p = T;
	BiTnode* r = NULL;
	while (p != NULL || StackEmpty(*S) == false) {//ջ����  true�����
		if (p != NULL) {
			Push1(S, p);//�˴�Push���p�Ĳ������͸��ļ���
			p = p->lchild;
		}
		else {
			GetTop1(*S, p);//
			if (p->rchild != NULL && p->rchild != r) {
				p = p->rchild;
				Push1(S, p);
				p = p->lchild;
			}
			else {
				Pop1(S, p);
				visit(p);
				r = p;
				p = NULL;
			}
		}
	}
}


//��ʮ����
//���������������¶��ϡ����ҵ���Ĳ�α����㷨
//˼·�����нڵ��ڲ�α����ﲻ��visit���Ƕ���ջ�������пջ��������ٴ�ջ��ȫ������
void LeverOrderReverse(BiTree root) {
	Stack S;
	Queue Q;
	BiTnode* p;
	if (root != NULL) {
		InitStack(S);
		InitQueue(Q);
		EnQueue(Q, root);
		while (IsEmpty(Q) == false) {
			DeQueue(Q, p);
			Push(S, p);
			if (p->lchild != NULL) EnQueue(Q, p->lchild);
			if (p->rchild != NULL) EnQueue(Q, p->rchild);
		}
		while (IsEmpty(S) == false) {
			Pop(S, p);
			visit(p);
		}
	}

}

//�ڶ�ʮ��
//���������ö�������洢����Ʒǵݹ��㷨�����ĸ߶�
//˼·����˳���������ƣ�����front��rear����������last==rear�жϵ�ǰ���Ƿ�����level��¼����
int BiTreeDepth(BiTree T) {
	if (T == NULL) return 0;
	int front = -1, rear = -1;
	int last = 0, level = 0;//last����ÿһ������һ���ڵ�rear��last==rear������ʵ��������һ���ڵ㣬��level+1�� ��ʼ��ֻ��һ�����ڵ�
	//����front��ʼʱ-1��last��ʼʱ0
	BiTree Q[maxsize];//����Q,Ԫ���Ƕ������ڵ�ָ���������㹻��
	Q[++rear] = T;//���ڵ����
	BiTree p;
	while (front < rear) {
		p = Q[++front];//����
		if (p->lchild != NULL) Q[++rear] = p->lchild;
		if (p->rchild != NULL) Q[++rear] = p->rchild;
		if (front == last) {
			level++;
			last = rear;//����last
		}
	}
	return level;
}

//�ڶ�ʮһ��
//����������������洢���ж������������Ƿ�Ϊ��ȫ������
//˼�룺���ò�α�������������սڵ�����Ƿ��зǿսڵ㣬�����������ȫ������
bool IsComplete(BiTree T) {
	InitQueue(Q);
	BiTnode* p;
	if (T == NULL) {//��������ȫ������
		return true;
	}
	EnQueue(Q, T);//�սڵ�Ҳ�������
	while (IsEmpty(Q) == false) {
		DeQueue(Q, p);
		if (p != NULL) {
			EnQueue(Q, p->lchild);//���Խ��սڵ�Ҳ�������������
			EnQueue(Q, p->rchild);
		}
		else {
			while (IsEmpty(Q) == false) {
				DeQueue(Q, p);
				if (p != NULL) return false;//����нڵ㲻�գ�������ȫ������
			}
		}
	}
	return true;
}

//�ڶ�ʮ����
//�������Զ�������洢��������ɾ����xΪֵ�ĸ��ڵ����������
//˼�룺ɾ��Ԫ��ֵΪx�Ľڵ㣬��ɾ������������ɾ�����ڵ�����ɾ�������ú������free���� ɾ���ڵ�Ҫ�����ڵ�����������ÿշ���Ұָ������
//�ò�����������ҵ��丸�ڵ�,��˳����и����������
void DeleteX(BiTree p) {//ɾ��ֵΪx�Ľڵ�
	if (p != NULL) {
		DeleteX(p->lchild);
		DeleteX(p->rchild);
		free(p);
	}
}
void Search(BiTree T, Elemtype x) {
	BiTree Q[maxsize];//maxsize�㹻�Ĵ�
	BiTnode* p;
	if (T != NULL) {
		if (T->data == x) {//���ڵ�ֵΪx��ɾ��������
			DeleteX(T);
			return;
		}
		InitQueue(Q);
		EnQueue(Q, T);
		while (IsEmpty(Q) != NULL) {
			DeQueue(Q, p);
			if (p->lchild != NULL) {
				if (p->lchild->data == x) {
					DeleteX(p->lchild);
					p->lchild = NULL;//���ڵ������ָ����ΪNULL
				}
				else {//���ֵ��Ϊx
					EnQueue(Q, p->lchild);//���������
				}
			}
			if (p->rchild != NULL) {
				if (p->rchild->data == x) {
					DeleteX(p->rchild);
					p->rchild = NULL;
				}
				else {
					EnQueue(Q, p->rchild);
				}
			}
		}
	}
}

//�ڶ�ʮ����
//�������ڵ�ṹΪ��llink,inof,rlink),rootָ��ö��������ڵ��ָ��,p��q�ֱ�Ϊָ��ö����������������ڵ��ָ��
//��д�㷨Ancestor(root, p, q, r)�ҵ�p��q����Ĺ������Ƚڵ�r
//LSA��Ŀ
typedef struct {
	BiTree t;
	int tag;//tag=0��ʾ����Ů�ѱ����ʣ�tag=1��ʾ����Ů�ѱ�����
}stack;
stack s[], s1[];//s1Ϊ����ջ����ջ�����㹻��
BiTree Ancestor(BiTree root, BiTnode* p, BiTnode* q) {
	int top = 0;
	int top1;
	BiTnode* T = root;
	while (T != NULL || top > 0) {//ջ����������
		while (T != NULL) {
			s[++top].t = T;
			s[top].tag = 0;
			T = T->lchild;
		}//�����֧ȫ����ջ
		while (top != 0 && s[top].tag == 1) {//��ջ���ڵ����������������ʹ����ж�ջ���ڵ���p����q����p������ȼ��븨��ջ
			if (s[top].t == p) {
				for (int i = 1; i <= top; i++) {
					s1[i] = s[i];
					top1 = top;
				}
			}
			if (s[top].t == q) {//��q��ѵ�ǰq��ջ�е�Ԫ�غ�p�ĸ���ջ�е�Ԫ�رȽϣ�������ҵ������ͬ�ڵ���Ϊ�������Ƚڵ�
				for (int i = top; i > 0; i--) {
					for (int j = top1; j > 0; j--) {
						if (s1[j].t == s[i].t) {
							return s[i].t;
						}
					}
				}
			}
			top--;//��ջ
		}//while
		if (top != 0) {//��ת
			s[top].tag = 1;//��ʾ�ڵ��Ҳ���ʹ���������while���÷���������
			T = s[top].t->rchild;
		}
	}//while
	return NULL;//pq�޹�������
}

//�ݹ����LSA
void Ancestor1(BiTree root, BiTnode* p, BiTnode* q, BiTree* r) {
	//���root=�ջ���root����p����q����root���ǹ������Ƚڵ�
	if (root == NULL || root == p || root = q) {
		*r = root;
		return;
	}
	//�ݹ����������в��ҹ�������
	BiTnode* left = NULL;
	Ancestor1(root->lchild, p, q, &left);
	//�ݹ����������в��ҹ�������
	BiTnode* right = NULL;
	Ancestor1(root->rchild, p, q, &right);
	//��ָ��Ϊ�մ���pq������������
	if (left == NULL) {
		*r = right;
		return;
	}
	//��ָ��Ϊ�մ���pq������������
	if (right == NULL) {
		*r = left;
		return;
	}
	//left��right�����մ��� p��q�ֱ��������������ʱrootΪ��������
	*r = root;
	return;
}

//�ڶ�ʮ����
//������������ö�������洢�����һ���㷨��ǿն�����b�Ŀ�ȣ����нڵ���������һ��Ľڵ������
//˼·�����ò���������������鵱�����д洢����������¼last=frontʱ��rear��last�Ĵ�С�ĸ�����Ϊmax
int maxWeight(BiTree T) {
	BiTree Q[maxsize];
	int front = -1, rear = -1;
	int last = 0;
	int max = -1;
	Q[++rear] = T;
	BiTnode* p = T;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	while (front < rear) {
		p = Q[++front];//����
		if (p->lchild != NULL) {
			Q[++rear] = p->lchild;
		}
		if (p->rchild != NULL) {
			Q[++rear] = p->rchild;
		}
		if (front == last) {
			int temp = rear - last;
			if (temp > max) max = temp;
			last = rear;
		}
	}
	return max;
}

//�ڶ�ʮ����
//����㷨������������Ҷ�ڵ㰴�����ҵ�˳������һ����������ͷָ��Ϊhead������������������ʽ�洢
//����ʱ��Ҷ�ڵ����ָ��������ŵ�����ָ��
//˼·���������������ģ�棬���ҽڵ㣬�ҵ�Ҷ�ڵ������һ��Ҷ�ڵ�Ҫ��ͷ������Ҷ�ڵ㶼��preָ�봦���ɣ����һ��Ҷ�ڵ㵥������
//��Ȼʱ���������������ϵĽڵ����������ڵ㣬����Ҫ�������Ӻ�̽ڵ��ָ��Ϊrchild
typedef BiTree LinkedList;
LinkedList head, pre = NULL;
LinkedList InOrderCreate(BiTree T) {
	if (T != NULL) {
		InOrderCreate(T->lchild);
		if (T->lchild == NULL && T->rchild == NULL) {
			if (pre==NULL) {//��һ��Ҷ�ڵ�Ĵ���
				head = T;
				pre = head;
			}
			else {
				pre->rchild = T;
				pre = T;
			}
		}
		InOrderCreate(T->rchild);
		pre->rchild = NULL;//���һ��Ҷ�ڵ㵥������
	}
	return head;
}

//�ڶ�ʮ����
//д�����������������������ָ���ڵ��ں����ǰ�������㷨
//BST�����ҽڵ�
//����˼·����BST���������������н��еݹ����������ڵݹ����ģ��ģ�3������ж�Ŀ��ڵ�Ĵ���
//��ȷ˼·���ں�������������ڵ�p���Һ��ӣ����Һ��������ĺ�������ǰ����㣬���������û���к��������������ĺ�������ǰ�����
//���û�����Һ��ӣ�������������������ǰ�������Ƚڵ�f����f������Ů������Ů�����ں����µ�ǰ������fû������Ů����˳��ǰ��Ѱ��˫�׵�
//˫�壬ֱ��˫��������Ů��   ���p����������ĵ�һ���ڵ㣬��p������ͺ�������ǰ��
typedef struct BSTnode {
	Elemtype data;
	struct BSTnode* lchild, * rchild;
	int ltag, rtag;
}BSTnode, *BSTree;

BSTree InPostPre(BSTree T, BSTree p) {
	BSTree q;
	if (p->rtag == 0) {
		q = p->rchild;
	}
	else if (p->ltag == 0) {
		q = p->lchild;
	}
	else if (p->lchild == NULL) {//p���������еĵ�һ�ڵ���ǰ��
		q = NULL;
	}
	else {
		while (p->ltag == 1 && p->lchild != NULL) {//˳�����������ң�����ڵ�û�������������
			p = p->lchild;
		}
		if (p->ltag == 0) q = p->lchild;
		else q = NULL;//���е�֧����p��Ҷ�ӽڵ㣬�ѵ����ڵ��޺���ǰ��
	}
	return q;
}

//�ڶ�ʮ����
//������Ժ����ֵܱ�ʾ���洢��ɭ�ֵ�Ҷ�ӽ����
//�����ֵܱ�ʾ��
typedef struct CSNode {
	Elemtype data;
	struct CSNode* firstchild, * nextsibling;//sibling �ֵܽ��õ�Ӣ�ﵥ��
}CSNode, * CSTree;
//������Ժ����ֵܱ�ʾ���洢��ɭ�ֵ�Ҷ�ӽڵ���
int Leaves(CSTree T) {
	if (T == NULL) return 0;
	if (T->firstchild == NULL) {//���һ���ڵ�û�к��ӣ�������ɭ����϶���Ҷ�ӽڵ�
		return 1 + Leaves(T->nextsibling);//����Ҷ�ӽڵ�����ֵ������е�Ҷ�ӽڵ�����
	}
	else {
		return Leaves(T->firstchild) + Leaves(T->nextsibling);
	}
}


//�ڶ�ʮ����
//��д�㷨�ж������Ķ������Ƿ�Ϊ����������BST
//˼·�����������������������һ���������У������ж��Ƿ��������
typedef int KeyType;
KeyType predt = -32767;//predtΪȫ�ֱ���,���浱ǰ����ǰ������ֵ����ֵ-32767=-����
int JudgeBST(BiTree T) {
	int b1, b2;
	if (T == NULL) {//�ݹ�߽����Ҷ�ӽڵ���BST���Է���true
		return 1;
	}
	else {
		b1=JudgeBST(T->lchild);
		if (b1 == 0 || predt >= T->data) {//�������������BST���ߵ�ǰ�ڵ������ǰ���ڵ�ֵ�����ڴ�����BST
			return 0;
		}
		predt = T->data;
		b2 = JudgeBST(T->rchild);
		return b2;
	}
}
//˼·2���������������visit�Ľ���浽������,����������Ԫ���Ƿ����



//�ڶ�ʮ����
//�ö����������ж�һ���������Ƿ�Ϊƽ����������㷨
typedef struct AVLnode {
	Elemtype data;
	int heigh;//�߶�
	struct AVLnode* lchild;
	struct AVLnode* rchild;
}AVLnode, * AVLtree;
//��ȡ�߶�
int height(AVLnode* T) {
	if (T == NULL) return 0;
	else return T->heigh;
}

//����ֵ
int abs(int a, int b) {
	return a - b > 0 ? a - b : b - a;
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
//��ʱ��AVL�ڵ�Ķ������ǲ����߶�height�ģ�����Ҫ��ִ�к���ʱ�����ж������߶�
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

