#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define ERROR 0
#define OK 1
typedef int Elemtype;
typedef int Status;
#define MAXSIZE 50  //����ջ��Ԫ�ص�������
typedef int ElemType;   //ElemType�����͸���ʵ���������������ٶ�Ϊint

typedef struct {
	ElemType data[MAXSIZE];
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
Status Push(SqStack* S, ElemType e) {
	//��ջ
	if (S->top == MAXSIZE - 1) {
		return ERROR;
	}
	S->top++;   //ջ��ָ������һ
	S->data[S->top] = e;    //���²���Ԫ�ظ�ֵ��ջ���ռ�
	return OK;
}

/*��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR*/
Status Pop(SqStack* S, ElemType* e) {
	if (S->top == -1) {
		return ERROR;
	}
	*e = S->data[S->top];   //��Ҫɾ����ջ��Ԫ�ظ�ֵ��e
	S->top--;   //ջ��ָ���һ
	return OK;
}

/*��ջ��Ԫ��*/
Status GetTop(SqStack S, ElemType* e) {
	if (S.top == -1) {   //ջ��
		return ERROR;
	}
	*e = S.data[S.top];   //��¼ջ��Ԫ��
	return OK;
}
