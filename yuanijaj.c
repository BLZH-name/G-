//using namespace std;
//
//#include"mystack.h"
//#include<iostream>
//#include "mytree.h"
////#include"mystack.h"
//#include"myqueue.h"
//#include<string>
//
//#include"haep.h"
//
//#include"graph.h"
//
//#include"prifix.h"
//
////#include"diction.h"
//
//#include"tool.h"
//
//
////int rand_ol(int min,int max);
////void stack_test();
//
//
//
//void faction() {
//	//trr();//树
//	//mat();//队列
//	//lize();//序列化
//	//Diction<string,int> ret("name", 20);
//	//ret.print();
//	//issue();
//	//operation();
//	hap();
//}
//
//int main() {
//	//stack_test(); 测试栈
//	faction();
//}
//
//
//#include <iostream>
//using namespace std;
//
//
//struct list {
//	int data[1000];
//	int lenth;
//};
//
//list* fate(list* ret,int x,int y) {
//	//内容略
//}
//int main() {	
//	list* p;
//	fate(p,10,25);
//
//}


////第一题
//template<typename SElemType>
//struct DblStack {
//	int top[2], bot[2];
//	SElemType* V;
//	int m;
//};
//
//template<typename SElemType>
//void create(DblStack<SElemType>& p,int size) {
//	p.m = size;
//	p.V = new SElemType[size];
//	p.bot[0] = 0;
//	p.top[0] = p.bot[0] - 1;
//	p.bot[1] = size - 1;
//	p.top[1] = p.bot[1] + 1;
//}
//
//template<typename SElemType>
//bool empty_stack_0(DblStack<SElemType>&p) {
//	return p.bot[0] == p.top[0] - 1;
//}
//
//template<typename SElemType>
//bool empty_stack_1(DblStack<SElemType>& p) {
//	return p.bot[1] == p.top[1] + 1;
//}
//
//template<typename SElemType>
//bool push_max(DblStack<SElemType>&p) {
//	return p.top[0] + 1 == p.top[1]&&;
//}
//
//template<typename SElemType>
//void push0(DblStack<SElemType>&p,SElemType val) {
//	if (!push_max(p)) return;
//	top[0]++;
//	p.V[top[0]] = val;
//}
//
//template<typename SElemType>
//void push1(DblStack<SElemType>& p, SElemType val) {
//	if (!push_max(p)) return;
//	top[1]--;
//	p.V[top[1]] = val;
//}
//
//template<typename SElemType>
//bool Pop0(DblStack<SElemType>& p, SElemType& out) {
//	if (empty0(p)) {
//		cout << "栈0为空，无法出栈！" << endl;
//		return false;
//	}
//	out = p.V[p.top[0]];   
//	p.top[0]--;               
//	return true;
//}
//template<typename SElemType>
//bool Pop1(DblStack<SElemType>& p, SElemType& out) {
//	if (empty0(p)) {
//		cout << "栈1为空，无法出栈！" << endl;
//		return false;
//	}
//	out = p.V[p.top[1]];   
//	p.top[1]++;               
//	return true;
//}

//#include<iostream>
//using namespace std;
//#include<cstring>
//#include<algorithm>
//#include<stack>
//
////第二题
//bool ifstr(string str) {
//	stack<char>ret;
//	int n = str.size()-1;
//	int i = 0;
//	while (i<=n/2) ret.push(str[i++]);
//	if (n % 2 == 0) i = n / 2;
//	while (i<=n) {
//		if (str[i] != ret.top()) return false;
//		ret.pop();
//		i++;
//	}
//	return true;
//}

//void Stack() {
//	int a;
//	stack<int>ret;
//	while (cin >> a) {
//		if (a == -1) {
//			cout << ret.top();
//			if (!ret.empty()) {
//				cout << "空栈，无法出栈" << endl;
//				continue;
//			}
//			else ret.pop();
//		}
//		else { 
//			if (ret.top() == ret.maxsize - 1) {//ret.maxsize自拟数据，表示栈的最大值
//				cout << "栈满" << endl;
//				continue;
//			}
//			ret.push(a); 
//		}
//	}
//}


////第四题
//#include<string>
//#include<cmath>
//#include<cctype>
//int Numse(string str) {
//	int i=0,ret = str.size();
//	int num = 0;
//	while (ret--) {
//		num = num + (pow(10, ret)) * (str[i] - '0');
//		i++; 
//	}
//	return num;
//}
//
//double sign(char c,double a,double b) {
//	if (c == '+') return a + b;
//	if (c == '-') return a - b;
//	if (c == '*') return a * b;
//	if (c == '/') {
//		if (b == 0) {
//			cout << "无效" << endl;
//			return 0;
//		}
//		return a / b;
//	}
//}
//
//int caculate() {
//	stack<double>num;
//	string str;
//	string tr;
//	getline(cin,str);
//	int i = 0;
//	while(i<str.size()) {
//		if (str[i] == ' ') {
//			i++; continue;
//		}
//		while (isdigit(str[i])) {
//			//isdigit函数，判断字符是否是0到1
//			tr += str[i];
//			i++;
//		}
//		if (!tr.empty()) {
//			num.push(Numse(tr));
//			tr.clear();
//		}
//		if (str[i] == '+' || str[i] == '/' || str[i] == '*' || str[i] == '-') {
//			if (num.size()<2) {
//				cout << "表达式有问题" << endl;
//				return 0;
//			}
//			double b = num.top(); num.pop();
//			double a = num.top(); num.pop();
//			double ret = sign(str[i],a,b);
//			num.push(ret);
//		}
//		if (str[i] == '$') break;
//		i++;
//	}
//	cout << num.top();
//	return 0;
//}


