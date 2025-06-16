#pragma once
#include <iostream>
using namespace std;

class RvReference
{
public:
	RvReference():m_num(new int(100)) {
		cout << "copy construct:my name is Jerry" << endl;
		printf("m_num address:%p\n", m_num);
	}
	RvReference(const RvReference&a):m_num(new int(*a.m_num)) {
		cout << "copy construct:my name is Tom" << endl;
		printf("m_num address:%p\n", m_num);
	}
	////移动构造函数->复用其他对象中的资源(堆内存)
	////m_num,浅拷贝
	//RvReference(RvReference&&a) :m_num(a.m_num) {
	//	a.m_num = nullptr;
	//	cout << "move construct..." << endl;
	//}
	virtual ~RvReference() {
		if (m_num) {
			delete m_num;
			m_num = nullptr;
		}
		cout << "destruct RvReference class..." << endl;
	}
public:
	int* m_num;
};

//赋值时候是临时对象，则调用移动构造函数，如果不是则调用拷贝构造函数
RvReference getObj() {
	RvReference t;
	return t;
}
RvReference getObj1() {
	return RvReference();
}

RvReference&& getObj2() {
	return RvReference();
}
