#pragma once

using namespace std;
#include<iostream>

template<typename T>
class mystack {
private:
	T* data;
	int lenth;//动态数组长度
	int top;//栈顶索引

	void expand() {
		int newlenth = lenth * 2;
		T* newdata = new T[newlenth];
		for (int i = 0; i <= top; i++) {
			newdata[i] = data[i];
		}
		delete [] data;
		data = newdata;
		lenth = newlenth;
	}


public:

	mystack():lenth(4),top(-1){
		data = new T[lenth];
	}

	void push(T ret) {
		if (top+1 >= lenth) expand();
		data[++top] = ret;
	}

	bool empty()const {
		return top == -1;
	}

	T Top() {
		if (empty()) {
			cout << "栈为空，无元素法返回"<<endl;
			return 0;
		}
		return data[top];
	}
	void pop() {
		if (empty()) {
			cout << "元素为空" << endl;
			return;
		}
		top--;
	}
};


//mystack<int> print_stack(Tree* p) {
//	//cout << p->data << "   " << p->hight<<endl;
//	//if (p == nullptr) return;
//	//print_stack(p->left);
//	//print_stack(p->right);
//	mystack<int>ret1;
//	if (p == nullptr) return ret1;
//	mystack<Tree*>sr;
//	sr.push(p);
//	while (!sr.empty()) {
//		Tree* newnode = sr.Top();
//		sr.pop();
//		ret1.push(newnode->data);
//		if (newnode->right != nullptr)
//			sr.push(newnode->right);
//		if (newnode->left != nullptr)
//			sr.push(newnode->left);
//	}
//	return ret1;
//}





















































