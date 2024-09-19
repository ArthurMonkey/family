#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Ok 1
#define Error 0
typedef int Elemtype;
typedef int Status;
typedef struct DNode {
	Elemtype data;
	struct DNode* prior, * next;
}DNode;
DNode* Create(DNode* L) {
	DNode* head = (DNode*)malloc(sizeof(DNode));
	if (head == NULL) return NULL;
	head->next = NULL;
	head->prior = NULL;
	return head;
}
bool Empty(DNode* head) {//�ж�˫�����Ƿ�Ϊ��
	if (head->next == NULL) return true;
	else return false;
}
bool InsertNextDNode(DNode* p, DNode* s) {//�ڽڵ�p�����ڵ�s
	if (p == NULL || s == NULL) return false;//��������ڵ�Ϊ�գ���Ϊ�Ƿ�����
	s->next = p->next;
	if (p->next != NULL) p->next->prior = s;
	s->prior = p;
	p->next = s;
	return true;
}
//��λ������������ͷ��㿪ʼ�ҵ���i-1���ڵ���
// 
//ǰ��������ҵ������ڵ��ǰ����㣬��ǰ�������к��

//ɾ��p�ڵ�ĺ�̽ڵ�
bool DeletNextDNode(DNode* p) {
	if (p == NULL) return false;
	DNode* q = p->next;
	if (q == NULL) return false;
	p->next = q->next;
	if (q->next != NULL) q->next->prior = p;
	free(q);
	return true;
}

bool DestoryList(DNode* L) {//��ͷ���
	//ѭ���ͷŸ������ݽ��
	while (L->next != NULL) {
		DeletNextDNode(L);  //ɾ��ͷ���ĺ�̽��
		free(L); //�ͷ�ͷ���
		L = NULL;  //ͷָ��ָ��NULL

	}
	return true;
}

void showList(DNode* head) {
	DNode* p = head;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int main() {
	DNode* L=(DNode*)malloc(sizeof(DNode));
	L = Create(L);
	if (L == NULL) printf("0\n");
	else printf("1\n");
	//��ʾ1�� �����ɹ�

	return 0;
}