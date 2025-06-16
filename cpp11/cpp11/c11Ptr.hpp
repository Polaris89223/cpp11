#pragma once
#include <iostream>
#include <memory>
using namespace std;

class C11Ptr {
public:
	C11Ptr() {
		cout << "construct C11Ptr..." << endl;
	}
	C11Ptr(int x):m_num(x){
		cout << "construct C11Ptr,x= "<<x<< endl;
	}
	C11Ptr(string str){
		cout << "construct C11Ptr,str= " << str << endl;
	}
	virtual ~C11Ptr() {
		cout << "destruct C11Ptr..."<< endl;
	}
	void setValue(int v) {
		m_num = v;
	}
	void print() {
		cout << "m_num: " << m_num << endl;
	}
private:
	int m_num = { 0 };
};
