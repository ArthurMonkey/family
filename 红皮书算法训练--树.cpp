#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct BiTnode {
	Elemtype data;//数据域
	struct BiTnode* lchild, * rchild;//左右孩子指针
}BiTnode, * BiTree;
#define ERROR 0
#define OK 1
#define maxsize 20
typedef int Elemtype;
typedef int Status;

void visit(BiTnode* p) {//访问节点，打印出data
	printf("%d ", p->data);
}
//栈的定义和基本操作
typedef struct {
	Elemtype data[maxsize];
	int top;    //用于栈顶指针
}SqStack;

void InitStack(SqStack* S) {
	S->top = -1;    //初始化栈顶指针
}

bool StackEmpty(SqStack S) {
	if (S.top == -1) {
		return true;    //栈空
	}
	else {
		return false;   //不空
	}
}

/*插入元素e为新的栈顶元素*/
Status Push(SqStack* S, Elemtype e) {
	//满栈
	if (S->top == maxsize - 1) {
		return ERROR;
	}
	S->top++;   //栈顶指针增加一
	S->data[S->top] = e;    //将新插入元素赋值给栈顶空间
	return OK;
}
Status Push1(SqStack* S, BiTnode* e) {
	//满栈
	if (S->top == maxsize - 1) {
		return ERROR;
	}
	S->top++;   //栈顶指针增加一
	S->data[S->top] = (*e).data;    //将新插入元素赋值给栈顶空间
	return OK;
}

