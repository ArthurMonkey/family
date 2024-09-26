#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define ERROR 0
#define OK 1
typedef int Elemtype;
typedef int Status;
#define MAXSIZE 50  //定义栈中元素的最大个数
typedef int ElemType;   //ElemType的类型根据实际情况而定，这里假定为int

typedef struct {
	ElemType data[MAXSIZE];
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
Status Push(SqStack* S, ElemType e) {
	//满栈
	if (S->top == MAXSIZE - 1) {
		return ERROR;
	}
	S->top++;   //栈顶指针增加一
	S->data[S->top] = e;    //将新插入元素赋值给栈顶空间
	return OK;
}

/*若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR*/
Status Pop(SqStack* S, ElemType* e) {
	if (S->top == -1) {
		return ERROR;
	}
	*e = S->data[S->top];   //将要删除的栈顶元素赋值给e
	S->top--;   //栈顶指针减一
	return OK;
}

/*读栈顶元素*/
Status GetTop(SqStack S, ElemType* e) {
	if (S.top == -1) {   //栈空
		return ERROR;
	}
	*e = S.data[S.top];   //记录栈顶元素
	return OK;
}
