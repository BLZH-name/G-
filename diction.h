#pragma once


template<typename T1,typename T2>

class Diction2 {
private:
	T1 first;
	T2 second;


public:
	Diction2(T1 val1, T2 val2) :first(val1), second(val2) {
	};


	void print() {
		cout << first << "   "<<second;
	}
};

//template<typename T>

class Diction1 {
private:
	int* data;
	int lenth;
	int p;
public:
	Diction1(){
		data = new int[lenth];
		p = 1; 
		lenth = 4;
	}

	void dataup() {
		lenth *= 2;
		int* newdata = new int[lenth];
		for (int i = 0; i <= p; i++)
			newdata[i] = data[i];
		delete[]data;
		data = newdata;
	}

	void add(int val) {
		data[p] = val;
	}


};
