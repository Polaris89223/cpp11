#pragma once
#include <iostream>
using namespace std;
//C++98中枚举全局可见的
enum TestColor:char{Red='a',Green,Blue};
//C++11 强类型枚举
enum class Color:char{ Red, Green, Blue };
enum struct Color1:int{ Red, Green, Blue };
class EnumTest {
public:
	EnumTest() {};
	static void print() {};
	std::string str;
};
