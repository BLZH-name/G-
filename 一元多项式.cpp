//#include<iostream>
//using namespace std;
//#include<random>
//
//
//int rand_ol(int a,int b) {
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int>dist(a,b);
//	return dist(rng);
//}
//
//
//struct Node {
//	int x;
//	int y;
//	Node* next;
//};
//
//
//class Preo {
//private:
//	Node* node;
//	int* pub;
//	int lenth;
//
//	void newlenth(int newlenth) {
//		int* newpub = new int[newlenth+1];
//		memset(newpub,0,(newlenth+1)*sizeof(int));
//		for (int i = 0; i <= lenth; i++)
//			newpub[i] = pub[i];
//		lenth = newlenth;
//		delete pub;
//		pub = newpub;
//	}
//
//	Node* create(int a,int b) {
//		Node* newnode = new Node;
//		newnode->next = nullptr;
//		newnode->x = a;
//		newnode->y = b;
//		return newnode;
//	}
//
//public:
//	Preo():lenth(4) {
//		pub = new int[lenth+1];
//		memset(pub, 0, (lenth + 1) * sizeof(int));
//		node = create(0, 0);
//	}
//	
//	void push_pub(int a,int b) {
//		if (b > lenth) newlenth(b);
//		pub[b] += a;
//	}
//
//	void print_pub() {
//		bool ret = false;
//		for (int i = 0; i <= lenth;i++) {
//			if (!pub[i]) continue;
//			else if (pub[i] > 0 && ret) cout << "+";
//			cout << pub[i] << "x^" << i;
//			if (!ret) ret = true;
//		}
//	}
//
//	void push_node(int a,int b) {
//		Node* cur = node->next;
//		Node* parent = node;
//		while (cur) {
//			if (b > cur->y) {
//				Node* newnode = create(a,b);
//				parent->next = newnode;
//				newnode->next = cur;
//				return;
//			}
//			else if (b == cur->y) {
//				cur->x += a;
//				return;
//			}
//			parent = cur;
//			cur = cur->next;
//		}
//		Node* newnode = create(a,b);
//		parent->next = newnode;
//	}
//
//	void print_node() {
//		Node* cur = node->next;
//		bool ret = false;
//		while (cur) {
//			if (cur->x != 0) {
//				if (cur->x > 0 && ret) cout << "+";
//				cout << cur->x << "x^" << cur->y;
//				ret = true;
//			}
//			cur = cur->next;
//		}
//	}
//
//};
//
//
//
////int main() {
////	int n = rand_ol(5, 15);
////	Preo p;
////	bool ret = false;
////	for(int i=0;i<n;i++){
////		int a = rand_ol(-10,10);
////		int  b = rand_ol(5,10);
////		p.push_node(a, b);
////		if (a != 0) {
////			if (a > 0 && ret) cout << "+";
////			cout << a << "x^" << b;
////			if (!ret) ret = true;
////		}
////	}
////	ret = false;
////	cout << endl;
////	for (int i = 0;i<n;i++) {
////		int a = rand_ol(-10,10);
////		int b = rand_ol(5,10);
////		p.push_node(a, b);
////		if (a > 0 && ret) cout << "+";
////		cout << a << "x^" << b;
////		if (!ret) ret = true;
////	}
////	cout << endl;
////	p.print_node();
////}
//
//
//void faction() {
//	int cie;
//	while (true) {
//		system("cls");
//		cout << "选择操作：" << endl;
//		cout << "1.线性表实现" << endl;
//		cout << "2.链表实现" << endl;
//		cout << "3.退出" << endl;
//		cin >> cie;
//		if (cie == 3) return;
//		if (cie == 1 || cie == 2) break;
//		cout << "无效操作";
//		system("pause");
//	}
//	int a, b, n;
//	cout << "输入第一个式子的项数" << endl;
//	//cin >> n;
//	n = rand_ol(5,10);
//	cout << n << endl;
//	Preo p;
//	while (n--) {
//		//cin >> a >> b;
//		a = rand_ol(-5,15);
//		b = rand_ol(5,10);
//		cout << a << "	" << b << endl;;
//		if (cie == 1) p.push_pub(a, b);
//		else p.push_node(a, b);
//	}
//
//
//	cout << "输入第二个式子的项数" << endl;
//	//cin >> n;
//	n = rand_ol(5, 10);
//	cout <<  n << endl;
//	while (n--) {
//		//cin >> a >> b;
//		a = rand_ol(-5, 15);
//		b = rand_ol(5, 10);
//		cout <<a << "	" <<  b << endl;;
//		if (cie == 1) p.push_pub(a, b);
//		else p.push_node(a, b);
//	}
//	cout << "最终式子:" << endl;
//	if (cie == 1) p.print_pub();
//	else p.print_node();
//}
//
//
//
//
//int main() {
//	faction();
//}
//
