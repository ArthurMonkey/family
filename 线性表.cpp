#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Ok 1
#define Error 0
typedef int Elemtype;
typedef int Status;

typedef struct {
	int length;
	Elemtype* elem;
}SqList;
Status InitList(SqList* L) {
	L->elem = (Elemtype*)malloc(sizeof(Elemtype));
	L->length = 0;
	if (L->elem == NULL) return Error;
	return Ok;
}
void printList(SqList L) {
	printf("当前顺序表长度为：%d\n", L.length);
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.elem[i]);
	}
	printf("\n");
}
Status InsertList(SqList* L, int loc, Elemtype e) {
	if (L->length == maxsize) return Error;
	if (loc<1 || loc>maxsize + 1) return Error;
	if (loc < L->length) {
		for (int i = L->length; i >= loc-1; i--) {
			L->elem[i+1] = L->elem[i];
		}
	}
	L->elem[loc-1] = e;
	L->length++;
	return Ok;
}
Status DeleteList(SqList* L, int loc, Elemtype* e) {
	if (L->length == 0) return Error;
	if (loc<1 || loc>maxsize) return Error;
	*e = L->elem[loc - 1];
	if (loc < L->length) {
		for (int i = L->length - 1; i >= loc; i--) {
			L->elem[i + 1] = L->elem[i];
		}
	}
	L->length--;
	return Ok;
}
Status Getelem(SqList L, int loc, Elemtype* e) {
	if (L.length == 0) return Error;
	if (loc<1 || loc>maxsize) return Error;
	*e = L.elem[loc - 1];
	return Ok;
}
int main() {
	SqList L;
	printf("------第一次生成列表--------\n");
	InitList(&L);
	printList(L);
	printf("------测试插入10个数------\n");
	for (int i = 1; i <= 10; i++) {
		InsertList(&L, i, i);
	}
	printList(L);
	printf("------第二次生成列表--------\n");
	InsertList(&L, 3, 0);
	printList(L);
	printf("------第三次生成列表--------\n");
	Elemtype e;
	DeleteList(&L, 6, &e);
	printf("%d\n", e);
	printList(L);
	printf("------第四次生成列表--------\n");
	Getelem(L, 5, &e);
	printf("%d\n", e);
	return 0;
}