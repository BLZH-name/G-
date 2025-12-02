//using namespace std;
//#include<iostream>
//#include<algorithm>
//#include<stack>
//#include<queue>
//
//
//int proce(int limite, int colim,
//	int left, int right) {
//	if (colim == limite) return 1;
//	int pos = 0;
//	int most = 0;
//	pos = limite & (~(colim | left | right));
//	int res = 0;
//	while (pos != 0){
//		most = pos & (~pos + 1);
//		pos = pos - most;
//		res += proce(limite, colim | most,
//			(left | most) << 1,
//			(right | most) >> 1);
//	}
//	return res;
//}
//
//int bniary(int n) {
//	int ret = 1;
//	while (n--) { ret = ret * 2; };
//	return ret;
//}
//
//int Quein(int n,int i) {
//
//}
//
//
//int main() {
//	//int ret = proce(8,1,0,0);
//	int ret = 0,num;
//	cin>> num;
//	while (num--) {
//		ret += bniary(num);
//	}
//	ret = proce(ret,0,0,0);
//	cout << ret;



//using namespace std;
//#include<iostream>
//#include<string>
//#include<algorithm>
//#include<vector>
//
//
//vector<int> next_create(string s) {
//	int i, j=0;
//	int n = s.size();
//	vector<int>next(n);
//	for (i = 1; i < n;i++) {
//		if (j > 0 && s[i] != s[j]) j = next[j - 1];
//		else if (s[i] == s[j]) j++;
//		next[i] = j;
//	}
//	return next;
//}
//
//vector<int> GetNextval(string s,vector<int>&next) {
//	int m = s.size();
//	vector<int>nextval(m,0);
//	int i,j = 0;
//	for (i = 0; i < m;i++) {
//		j = next[i];
//		while (j>0&&s[i]==s[j]) {
//			j = nextval[j];
//		}
//		nextval[i] = j;
//	}
//	return nextval;
//}
//
//
//void string_KPM(string str, string s) {
//	int i, j = 0;
//	int m = s.size();
//	vector<int> next = next_create(s);
//	int n = str.size();
//	for (i = 1; i < n; i++) {
//		if (j > 0 && str[i] != s[j]) j = next[j - 1];
//		else if (str[i] == s[j]) j++;
//		if (j == m) {
//			int k = m;
//			while (k--) {
//				str.erase(str[k]);
//			}
//		}
//		next[i] = j;
//
//	}
//	cout << str;
//}
//
//	int main() {
//		string str, s;
//		cin >> str >> s;
//		string_KPM(str,s);
//	
//	}

// 
// 
//}
//
//int main() {
//	string str1, str2;
//	cin >> str1 >> str2;
//	int ret=string_KPM(str1,str2);
//	cout << ret;
//}
//#include<iostream>
//#include<string>
//using namespace std;
//#include<fstream>
//#include<vector>
//
//
//
////第一题
//void string_numget() {
//	string str;
//	cin >> str;
//	int ret[37] = { 0 };
//	int i = 0;
//	while (str[i] != '\0') {
//		if (isdigit(str[i])) ret[str[i] - '0' + 26]++;
//		else ret[str[i] - 'A']++;
//		i++;
//	}
//	ofstream outFile("E:\C - data\DF.txt");
//	outFile << str << endl;
//	for (i = 0; i < 36; i++) {
//		if (i <= 25) {
//			outFile << char(i + 65) << ":" << ret[i] << endl;
//
//		}
//		else
//			outFile << i - 26 << ":" << ret[i] << endl;
//	}
//	outFile.close();
//}
//
////第三题
//void insert(char* s, char* t, int pos) {
//	int size_s = 0, size_t = 0;
//	char* p = s;
//	int i = 0, j;
//	while (*p != '\0') {
//		size_s++; p++;
//	}
//	p = t;
//	while (*p != '\0') {
//		size_t++; p++;
//	}
//	p = s;
//	for (p = s + size_s; p >= s + pos; p--) {
//		*(p + size_t) = *p;
//	}
//	for (i = 0; i < size_t; i++)
//		*(s + pos + i) = t[i];
//}
//
////第四题
//void format(string s1,string s2,string s3,int n) {
//	int size = s1.size();
//	if (n == size) return;
//	else if (size < n) {
//		int x = n - size;
//		if (size % 2 == 1) {
//			s3 += *(s1.end() - 1);
//			s1.erase(s1.end()-1);
//			x++;
//		}
//		while (x--) {
//			s1.insert(s1.begin()+s1.size()/2, ' ');
//		}
//	}
//	else {
//		while (s1.size()!=n) {
//			s1.erase(s1.end()-1);
//		}
//	}
//	cout << s1;
//}
//
////第五题
//bool yes_or_no(vector<vector<int>>a) {
//	vector<int>ret;
//	int i, j;
//	int n = a.size();
//	int m = a[0].size();
//	for (i = 0; i < n; i++) {
//		for (j = 0; j < m; j++) {
//			if (ret[a[i][j]]) {
//				cout << "no";
//				return false;
//			}
//			else ret[a[i][j]]++;
//		}
//	}
//}
//
////第六题
//void srot_a(int a[],int n) {
//	int i = 0,j=1;
//	vector<int>ret;
//	for (i = 0; i < n,n-j!=i;i++) {
//		if (a[i] < 0) {
//			ret[n - j] = a[i];
//			j++;
//		}
//		else ret[i] = a[i];
//	}
//}
//
//
//
//int main() {
//	string str1;
//	cin >> str1;
//	format(str1," "," ",6);
//
//}


