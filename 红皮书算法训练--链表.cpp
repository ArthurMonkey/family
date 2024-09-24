#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;

typedef struct Lnode {
	Elemtype data;
	struct Lnode* next;
}Lnode, *LinkList;
typedef struct DNode {
	Elemtype data;
	struct DNode* prior, * next;
}DNode, *DLinkList;
//第六题
//递归边界; L为空表
//递归条件 (L,e)  -----(L->next, e)
void DeleteNode(LinkList &L, Elemtype e) {//调用链表，要换回去， 函数类型为void，所以LinkList也要加&
	if (L == NULL) return;
	else {
		if (L->data == e) {
			Lnode* p = L->next;
			L->data = p->data;
			L->next = p->next;
			free(p);
			DeleteNode(L, e);//完成删除后，递归调用自身即可，因为已经少了一个节点了
		}
		else {
			 DeleteNode(L->next, e);
		}
	}
}

//第七题
//带头结点的单链表，反向输出每个节点的值
void Reverseprintf(LinkList* L) {
	Lnode* head = (Lnode*)malloc(sizeof(Lnode));
	head->next = NULL;
	Lnode* p = (*L)->next;
	while (p != NULL) {
		Lnode* s = (Lnode*)malloc(sizeof(Lnode));
		s->data = p->data;
		s->next = head->next;
		head->next = s;
		p = p->next;
	}
	p = head->next;
	while (p != NULL) {
		printf("%d ", p->data);
	}
	return;
}
/*    //缺少函数，但笔试考试可直接用
//法二：利用栈进行先入后出
void Reverseprintf1(LinkList L) {
	InitStack(S);
	Lnode* p = L;
	while (p->next != NULL) {
		Push(S, p);
	}
	while (IsEmpty(S) == false) {
		Pop(S, p);
		printf("%d ", p->data);
	}
}
*/

//第八题
//编写算法，将带头结点的单链表就地逆置，辅助空间复杂度为O（1）
//头插法，但是将头结点L单独摘出来，用辅助指针遍历原队列，将原队列节点全部摘下
LinkList ReverseRightnow(LinkList L) {
	Lnode* p = L->next;
	Lnode* r;
	L->next = NULL;//已摘下头结点
	while (p != NULL) {//处理最后一个节点
		r = p;
		p = p->next;
		r->next = L->next;
		L->next = r;
	}
	return L;
}

