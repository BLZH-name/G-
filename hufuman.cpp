//
//
//
//using namespace std;
//#include<iostream>
//#include<fstream>
//#include <bitset>
//#include<vector>
//#include<string>
//#include <unordered_map>
//#include<queue>
//
//struct Node {
//	char data;
//	int freq;
//	Node* left;
//	Node* right;
//	Node(char c, int t) :data(c), freq(t), left(nullptr), right(nullptr) {}
//	Node(Node* l, Node* r) :data(0), freq(l->freq + r->freq), left(l), right(r) {}
//};
//
//struct CompareNode {
//	bool operator()(Node* a, Node* b) {
//		return a->freq > b->freq;
//	}
//};
//
//class Hufuman {
//private:
//	string inpath;
//	string outpath;
//	int count;
//public:
//
//	Hufuman(string s1,string s2):inpath(s1),outpath(s2) {}
//
//	unordered_map<char, int> countfreq() {
//		unordered_map<char, int>freq;
//		ifstream in(inpath, ios::binary);
//		if (!in) {
//			cout << "读取失败" << endl; exit(1);
//		}
//		char c;
//		while (in.read((char*)&c, 1)) freq[c]++;
//		in.close();
//		return freq;
//	}
//
//	Node* buildTree(unordered_map<char, int>& freq) {
//		priority_queue<Node*, vector<Node*>, CompareNode>ret;
//		for (const auto& p : freq) {
//			ret.push(new Node(p.first, p.second));
//		}
//		while (ret.size() > 1) {
//			auto left = ret.top(); ret.pop();
//			auto right = ret.top(); ret.pop();
//			ret.push(new Node(left, right));
//		}
//		return ret.empty() ? nullptr : ret.top();
//	}
//
//	void getcodes(Node* root, string code, unordered_map<char, string>& codes) {
//		if (!root) return;
//		if (!root->left && !root->right) {
//			codes[root->data] = code.empty() ? "0" : code;
//		}
//		getcodes(root->left, code + "0", codes);
//		getcodes(root->right, code + "1", codes);
//	}
//
//	unordered_map<char, int> countFrequency(vector<string>& files) {
//		unordered_map<char, int> freqMap;
//		for (const auto& file : files) {
//			ifstream inFile(file, std::ios::binary);
//			char ch;
//			while (inFile.get(ch)) {
//				freqMap[ch]++;
//			}
//			inFile.close();
//		}
//		return freqMap;
//	}
//
//
//
//
//	void compress() {
//		auto freq = countfreq();//读入文件编码
//		if (freq.empty()) { cout << "文件为空" << endl; return; }
//		auto root = buildTree(freq);//创建哈夫曼树完成
//		unordered_map<char, string>codes;
//		getcodes(root, "", codes);//构建编码
//
//		ofstream out(outpath, ios::binary);
//		int code_size = codes.size();
//		out.write((char*)&code_size, sizeof(code_size));
//
//		for (const auto& p : codes) {
//			char c = p.first;
//			const string& code = p.second;
//			int len = code.size();
//
//			out.write((char*)&c, 1);
//			out.write((char*)&len, sizeof(len));
//
//			bitset<8> bits;
//			for (int i = 0; i < len; ++i) {
//				bits[i % 8] = (code[i] == '1');
//				if (i % 8 == 7 || i == len - 1) {
//					out.put((char)bits.to_ulong());
//					bits.reset();
//				}
//			}
//		}
//
//		string bits;
//		ifstream in(inpath, ios::binary);
//		char c;
//		while(in.read((char*)&c,1)){
//			bits += codes[c];
//		}
//		in.close();
//
//		int  pad = 8 - (bits.size() % 8);
//		if (pad != 8) bits += string(pad, '0');
//		out.write((char*)&pad,sizeof(pad));
//
//		for (size_t i = 0; i < bits.size();i+=8) {
//			bitset<8> b(bits.substr(i,8));
//			out.put((char)b.to_ulong());
//		}
//		out.close();
//		cout << outpath;
//		
//	}
//
//	void decom(string inpath,string outpath) {
//		ifstream in(inpath, ios::binary);
//		if (!in) {
//			cerr << "打开失败" << endl; exit(1);
//		}
//
//		int codesize;
//		in.read((char*)&codesize, sizeof(codesize));
//		unordered_map<string, char>codemap;
//
//		for (int i = 0; i < codesize;++i) {
//			char c;
//			int len;
//			in.read((char*)&c, 1);
//			in.read((char*)&len,sizeof(len));
//	
//			string code;
//			int bytes = (len + 7) / 8;
//			for (int j = 0; j < bytes;++j) {
//				char byte;
//				in.read((char*)&byte, 1);
//				bitset<8>b(byte);
//				for (int k = 0; k < 8 && code.size() < len;++k) {
//					code += b[k] ? "1" : "0";
//				}
//			}
//			codemap[code] = c;
//		}
//
//		int pad;
//		in.read((char*)&pad,sizeof(pad));
//
//		string bits;
//		char byte;
//		while (in.read((char*)& byte, 1)) bits += bitset<8>(byte).to_string();
//		if (pad != 8) bits = bits.substr(0, bits.size() - pad);
//
//		ofstream out(outpath,ios::binary);
//		string current;
//		for (char bit:bits) {
//			current += bit;
//			if (codemap.count(current)) {
//				out.put(codemap[current]);
//				current.clear();
//			}
//		}
//		out.close();
//		in.close();
//
//		cout << "解压结束" << outpath;
//	}
//
//};
//
//int main() {
//	
//	
//}
