#pragma once

using namespace std;
#include"tool.h"
#include<iostream>
#include<cstring>

//template<typename T>


class Prefix {
public:
	int end;
	int pass;
	Prefix* next[26];
	Prefix() :pass(0), end(0) {
		memset(next, 0, sizeof(next));
	}
};

//template<typename T>
class Probro {
private:
	Prefix* root;
public:
	Probro() :root(new Prefix()) {}
	/*~Probro() { destroTree(root); }*/

	void destroTree(Prefix* node) {
		if (!node) return;
		for (int i = 0; i < 26; i++) {
			destroTree(node->next[i]);
		}
		delete node;
	}

	void insert(string str) {
		int index;
		Prefix* cur = root;
		for (char i : str) {
			index = i - 'a';
			cur->pass++;
			if (!cur->next[index]) cur->next[index] = new Prefix();
			cur = cur->next[index];
		}
		cur->end++;
	}


	bool search(Prefix* node, string str, int ind) {
		int index,i=0;
		if (ind == str.size()) {
			cout << "匹配" << endl;
			return true;
		}
		index = str[ind] - 'a';
		if (node->next[index])search(node->next[index], str, ind+1);
		else {
			cout << "不匹配" << endl;
			return false;
		}
		
	}

	void delete_data(Prefix* node,string str,int ind) {
		int index, i = 0;
		if (ind == str.size()) {
			return ;
		}
		index = str[ind] - 'a';
		if (node->next[index]) {
			node->end--;
			node->pass--;
			if (node->pass == 0) {
				//for (i = 0; i < 26; i++) {
					destroTree(*node->next);
				//}
				return;
			}
			delete_data(node->next[index], str, ind + 1);
		}
	}

	void print(Prefix* node,string str,int level) {
		if (!node) return ;
		string indent(level*4,' ');
		cout << indent << "-" << str;
		cout << "(pass=" << node->pass << ",end=" << node->end << ")" << endl;
		for (int i=0; i < 26;i++) {
			if (node->next[i]) {
				char c = 'a' + i;
				print(node->next[i],str+c,level+1);
			}
		}
	
	}

	void faction() {
		Prefix* node = root;
		string str;
		//print(node,str,1);
		//cin >> str;
		//search(root, str, 0);
		cin >> str;
		if (search(node, str, 0)) {
			delete_data(node, str, 0);
			print(node, str, 1);
		}
		else cout << "不存在" << endl;
		//str.clear();
		
		//destroTree(node);
	}

};


void operation() {
	Probro p;
	string str;
	int m = rand_ol(4, 10);
	while (m--) {
		int n = rand_ol(4, 10);
		while (n--) {
			str += char(rand_ol(97, 122));//创建字符串
		}
		cout << str << endl;
		p.insert(str);//处理
		str.clear();
	}
	//int n;
	//cin >> n;
	//while (n--) {
	//	cin >> str;
	//	p.insert(str);//处理
	//	str.clear();
	//}
	p.faction();
}


//#include"tool.h"
//#include<iostream>
//#include<cstring>
//#include<string>
//
////template<typename T>
//
//
//class Prefix {
//public:
//	int end;
//	int pass;
//	Prefix():pass(0),end(0) {}
//};
//
////template<typename T>
//class Probro{
//private:
//	Prefix val[26];
//public:
//	Probro(){
//
//		Prefix* val = new Prefix[26];
//	}
//	void insert(string str) {
//		int i = 0;
//		while (i<str.size()-1) {
//			val[int(str[i]) - 97].pass++;
//			if (i == str.size() - 2) val[int(str[i]) - 97].end++;
//			i++;
//		}
//	}
//	void print() {
//		int i = 0;
//		while (i<26) {
//			cout << char(i+97)<<"  " << "：" << endl;
//			cout << "pass:" << val[i].pass<<endl;
//			cout << "end:" << val[i++].end<<endl;
//		}
//	}
//};
//
//
//void operation() {
//	Probro p;
//	string str;
//	int m = rand_ol(4, 10);
//	while (m--) {
//		int n = rand_ol(4, 10);
//		while (n--) {
//			str += char(rand_ol(97, 122));//创建字符串
//		}
//		cout << str<<endl;
//		p.insert(str);//处理
//		str.clear();
//	}
//	p.print();
//}


//前缀和结构体实现
//struct Node {
//	int pass;
//	int end;
//	Node() :pass(0), end(0) {}
//};
//void operation() {
//	Node* node = new Node[26];
//	string str;
//	int i = 0, n = rand_ol(5,10),m=rand_ol(5,10);
//	
//	while (m--) {
//		i = 0;
//		n = rand_ol(5, 10);
//		int y = n;
//		while (y--) {
//			str += char(rand_ol(97, 122));//创建字符串
//		}
//		cout << str<<endl;
//		while (i++ < n) {
//			node[int(str[i]) - 97].pass++;
//			if (i == n-1) node[int(str[i]) - 97].end++;
//		}
//		str.clear();
//	}
//	cout << endl;
//	i = 26;
//	while (i--) {
//		cout << node[i].pass;
//	}
//	i = 26;
//	cout << endl;
//	while (i--) {
//		cout << node[i].end;
//	}
//}


























