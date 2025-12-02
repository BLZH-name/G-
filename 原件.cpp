//#include<iostream>
//#include<cstdio>
//#include <random>
//using namespace std;
////#include<limits>
//
//#define MAXSIZE	1000
//
//
//typedef struct {
//	int lenth;
//	int* elem;
//	
//
//
//
//
//}Test;
//
//Test T;
//
//int creat_num_a(int min,int max) {
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int> dist(min, max);
//	return dist(rng);
//}
//
//void print(Test& T) {
//	int i;
//	if (T.lenth < 1) {
//		cout << "没有值可以打印";
//		return;
//	}
//	cout << "剩下的值：" << endl;
//	for (i = 0; i < T.lenth; i++)
//		cout << T.elem[i]<<"  ";
//
//}
//
//void data_delete(Test&T) {
//	delete T.elem;
//	if (T.elem) {
//		cout << "删除成功";
//		T.lenth = 0;
//	}
//	else cout << "删除失败";
//}
//
//void create(Test& T) { //创建线性表	
//	T.elem = new int[MAXSIZE];
//	if (!T.elem) exit(OVERFLOW);
//	T.lenth = 0;
//}
//
//
//void find_data(Test&T) {
//	cout << "输入要找的值";
//	int y,i; 
//	cin >> y;
//	cout<<y;
//	for (i = 0; i < T.lenth; i++) {
//		if (T.elem[i] == y) {
//			cout << "在第" << i + 1 << "个位置"<<endl;
//			return;
//		}
//	}
//	cout << "查无此值";
//}
//
//
//void exit_bl() {
//	cout << "错误操作,重新操作";
//	system("pause");
//	system("cls");
//	create(T);
//}
//
//void add_data(Test&T) {
//	cout << "输入要输入的值的数量：";
//	int n;
//	cin >> n;
//	if (n < 1) exit_bl();
//	int i, a;
//	for (i = 0; i < n; i++){
//		a = creat_num_a(10,1000);
//		T.elem[i] = a;
//		T.lenth++;
//	}
//	cout << endl;
//}
//
//
//void delete_data2(Test&T) {
//	cout << "输入下标";
//	int a; cin >> a;
//	if (a > T.lenth || a < 1) {
//		cout << "没有";
//	}
//	for (int j = a; j < T.lenth; j++)
//		T.elem[j] = T.elem[j + 1];
//	T.lenth--;
//}
//
//void insert_data(){
//	cout << "输入插入的值";
//	int a,i; cin >> a;
//	cout << "输入插入的位置";
//	int g; cin >> g;
//	if (g<0 || g>T.lenth) {
//		cout << "位置不对，该罚！";
//	}
//	for (i = T.lenth-1; i > g; i--) {
//		T.elem[i + 1] = T.elem[i];
//	}
//	T.elem[g] = a;
//	T.lenth++;
//}
//
//
//void delete_data1(Test&T) {
//	cout << "输入元素" << endl; int y, i;
//	cin >> y;
//	cout << y;
//	for (i = 0; i < T.lenth; i++) {
//		if (T.elem[i] == y) {
//			for (int j = i; j < T.lenth; j++)
//				T.elem[j] = T.elem[j + 1];
//			cout << "删除成功";
//			T.lenth--;
//			return;
//		}
//	}
//	cout << "查无此值";
//}
//
//void faction() {
//	
//	cout << "正在创建线性表初始值........"<<endl;
//	create(T);//创建线性表
//	add_data(T);//往里面添加初始值
//	int a = 1;
//	while (a!=6) {
//		print(T);//打印
//		cout << "请选择你的操作：" << endl;
//		cout << "   1.查找    2.删除元素(输入元素)    3.删除元素(输入下标,1开始)   4.删除线性表   5.插入    6.退出"<<endl;
//		cin >> a;
//		switch (a) {
//		case 1:  find_data(T); break;//查找
//		case 2:  delete_data1(T); break;//删除
//		case 3: delete_data2(T); break;//删除
//		case 4:data_delete(T); break;//删除
//		case 5:insert_data(); break;//插入
//		default:
//			cout << "输入的什么玩意儿"<<endl;
//			
//		}
//		system("pause");
//		system("cls");
//	}
//}
//
//int main() {
//
//	faction();
//}
