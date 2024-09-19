#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Error 0
#define Ok 1
typedef int Elemtype;
typedef int Status;
typedef struct Node {
	Elemtype data;
	struct Node* next;
}Node;
Node* CreatHeadInsert() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	for (int i = 0; i < 10; i++) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i;
		p->next = head->next;
		head->next = p;
	}
	return head->next;
}
void showList(Node* head) {
	Node* p=head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
Node* CreatTailInsert() {
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	Node* r = head;
	for (int i = 0; i < 10; i++) {
		Node* p = (Node*)malloc(sizeof(Node));
		p->data = i;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	return head->next;
}
bool ListInsert(Node* L, int i, Elemtype e) {//��λ����룺�ڸ���iǰ����ڵ�
	if (i < 1) return false;
	if (i == 1) {
		Node* s = (Node*)malloc(sizeof(Node));
		s->data = e;
		s->next = L;
		L=s;
		return true;
	}
	Node* p = L;
	int j = 1;//��ʼ�ڵ㣬ָ���1���ڵ㣨����ͷ��㣩
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool InsertNextNode(Node* p, Elemtype e) {//�ڸ����ڵ������½ڵ�
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL) return false;//ĳЩ����·���ʧ�ܣ������ڴ治��
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}
bool ListInsert1(Node* L, int i, Elemtype e) {//��λ����룺�ڸ���iǰ����ڵ�,�к���������ԶԵ�i-1�ڵ�ʵ�ֺ��
	if (i < 1) return false;
	Node* p = L;
	int j = 1;//��ʼ�ڵ㣬ָ���1���ڵ㣨����ͷ��㣩
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	return InsertNextNode(p, e);
}
bool InsertPriorNode(Node* p, Elemtype e) {//ָ���ڵ�ǰ�壬������ָ���ڵ��壬Ȼ�󽻻������ڵ����ݼ���
	if (p == NULL) return false;
	Node* s = (Node*)malloc(sizeof(Node));
	if (s == NULL) return false;
	s->next = p->next;
	p->next = s;
	s->data = p->data;
	p->data = e;
	return true;
}
bool ListDelete(Node* L, int i, Elemtype* e) {//ɾ��ָ��λ��Ľڵ�,����Ԫ��ֵ
	if (i < 1) return false;
	Node* p;
	int j = 1;//����ͷ��㣬ָ��1�� ��ͷ���ָ��0
	p = L;
	while (p != NULL && j < i - 1) {//p�ƶ�ͬʱ��Ҫj������
		p = p->next;
		j++;
	}
	if (p == NULL) return false;//p��
	if (p->next == NULL) return false;//p-1��
	//��ʱpָ���i-1���ڵ�
	Node* q = p->next;
	*e = q->data;
	p->next = q->next;
	free(q);
	return true;
}
bool DeleteNode(Node* p) {//ɾ��ָ���ڵ�
	if (p == NULL) return false;
	Node* q = p->next;//q��p��
	p->data = q->data;//�Ƚ���p��q��data����ɾ��p�ĺ�̽ڵ㣬�Ӷ���ɶ�ָ���ڵ�p��ɾ��
	p->next = q->next;
	free(q);
	return true;
}
Node* GetElem(Node* L, int i) {//��λ����ң����ص�i���ڵ�
	if (i < 0) return NULL;//����ǽڵ����ͣ������Ҳ����ڵ㣬�򷵻�һ��NULLָ��ȼ��ڿսڵ�
	Node* p;
	int j = 1;//����ͷ��㣬���±�1��ʼ
	p = L;
	while (p != NULL && j < i) {
		p = p->next;
		j++;
	}
	return p;
}
Node* LocateElem(Node* L, Elemtype e) {//��ֵ���ң��ڱ�L���ҵ����и����ؼ��ֵ�Ԫ�أ����ؽڵ�
	Node* p = L;
	while (p != NULL && p->data != e) {
		p = p->next;
	}
	return p;
}
int Length(Node* L) {//��������
	int len = 0;
	Node* p = L;
	while (p != NULL) {
		p = p->next;
		len++;
	}
	return len;
}
Node* Reverse(Node* L) {//������������ͷ���.
	Node* p, * q;//�������ʼ������ָ�룬��ʼ���ʹ���ڵ�
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	p = L;//pָ���һ���ڵ�
	while (p!= NULL) {
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
	return head->next ;
}
int main() {
	Node* L = CreatHeadInsert();
	showList(L);
	Node* H = CreatTailInsert();
	showList(H);
	ListInsert(L, 3, 9);
	showList(L);
	ListInsert1(H, 3, 9);
	showList(H);
	printf("%d\n", Length(L));
	Node* K = Reverse(H);
	showList(K);
	return 0;
}