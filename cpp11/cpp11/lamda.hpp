#pragma once
#include <iostream>
#include <functional>
using namespace std;

void lamdaFunc(int x, int y) {
	int a = 0;
	int b = 0;
	using ptr = void(*)(int);
	[=, &x](int z)mutable {
		int c = a;
		int d = x;
		b++;
		cout << " b:" << b << endl;
	}(10);
	ptr pt1 = [](int x) {
		cout << " x:" << x << endl;
	};
	pt1(11);

	function<void(int)> ff = [=](int x) {
		cout << " x:" << x << endl;
	};
	ff(12);

	function<void(int)> ee = bind([=](int x) {
		cout << " x:" << x << endl;
	},placeholders::_1);
	ee(13);
	cout << " b:" << b << endl;
}

