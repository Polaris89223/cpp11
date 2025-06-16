#pragma once
#include <iostream>
#include <memory>
using namespace std;
/*
* shared_ptr 使用注意事项：
* 1.不能使用一个原始地址初始化多个共享智能指针
* 2.函数不能返回管理了this的共享智能指针对象
* 3.共享智能指针不能循环引用(乱伦)
*/
struct SharedPtr:public enable_shared_from_this<SharedPtr>
{
	shared_ptr<SharedPtr> getSharedPtr() {
		return shared_from_this();
	}
	~SharedPtr() {
		cout << "class SharedPtr is descontruct..." << endl;
	}
};
struct TA;
struct TB;
struct TA {
	//shared_ptr<TB> bptr;
	weak_ptr<TB> bptr;
	~TA() {
		cout << "class TA is descontruct..." << endl;
	}
};

struct TB {
	//shared_ptr<TA> aptr;
	weak_ptr<TA> aptr;
	~TB() {
		cout << "class TB is descontruct..." << endl;
	}
};

//循环引用
void testSharedPtr() {
	shared_ptr<TA> ap(new TA);
	shared_ptr<TB> bp(new TB);
	cout << "TA object use_count:" << ap.use_count() << endl;
	cout << "TB object use_count:" << bp.use_count() << endl;

	ap->bptr = bp;
	bp->aptr = ap;

	cout << "TA object use_count:" << ap.use_count() << endl;
	cout << "TB object use_count:" << bp.use_count() << endl;
}
