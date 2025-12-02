using namespace std;

#include<iostream>
#include<random>

int rand_ol(int min, int max) {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(rng);
}

template <typename T> 
class Elem {
private:
	int lenth;
	T* data;
	int p;
	void data_expand() {
		lenth *= 2;
		T* newdata = new T[lenth];
		for (int num : data)
			newdata[num] = data[num];
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
		data = new T[lenth];
	}

	void push(int val) {
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
				for (j = i+1; j < p; j++)
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
				cout << "1.下标         2.元素     3.返回上一级 " << endl;
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

	void print(Elem<int>& p) {
		if (!p.empty()) {
			cout << "已插入元素：" << endl;
			p.print();
		}
		cout << endl;
		cout << "1.插入元素" << endl;
		cout << "2.删除元素" << endl;
		cout << "3.查找元素" << endl;
		cout << "4.排序" << endl;
		cout << "5.退出" << endl;
		cout << "" << endl;
	}

	int main() {
		Elem<int>p;
		int a, n = 0, num;
		while (1) {
			system("cls");
			cout << "输入你的操作：" << endl;
			print(p);
			a = rand_ol(1,4);
			cin >> a;
			switch (a) {
			case 1:
				cout << "输入插入个数" << endl;
				n = rand_ol(10, 20);
				while (n--) {
					num = rand_ol(10, 90);
					p.push(num);
					cout << num << "   " << endl;
				}
				break;
			case 2:
				system("cls");
				p.delete_elem();
				break;
			case 3:
				system("cls");
				p.print();
				cout << "输入查找的值：" << endl;
				cin >> a;
				n = p.data_find(a);
				if (n == -1)
					cout << "查无此值" << endl;
				else cout << "要找的值在下标" << n << "处" << endl;
				system("pause");
				break;
			case 4:
				p.sort_data();
				break;
			case 5:
				return 0;

			}
		}
	}