//递归解决dijkstra
//using namespace std;
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<climits>
//
//struct grr { 
//	int to;
//	int w;
//	grr(int t, int weight) : to(t), w(weight) {}
//};
//
//vector<vector<grr>> adj;
//vector<int> dist;//起点到各顶点的最短距离
//vector<bool> visited;//标记是否访问
//vector<int> pre;//回溯数组
//vector<string> city = {"A","B","C","D","E"};
//
//void dijkstraRecursive() {
//	int n = adj.size();
//	int u = -1;
//	for (int i = 0; i < n;i++) {
//		if (!visited[i] && (u == -1 || dist[i] < dist[u])) u = i;
//	}
//	if (u == -1) return;
//	visited[u] = true;
//	for (const grr &e:adj[u]) {
//		int v = e.to, w = e.w;
//		if (!visited[v] && dist[v] > dist[u] + w) {
//			dist[v] = dist[u] + w;
//			pre[v] = u;
//		}
//	}
//	dijkstraRecursive();
//}
//
//void printPath(int end) {
//	if (pre[end] == -1) {
//		cout << city[end];
//		return;
//	}
//	printPath(pre[end]);
//	cout << " → " << city[end];
//}
//
//
//void dijikstraInit(int start) {
//	int n = adj.size();
//	dist.assign(n,INT_MAX);
//	visited.assign(n, false);
//	pre.assign(n,-1);
//	dist[start] = 0;
//	dijkstraRecursive();
//}
//
//
//int main() {
//	adj.resize(5);
//	adj[0].emplace_back(3, 2);
//	adj[0].emplace_back(1, 100);
//	adj[0].emplace_back(4, 999);
//	adj[1].emplace_back(2, 6);
//	adj[2].emplace_back(4, 7);
//	adj[3].emplace_back(1, 7);
//	int start = 0;
//	dijikstraInit(start);
//
//	cout << "起点" << city[start] << "到各城市的最短路径：\n";
//	for (int i = 0; i < 4; i++) {
//		if (dist[i] == INT_MAX) {
//			cout << city[start] << "→" << city[i] << "：不可达\n";
//		}
//		else {
//			cout << city[start] << "→" << city[i] << "：距离=" << dist[i]
//				<< "，路径：";
//			printPath(i);
//			cout << "\n";
//		}
//	}
//
//}



//dijkstra算法
//using namespace std;
//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<climits>
//#include<random>
//
//int rand_ol(int min, int max) {
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int>dist(min, max);
//	return dist(rng);
//}
//
//
//struct Node {
//	int to;
//	int w;
//	Node(int l, int weigth) :to(l), w(weigth) {}
//};
//
//class dijkstra_alo {
//private:
//	int n;
//	int m;
//	vector<vector<Node>>data;
//	vector<int>min_dista;
//	vector<bool>confirm;
//	vector<int>pre;
//
//public:
//	dijkstra_alo(int x,int y) {
//		n = x;
//		m = y;
//		min_dista.assign(n, INT_MAX);
//		confirm.assign(n, false);
//		data.resize(n);
//	}
//
//	void push() {
//		int t = m;
//		int a, b, w;
//		while (t--) {
//			cin >> a >> b >> w;
//			data[a].emplace_back(b, w);
//		}
//	}
//
//	void dijk() {
//		int n = data.size();
//		int u = -1, i;
//		for (i = 0; i < n; i++)
//			if (!confirm[i] && (u == -1 || min_dista[u] > min_dista[i])) u = i;
//		if (u == -1) return;
//		confirm[u] = true;
//		for (const Node& e : data[u]) {
//			int v = e.to, w = e.w;
//			if (!confirm[v] && min_dista[v] > (min_dista[u]+w)) {
//				min_dista[v] = min_dista[u] + w;
//				pre[v] = u;
//			}
//		}
//		dijk();
//	}
//};
//
//
//int main() {
//	int n, m; cin >> n >> m;//n点m边
//	dijkstra_alo p(n,m);
//	p.push();
//	p.dijk();
//}


