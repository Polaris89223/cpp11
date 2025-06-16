#pragma once
#include <iostream>
#include <functional>
using namespace std;
class A 
{
public:
	//构造函数参数是一个包装器对象
	A(std::function<void(int, string)>f) :callback(f) {

	}
	void notify(int id, string name) {
		callback(id, name);//调用通过构造函数得到的函数指针
	}
private:
	function<void(int, string)> callback;
};

void testBind(int x, int y, const function<void(int, int)>&f) {
	if (0 == (x % 2)) {
		f(x, y);
	}
}
void output_add(int x, int y) {
	cout << "x: " << x << ",y: " << y
		<< ",x+y: " << x + y << endl;
}


