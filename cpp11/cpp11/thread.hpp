#pragma once
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
using namespace std;

class ThreadBase {
public:
	void showMsg(string name, int age) {
		cout << "My name is:" << name << ",I am:" << age << "old years..." << endl;
	}
	static void message() {
		cout << R"(我是梦琪的路飞，是要成为海贼王的男人！！)" << endl;
	}
};

void threadFunc() {
	cout << "I am son thread,My name is lufy..." << this_thread::get_id() << endl;
}
void threadFunc1(string name ,int age) {
	cout << "I am son thread,My name is"<<name<<",age"<<age<<this_thread::get_id() << endl;
}
once_flag g_flag;
void do_once(int a,string b) {
	cout << "name: " << b << ",age: " << a << endl;
}
void do_something(int age, string name) {
	static int num = 1;
	call_once(g_flag, do_once, 19, "luffy");
	cout << endl;
	cout << "do_something() funciton num=" << num++ << endl;
}
void threadTest() {
	cout << "parent thread id:" << this_thread::get_id() << endl;

	//创建空的线程对象
	thread t1;

	//2.创建一个可用的子线程
	thread t2(threadFunc);
	thread t3(threadFunc1,"Tom",18);
	thread t4([=](int id) {
		cout << "arg id:" << id << " thread id: " << this_thread::get_id() << endl;
	}, 1001);
	thread&& t5 = move(t4);
	t2.join();
	t3.join();
	t5.detach();
	cout << "t5 thread id:" << t5.get_id() << endl;

	thread t6;
	cout << "t6 joinable: " << t6.joinable() << endl;

	thread t7(threadFunc);
	cout << "t7 joinable: " << t7.joinable() << endl;
	t7.join();
	cout << "t7 joinable: " << t7.joinable() << endl;

	thread t8(threadFunc);
	t8.detach();
	cout << "t8 joinable: " << t8.joinable() << endl;

	//传递静态成员函数
	thread t9(&ThreadBase::message);

	//传递类的成员函数
	ThreadBase base;
	thread t10(&ThreadBase::showMsg, base,"lufei",19);
	thread t11(&ThreadBase::showMsg, &base, "lufei", 19);
	thread t12(bind(&ThreadBase::showMsg, &base, "lufei", 19));
	thread t13(bind(&ThreadBase::showMsg, base, "lufei", 19));
	
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();

	thread t14(do_something, 20, "ace");
	thread t15(do_something, 20, "sabo");
	thread t16(do_something, 19, "luffy");

	t14.join();
	t15.join();
	t16.join();
}
//编写一个单例模式的类-->懒汉模式
once_flag g_base_flag;
class SigleBase {
public:
	SigleBase(const SigleBase&obj) = delete;
	SigleBase& operator = (const SigleBase&obj) = delete;
	static SigleBase* getInstance(){
		call_once(g_base_flag, [&]() {
			obj = new SigleBase;
			cout << "instance creating ..." << endl;
		});
		return obj;
	}
	void setName(string name) {
		this->name = name;
	}
	string getName() {
	   return this->name;
	}
private:
	SigleBase(){};
	static SigleBase* obj;
	string name;
};
SigleBase* SigleBase::obj = nullptr;
void MySigleTest(string name) {
	SigleBase::getInstance()->setName(name);
	cout << "my name is:" << SigleBase::getInstance()->getName() << endl;
}