//线索二叉树
//using namespace std;
//#include<iostream>
//#include<string>
//#include<random>
//
//int rand_ol(int min,int max) {
//
//	static std::mt19937 rng(std::random_device{}());
//	std::uniform_int_distribution<int>dist(min,max);
//	return dist(rng);
//}
//
//struct Node {
//	int data;
//	Node* left;
//	Node *right;
//	int ltag, rtag;
//};
//
//class binary_tree{
//private:
//	void go_print(Node* p) {
//		if (!p) return;
//		go_print(p->left);
//		cout << p->data << " ";
//		go_print(p->right);
//	}
//	void go_Inthred(Node* t, Node* pre) {
//		if (t) {
//			go_Inthred(t->left, pre);
//			if (!t->left) {
//				t->left = pre;
//				t->ltag = 1;
//			}
//			if (pre && !pre->right) {
//				pre->right = t;
//				pre->rtag = 1;
//			}
//			pre = t;
//			go_Inthred(t->right, pre);
//		}
//	}
//private:
//	Node* node;
//
//public:
//	binary_tree(){
//		node = nullptr;
//	}
//
//	Node* create_node(int val) {
//		Node* newnode = new  Node;
//		newnode->data = val;
//		newnode->left = nullptr;
//		newnode->right = nullptr;
//		return newnode;
//	}
//
//	void push(int val) {
//		if (!node) {
//			node = create_node(val); return;
//		}
//		Node* cur = node;
//		Node* parent = nullptr;
//		while (cur) {
//			parent = cur;
//			if (val > cur->data)
//				cur = cur->right;
//			else cur = cur->left;
//		}
//		if (val > parent->data) parent->right = create_node(val);
//		else parent->left = create_node(val);
//	}
//
//	
//
//	void Inthred() {
//		if (node) go_Inthred(node,NULL);
//		else {
//			cout << "树为空"; return;
//		}
//	}
//
//	void print() {
//		Node* cur = node;
//		go_print(cur);
//	}
//};
//
//
//int main() {
//	binary_tree p;
//	int a,n = rand_ol(10, 20);
//	while (n--) {
//		a = rand_ol(0,50);
//		cout << a << "  ";
//		p.push(a);
//	}
//	cout << endl;
//	p.print();
//	p.Inthred();
//
//}

//线索二叉树
//using namespace std;
//#include<iostream>
//#include<string>
//
//struct Node {
//	int data;
//	Node* left;
//	Node* right;
//	int rtag;
//	int ltag;
//};
//
//class Tree {
//private:
//	Node* node;
//
//	Node* create_node(int val) {
//		Node* newnode = new Node;
//		newnode->data = val;
//		newnode->left = nullptr;
//		newnode->right = nullptr;
//		return newnode;
//	}
//
//
//public:
//	Tree() {
//		node = nullptr;
//	}
//
//
//	void push(int val) {
//		Node* cur = node;
//		Node* parent = nullptr;
//		if (!cur) {
//			node = create_node(val);
//			return;
//		
//		}
//		while (cur) {
//			parent = cur;
//			if (val > cur->data) cur = cur->right;
//			else cur = cur->left;
//		}
//		if (val > parent->data) parent->right = create_node(val);
//		else parent->left = create_node(val);
//	}
//
//	void Inthred(Node*p,Node*pre ) {
//		if (p) {
//			Inthred(p->left,pre);
//			if (!p->left) {
//				p->left = pre; p->ltag = 1;
//			}
//			if (!p->right) {
//				p->right = pre; p->rtag = 1;
//			}
//			pre = p;
//			Inthred(p->right,pre);
//		}
//	}
//
//};
//
//int main() {
//
//}

//using namespace std;
//
//#include<iostream>
//#include<string>
//#include<vector>
//
//
//
//int proces(string str,int i) {
//	int sum = 0;
//	if (i == str.size()) return 1;
//	if (str[i] == '0') return  0;
//	if (str[i] == '1') {
//		sum+=proces(str,i+1);//i单独作为个体
//		if (i + 1 < str.size()) sum+=proces(str,i+2);
//	}
//	else if (str[i] == '2') {
//		sum+=proces(str, i + 1);
//		if (i+1<str.size()&&str[i+1]<='6') {
//			sum+=proces(str,i+2);
//		}
//	}
//	else sum+=proces(str,i+1);
//	return sum;
//
//}
//
//int main() {
//	string str;
//	cin >> str;
//	int ret=proces(str, 0);
//	cout << ret;
//}