//#define MAXSIZE 100
//template<typename T>
//bool iost(char ret[],stack<T>&val,int n) {
//	int i = 0;
//	for (i = 0; i < n;i++) {
//		if (ret[i] == 'O') {
//			if (val.empty) return false;
//			val.pop();
//		}
//		if (ret[i] == 'I')
//			if (val.top == MAXSIZE - 1) return false;
//		val.push(1);
//		}
//	return true;
//}





//typedef struct List {
//	List* next;
//	int data;
//};

//typedef struct Rear {
//	List* rear;
//};
//
//bool empty(Rear*p) {
//	return p->rear->next == p->rear;
//}
//
//bool dequeue(Rear*p,int val) {
//	if (empty(p)) return false;
//	List* head = p->rear->next;
//	List* front = head->next;
//	val = front->data;
//	head->next = front->next;
//	if (front == p->rear) p->rear = head;
//	delete front;
//	return true;
//}
//
//void enqueue(Rear*p,int val) {
//	List* newnode = new List;
//	newnode->data = val;
//	newnode->next = p->rear->next;
//	p->rear->next = newnode;
//	p->rear = newnode;
//}
//
//void list_create(Rear*p) {
//	List* head = new List;
//	head->next = head;
//	p->rear = head;
//}
//
//void queue_list() {
//	Rear* r;
//	list_create(r);
//}
//
//int main() {
//	queue_list();
//}


//
//void enqueue(int Q[], int m,int val,
//	int front, int rear, int tag) {
//	if (rear == front && tag == 1) return;
//	Q[rear] = val;
//	rear=(rear+1)%m;
//	if (rear == front) tag = 1;
//}
//void dequeue(int Q[], int m,
//	int front, int rear, int tag) {
//	if (rear == front && tag == 0) return;
//	front=(front+1)%m;
//	if (rear == front) tag == 0;
//}


//template <typename T>
//struct Queue {
//	T* data;
//	int front;
//	int rear;
//	int capcity;
//	int size;
//	Queue() :capcity(1000){
//		data =new Queue[capcity];
//	}
//};
//void delete_head(Queue<int> p) {
//	if (p.rear== p.front) return;
//	p.rear--;
//	if (p.rear < 0) p.rear = p.capcity - 1;
//}
//void push_data(Queue<int> p,int val) {
//	if ((p.rear + 1)%p.capcity == p.front) return;
//	p.front--;
//	if (p.front < 0) p.front = p.capcity - 1;
//	p.data[p.front] = val;
//}


////9.1
//int Ack(int m,int n) {
//	int ret = 0;
//	if (m == 0) ret = n + 1;
//	else if (m != 0 && n == 0) ret = Ack(m-1,1);
//	else {
//		ret = Ack(m - 1, Ack(m, n - 1));
//	}
//	return ret;
//}
//
////9.2
//struct node {
//	int n;
//	int m;
//};
//
//int Ackermann(int m,int n) {
//	stack<node>s;
//	node node, temp;
//	node.m = m;
//	node.n = n;
//	s.push(node);
//	int ret = 0;
//	while(!s.empty()){
//		node=s.top();
//		s.pop();
//		if (node.n == -1) node.n = ret;
//		if (node.m == 0) {
//			ret = node.n + 1;
//		}
//		else if (node.n == 0) {
//			temp.m = node.m - 1;
//			temp.n = 1;
//			s.push(temp);
//		}
//		else {
//			temp.m = node.m - 1;
//			temp.n = -1;
//			s.push(temp);
//			temp.m = node.m;
//			temp.n = node.n - 1;
//			s.push(temp);
//		}
//	}
//	return ret;
//}


////第十题
//typedef struct List {
//	List* next;
//	int data;
//};
////10.1
//int List1(List*p,int max) {
//	int ret=0;
//	if (!p) return 0;
//	if (p->next) ret=List1(p->next,max);
//	max = ret > p->data ? ret : p->data;
//	return max;
//}
////10.2
//int List2(List*p) {
//	if (!p) return 0; 
//	if (!p->next) return 1;
//	int ret=List2(p->next)+1;
//	return ret;
//}
////10.3
//int List3(List*p,int sum,int n) {
//	sum += p->data;
//	n++;
//	int ret = 0;
//	if (!p->next) ret= sum / n;
//	else ret=List3(p->next,sum,n);
//	return ret;
//}



using namespace std;
#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>


int proce(int limite,int colim,
	int left,int right) {
	if (colim == limit) return 1;
	int pos = 0;
	int most = 0;
	pos = limite & (~(colim|left|right));
	int res = 0;
	while (pos != 0)I{
		most = pos & (~pos+1);
		pos = pos - most;
		res += proce(limite, colim | most,
			(left | most) << 1,
			(right | most) >> 1);
	}
	return res;

}



int main() {



}