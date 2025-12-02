//using namespace std;
//
//#include<iostream>
//#include<random>
//
//
//int rand_ol(int min,int max) {
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int>dist(min,max);
//	return dist(rng);
//}
//
//typedef struct list {
//	list* next;
//	int data;
//};
//
//bool my_empty(list*p);
//
//void push(int val,list*& p) {
//	list* cur = new list;
//	cur->data = val;
//	cur->next = nullptr;
//	if (!p) p = cur;
//	else {
//		list* ret = p;
//		while (ret->next) ret = ret->next;
//		ret->next = cur;
//	}
//}
//
//int lenth_size(list*p) {
//	int i = 0;
//	while (p) {
//		i++;
//		p = p->next;
//	}
//	return i;
//}
//
//void create(list*& p) {
//as:
//	list* re = p;
//	if (p) {
//		cout << "是否清空之前的链表" << endl;
//		cout << "1.是                2.否" << endl;
//		int t; cin >> t;
//		if (t != 2 && t != 1) {
//			cout << "无效操作,拜拜了您嘞" << endl;
//			return;
//		}
//		while (p&&t==1) {
//			p = p->next;
//			delete re;
//			re = p;
//		}
//	}
//	if (!p) {
//		cout << "初始化成功" << endl;
//		cout << "选择初始值的构成方式：" << endl;
//	}
//	cout << "1.自己加入值        2.随机生成值" << endl;
//	int t,n,a; cin >> t;
//	switch (t) {
//	 case 1:
//		 cout << "输入需要的个数" << endl;
//		 cin >> n;
//		 cout << "开始输入值" << endl;
//		 while (n--) {
//			 cin >> a;
//			 push(a,p);
//		 }
//		 break;
//	case 2:
//		n = rand_ol(10,20);
//		while (n--) {
//			a = rand_ol(10,100);
//			push(a,p);
//		}
//		break;
//	default:
//		cout << "??????????" << endl;
//		cout << "你在输入什么？找茬吗" << endl;
//		system("pause");
//		goto as;
//	}
//	cout << "创建成功" << endl;
//
//	
//}
//
//void size_delete(list*&p) {
//	if (my_empty(p)) {
//		cout << "当前为空链表或者未创建链表" << endl;
//		cout << "即将返回上一级" << endl;
//		return;
//	}
//	cout << "输入你要删除的值" << endl;
//	int t;cin >> t;
//	list* ret = p;
//	if (ret->data==t) {
//		list* cur = p->next;
//		delete p;
//		p= cur;
//		cout << "已删除" << endl;
//		return;
//	}
//	while(ret) {
//		if (ret->next->data == t&&ret->next->next) {
//			list* cur = ret->next->next;
//			delete ret->next;
//			ret->next = cur;
//			cout << "已删除" << endl;
//			return;
//		}
//		if (ret->next->data == t && !ret->next->next)
//		{
//			list* cur = ret->next;
//			delete cur;
//			ret->next = nullptr;
//			cout << "已删除" << endl;
//			return;
//		}
//		ret = ret->next;
//
//	}
//	cout << "查无此值" << endl;
//}
//
//void size_find(list*&p) {
//	if (my_empty(p)) {
//		cout << "当前为空链表或者未创建链表" << endl;
//		cout << "即将返回上一级" << endl;
//		return;
//	}
//	list* ret = p;
//	int i = 0;
//	cout << "输入查找的元素" << endl;
//	int num; cin >> num;
//	while (ret) {
//		i++;
//		if (ret->data == num) {
//			cout << "在第" << i<< "个位置" << endl;
//			
//			return;
//		}
//		ret = ret->next;
//	}
//}
//
//void print(list* e) {
//	if (my_empty(e)) {
//		cout << "当前为空链表或者未创建链表" << endl;
//		cout << "即将返回上一级" << endl;
//		return;
//	}
//	cout << "当前链表：";
//	while (e) {
//		cout << e->data;
//		if (e->next) cout << "->";
//		e = e->next;
//	}
//	cout << endl;
//}
//
//void prin(list* p) {
//	if (p) print(p);
//	cout << "请选择操作" << endl;
//	cout << "1.初始化列表" << endl;
//	cout << "2.删除元素" << endl;
//	cout << "3.查找元素" << endl;
//	cout << "4.插入值" << endl;
//	cout << "5.退出" << endl;
//}
//
//void insert_data(list*& p) {
//	if (my_empty(p)) {
//		cout << "当前为空链表或者未创建链表" << endl;
//		cout << "即将返回上一级" << endl;
//		return;
//	}
//	list* ret = p;
//	int len = lenth_size(p);
//	int a, b,i=1;
//	cout << "选择插入的值的位置" << endl;
//	cin >> a;
//	if (a>len+1||a<1) {
//		cout << "无效位置" << endl;
//		return;
//	}
//	cout << "选择插入的值"<<endl;
//	cin >> b;
//	cout << "请稍等.........." << endl;
//	if (a == len + 1) {
//		push(b, p);
//		return;
//	}
//	if (a == 1) {
//		list* re = new list;
//		re->data = b;
//		re->next = ret;
//		p = re;
//		return;
//	}
//	while (ret) {
//		if (i+1== a) {
//			list* cur = ret->next;
//			list* newnode = new list;
//			newnode->data = b;
//			ret->next = newnode;
//			newnode->next = cur;
//			return;
//		}
//		i++;
//		ret = ret->next;
//	}
//}
//
//bool my_empty(list*p) {
//	return !p;
//}
//
//
//list* head() {
//	list* p = new list;
//	p->data = 0;
//	p->next = nullptr;
//	return p;
//}
//
//
//void faction() {
//	
//
//
//}
//
//int main() {
//	faction();
//}
//
//
//
//
//
//
//
//
//
