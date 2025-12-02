#pragma once
//无向图  dire graph
#include<iostream>
//#include"diction.h"
#include"tool.h"
#include"mystack.h"
#include<vector>
#include<set>

using namespace std;

template<typename T>

class graph {
private:
	int size;
	int data;
	vector<T>vertex;
	vector<int>ver;
	mystack<int>vet;
	vector<vector<int>>side;//记录连线
	set<int>set;
public:
	graph(int val) :size(0) {
		vertex.resize(val);
		side.resize(val+1, vector<int>(val+1,0));
	}
	void get_point(int val) {
		if (size >= vertex.size()) {
			cout << "容量不足" << endl;
			return;
		}
		vertex[size++] = val;
	}
	void print() {
		for (int num : vertex) cout << num<<"   ";
		int i, j;
		cout << endl;
		/*for (i = 1; i <= size; i++) {
			for (j = 1; j <= size; j++)
				cout << side[i][j];*/
		cout << endl;
		while(!vet.empty()){
			cout << vet.Top()<<"   ";
			vet.pop();
		}
	}
	void get_side(int x,int y) {
		if (x == y) return;
		side[x][y] = 1;
		side[y][x] = 1;
	}

	void fact() {
		int i, j;
		for (i = 1; i <= size;i++) {
			for (j = 1; j <= size; j++) {
				if (side[i][j] == 1) {
					if (set.find(i) == set.end())
					{
						vet.push(i);
						set.insert(i);
					}
					if (set.find(j) == set.end())
					{
						vet.push(j);
						set.insert(j);
					}

				}
					
			}
		}

	}
};

void issue() {
	int n,i=0, m, a, b;
	//cin >> n>>m;
	n = rand_ol(5,5);
	m = rand_ol(4,4);
	cout <<"n为:"<< n <<"    " << "m为：" << m << endl;
	graph<int>p(n);
	while (++i<=n) {
		p.get_point(i);
	}
	i = 0;
	while (i++<m) {
		//cin >> a >> b;
		do{
			a = rand_ol(1, n);
			b = rand_ol(1, n);
		} while (a == b);
		cout << a << "  " << b << endl;
		p.get_side(a, b);
	}
	p.fact();
	p.print();
	//p.print();
}

//template <typename T>
//struct Node {
//	T data;
//	int* to;
//	int len;
//	Node():len(1) {
//		to = new int[len];
//	}
//};
//
//template <typename T>
//class graph {
//private:
//	Node<int> node;
//public:
//	void addup() {
//
//	}
//};