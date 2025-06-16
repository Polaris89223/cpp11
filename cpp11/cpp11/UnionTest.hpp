#pragma once
#include <iostream>
#include <string>
using namespace std;

union UnionTest {
	//C++98对联合体的语法限制
	//不允许非pod类型作为数据成员
	//string str;//c++98中语法错误
	//不允许出现静态成员(成员变量、成员函数)
	static int num;
	static int print(){
		num = 900;
		cout << "static num:" << num << endl;
		return 100;
	}
	//不允许出现引用
	int num1;
	//int& ref = num1;
};
int UnionTest::num = 10;
class Teacher {
public:
	Teacher() {};
	void setText(string s) {
		name = s;
	}
private:
	string name;
};
union Student {
	Student()
	{ 
		//定位放置new
		new (&name)string;
	}
	~Student() {

	}
	int id;
	Teacher t;
	//c++11中如果联合提存在非pod类型，则默认构造函数和析构函数会被自动删除，需要自己手动定义
	string name;
};

struct Foreigner {
	Foreigner(string a, string p) :addr(a), phone(p) {}
	string addr;
	string phone;
};

class PersonInfo {
public:
	enum class Category :char {Student,Local,Foreign};
	PersonInfo(int num) :number(num),c(Category::Student) {}
	PersonInfo(string str) :idNum(str), c(Category::Local) {}
	PersonInfo(string a,string p):fore(a,p), c(Category::Foreign) {}
	~PersonInfo() {}
	void print() {
		switch (c) {
		case Category::Student:
			cout << "Student school number: " << number << endl;
			break;
		case Category::Local:
			cout << "Local People ID number: " << idNum << endl;
			break;
		case Category::Foreign:
			cout << "Foreigner address: " << fore.addr 
				<< ",phone: "<< fore.phone << endl;
			break;

		}
	}
private:
	Category c;
	union {
		int number;
		string idNum;
		Foreigner fore;
	};
};