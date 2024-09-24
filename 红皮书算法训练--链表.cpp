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
//������
//�ݹ�߽�; LΪ�ձ�
//�ݹ����� (L,e)  -----(L->next, e)
void DeleteNode(LinkList &L, Elemtype e) {//��������Ҫ����ȥ�� ��������Ϊvoid������LinkListҲҪ��&
	if (L == NULL) return;
	else {
		if (L->data == e) {
			Lnode* p = L->next;
			L->data = p->data;
			L->next = p->next;
			free(p);
			DeleteNode(L, e);//���ɾ���󣬵ݹ���������ɣ���Ϊ�Ѿ�����һ���ڵ���
		}
		else {
			 DeleteNode(L->next, e);
		}
	}
}

//������
//��ͷ���ĵ������������ÿ���ڵ��ֵ
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
/*    //ȱ�ٺ����������Կ��Կ�ֱ����
//����������ջ����������
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

//�ڰ���
//��д�㷨������ͷ���ĵ�����͵����ã������ռ临�Ӷ�ΪO��1��
//ͷ�巨�����ǽ�ͷ���L����ժ�������ø���ָ�����ԭ���У���ԭ���нڵ�ȫ��ժ��
LinkList ReverseRightnow(LinkList L) {
	Lnode* p = L->next;
	Lnode* r;
	L->next = NULL;//��ժ��ͷ���
	while (p != NULL) {//�������һ���ڵ�
		r = p;
		p = p->next;
		r->next = L->next;
		L->next = r;
	}
	return L;
}

//�ھ���
//һ����ͷ���ĵ�����L������㷨ʹ��Ԫ�ص�������
//����ֱ�Ӳ���˼�룬�ҵ��������λ�ã�Ȼ���ǰһ��Ԫ��ʵ�ֺ��
LinkList IncreaseList(LinkList L) {
	Lnode* p = L->next->next;//p��������,preָ������ͷ���ÿ�α���Ҫ�ã�r�������p�ĺ�̽�㣬��Ϊÿ��ѭ��pҪ��ժ����
	L->next->next = NULL;//���ó�ʼʱֻ��һ���ڵ�
	Lnode* r = L->next;
	Lnode* pre;
	while (p != NULL) {
		r = p->next;//���������̽��
		pre = L;
		p->next = NULL;//ժ��p
		while (pre->next != NULL && pre->next->data < p->data) {//���������һ���ڵ�����ҵ��������λ��
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = r;//��ԭp�� pre�����ڿ�ͷ��ԭҲ�����ڽ�β��ԭ
	}
	return L;
}

//��ʮ��
//��������������д�㷨�ҵ������ڵ�
//��һ��O(len1*len2)���ҵ������ڵ���㣬����ʱ
//������O��len1+len2)  ���������ĳ���ڵ㿪ʼΪ�����ڵ㣬������ֱͬ�������������������ȿ��ܲ�һ��
//���Էֱ�����õ�����len��Ȼ��len1-len2=k�� ��һ������k��Ȼ��ʼͬʱ�������������ͬ������й����ڵ�
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
		longlist = L1->next;//����ͷ���
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
			return longlist;//���ع����ڵ㿪ʼ��������ڵ㣬���򹫹������ɵó�
		}
		else {
			longlist = longlist->next;
			shortlist = shortlist->next;
		}
	}
	return NULL;
}

//��ʮһ��
//��һ����ͷ���ĵ�����A���������ͷ����A��B��ʹ��A���к����������Ԫ�أ�B���к������ż��Ԫ�أ��ұ������˳�򲻱�
//B������ʱ��β�巨����A����нڵ��ȥ�������뵽�µĽڵ㣬��¼�����ż��ͷ������=0
//���������Բ�������num��ֱ�ӶԱ�A���������ƶ�����Ȼ�ͻ��ҵ��õ�B��ȥ�Ľ��
LinkList DivideList(LinkList &A) {//&A ���Բ����ں��������*ʹ�ã����ö��Ǹı亯��
	Lnode* p = A->next;//�����
	int num = 0;
	LinkList B = (Lnode*)malloc(sizeof(Lnode));
	B->next = NULL;
	Lnode* rb = B, * ra = A;
	A->next = p;//A�ÿ�������������
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
	ra->next = NULL;//Ҫ�ǵô�����������β�ڵ��ָ��ȥNULL��������γ�Ұָ��
	rb->next = NULL;
	return B;
}

//��ʮ����
//��һ��a1b1a2b2.....anbn�ĵ���������������A:a1a2...an  B:bn....b2b1
LinkList DivideList2(LinkList &A) {
	LinkList B = (Lnode*)malloc(sizeof(Lnode));
	B->next = NULL;
	Lnode* p = A->next;//�����
	A->next = NULL;//A��������ͷ���
	Lnode* ra = A, * rb;
	int i = 0;
	while (p != NULL) {
		i++;
		if (i % 2 == 1) {
			ra->next = p;
			ra = p;
			p = p->next;
		}
		else {//��B��ͷ�巨
			rb = p;
			p = p->next;
			rb->next = B->next;
			B->next = rb;
		}
	}
	ra->next = NULL;//ֻ��A�ı�β�ڵ���NULL����
	return B;
}

//��ʮ����
//A,B��������򣬽�����Ԫ�ز���������C��Ҫ���ƻ�����AB
//˼·������len1��len2�� Ȼ���ͷ��β����AB������ָ��˭�ȶԷ�С˭����ƶ��������������������ָ��ͬʱ�ƶ������򵥸��ƶ�,
// ֱ��һ���ƶ�����β����
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

//��ʮ����
//��֪��������A��B������Ԫ�ص������У���A��B�Ľ��������������A��
//˼·���鲢˼�룺��������ָ�����������ɨ�裬��ͬ�ڵ���һ����һ���ͷţ������ͬ���ĸ�С�ͷ���һ����ֱ����������һ��
//������ʣ�µ�һ������ȫ���ͷ�
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
			q->next = pa;//β�巨
			q = pa;
			pa = pa->next;
			u = pb;
			pb = pb->next;//����ƶ�b��a�Ѿ������ժ�����Բ������ƶ�
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
	q->next = NULL;//��������β����������
	free(B);//�ͷ�B�ı�ͷ�ڵ�
	return A;
}

//��ʮ����
//���һ���㷨�жϴ�ͷ����ѭ��˫�����Ƿ�Գ�
bool Symmetry(DLinkList L) {
	DNode* p = L->next, * q = L->prior;
	while (p != q && p->next != q) {//����ѭ������Ҫ�����
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

//��ʮ����
//��ͷ����ѭ���������ҳ��������нڵ�ֵ��С�ĵĽ�㲢�����Ȼ�󽫸ýڵ����ɾ����ֱ�������Ϊֹ��Ȼ��ɾ����ͷ���
//ɾ���ڵ㣬�ҵ�p��pǰ��pre��Ȼ��ɾ��p��ѭ��ֱ������Ϊ��
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
	free(L);//��ͷ����ͷ�
}

//��ʮ����
//�ж�һ�������Ƿ��л����ҳ�������ڵ㲢���أ����򷵻�NULL
Lnode* FindLoopStart(LinkList L) {
	Lnode* fast = L, * slow = L;
	while (slow != NULL && fast != NULL) {
		fast = fast->next->next;//fast��������slow��һ��
		slow = slow->next;
		if (slow == fast) break;
	}
	if (slow == NULL || fast->next == NULL) return NULL;//fastһ����2�����п�����1���͵��յ���
	//slowΪ�����㣬ͨ��������Եõ���ڵ�Ҫ��p1�����L�ߣ�p2��slow���ߣ�����ſ����ڻ�����ڵ㴦����
	Lnode* p1 = L, * p2 = slow;//
	while (p1 != p2) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}