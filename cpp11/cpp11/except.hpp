#include <iostream>
#include <string>
#include <map>
using namespace std;
struct MyException {
	MyException(string str):msg(str) {}
	string msg;
};

void exceptFunc() throw(int,double,MyException){
	try
	{
		//throw 1;
		throw MyException("string exception!");
	}
	catch (const int e)
	{
		cout << "thow value:" << e << endl;
	}
	catch (MyException e) {
		cout << "MyException:" << e.msg << endl;
	}
}

void noExceptFunc()noexcept(false) {
	try
	{
		throw 1;
		throw MyException("string exception!");
	}
	catch (const int e)
	{
		cout << "thow value:" << e << endl;
	}
	catch (MyException e) {
		cout << "MyException:" << e.msg << endl;
	}
	cout << "noExceptFunc "<< endl;
}