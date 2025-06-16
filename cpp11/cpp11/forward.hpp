#pragma once
#include <iostream>
using namespace std;
template <typename T>
void printValue(T&t) {
	cout << "l-value: " << t << endl;
}

template <typename T>
void printValue(T&&t) {
	cout << "r-value: " << t << endl;
}

template <typename T>
void testForward(T&&v) {
	printValue(v);
	printValue(move(v));
	printValue(forward<T>(v));
	cout << endl;
}