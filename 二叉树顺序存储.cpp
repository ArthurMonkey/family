#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
typedef int Status;
struct TreeNode {
	Elemtype value;
	bool isEmpty;
};
int main() {
	TreeNode t[maxsize];
	for (int i = 0; i < maxsize; i++) {
		t[i].value = i;
		t[i].isEmpty = true;
	}
	for (int i = 0; i < maxsize; i++) {
		printf("%d ", t[i].value);
	}
	return 0;
}