// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <cassert>
#include "template.hpp"
#include "except.hpp"
#include "auto.hpp"
using namespace std;
struct Base {
	Base() :a(250) {}
	Base(int num) :a(num) {}
	int a{0};
	int b = 1;
	string str = "hello";
	string strl{ "hello" };
	static int c;
	static const double d;
	static const char*const e;
	//c++98标准：变量是静态变量，并且类型是整形或者枚举类型
	static const int f = 0;
};
int Base::c = 8;
const double Base::d = 3.14;
const char*const Base::e = "i am porlaris";

char* createArray(int size) {
	assert(size > 0);
	char* array = new char[size];
	return array;
}
int main()
{
	//特性1 原始字面量 语法 R"XXX(原始字符串)XXX",其中()两边的字符串可以省略，原始字面量R可以
	//直接表示字符串的实际含义，而不需要额外对字符串做转义
	string str = R"(D:\hello\World\test.text)";
	string str1 = R"(<html>
                     <title>
                     我是海贼王
                     </title>
                    </html>
				 )";
	cout << str << endl;
	cout << str1 << endl;

	/*
	特性2 long long 类型 超长整形
	*/
	//有符号
	long int n = 100L;
	//signed long long
	//signed long long int
	long long num1 = 1000LL;
	//unsigned long long int
	unsigned long long num2 = 111ULL;

	//占内存大小最少是8字节
	//LLONG_MAX LLONG_MIN
	cout<<"long long max: " << LLONG_MAX
		<< ", long long min: " << LLONG_MIN
	    << " ,unsigned long long max: " << ULLONG_MAX;

	//低等级int 到 高等级 int
	char c = 6;
	long long d = c;

	//标准int 自定义int
	typedef int aa;
	aa bb = 5;
	int num = bb;
	long long num3 = bb;
	//有符号int ==》无符号int (内存大小相同)==>有符号===》无符号整形
	unsigned int num4 = num3;
	//隐式类型转换 低等级=》高等级  自定义类型=>标准类型   (内存相同) 有符号类型=》无符号类型


	//特性3 类成员变量的快速初始化 可以在类中对非静态成员直接进行初始化
	//请看Base结构体定义
	//c++11 中在类内部有两种初始化 = 和 {}
	//初始化列表值会覆盖类内部初始化值
	Base test;
	cout << "test.a: " << test.a << endl;

	//特性4 final关键字和override
	//final 关键字来限制某个类不能被继承，或者某个函数不能被重写
	//如果使用final修饰函数，只能修饰虚函数，并且要把final关键字放到类名或者函数名的后面。
	//ovveride 关键字确保在派生类中声明的重写函数与基类的虚函数有相同的签名，同时也明确将会
	//重写基类虚函数，可以保证重写虚函数的正确性，也提高代码可读性，和final一样这个关键字写到
	//函数名的后面

	//特性5 模板的优化
	/*
	 1.模板的右尖括号
	 在泛型编程中，模板实例化有一个非常繁琐的地方，那就是连续两个右尖括号(>>)会被编译器解析
	 成右移操作符，而不是模板参数表的结束。C++11改进了编译器的解析规则，尽可能地将多个右尖括
	 号(>)解析成模板参数结束符,方便我们编写模板相关的代码。
	 2.默认模板参数
	 C++98标准中，类模版可以有默认的模板参数,但是不支持函数的默认模板参数，C++11中
	 支持对函数模板添加默认的模板参数。
	 如果可以推导出参数类型则使用推导出类型
	 如果无法推导出参数类型则编译器会使用默认模板参数
	 如果无法推导出模板参数类型并且没有默认模板参数，编译器就会报错。
	*/
	map<int, string> m;
	m.insert(make_pair(1, "ace"));
	m.insert(make_pair(2, "sabo"));
	m.insert(make_pair(3, "luffy"));
	//C++11才会将两个右尖括号(>>)解析为模板参数结束符
	Container<map<int, string>>container;
	container.print(m);

	//默认模板参数
	func(100);

	//自动类型推导，根据传递的实参
	mytest('a', 'b');
	mytest<int>('a', 'b');
	mytest<char>('a', 'b');
	mytest<int,char>('a', 'b');
	mytest<char,int>('a', 'b');
	mytest();

	//特性6 静态断言 static_assert
	//断言assert(),运行时检查
	//静态断言，编译器期间检查
	char* pBuffer = createArray(10);
	if (nullptr != pBuffer) {
		delete []pBuffer;
		pBuffer = nullptr;
	}
	static_assert(sizeof(long*)==4,"current os is x86");
	cout << "hello,world" << endl;

	//特性7 noexcept 放在函数名的后面表示该函数不会抛出异常
	exceptFunc();
	noExceptFunc();

	//特性8 数值类型和字符串之间的转换
	//1.数值转为字符串 to_string()
	long double dd = 3.1415926789;
	string pi = "pi is " + to_string(dd);
	string love = "love is " + to_string(3.14);
	cout << pi << endl;
	cout << love << endl;

	//2.字符串转为数值类型 stoi
	string str_dec = "2022.02.04,Beijing Winter Olympics";
	string str_hex = "40c3";
	string str_bin = "-10010110001";
	string str_auto = "0x7f";
	size_t sz;
	int i_dec = stoi(str_dec, &sz);
	int i_hex = stoi(str_hex, nullptr, 16);
	int i_bin = stoi(str_bin, nullptr, 2);
	int i_auto = stoi(str_auto, nullptr, 0);
	cout << "....sz= " << sz << endl;
	cout << str_dec << ": " << i_dec << endl;
	cout << str_hex << ": " << i_hex << endl;
	cout << str_bin << ": " << i_bin << endl;
	cout << str_auto<< ": " << i_auto << endl;

	//特性9 自动类型推导auto和decltype
	//auto 变量名=变量值;
	//当变量不是指针或者引用类型时，推导的结果中不会保留const、volatile关键字
	//当变量是指针或者引用类型时，推导的结果中会保留const、volatile关键字
	//auto的限制 
	//  1)不能用于函数形参 
	//  2)不能用于类的非静态成员变量的初始化
	//  3)不能使用auto关键字定义数组 
	//  4)不能使用auto推导出模板参数
	//auto的应用
	/*
	    1)用于STL容器的遍历
		2)用于泛型编程
	*/

	//没有const修饰
	auto auto1 = 1;
	auto auto2 = 3.14;
	auto auto3 = 'a';
	int temp = 110;
	auto *auto4 = &temp;
	auto auto5 = &temp;
	auto &auto6 = temp;
	auto auto7 = temp;
	//有const修饰
	const auto auto8 = temp;
	auto auto9 = auto8;
	auto auto10 = auto8;
	//auto11: const int&
	const auto& auto11 = temp;
	//auto12: const int&
	auto& auto12 = auto11;
	//auto13: const int*
	auto* auto13 = &auto8;

	autoFunc<T1>();
	autoFunc<T2>();

	autoFunc1<T1, int>();
	autoFunc1<T2, string>();
	getchar();
}