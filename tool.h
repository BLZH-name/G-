#pragma once
#include<random>
#include<cstring>

int rand_ol(int min,int max) {
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int>dist(min, max);
	return dist(rng);
}

int max(int a,int b) {
	return a > b ? a : b;
}

int power_2(int n) {
	int ret=1;
	while (n--) {
		ret *= 2;
	}
	return ret;
}

template<typename T>

void sort_min(T*p,T begin,T end) {
	int i, j,temp;
	int ret = end - begin;
	if (ret < 1) return;
	for (i = begin; i < end; i++) {
		for (j = i; j < end; j++) {
			if (*(p + i) > *(p + j))
			{
				temp = *(p + i);
				*(p + i) = *(p + j);
				*(p + j) = temp;
			}
		}
	}
}

template<typename T>
void sort_max(T*p,T begin,T end) {
	int i, j,temp;
	int ret = end - begin;
	if (ret < 1) return;
	for (i = begin; i < end; i++) {
		for (j = i; j < end; j++) {
			if (*(p + i) < *(p + j))
			{
				temp = *(p + i);
				*(p + i) = *(p + j);
				*(p + j) = temp;
			}
		}
	}
}

