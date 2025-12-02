using namespace std;

#include<iostream>
#include<random>

class Elem {
private:
	int lenth;
	int* data;
	int p;
	void data_expand() {
		lenth *= 2;
		int* newdata = new int[lenth];
		for (int i=0;i<p;i++)
			newdata[i] = data[i];
		data = newdata;
	}

	void data_delete(int val) {
		int i;
		for (i = val; i < p - 1; i++)
			data[i] = data[i + 1];
		p--;
	}


public:
	Elem() :lenth(4), p(0) {
		data = new int[lenth];
	}

	void push(int val) {
		if (p == lenth) data_expand();
		data[p] = val;
		p++;
	}

	void sort_data() {
		if (p == 0) {
			cout << "没有值可以用来排序" << endl;
			system("pause");
			return;
		}
		system("cls");
		print();
		cout << "你希望的排列方式是:" << endl;
		cout << "1.从大到小      2.从小到大" << endl;
		int a, i, j, temp; cin >> a;
		switch (a) {
		case 1:
			for (i = 0; i < p; i++) {
				for (j = i + 1; j < p; j++)
				{
					if (data[i] < data[j]) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
				}
			}
			break;
		case 2:
			for (i = 0; i < p; i++) {
				for (j = i + 1; j < p; j++)
				{
					if (data[i] > data[j]) {
						temp = data[i];
						data[i] = data[j];
						data[j] = temp;
					}
				}
			}
			break;
		default:
			cout << "找茬？" << endl;
			system("pause");
			return;
		}
		cout << "排序成功" << endl;
		print();
		system("pause");
	}
	int data_find(int val) {
		int i = 0;
		for (i = 0; i < p; i++) {
			if (val == data[i]) return i;
		}
		return -1;
	}

	bool empty() {
		return p == 0;
	}


	void delete_elem() {
		int ret;
		while (1) {
			system("cls");
			print();
			cout << "输入下标还是元素" << endl;
			cout << "1.下标         2.元素     3.退出查找 " << endl;
			int a;
			cin >> a;
			switch (a) {
			case 1:
				cout << "输入下标：" << endl;
				cin >> a;
				while (a < 0 && a >= p) {
					system("cls");
					cout << "输入错误，请重新输入：" << endl;
					cin >> a;
				}
				data_delete(a);
				break;
			case 2:
				cout << "输入元素" << endl;
				cin >> a;
				ret = data_find(a);
				if (ret == -1) {
					cout << "无效输入" << endl;
					system("pause");
					return;
				}
				data_delete(ret);
				break;
			case 3:
				return;
			default:
				cout << "无效输入" << endl;
				system("pause");
				continue;
			}
			system("cls");
		}
	}

	void print() {
		int i;
		if (p == 0) cout << "暂无元素" << endl;
		for (i = 0; i < p; i++) {
			cout << data[i] << "  ";
		}
		cout << endl;
	}

};


int main() {
	Elem rep;
	int n,a;
	cout << "输入要输入的元素个数" << endl;
	cin >> n;
	cout << "输入元素" << endl;
	while(n--){
		cin >> a;
		rep.push(a);
	}
	cout << "当前已有元素为:" << endl;
	rep.print();
	cout << "接下来进行查找操作" << endl;
	cout << "输入要查找的元素" <<endl;
	cin >> a;
	int ret=rep.data_find(a);
	if (ret == -1)  cout << "查无此值" << endl;
	else cout << "第一次出现在在下标" << ret << "处" << endl;
	system("pause");
	cout << "接下来进行元素删除测试" << endl;
	system("pause");
	rep.delete_elem();
	system("pause");
	cout << "接下来进行排序操作" << endl;
	system("pause");
	rep.sort_data();
}

