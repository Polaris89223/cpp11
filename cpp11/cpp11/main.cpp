// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "template.hpp"
#include "except.hpp"
#include "auto.hpp"
#include "declaretype.hpp"
#include "nullptr.hpp"
#include "lamda.hpp"

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
//函数声明
int func_int() { return 10; };
int& func_int_r() { int a = 10; return a;};
int&& func_int_rr() { return 10; };
const int func_cint() { return 10; };
const int& func_cint_r() { return 10; };
const int&& func_cint_rr() { return 10; };
const Base func_cBase(){ 
	Base a;
	return a; };

//T->参数1类型  U->参数2类型
template <typename T,typename U>
auto add(T t, U u)->decltype(t+u){
	return t + u;
}

int main()
{
	/*特性1 原始字面量 语法 R"XXX(原始字符串)XXX",其中()两边的字符串可以省略，
	原始字面量R可以直接表示字符串的实际含义，而不需要额外对字符串做转义*/
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

	/*特性9 自动类型推导auto和decltype
	auto 变量名=变量值;
	当变量不是指针或者引用类型时，推导的结果中不会保留const、volatile关键字
	当变量是指针或者引用类型时，推导的结果中会保留const、volatile关键字
	auto的限制 
	  1)不能用于函数形参 
	  2)不能用于类的非静态成员变量的初始化
	  3)不能使用auto关键字定义数组 
	  4)不能使用auto推导出模板参数
	auto的应用
	    1)用于STL容器的遍历
		2)用于泛型编程
	decltype 类型推导，不需要初始化,推导出来的类型可以用于重新定义变量
	语法 decltype(表达式)
	推导规则
	   1)表达式为普通变量或者普通表达式或类表达式，这种情况下，使用decltype推导出
	   的类型和表达式的类型是一致的。
	   2)表达式是函数调用，使用decltype推导出的类型和函数返回值一致。如果函数返回
	   的是一个纯右值，对于纯右值而言只有类型类型可以携带const、volatile限定符
	   除此之外需要忽略掉这两个限定符。
	   3）如果表达式是一个左值，或者被括号()包围，使用decltype推导出的是表达式类型
	   的引用（如果右const、volatile限定符不能忽略）
	应用
	   泛型编程
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

	int x = 0;
	//a:int
	decltype(x) a = x;
	//b:int
	decltype(func_int()) b = x;
	//cc:int&
	decltype(func_int_r()) cc = x;
	//dddd:int&&
	decltype(func_int_rr()) dddd = 0;
	//e:int
	decltype(func_cint()) e = 0;
	//f:int&
	decltype(func_cint_r()) f = 0;
	//g:int&&
	decltype(func_cint_rr()) g = 0;
	//h:const Base
	decltype(func_cBase()) h = 0;

	const Base baseObj;
	//带有括号的表达式
	//aaa:int
	decltype(baseObj.b) aaa = 0;
	//bbb:const int&
	decltype((baseObj.b)) bbb = 0;
	int mm = 0;
	int nn = 0;
	//ccc:int
	decltype(mm+nn) ccc = 0;
	//xxx:int&
	decltype(nn=mm+nn) xxx = nn;

	list<int> ls{ 1,2,3,4,5,6,7 };
	MyContainer<list<int>> mycontainer;
	mycontainer.print(ls);

	const list<int> ls1{ 1,2,3,4,5,6,7 };
	MyContainer<const list<int>> mycontainer1;
	mycontainer1.print(ls1);

	/*
	特性10 返回值类型后置语法，说直白点就是将decltype和auto结合起来完成返回类型的推导
	auto func(参数1，参数2,...)->decltype(表达式)
	auto会追踪deltype()推导出的类型
	*/
	int afterX = 520;
	double afterY = 13.14;
	auto aftetVal = add<int, double>(afterX, afterY);
	cout << "aftetVal: " << aftetVal << endl;

	/*
	特性11 基于范围的for循环
	for(declaration:expression){
	  //循环体
	}
	declaration表示遍历声明，在遍历过程中，当前被遍历到的元素会被存储到声明的变量中
    expression是要遍历的对象，它可以是表达式、容器、数组，初始化列表等。
	注意事项：
	     1)使用普通的for循环方式（基于迭代器）遍历关系型容器，auto自动推导出的是一个
		 迭代器类型，需要使用迭代器的方式去除元素中的键值对（和指针的操作方式相同）
		  it->first it->second
		 2)使用基于范围的for循环遍历关系型容器，auto自动推导出的类型是容器中的value_type
		 相当于一个队组（std::pair)对象，提取值的方式如下:
		 it.first it.second
		 3)元素只读，对应set容器来说，内部元素是只读的，这是由容器特性决定的，因此在
		 基于范围的for循环中auto&会被视为const auto&
		 4)map容器中key也是只读的
		 5)访问次数:基于范围的for循环,访问容器只访问1次。
	*/
	vector<int> vt{ 1,2,3,4,5,6,7,8,9 };
	for (auto it = vt.begin(); it != vt.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	//基于范围的for循环
	for (auto& it : vt) {
		cout << it << " ";
	}
	cout << endl;

	/*
	特性12 指针空值类型-nullptr
	nullptr无法转换为整形，但是可以隐士匹配指针类型，在C++11标准下，相比NULL和0，
	使用nullptr初始化指针可以令我们编写的程序更加健壮。
	*/
	int* ptr1 = nullptr;
	char* ptr2 = nullptr;
	double* ptr3 = nullptr;
	void* ptr4 = nullptr;

	//int
	nullptrFunc(10);
	//char*
	nullptrFunc(nullptr);

	/*
	特性13 lamda表达式
	语法：[capture](params)opt->ret{body;};
	其中capture是捕获列表，params是参数列表 opt是函数选项，ret是返回值类型，body是
	opt选项,不需要可以省略
	   mutable :可以修改按值传递进来的拷贝
	   exception:指定函数抛出的异常，如抛出整数类型的异常，可以使用throw ()；
	函数体
	[]不捕捉任何变量
	[&]捕获外部作用域中所有变量，并列为引用在函数体内使用(按引用捕获)
	[=]捕获外部作用域中所有变量，并作为副本在函数体内使用(按值捕获)
	   拷贝的副本在匿名函数体内部都是只读的
	[=,&foo]按值捕获外部作用域中所有变量，并按照引用捕获外部变量foo
	[bar]按值捕获bar变量，同时不捕获其他变量
	[&bar]按引用捕获bar变量，同时不捕获其他变量
	[this]捕获当前类中的this指针
	   函数本质：
	     1)lamda表达式的类型在c++11中会被看成一个带operator()的类，即仿函数。
		 2)按照C++标准，lamda表达式的operator()默认是const的，一个const成员函数
		 是无法修改成员变量值的。
     mutable 选项的作用在于取消operator()的const属性。
	     3）lamda表达式在C++中被看作是一个仿函数，因此可以使用std::fuction和std::bind
		 来存储和操作lamda表达式。
		 4）对于没有捕获任何外部变量的lamda表达式，可以转成一个普通的函数指针。
	*/
	auto lamdaFunc1 = [&](int x,int y)->int{return x+y; };
	lamdaFunc(1,2);

	getchar();
}