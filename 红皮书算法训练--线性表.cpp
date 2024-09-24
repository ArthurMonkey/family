//完成1-5题
#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
typedef struct {
	Elemtype *elem;
	int length;
}SqList;

//第一题
void reverse(SqList* L) {
	Elemtype temp;
	for (int i = 0; i < ((*L).length-1) / 2; i++) {
		temp = (*L).elem[i];
		(*L).elem[i] = (*L).elem[(*L).length - 1 - i];
		(*L).elem[(*L).length - 1 - i] = temp;
	}
}

//第二题
bool Delete_same(SqList &L) {
	if (L.length == 0) return false;
	int i, j;
	for (i = 0, j = 1; j < L.length; j++) {
		if (L.elem[i] != L.elem[j]) {
			L.elem[++i] = L.elem[j];
		}
	}
	L.length = i + 1;
	return true;
}


//第三题
bool MergeSqList(SqList a, SqList b, SqList &c) {
	if (a.length + b.length > maxsize) return false;//判满
	int len1 = a.length;
	int len2 = b.length;
	int i = 0, j = 0;
	int len3 = 0;
	while (i < len1 && j < len2) {
		if (a.elem[i] <= b.elem[j]) {
			c.elem[len3++] = a.elem[i];
			i++;
		}
		else if (a.elem[i] > b.elem[j]) {
			c.elem[len3++] = b.elem[j];
			j++;
		}
	}
	if (i == len1) {
		for (; j < len2; j++) {
			c.elem[len3++] = b.elem[j];
		}
	}
	else if (j == len2) {
		for (; i < len2; i++) {
			c.elem[len3++] = a.elem[i];
		}
	}
	c.length = len3;
	return true;
}
//第四题
void reverseSqList(SqList a[], int left, int right, int len) {
	if (left >= right || right >= len) return;
	SqList temp;
	for (int i = left, j = right; i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}
void Exchange(SqList a[], int m, int n, int len) {
	reverseSqList(a, 0, m+n-1, len);
	reverseSqList(a, 0, n - 1, len);
	reverseSqList(a, n, m + n - 1, len);
}

//第五题
int Binary_search(SqList L, Elemtype e, int* mid) {
	int low = 0, high = L.length - 1;
	while (low < high) {
		*mid = (low + high) / 2;
		if (L.elem[*mid] == e) return *mid;
		else if (L.elem[*mid] < e) {
			low = *mid + 1;
		}
		else {
			high = *mid - 1;
		}
	}
	return -1;
}
bool Search(SqList& L, Elemtype e) {
	int* mid;
	if (Binary_search(L, e, mid) != -1) {
		if (*mid < maxsize - 1) {
			Elemtype temp = L.elem[*mid];
			L.elem[*mid] = L.elem[*mid + 1];
			L.elem[*mid + 1] = temp;
			return true;//代表找到了并完成了交换
		}
		else {
			return false;
		}
	}
	else {
		if (L.length >= maxsize) return false;
		else {
			for (int i = L.length=1; i >=*mid; i--) {
				L.elem[i + 1] = L.elem[i];
			}
		}
		return false;//代表没找到，完成了插入
	}
}