//第九题
//一个带头结点的单链表L，设计算法使其元素递增有序
//采用直接插入思想，找到带插入的位置，然后对前一个元素实现后插
LinkList IncreaseList(LinkList L) {
	Lnode* p = L->next->next;//p遍历旧链,pre指新链的头结点每次遍历要用，r保存旧链p的后继结点，因为每次循环p要被摘下来
	L->next->next = NULL;//先让初始时只有一个节点
	Lnode* r = L->next;
	Lnode* pre;
	while (p != NULL) {
		r = p->next;//保存旧链后继结点
		pre = L;
		p->next = NULL;//摘下p
		while (pre->next != NULL && pre->next->data < p->data) {//遍历到最后一个节点或者找到带插入的位置
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = r;//还原p， pre可以在开头还原也可以在结尾还原
	}
	return L;
}

//第十题
//给定两个链表，编写算法找到公共节点
//法一：O(len1*len2)，找到公共节点就算，但超时
//法二：O（len1+len2)  两个链表从某个节点开始为公共节点，后面相同直到结束，但两个链表长度可能不一样
//所以分别遍历得到两个len，然后len1-len2=k， 第一个先走k个然后开始同时遍历，如果有相同结果则有公共节点
int Length(LinkList L) {
	int len = 0;
	Lnode* p = L;
	while (p!= NULL) {
		p = p->next;
		len++;
	}
	return len;
}
LinkList SearchEqualList(LinkList L1, LinkList L2) {
	int len1 = Length(L1);
	int len2 = Length(L2);
	LinkList longlist, shortlist;
	int dist;
	if (len1 > len2) {
		longlist = L1->next;//均带头结点
		shortlist = L2->next;
		dist = len1 - len2;
	}
	else {
		longlist = L2->next;
		shortlist = L1->next;
		dist = len2 - len1;
	}
	while (dist>0) {
		longlist = longlist->next;
		dist--;
	}
	while (longlist != NULL) {
		if (longlist == shortlist) {
			return longlist;//返回公共节点开始处的链表节点，后序公共链表即可得出
		}
		else {
			longlist = longlist->next;
			shortlist = shortlist->next;
		}
	}
	return NULL;
}

//第十一题
//将一个带头结点的单链表A拆成两个带头结点的A和B，使得A表中含有序号奇数元素，B表中含有序号偶数元素，且保持相对顺序不变
//B表生成时用尾插法，对A表进行节点的去掉并加入到新的节点，记录序号奇偶，头结点序号=0
//法二：可以不用设置num，直接对表A进行两次移动，自然就会找到该到B里去的结点
LinkList DivideList(LinkList &A) {//&A 可以不用在函数体里加*使用，作用都是改变函数
	Lnode* p = A->next;//存旧链
	int num = 0;
	LinkList B = (Lnode*)malloc(sizeof(Lnode));
	B->next = NULL;
	Lnode* rb = B, * ra = A;
	A->next = p;//A置空用来存新链表
	while (p != NULL) {
		num++;
		if (num % 2 == 0) {
			rb->next = p;
			rb = p;
		}
		else {
			ra->next = p;
			ra = p;
		}
		p = p->next;
	}
	ra->next = NULL;//要记得处理两个链表尾节点的指针去NULL，否则会形成野指针
	rb->next = NULL;
	return B;
}

//第十二题
//讲一个a1b1a2b2.....anbn的单链表拆成两个链表A:a1a2...an  B:bn....b2b1
LinkList DivideList2(LinkList &A) {
	LinkList B = (Lnode*)malloc(sizeof(Lnode));
	B->next = NULL;
	Lnode* p = A->next;//存旧链
	A->next = NULL;//A做新链的头结点
	Lnode* ra = A, * rb;
	int i = 0;
	while (p != NULL) {
		i++;
		if (i % 2 == 1) {
			ra->next = p;
			ra = p;
			p = p->next;
		}
		else {//对B用头插法
			rb = p;
			p = p->next;
			rb->next = B->next;
			B->next = rb;
		}
	}
	ra->next = NULL;//只对A的表尾节点做NULL处理
	return B;
}

//第十三题
//A,B表各自有序，将公共元素产生单链表C，要求不破坏链表AB
//思路：先求len1，len2， 然后从头到尾遍历AB，两个指针谁比对方小谁向后移动，如果有相等则输出，两指针同时移动，否则单个移动,
// 直到一个移动到表尾结束
//1 3 5 6 9
//2 4 5 9 10
LinkList CreateListCommon(LinkList A, LinkList B) {
	LinkList C = (Lnode*)malloc(sizeof(Lnode));
	C->next = NULL;
	Lnode* ra=A->next, * rb=B->next, * rc = C;
	Lnode* s;
	while (ra != NULL && rb != NULL) {
		if (ra->data < rb->data) {
			ra = ra->next;
		}
		else if (rb->data < ra->data) {
			rb = rb->next;
		}
		else {
			s = (Lnode*)malloc(sizeof(Lnode));
			s->data = ra->data;
			s->next = NULL;
			rc->next = s;
			rc = s;
			ra = ra->next;
			rb = rb->next;
		}
	}
	rc->next = NULL;
	return C;
}

//第十四题
//已知两个链表A和B，其内元素递增排列，求A与B的交集并存放于链表A中
//思路：归并思想：两个工作指针对两个链表扫描，相同节点留一个另一个释放，如果不同则哪个小释放哪一个，直到两个链表一个
//结束，剩下的一个链表全部释放
LinkList Union(LinkList& A, LinkList& B) {
	Lnode* pa = A->next, * pb = B->next;
	A->next = NULL;
	Lnode* q = A;
	Lnode* u;
	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			u = pa;
			pa = pa->next;
			free(u);
		}
		else if (pa->data > pb->data) {
			u = pb;
			pb = pb->next;
			free(u);
		}
		else {
			q->next = pa;//尾插法
			q = pa;
			pa = pa->next;
			u = pb;
			pb = pb->next;//向后移动b，a已经完成了摘下所以不用再移动
			free(u);
		}
	}
	while (pa != NULL) {
		u = pa;
		pa = pa->next;
		free(u);
	}
	while (pb != NULL) {
		u = pb;
		pb = pb->next;
		free(u);
	}
	q->next = NULL;//对新链的尾部单独处理
	free(B);//释放B的表头节点
	return A;
}

//第十五题
//设计一个算法判断带头结点的循环双链表是否对称
bool Symmetry(DLinkList L) {
	DNode* p = L->next, * q = L->prior;
	while (p != q && p->next != q) {//跳出循环条件要看清楚
		if (p->data == q->data) {
			p = p->next;
			q = q->next;
		}
		else {
			return false;
		}
	}
	return true;
}

//第十六题
//带头结点的循环单链表，找出单链表中节点值最小的的结点并输出，然后将该节点从中删除，直到链表空为止，然后删除表头结点
//删除节点，找到p和p前置pre，然后删除p，循环直到链表为空
void Del_All(LinkList& L) {
	Lnode* p, * pre, * minp, * minpre;
	while (L->next != L) {
		p = L->next;
		pre = L;
		minp = p;
		minpre = pre;
		while (p != L) {
			if (p->data < minp->data) {
				minp = p;
				minpre = pre;
			}
			pre = p;
			p = p->next;
		}
		printf("%d ", minp->data);
		minpre->next = pre->next;
		free(minp);
	}
	free(L);//表头结点释放
}

//第十八题
//判断一个链表是否有环，找出环的入口点并返回，否则返回NULL
Lnode* FindLoopStart(LinkList L) {
	Lnode* fast = L, * slow = L;
	while (slow != NULL && fast != NULL) {
		fast = fast->next->next;//fast走两步，slow走一步
		slow = slow->next;
		if (slow == fast) break;
	}
	if (slow == NULL || fast->next == NULL) return NULL;//fast一次走2步，有可能走1步就到终点了
	//slow为相遇点，通过计算可以得到入口点要让p1从起点L走，p2从slow点走，两点才可能在环的入口点处相遇
	Lnode* p1 = L, * p2 = slow;//
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}