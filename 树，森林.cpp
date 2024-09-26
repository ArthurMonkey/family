#include<stdio.h>
#include<stdlib.h>
#define maxsize 20
typedef int Elemtype;
//树的双亲表示法
//根节点的双亲域=-1，其余节点的双亲域均用数组中双亲节点的下标节点来表示
typedef struct {
	Elemtype data;
	int parent;//双亲位置域，因为是用数组存的,所以要知道
}PTNode;
typedef struct {
	PTNode nodes[maxsize];//双亲表示
	int n;//节点数
}PTree;//树里存的是所有的双亲节点以及节点总数

//孩子兄弟表示法
typedef struct CSNode {
	Elemtype data;
	struct CSNode* firstchild, * nextsibling;//sibling 兄弟姐妹的英语单词
}CSNode, *CSTree;

//编程求以孩子兄弟表示法存储的森林的叶子节点数
int Leaves(CSTree T) {
	if (T == NULL) return 0;
	if (T->firstchild == NULL) {//如果一个节点没有孩子，那它在森林里肯定是叶子节点
		return 1 + Leaves(T->nextsibling);//返回叶子节点和其兄弟子树中的叶子节点总数
	}
	else {
		return Leaves(T->firstchild) + Leaves(T->nextsibling);
	}
}