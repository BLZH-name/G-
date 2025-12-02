#pragma once

#include<iostream>
using namespace std;
#include"tool.h"
#include<signal.h>


template<typename T>
class myqueue_arr {
private:
	T* data;//数据
	int size;//数组大小
	int begin;
	int rear;
public:
	myqueue_arr(int val) :size(val), begin(0), rear(1){
		data = new T[size];
	};
	

	void dequeue() {
		begin++;
	}

	void print() {
		int ret = begin;
		while (ret!=rear-1) {
			cout << data[ret++%size]<<"   ";
		}
	}
	void inserqueue(int val) {
		data[rear - 1] = val;
		++rear % size;
		decide();
	}


	void enqueue(int val) {
		
		cout << "begin:" << begin << "   " << "rear:" << rear <<endl;
		if (decide()) {
			cout << "队列已满，强制中断输入";
			//exit();
			exit(EXIT_FAILURE);
			//abort();
			//raise(SIGKILL);	
		}
		data[rear-1] = val;
		rear++;
		if (rear >= size) rear = rear%size;
	}

	bool decide() {
		return begin == rear;
	}
};

//void mat() {
//	cout << "输入数组大小：";
//	int y; cin >> y;
//	myqueue_arr<int>ret(y);
//	int i, n;
//	cout << "输入需要的数据个数：";
//	cin >> n;
//	for (i = 0; i < n; i++) {
//		ret.enqueue(rand_ol(10, 50));
//	}
//	system("pause");
//	ret.print();
//	system("pause");
//
//	ret.inserqueue(rand_ol(10, 78));
//	ret.print();
//}


