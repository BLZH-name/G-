
//class Tree {
//private:
//	int data;
//	Tree* left;
//	Tree* right;
//	Tree* y;
//	int hight;
//public:
//	Tree(int val) : data(val), left(nullptr), right(nullptr),hight(1) {}
//
//	void fact(int val) {
//		Tree* T = nullptr;
//		push(T, val);
//	}
//	
//	int max(int a,int b) {
//		return a > b ? a : b;
//	}
//
//	int gethight(Tree*& T) {
//		if (T == NULL) return 0;
//		return T->hight;
//	}
//
//	int getblance(Tree*&T){
//		return gethight(T->left) - gethight(T->right);
//	}
//
//	void Right(Tree*&T) {
//		Tree* newnode = new Tree((T->left)->data);
//		newnode->right = T;
//		T = newnode;
//	}
//
//	void Left(Tree*&T) {
//		Tree* newnode = new Tree((T->right)->data);
//		newnode->left = T;
//		T = newnode;
//	}
//
//
//	void LeftRight(Tree*&T) {
//		Tree* newnode = new Tree((T->left)->data);
//		newnode->left = newnode->right;
//		newnode->right = T;
//		T = newnode;
//	}
//	
//	void RightLeft(Tree*& T) {
//		Tree* newnode = new Tree((T->right)->data);
//		newnode->right =newnode->left;
//		newnode->left = T;
//		T = newnode;
//	}
//
//
//	Tree* push(Tree*&T,int val) {
//		if (T == NULL)
//			return create(T,val);
//		else if (val > T->data) T->right=push(T->right, val);
//		else T->left=push(T->left, val);
//		T->hight = 1 + max(gethight(T->left),gethight(T->right));
//		int blance = getblance(T);
//		if (blance > 1 && getblance(T->left) > 0) Right(T);
//		else if (blance > 1 && getblance(T->left) < 0)  LeftRight(T);
//		else if (blance < -1 && getblance(T->right) < 0) Left(T);
//		else if (blance < -1 && getblance(T->right)>0) RightLeft(T);
//		
//	}
//
//	Tree* create(Tree*&T,int val) {
//		Tree* newnode = new Tree(val);
//		 T = newnode;
//		 return T;
//	}
//	void print(Tree*T) {
//		if (T == NULL) return;
//		cout << "节点为：" << T->data << "   " << "高度为：" << T->hight<<endl;
//		print(T->left);
//		print(T->right);
//	}
//};


#pragma once
#include <cstddef>
#include<iostream>
using namespace std;


class Tree {
public:
	Tree* right;
	Tree* left;
	int data;
	int hight;
	Tree(int val) :data(val),left(nullptr),right(nullptr),hight(1){}
};

Tree* newcreate(Tree*&T,int val) {
	Tree* newnode = new Tree(val);
	//T = newnode;
	return newnode;
}


int gethight(Tree*& p) {
	return p == nullptr ? 0 : p->hight;
}

int getblance(Tree*& p) {
	return gethight(p->left) - gethight(p->right);
}

	void Right(Tree*&T) {
		Tree* newnode = T->left;
		T->left = newnode->right;
		newnode->right = T;
		T = newnode;
		T->hight = 1 + max(gethight(T->left), gethight(T->right));
		T->right->hight = 1 + max(gethight(T->right->left), gethight(T->right->right));
	}

	void Left(Tree*&T) {
		Tree* newnode = T->right;
		T->right=newnode->left;
		newnode->left = T;
		T = newnode;

		T->hight = 1 + max(gethight(T->right), gethight(T->left));
		T->left->hight = 1 + max(gethight(T->left->right), gethight(T->left->left));
	}


	void LeftRight(Tree*&T) {
		Left(T->left);
		//Right(T);
		/*Tree* newnode = T->left->right;
		T->left->right=newnode->left;
		newnode->left=T->left;
		T->left = newnode;
		T->left->hight = 1 + max(gethight(T->left->right), gethight(T->left->left));*/
		Right(T);
	}
	
	void RightLeft(Tree*& T) {
		Right(T->right);
		Left(T);
		/*Tree* newnode = T->right->left;
		T->right->left = newnode->right;
		T->right = newnode;
		T->right = newnode;
		T->right->hight = 1 + max(gethight(T->right->left), gethight(T->right->right));*/
	}

Tree* create(Tree*&p,int val) {
	if (p == nullptr) return newcreate(p, val);
	else if (val > p->data) p->right = create(p->right, val);
	else p->left = create(p->left, val);
	p->hight = 1 + max(gethight(p->right), gethight(p->left));
	int blance;
	blance = getblance(p);
	if (blance > 1 && getblance(p->left) > 0) Right(p);
	else if (blance > 1 && getblance(p->left) < 0)  LeftRight(p);
	else if (blance < -1 && getblance(p->right) < 0) Left(p);
	else if (blance < -1 && getblance(p->right)>0) RightLeft(p);
	return p;
	
}


void print_tree(Tree*&p) {
	if (p == nullptr) return;
	print_tree((*p).left);
	cout << "节点:" << (*p).data << "   " << "高度:" << (*p).hight << "   "<<endl;
	print_tree((*p).right);
}

//void trr() {
//	Tree* T = nullptr;
//	int n, i, a;
//	n = rand_ol(10, 30);
//	cout << "n为：" << n << endl;
//	for (i = 0; i < n; i++) {
//		a = rand_ol(5, 100);
//		cout << a << "   ";
//		T = create(T, a);
//	}
//	cout << endl;
//	cout << endl;
//	//print(T);
//	mystack<int>l;
//	l = print_stack(T);
//	cout << endl;
//	while (!l.empty()) {
//		cout << l.Top() << "  ";
//		l.pop();
//	}
//}









