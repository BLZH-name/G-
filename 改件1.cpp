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
//	int* ul;
//
//}elem;
//
//elem E;
//
//void del(elem& E) {
//	delete E.ul;
//	if (E.ul) {
//		cout << "删除成功"<<endl;
//		E.lenth = 0;
//	}
//	else cout << "删除失败"<<endl;
//}
//
//void create(elem& E) { //创建线性表	
//	E.ul = new int[MAXSIZE];
//	if (!E.ul) exit(OVERFLOW);
//	E.lenth = 0;
//}
//
//
//void find_data(elem& E) {
//	cout << "输入要找的值"<<endl;
//	int y, i;
//	cin >> y;
//	cout << y;
//	for (i = 0; i < E.lenth; i++) {
//		if (E.ul[i] == y) {
//			cout << "在第" << i + 1 << "个位置" << endl;
//			return;
//		}
//	}
//	cout << "查无此值"<<endl;
//}
//
//
//void kuall() {
//	cout << "错误操作,重新操作"<<endl;
//	system("pause");
//	system("cls");
//	create(E);
//}
//
//void add_data(elem& E) {
//	cout << "输入要输入的值的数量："<<endl;
//	int n;
//	cin >> n;
//	if (n < 1) kuall();
//	int i, a;
//	cout << "输入值"<<endl;
//	for (i = 0; i < n; i++) {
//		cin >> a;
//		E.ul[i] = a;
//		E.lenth++;
//	}
//	cout << endl;
//}
//
//
//void del1(elem& E) {
//	cout << "输入删除的值下标"<<endl;
//	int a; cin >> a;
//	if (a > E.lenth || a < 1) {
//		cout << "没有"<<endl;
//	}
//	for (int j = a; j < E.lenth; j++)
//		E.ul[j] = E.ul[j + 1];
//	E.lenth--;
//}
//
//void insert_data() {
//	cout << "输入插入的值"<<endl;
//	int ret, i; cin >> ret;
//	cout << "输入插入的位置"<<endl;
//	int got; cin >> got;
//	if (got<0 || got>E.lenth) {
//		cout << "位置不对"<<endl;
//		return;
//	}
//	for (i =E.lenth; i >got; i--) {
//		E.ul[i] = E.ul[i-1];
//	}
//	E.lenth++;
//	E.ul[got] = ret;
//}
//
//
//void del2(elem& E) {
//	cout << "输入要删除元素" << endl; int y, i;
//	cin >> y;
//	cout << y;//多余的
//	for (i = 0; i < E.lenth; i++) {
//		if (E.ul[i] == y) {
//			for (int j = i; j < E.lenth; j++)
//				E.ul[j] = E.ul[j + 1];
//			cout << "删除成功"<<endl;
//			E.lenth--;
//			return;
//		}
//	}
//	cout << "查无此值"<<endl;
//}
//
//void faction() {
//
//	create(E);//创建线性表
//	add_data(E);//加入初始值
//	find_data(E);//寻找
//	del2(E);//删除
//	del1(E);//删除
//	insert_data();//插入
//	cout << "得到：" << endl;
//	for (int i = 0; i < E.lenth; i++)
//		cout << E.ul[i]<<"   ";
//	del(E);//删除表
//}
//
//int main() {
//
//	faction();
//}
