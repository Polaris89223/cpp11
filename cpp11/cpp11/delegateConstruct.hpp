#pragma once
#include<iostream>
using namespace std;
class MyDelegateConstruct {
public:
	MyDelegateConstruct() {};
	MyDelegateConstruct(int max) {
		this->m_max = max > 0 ? max : 100;
	}
	MyDelegateConstruct(int max,int min): MyDelegateConstruct(max){
		this->m_min = min > 0 && min < max ? min : 1;
	}
	MyDelegateConstruct(int max, int min,int mid) : MyDelegateConstruct(max,min){
		this->m_middle = mid<max && mid>max?mid:50;
	}
private:
	int m_max = 0;
	int m_min = 0;
	int m_middle = 0;
};

class MyConstructBase {
public:
	MyConstructBase(int i) :m_i(i) {};
	MyConstructBase(int i,double j) :m_i(i),m_j(j) {};
	MyConstructBase(int i, double j, string k) :m_i(i), m_j(j),m_k(k){};
	void func(int i) {
		cout << "base class: i=" << i << endl;
	}
	void func(int i,string str) {
		cout << "base class: i=" << i <<" ,str="<<str<< endl;
	}
private:
	int m_i;
	double m_j;
	string m_k;
};

class ChildBase:public MyConstructBase{
public:
	//使用父类构造函数
	using MyConstructBase::MyConstructBase;
	//使用父类隐藏了的func方法
	using MyConstructBase::func;
	void func() {
		cout << "MyConstructBase class"<<endl;
	}
};