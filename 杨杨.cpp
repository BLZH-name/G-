//本次实验的步骤或程序及运行结果（表格不够可另加附页）。
//顺序存储
//#include<iostream>
#include<random>

int rand_ol(int min, int max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int>dist(min, max);
    return dist(rng);
}
//
//int main() {
//    int a[M] = { 0 }, b[M] = { 0 }, c[M] = { 0 }, n, x, y;
//    /*cin >> n;*/
//    n = rand_ol(1, 10);
//    cout << n << endl;
//    for (int i = 0; i < n; i++) {
//        //cin >> x >> y; 
//        x = rand_ol(1,10);
//        y = rand_ol(1,10);
//        cout << x << "  " << y << endl;
//        a[y] = x;
//    }
//    //cin >> n;
//    n = rand_ol(1,10);
//    cout << n << endl;
//    for (int i = 0; i < n; i++) {
//        x = rand_ol(1, 10);
//        y = rand_ol(1, 10);
//        cout << x << "  " << y << endl; b[y] = x;
//    }
//    for (int i = 0; i < M; i++)c[i] = a[i] + b[i];
//    bool f = 1;
//    for (int i = M - 1; i >= 0; i--)
//        if (c[i]) {
//            if (!f)cout << (c[i] > 0 ? "+" : "");
//            cout << c[i] << "x*" << i; f = 0;
//        }
//    if (f)cout << 0;
//    return 0;
//}
#include <iostream>
using namespace std;
// 链表节点类
struct PolyNode {
    int coef;
    int exp;
    PolyNode* next;
    PolyNode(int c = 0, int e = 0, PolyNode* n = nullptr)
        : coef(c), exp(e), next(n) {
    }
};
// 多项式链表类
class PolyList {
private:
    PolyNode* head;  // 头节点（不存数据）
public:
    // 构造函数
    PolyList() { head = new PolyNode(); }
    // 析构函数（释放内存）
    ~PolyList() {
        PolyNode* p = head;
        while (p) {
            PolyNode* temp = p;
            p = p->next;
            delete temp;
        }
    }
    // 创建多项式（输入系数 指数，以0 0结束）
    void create() {
        PolyNode* p = head;
        int c, e;
        int y = 0;
        cout << "输入多项式（系数 指数，以0 0结束）：" << endl;;
        while (true) {
            //cin >> c >> e;
            y++;
            c = rand_ol(1,10);
            e = rand_ol(1,10);
            if (y == 7) {
                c = 0; e = 0;
            }
            cout << c << "  " << e<<endl;
            if (c == 0 && e == 0) break;
            p->next = new PolyNode(c, e);
            p = p->next;
        }
    }
    // 多项式相加（返回新的多项式）
    PolyList add(const PolyList& other) const {
        PolyList res;
        PolyNode* pa = head->next, * pb = other.head->next, * pr = res.head;
        while (pa && pb) {
            if (pa->exp > pb->exp) {
                pr->next = new PolyNode(pa->coef, pa->exp);
                pr = pr->next;
                pa = pa->next;
            }
            else if (pa->exp < pb->exp) {
                pr->next = new PolyNode(pb->coef, pb->exp);
                pr = pr->next;
                pb = pb->next;
            }
            else {
                int newCoef = pa->coef + pb->coef;
                if (newCoef != 0) {
                    pr->next = new PolyNode(newCoef, pa->exp);
                    pr = pr->next;
                }
                pa = pa->next;
                pb = pb->next;
            }
        }
        // 追加剩余项
        while (pa) {
            pr->next = new PolyNode(pa->coef, pa->exp);
            pr = pr->next;
            pa = pa->next;
        }
        while (pb) {
            pr->next = new PolyNode(pb->coef, pb->exp);
            pr = pr->next;
            pb = pb->next;
        }
        return res;
    }
    // 输出多项式
    void print() const {
        PolyNode* p = head->next;
        while (p) {
            if (p != head->next && p->coef > 0) cout << "+";
            cout << p->coef << "X^" << p->exp;
            p = p->next;
        }
        cout << endl;
    }
};
// 测试
int main() {
    PolyList A, B;
    cout << "创建多项式A：\n";
    A.create();
    cout << "创建多项式B：\n";
    B.create();
    PolyList res = A.add(B);
    cout << "多项式A："; A.print();
    cout << "多项式B："; B.print();
    cout << "相加结果："; res.print();
    return 0;
}