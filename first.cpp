#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int d, int b) {
	return d < b;
}
int main() {
	int a[5] = { 0, 3 ,2, 4,7 };
	sort(a, a + 5, cmp);
	for (int i = 0; i < 5; i++) {
		printf("%d ", a[i]);
	}
	return 0;
}