//反转栈
//using namespace std;
//#include<iostream>
//#include<string>
//#include<stack>
//
//int f(stack<int>&ret);
//
//void reverse(stack<int>&ret) {
//	if (ret.empty()) return;
//	int i = f(ret);
//	reverse(ret);
//	ret.push(i);
//}
//
//int f(stack<int>&ret) {
//	int resulst = ret.top(); ret.pop();
//	if (ret.empty()) return resulst;
//	else {
//		int last = f(ret);
//		ret.push(resulst);
//		return last;
//	}
//}
//
//int main() {
//	stack<int> s;
//	s.push(1);
//	s.push(2);
//	s.push(3);  // 栈：底[1,2,3]顶
//
//	reverse(s);
//
//	// 输出反转后的栈（顶[1,2,3]底 → 弹出顺序为1,2,3）
//	while (!s.empty()) {
//		cout << s.top() << " ";
//		s.pop();
//	}  // 输出：1 2 3
//	return 0;
//}


//并查集实现
//using namespace std;
//#include<iostream>
//
//class  Union_Find{
//private:
//	int* father;
//	int lenth;//元素长度
//public:
//	Union_Find(int val):lenth(val){
//		father = new int[lenth];
//		int i = 0;
//		for (i; i < lenth;i++)
//			father[i] = i;
//	}
//
//	int find(int x) {
//		if (x == father[x]) return x;
//		return father[x] = find(x);
//		return  x;
//	}
//
//	void Union(int x,int y) {
//		int fy = find(y);
//		int fx = find(x);
//		if (fy != fx) {
//			father[fy] = fx;
//		}
//	}
//};
//
//
//int main() {
//
//}

//感染法解决岛问题
//using namespace std;
//#include<iostream>
//#include<vector>
//#include<algorithm>
//
//void island(vector<vector<int>>&ret ,int i,int j) {
//	if (i < 0 || j < 0 || i >= ret.size() || j >= ret[0].size() || ret[i][j] != 1) return;
//	ret[i][j] = 2;
//	island(ret, i + 1, j);
//	island(ret, i - 1, j);
//	island(ret, i , j+1);
//	island(ret, i, j-1);
//}
//
//int main() {
//	int i = 0,j=0,sum=0;
//	int n, m; cin >> n >> m;
//	vector<vector<int>>ret;
//	int y;
//	for (i = 0; i < n; i++) {
//		vector<int>row;
//		for (j = 0; j < m; j++) {
//			cin >> y;
//			row.emplace_back(y);
//		}
//		ret.emplace_back(row);
//		row.clear();
//	}
//
//	for (i=0; i < ret.size();i++) {
//		for (j = 0; j < ret[0].size(); j++) {
//			if (ret[i][j] == 1) {
//				sum++;
//				island(ret,i,j);
//			}
//		}
//	}
//	cout << sum;
//}

//using namespace std;
//#include<iostream>
//#include<fstream>
//#include<string>
//
//int main() {
//	fstream Infile("E:\\C-data\\55\\blah.cpp");
//	fstream outfile("E:\\C-data\\dar\\cv.txt");
//	if (!outfile.is_open()) {
//		cout << "1打开失败" << endl;
//		return 1;
//	}
//	if (!Infile.is_open()) {
//		cout << "2打开失败" << endl;
//		return 1;
//	}
//	string line;
//	while(getline(Infile,line)) {
//		outfile << line << '\n';
//	}
//	Infile.close();
//	outfile.close();
//	cout << "成功" << endl;
//}


//移盘子问题
//using namespace std;
//#include<iostream>
//#include<string>
//
//void func(int n,string start,string end,string other) {
//	if (n == 1)
//		cout << "Move 1 from" << start << "to" << end << endl;
//	else {
//		func(n-1,start,other,end);
//		cout << "Move  " << n << "  from" << start << "  to" << end<<endl;
//		func(n-1,other,end,start);
//	}
//}
//
//int main() {
//	int n = 3;
//	func(n,"左","右","中");
//}

//
//
//using namespace std;
//#include<iostream>
//#include<string>
//#include"mytree.h"
//
//void fute(Tree* tr) {
//	Tree* cur = tr;
//	Tree* mostright = nullptr;
//	while (cur!=nullptr) {
//		mostright = cur->left;
//		if (mostright != nullptr) {
//			
//		}
//	}
//}
//
//
//int main() {
//	Tree* tr=nullptr;
//
//}













