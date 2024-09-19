#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
#define Error 0
#define Ok 1
typedef int Elemtype;
typedef int Status;
struct Node {
	Elemtype data;
	int next;//int下标，做指针
}node[maxsize];