/*若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR*/
Status Pop(SqStack* S, Elemtype* e) {
	if (S->top == -1) {
		return ERROR;
	}
	*e = S->data[S->top];   //将要删除的栈顶元素赋值给e
	S->top--;   //栈顶指针减一
	return OK;
}
Status Pop1(SqStack* S, BiTnode* e) {
	if (S->top == -1) {
		return ERROR;
	}
	(*e).data = S->data[S->top];   //将要删除的栈顶元素赋值给e
	S->top--;   //栈顶指针减一
	return OK;
}
/*读栈顶元素*/
Status GetTop(SqStack S, Elemtype* e) {
	if (S.top == -1) {   //栈空
		return ERROR;
	}
	*e = S.data[S.top];   //记录栈顶元素
	return OK;
}
Status GetTop1(SqStack S, BiTnode* e) {
	if (S.top == -1) {   //栈空
		return ERROR;
	}
	(*e).data = S.data[S.top];   //记录栈顶元素
	return OK;
}
//
// 
// 
// 
//第十八题
//编写二叉树后序遍历的非递归算法
//gettop1，push1，pop1，等都是为了符合电脑语法要求所写。
void PostOrderStack(BiTree T) {
	SqStack* S;
	InitStack(S);
	BiTnode* p = T;
	BiTnode* r = NULL;
	while (p != NULL || StackEmpty(*S) == false) {//栈不空  true代表空
		if (p != NULL) {
			Push1(S, p);//此处Push里的p的参数类型更改即可
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


//第十九题
//给出二叉树的自下而上、从右到左的层次遍历算法
//思路：所有节点在层次遍历里不用visit而是都入栈，当队列空或者树空再从栈中全部读出
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

//第二十题
//二叉树采用二叉链表存储，设计非递归算法求树的高度
//思路：用顺序队列来设计，利用front和rear，并且设置last==rear判断当前层是否完结和level记录层数
int BiTreeDepth(BiTree T) {
	if (T == NULL) return 0;
	int front = -1, rear = -1;
	int last = 0, level = 0;//last代表每一层的最后一个节点rear，last==rear代表访问到当层最后一个节点，让level+1； 初始层只有一个根节点
	//所以front初始时-1，last初始时0
	BiTree Q[maxsize];//队列Q,元素是二叉树节点指针且容量足够大
	Q[++rear] = T;//根节点入队
	BiTree p;
	while (front < rear) {
		p = Q[++front];//出队
		if (p->lchild != NULL) Q[++rear] = p->lchild;
		if (p->rchild != NULL) Q[++rear] = p->rchild;
		if (front == last) {
			level++;
			last = rear;//更新last
		}
	}
	return level;
}

//第二十一题
//二叉树按二叉链表存储，判定给定二叉树是否为完全二叉树
//思想：采用层次遍历，如果遇到空节点其后是否有非空节点，如果有则不是完全二叉树
bool IsComplete(BiTree T) {
	InitQueue(Q);
	BiTnode* p;
	if (T == NULL) {//空树是完全二叉树
		return true;
	}
	EnQueue(Q, T);//空节点也可以入队
	while (IsEmpty(Q) == false) {
		DeQueue(Q, p);
		if (p != NULL) {
			EnQueue(Q, p->lchild);//可以将空节点也可以纳入队列中
			EnQueue(Q, p->rchild);
		}
		else {
			while (IsEmpty(Q) == false) {
				DeQueue(Q, p);
				if (p != NULL) return false;//如果有节点不空，则不是完全二叉树
			}
		}
	}
	return true;
}

//第二十二题
//二叉树以二叉链表存储，遍历树删除以x为值的根节点和它的子树
//思想：删除元素值为x的节点，先删除左右子树再删除根节点所以删除操作用后序遍历free掉。 删除节点要将父节点的左右子树置空否则野指针会出错
//用层序遍历方便找到其父节点,用顺序队列辅助层序遍历
void DeleteX(BiTree p) {//删除值为x的节点
	if (p != NULL) {
		DeleteX(p->lchild);
		DeleteX(p->rchild);
		free(p);
	}
}
void Search(BiTree T, Elemtype x) {
	BiTree Q[maxsize];//maxsize足够的大
	BiTnode* p;
	if (T != NULL) {
		if (T->data == x) {//根节点值为x，删除整棵树
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
					p->lchild = NULL;//父节点的左孩子指针置为NULL
				}
				else {//如果值不为x
					EnQueue(Q, p->lchild);//左子树入队
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

//第二十三题
//二叉树节点结构为（llink,inof,rlink),root指向该二叉树根节点的指针,p和q分别为指向该二叉树中任意两个节点的指针
//编写算法Ancestor(root, p, q, r)找到p和q最近的公共祖先节点r
//LSA题目
typedef struct {
	BiTree t;
	int tag;//tag=0表示左子女已被访问，tag=1表示右子女已被访问
}stack;
stack s[], s1[];//s1为辅助栈，两栈容量足够大
BiTree Ancestor(BiTree root, BiTnode* p, BiTnode* q) {
	int top = 0;
	int top1;
	BiTnode* T = root;
	while (T != NULL || top > 0) {//栈不空树不空
		while (T != NULL) {
			s[++top].t = T;
			s[top].tag = 0;
			T = T->lchild;
		}//向左分支全部入栈
		while (top != 0 && s[top].tag == 1) {//当栈顶节点左右子树均被访问过，判定栈顶节点是p还是q，是p则把祖先加入辅助栈
			if (s[top].t == p) {
				for (int i = 1; i <= top; i++) {
					s1[i] = s[i];
					top1 = top;
				}
			}
			if (s[top].t == q) {//是q则把当前q的栈中的元素和p的辅助栈中的元素比较，如果能找到最近相同节点则为公共祖先节点
				for (int i = top; i > 0; i--) {
					for (int j = top1; j > 0; j--) {
						if (s1[j].t == s[i].t) {
							return s[i].t;
						}
					}
				}
			}
			top--;//退栈
		}//while
		if (top != 0) {//右转
			s[top].tag = 1;//表示节点右侧访问过，接下来while里让访问右子树
			T = s[top].t->rchild;
		}
	}//while
	return NULL;//pq无公共祖先
}

//递归类解LSA
void Ancestor1(BiTree root, BiTnode* p, BiTnode* q, BiTree* r) {
	//如果root=空或者root就是p或者q，那root就是公共祖先节点
	if (root == NULL || root == p || root = q) {
		*r = root;
		return;
	}
	//递归在左子树中查找公共祖先
	BiTnode* left = NULL;
	Ancestor1(root->lchild, p, q, &left);
	//递归在右子树中查找公共祖先
	BiTnode* right = NULL;
	Ancestor1(root->rchild, p, q, &right);
	//左指针为空代表pq都在右子树里
	if (left == NULL) {
		*r = right;
		return;
	}
	//右指针为空代表pq都在左子树里
	if (right == NULL) {
		*r = left;
		return;
	}
	//left，right都不空代表 p和q分别在左右子树里，此时root为公共祖先
	*r = root;
	return;
}

//第二十四题
//假设二叉树采用二叉链表存储，设计一个算法求非空二叉树b的宽度（具有节点数最多的那一层的节点个数）
//思路：采用层序遍历，利用数组当作队列存储二叉树，记录last=front时，rear和last的大小的个数记为max
int maxWeight(BiTree T) {
	BiTree Q[maxsize];
	int front = -1, rear = -1;
	int last = 0;
	int max = -1;
	Q[++rear] = T;
	BiTnode* p = T;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	while (front < rear) {
		p = Q[++front];//出队
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

//第二十五题
//设计算法，将二叉树的叶节点按从左到右的顺序连成一个单链表，表头指针为head，二叉树按二叉链表方式存储
//链接时用叶节点的右指针域来存放单链表指针
//思路：采用中序遍历的模版，先找节点，找到叶节点后处理，第一个叶节点要绑头后，其余叶节点都用pre指针处理即可，最后一个叶节点单独处理
//虽然时单链表，但单链表上的节点依旧是树节点，所以要明白链接后继节点的指针为rchild
typedef BiTree LinkedList;
LinkedList head, pre = NULL;
LinkedList InOrderCreate(BiTree T) {
	if (T != NULL) {
		InOrderCreate(T->lchild);
		if (T->lchild == NULL && T->rchild == NULL) {
			if (pre==NULL) {//第一个叶节点的处理
				head = T;
				pre = head;
			}
			else {
				pre->rchild = T;
				pre = T;
			}
		}
		InOrderCreate(T->rchild);
		pre->rchild = NULL;//最后一个叶节点单独处理
	}
	return head;
}

//第二十六题
//写出在中序线索二叉树里查找指定节点在后序的前驱结点的算法
//BST树里找节点
//错误思路：在BST中序线索二叉树中进行递归后序遍历，在递归遍历模版的（3）里进行对目标节点的处理
//正确思路：在后序序列中如果节点p有右孩子，则右孩子是它的后序序列前驱结点，如果有左孩子没有有孩子则左孩子是它的后序序列前驱结点
//如果没有左右孩子，则线索二叉树的线索前驱的祖先节点f，若f有左子女则左子女是其在后序下的前驱，若f没有左子女，则顺着前驱寻找双亲的
//双清，直到双亲有左子女。   如果p是中序遍历的第一个节点，则p在中序和后序下无前驱
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
	else if (p->lchild == NULL) {//p是中序序列的第一节点无前驱
		q = NULL;
	}
	else {
		while (p->ltag == 1 && p->lchild != NULL) {//顺左线索向上找，如果节点没有左孩子则继续找
			p = p->lchild;
		}
		if (p->ltag == 0) q = p->lchild;
		else q = NULL;//仅有单支树，p是叶子节点，已到根节点无后续前驱
	}
	return q;
}

//第二十七题
//编程求以孩子兄弟表示法存储的森林的叶子结点数
//孩子兄弟表示法
typedef struct CSNode {
	Elemtype data;
	struct CSNode* firstchild, * nextsibling;//sibling 兄弟姐妹的英语单词
}CSNode, * CSTree;
//编程求以孩子兄弟表示法存储的森林的叶子节点数
int Leaves(CSTree T) {
	if (T == NULL) return 0;
	if (T->firstchild == NULL) {//如果一个节点没有孩子，那它在森林里肯定是叶子节点
		return 1 + Leaves(T->nextsibling);//返回叶子节点和其兄弟子树中的叶子节点总数
	}
	else {
		return Leaves(T->firstchild) + Leaves(T->nextsibling);
	}
}


//第二十八题
//编写算法判定给定的二叉树是否为二叉排序树BST
//思路：二叉排序树的中序遍历是一个递增序列，所以判断是否递增即可
typedef int KeyType;
KeyType predt = -32767;//predt为全局变量,保存当前中序前驱结点的值，初值-32767=-无穷
int JudgeBST(BiTree T) {
	int b1, b2;
	if (T == NULL) {//递归边界就是叶子节点是BST可以返回true
		return 1;
	}
	else {
		b1=JudgeBST(T->lchild);
		if (b1 == 0 || predt >= T->data) {//如果左子树不是BST或者当前节点的中序前驱节点值比现在大则不是BST
			return 0;
		}
		predt = T->data;
		b2 = JudgeBST(T->rchild);
		return b2;
	}
}
//思路2：或者中序遍历把visit的结果存到数组里,最后检查数组的元素是否递增



//第二十九题
//用二叉树便利判定一个二叉树是否为平衡二叉树的算法
typedef struct AVLnode {
	Elemtype data;
	int heigh;//高度
	struct AVLnode* lchild;
	struct AVLnode* rchild;
}AVLnode, * AVLtree;
//获取高度
int height(AVLnode* T) {
	if (T == NULL) return 0;
	else return T->heigh;
}

//绝对值
int abs(int a, int b) {
	return a - b > 0 ? a - b : b - a;
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
//有时候AVL节点的定义里是不含高度height的，所以要在执行函数时连带判定函数高度
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

