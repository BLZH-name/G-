//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include<random>
//
//
//int rand_ol(int min, int max) {
//    static std::mt19937 rng(std::random_device{}());
//    std::uniform_int_distribution<int>dist(min, max);
//    return dist(rng);
//}
//
//using namespace std;
//
//// 顺序存储的多项式（数组下标=指数，元素值=系数）
//struct SeqPolynomial {
//    vector<int> coeffs;  // coeffs[i] 表示 x^i 的系数
//
//    // 构造函数：初始化最高次项为maxExp
//    SeqPolynomial(int maxExp = 0) : coeffs(maxExp + 1, 0) {}
//
//    // 输入多项式
//    void input() {
//        int n;  // 非零项数
//        cout << "输入非零项数：";
//        //cin >> n;
//        n = rand_ol(5, 10); cout << n << endl;
//        int exp, coeff;
//        for (int i = 0; i < n; ++i) {
//            cout << "输入第" << i + 1 << "项（指数 系数）：" << endl;
//            //cin >> exp >> coeff;
//            exp = rand_ol(1,10);
//            coeff = rand_ol(-10,10);
//            cout << exp << "  " << coeff;
//            // 若指数超过当前数组长度，扩展数组
//            if (exp >= coeffs.size()) {
//                coeffs.resize(exp + 1, 0);
//            }
//            coeffs[exp] = coeff;
//        }
//        cout << endl;
//    }
//
//    // 输出多项式
//    void output() {
//        bool first = true;
//        for (int exp = coeffs.size() - 1; exp >= 0; --exp) {
//            int coeff = coeffs[exp];
//            if (coeff == 0) continue;
//
//            // 符号处理
//            if (!first) {
//                cout << (coeff > 0 ? " + " : " - ");
//                coeff = abs(coeff);
//            }
//            else if (coeff < 0) {
//                cout << "-";
//                coeff = abs(coeff);
//            }
//            first = false;
//
//            // 系数和指数处理
//            if (coeff != 1 || exp == 0) cout << coeff;
//            if (exp > 0) cout << "x";
//            if (exp > 1) cout << "^" << exp;
//        }
//        if (first) cout << "0";  // 零多项式
//        cout << endl;
//    }
//
//    // 多项式加法：当前多项式 += 另一个多项式
//    SeqPolynomial operator+(const SeqPolynomial& other) {
//        SeqPolynomial res(max(coeffs.size(), other.coeffs.size()) - 1);
//        // 复制当前多项式
//        for (int i = 0; i < coeffs.size(); ++i) {
//            res.coeffs[i] = coeffs[i];
//        }
//        // 加上另一个多项式
//        for (int i = 0; i < other.coeffs.size(); ++i) {
//            res.coeffs[i] += other.coeffs[i];
//        }
//        return res;
//    }
//};
//
//
//// 链表节点（系数+指数+后继指针）
//struct PolyNode {
//    int coeff;  // 系数
//    int exp;    // 指数
//    PolyNode* next;
//    PolyNode(int c = 0, int e = 0, PolyNode* n = nullptr) : coeff(c), exp(e), next(n) {}
//};
//
//// 链式存储的多项式
//class LinkPolynomial {
//private:
//    PolyNode* head;  // 头节点（不存数据）
//
//public:
//    LinkPolynomial() : head(new PolyNode()) {}
//
//    // 销毁链表
//    ~LinkPolynomial() {
//        PolyNode* p = head;
//        while (p) {
//            PolyNode* q = p->next;
//            delete p;
//            p = q;
//        }
//    }
//
//    // 插入节点（按指数降序，保证有序）
//    void insert(int coeff, int exp) {
//        if (coeff == 0) return;  // 系数为0不存储
//        PolyNode* p = head, * q = head->next;
//        // 找到插入位置（exp大于当前节点则插入）
//        while (q && q->exp > exp) {
//            p = q;
//            q = q->next;
//        }
//        // 若指数相同，合并系数
//        if (q && q->exp == exp) {
//            q->coeff += coeff;
//            if (q->coeff == 0) {  // 合并后系数为0，删除节点
//                p->next = q->next;
//                delete q;
//            }
//        }
//        else {
//            // 插入新节点
//            p->next = new PolyNode(coeff, exp, q);
//        }
//    }
//
//    // 输入多项式
//    void input() {
//        int n;
//        cout << "输入非零项数：";
//        //cin >> n;
//        n = rand_ol(5,10);
//        cout << n << endl;
//        int exp, coeff;
//        for (int i = 0; i < n; ++i) {
//            cout << "输入第" << i + 1 << "项（指数 系数）：" << endl;;
//            //cin >> exp >> coeff;
//            exp = rand_ol(1,10);
//            coeff = rand_ol(-10,10);
//            cout << exp << "  " << coeff << endl;
//            insert(coeff, exp);
//        }
//        cout << endl;
//    }
//
//
//    // 输出多项式
//    void output() {
//        PolyNode* p = head->next;
//        if (!p) {
//            cout << "0" << endl;
//            return;
//        }
//        bool first = true;
//        while (p) {
//            // 符号处理
//            if (!first) {
//                cout << (p->coeff > 0 ? " + " : " - ");
//            }
//            else if (p->coeff < 0) {
//                cout << "-";
//            }
//            first = false;
//            int coeff = abs(p->coeff);
//
//            // 系数和指数处理
//            if (coeff != 1 || p->exp == 0) cout << coeff;
//            if (p->exp > 0) cout << "x";
//            if (p->exp > 1) cout << "^" << p->exp;
//
//            p = p->next;
//        }
//        cout << endl;
//    }
//
//    // 多项式加法：当前多项式 + 另一个多项式
//    LinkPolynomial operator+(const LinkPolynomial& other) {
//        LinkPolynomial res;
//        PolyNode* p = head->next, * q = other.head->next;
//        // 合并两个有序链表
//        while (p && q) {
//            if (p->exp > q->exp) {
//                res.insert(p->coeff, p->exp);
//                p = p->next;
//            }
//            else if (p->exp < q->exp) {
//                res.insert(q->coeff, q->exp);
//                q = q->next;
//            }
//            else {
//                res.insert(p->coeff + q->coeff, p->exp);
//                p = p->next;
//                q = q->next;
//            }
//        }
//        // 处理剩余节点
//        while (p) {
//            res.insert(p->coeff, p->exp);
//            p = p->next;
//        }
//        while (q) {
//            res.insert(q->coeff, q->exp);
//            q = q->next;
//        }
//        return res;
//    }
//};
//
//int main() {
//    // 1. 顺序存储测试
//    cout << "=== 顺序存储多项式加法 ===" << endl;
//    SeqPolynomial seqP1, seqP2;
//    cout << "输入多项式P1：" << endl;
//    seqP1.input();
//    cout << "输入多项式P2：" << endl;
//    seqP2.input();
//    SeqPolynomial seqRes = seqP1 + seqP2;
//    cout << "P1 + P2 = ";
//    seqRes.output();
//
//    cout << endl;
//
//    // 2. 链式存储测试
//    cout << "=== 链式存储多项式加法 ===" << endl;
//    LinkPolynomial linkP1, linkP2;
//    cout << "输入多项式P1：" << endl;
//    linkP1.input();
//    cout << "输入多项式P2：" << endl;
//    linkP2.input();
//    LinkPolynomial linkRes = linkP1 + linkP2;
//    cout << "P1 + P2 = ";
//    linkRes.output();
//
//    return 0;
//}