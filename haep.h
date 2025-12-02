#pragma once

#include"tool.h"


template<typename T>

class my_heap {
private:
	int lenth;//动态数组长度
	int size;// 元素个数
	T* data;
	int type;
	void data_iter() {
		lenth *= 2;
		T* newdata = new T[lenth];
		for (int i = 0; i < size; i++)
			newdata[i] = data[i];
		delete[]data;
		data = newdata;
	}

public:
	my_heap(string type_str) :lenth(4),size(0){
		data = new T[lenth];
		if (type_str == "min") type = 0;
		else type = 1;
	}
	
	void judge() {
		int node=size-1;
		int parent = (node - 1) / 2;
		if (type == 1) {
			while (data[node] > data[parent] && node != parent) {
				int temp;
				temp = data[node];
				data[node] = data[parent];
				data[parent] = temp;
				node = parent;
				parent = (node - 1) / 2;
			}
		}
		else {
			while (data[node] < data[parent] && node != parent) {
				int temp;
				temp = data[node];
				data[node] = data[parent];
				data[parent] = temp;
				node = parent;
				parent = (node - 1) / 2;
			}
		}
	}

	int Top() {
		if (empty()) return 0;
		return data[0];
	}


	bool empty() {
		return size == 0;
	}

	bool full_elemt() {
		return size == lenth;
	}


	void add(int val) {
		if (!full_elemt()) data_iter();
		data[size] = val;
		size++;
		judge();
	}

	void print() {
		int a=1;
		char r=' ';
		for (int i = 0; i < size; i++) {
			cout << data[i] << "   ";
			if (i + 1 == power_2(a) - 1) {
				a++;
				cout << endl;
			}
		}
	}
};

//void hap() {
//	my_heap<int>ret("min");
//	int i=0,n = rand_ol(10,20);
//	while (i++<n) {
//		int get = rand_ol(10,100);
//		cout << get << "     ";
//		ret.add(get);
//	}
//	cout << endl;
//	ret.print();
//}





