#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
//����˫�ױ�ʾ��
//���ڵ��˫����=-1������ڵ��˫�������������˫�׽ڵ���±�ڵ�����ʾ
typedef struct {
	Elemtype data;
	int parent;//˫��λ������Ϊ����������,����Ҫ֪��
}PTNode;
typedef struct {
	PTNode nodes[maxsize];//˫�ױ�ʾ
	int n;//�ڵ���
}PTree;//�����������е�˫�׽ڵ��Լ��ڵ�����

//�����ֵܱ�ʾ��
typedef struct CSNode {
	Elemtype data;
	struct CSNode* firstchild, * nextsibling;//sibling �ֵܽ��õ�Ӣ�ﵥ��
}CSNode, *CSTree;

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