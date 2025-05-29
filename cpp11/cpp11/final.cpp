#include <iostream>
using namespace std;
class FinalBase {
public:
	virtual void test(){
		cout << "FinalBase class..."<<endl;
	}
};

class Child:public FinalBase {
public:
	void test() override
	{
		cout << "child class..." << endl;
	}
};

class GrabdChild :public Child {
public:
	void test()override final
	{
		cout << "GrabdChild class..." << endl;
	}
};