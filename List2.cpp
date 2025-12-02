//using namespace std;
//#include<iostream>
//#include<random>
//
//int rand_ol(int min,int max) {
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int>dist(min,max);
//	return dist(rng);
//}
//
//typedef struct list {
//	list* next;
//	list* preve;
//	int data;
//};
//
//class link {
//private:
//	list* node;
//	int lenth;
//
//	bool empty(list*& p) {
//		return !p;
//	}
//
//	void push(int val) {
//		list* cur = new list;
//		cur->data = val;
//		cur->next = nullptr;
//		if (!node->next) {
//			node->next = cur;
//			cur->preve = node;
//			lenth++;
//			return;
//		}
//		list* re = node->next;
//		while (re->next) re = re->next;
//		re->next = cur;
//		cur->preve = re;
//		lenth++;
//	}
//
//public:
//	link():lenth(0) {	
//		node = new list;
//		node->data = 0;
//		node->next = NULL;
//		node->preve = NULL;
//	}
//	~link() {
//		delete node;
//	}
//
//	void insert() {
//		int a, b;
//		if (empty(node->next)) {
//			cout << "空链表" << endl;
//			return;
//		}
//		cout << "输入插入的位置，插入的值"<<endl;
//		cin >> a >> b;
//		if (a<1 || a>lenth + 1) {
//			cout << "无效位置" << endl;
//			return;
//		}
//		else if (a == lenth+1) push(b);
//		else {
//			list* re = node;
//			int t = 0;
//			while (re) {
//				if (t + 1 == a) {
//					list* cur = new list;
//					list* pot = re->next;
//					cur->next = nullptr;
//					cur->preve= nullptr;
//					cur->data = b;
//					re->next = cur;
//					cur->preve = re;
//					cur->next = pot;
//					pot->preve = cur;
//					break;
//				}
//				re = re->next;
//				t++;
//			}
//		}
//		lenth++;
//	}
//
//	void find_data() {
//		if (empty(node->next)) {
//			cout << "空链表" << endl;
//			return;
//		}
//		list* re = node;
//		int ret = 0;
//		cout << "输入元素" << endl;
//		int y; cin >> y;
//		while (re->next) {
//			ret++; re = re->next;
//			if (re->data == y) {
//				cout << "在第" << ret << "位" << endl;
//				return;
//			}
//		}
//		cout << "查无此值" << endl;
//	}
//
//
//	void size_delete() {
//		if (empty(node->next)) {
//			cout << "空链表" << endl;
//			return;
//		}
//		list* re = node;
//		cout << "输入删除的元素" << endl;
//		int t; cin >> t;
//		while (re->next) {
//			if (re->next->data == t)  {
//				list* ret = re->next->next;
//				if (ret) {
//					list* del = re->next;
//					re->next = ret;
//					ret->preve = re;
//					delete del;
//				}
//				else {
//					delete re->next;
//					re->next = nullptr;
//					re->preve = nullptr;
//				}
//				lenth--;
//				return;
//			}
//			re = re->next;
//		}
//		cout << "查无此值" << endl;
//	}
//	void create() {
//		list* re = node->next;
//		/*if (node->next) node->next = nullptr;*/
//		if (re) {
//			cout << "要清空之前的操作吗" << endl;
//			cout << "1.YES            2.NO" << endl;
//			int fale; cin >> fale;
//			switch (fale) {
//			case 1:
//				while (re) {
//					list* mo = new list;
//					mo = re;
//					re = re->next;
//					delete mo;
//				}
//				node->next = nullptr;
//				lenth = 0;
//				break;
//			case 2:break;
//			default:
//				cout << "操作失败，正在返回上一级" << endl;
//				return;
//			}
//			
//		}
//		int t,n = rand_ol(10,20);
//		cout << "n为：" << n<<endl;
//		while (n--) {
//			t = rand_ol(10,100);
//			push(t);
//		}
//		cout << "加入完成" << endl;
//	}
//	void print() {
//		list* ret = node;
//		if (!node->next) return;
//		cout << "当前链表为:"<<endl;
//		while (ret->next) {
//			ret = ret->next;
//			cout << ret->data << "->";
//		}
//		
//		cout << endl;
//		while (ret) {
//			cout << ret->data << "<-";
//			ret = ret->preve;
//			if (!ret->preve) break;
//			
//		}
//		cout << endl;
//		cout << "lenth为：" << lenth<<endl;
//	}
//
//	void title() {
//		cout << endl;
//		cout << "1.初始化单链表" << endl;
//		cout << "2.删除" << endl;
//		cout << "3.插入" << endl;
//		cout << "4.查找" << endl;
//		cout << "5.退出" << endl;
//
//	}
//};
//
//void link_test() {
//	link rep;
//	while (1) {
//		system("cls");
//		rep.print();
//		rep.title();
//		int a; cin >> a;
//		switch (a) {
//		case 1:
//			rep.create();
//			system("pause");
//			break;
//		case 2:
//			rep.size_delete();
//			system("pause");
//			break;
//		case 3:
//			rep.insert();
//			system("pause");
//			break;
//		case 4:
//			rep.find_data();
//			system("pause");
//			break;
//		case 5:
//			return;
//		default:
//			cout << "凸（-  - ）凸" << endl;
//			cout << "毫无意义" << endl;
//			system("pause");
//		}
//	}
//}
//
//int main() {
//	link_test();
//}
//
//
