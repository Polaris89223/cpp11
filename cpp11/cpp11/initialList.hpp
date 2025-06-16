#pragma once
#include <iostream>
using namespace std;
using personFuncptr = void(*)(int,string);
class Person {
public:
	Person(int age) :m_age(age){};
	Person(int age, const std::string name):m_age(age),m_name(name){

	}
	static void hello(int a, string name) {
	  cout << "number:" << a << ",name:" << name << endl;
	}
	void world(int a, string name) {
		cout << "number:" << a << ",name:" << name << endl;
	}
	//重载()
	void operator()(string msg) {
		cout << "仿函数:" << msg << endl;
	}
	//类对象转换为函数指针
	operator personFuncptr() {
		return hello;
	}
	int m_id;
private:
	int m_age;
	std::string m_name;
};

Person getPerson() {
	return { 25,"Lucy" };
}
void funcPerson(initializer_list<int> ls){
	auto it = ls.begin();
	for (;it!= ls.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//普通函数
void printPerson(int age, string name) {
	cout << " age:" << age << " , name: " << name << endl;
}
