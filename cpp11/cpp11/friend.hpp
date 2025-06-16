#pragma once
#include <iostream>
using namespace std;
class Tom;
using Honey = Tom;
class Jack {
	//friend class Tom; //C++98标准
	friend Tom;//C++11标准
private:
	string name = "jack";
	void print() {
		cout << "my name is:" << name << endl;
	}
};

class Lucy {
	//friend class Honey; //C++98标准
	friend Honey;//C++11标准
protected:
	string name = { "lucy" };
	void print() {
		cout << "my name is:" << name << endl;
	}
};

class Tom {
public:
	void print() {
		cout << j.name << endl << l.name << endl;
		j.print();
		l.print();
	}
private:
	Jack j;
	Lucy l;
};

template <typename T>
class Rectangle{
public:
	friend T;
	Rectangle(int w, int h) :width(w), height(h) {}
private:
	int width;
	int height;
};

template <typename T>
class Circle {
public:
	friend T;
	Circle(int r) :radius(r){}
private:
	int radius;
};

class Verify {
public:
	Verify(int w, int h, Rectangle<Verify>& r) {
		if (r.width > w && r.height > h) {
			cout << "Rectangle is valid" << endl;
		}
		else {
			cout << "Rectangle is invalid" << endl;
		}
	}
	Verify(int r, Circle<Verify>& c) {
		if (c.radius<r) {
			cout << "Circle is valid" << endl;
		}
		else {
			cout << "Circle is invalid" << endl;
		}
	}
};

