//
//#include<iostream>
//using namespace std;
//#include<bitset>
//
//
//int N_Queens(int row,int colim,int left,int right) {
//	if (row == colim) return 1;
//	int pos = 0;
//	int most = 0;
//	pos = row & (~(colim | left | right));
//	int res = 0;
//	while (pos!=0) {
//		most = pos & (~pos + 1);
//		pos = pos - most;
//		res += N_Queens(row,colim|most,(left|most)<<1,(right|most)>>1);
//	}
//	return res;
//}
//
//void faction() {
//	int n;
//	cin>>  n;
//	int ret=N_Queens(n,0,0,0);
//	cout << ret;
//}
//
//
//
//int main() {
//	faction();
//}