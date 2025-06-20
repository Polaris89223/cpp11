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
#include "delegateConstruct.hpp"
#include "initialList.hpp"
#include "functional.hpp"
#include "rvReference.hpp"
#include "forward.hpp"
#include "c11Ptr.hpp"
#include "sharedPtr.hpp"
#include "friend.hpp"
#include "enumtest.hpp"
#include "UnionTest.hpp"
#include "chrono.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "condition.hpp"
#include "atomic.hpp"
#include "future.hpp"
#include "packagetask.hpp"
#include "async.hpp"

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

struct T
{
	constexpr T():a(100) {}
	int a;
};

struct person {
	const char* name;
	int age;
};

template<typename T>
constexpr T display(T t) {
	return t;
}

template<typename T>
struct MyMap {
	typedef map<int, T>mapType;
};

template<typename T>
using MMap = map<int, T>;


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
	   的引用（如果有const、volatile限定符不能忽略）
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

	/*
	特性14 constexpr(常量表达式)：指的就是由多个(>=1)常量(值不会改变)组成并且在编译
	过程中就得到计算结果的表达式。
	常量表达式发生在编译期间
	凡是修饰"只读"语义的场景使用const，表达"常量"语义的场景使用constexpr
	1.常量表达式函数
	    1）修饰函数，函数必须由返回值，并且return返回的表达式是常量表达式。
		2）函数在使用之前，必须由对应的定义语句。
		3）整个函数的函数体中，不能出现非常量表达式之外的语句（using指令 typedef语句
		以及static_assert断言、return语句除外）
	2.修饰模板函数
	   如果constexpr修饰的模版函数实例化结果不满足常量表达式函数的要求，则constexpr会
	   被自动忽略，即该函数等同于一个普通函数。
	3.修饰构造函数
	   构造函数的函数体必须为空，并且必须采用初始化列表的方式为各个成员赋值。
	*/
	const int expi = 520;
	constexpr int expj = expi + 1;
	constexpr T expBase;
	constexpr struct person person1 {"lucy",19};
	constexpr struct person personret = display<struct person>(person1);

	/*
	特性15:using的使用
	  语法：using 新的类型  = 旧的类型;
	  1.定义类型别名
	  2.为模板定义别名
	  using语法和typedef一样，并不会创建出新的类型，他们只是给某些类型定义了新的名字
	  using相较于typedef的优势在于定义函数指针别名看起来更加直观，并且可以给模版定义
	  别名
	*/
	typedef int Integer;
	Integer integerA = 0;
	typedef int(*funcPtr)(int, string);
	using func1 = int(*)(int, string);

	MyMap<int>::mapType maptype1;
	maptype1.insert(make_pair(1, 1));
	maptype1.insert(make_pair(2, 2));
	maptype1.insert(make_pair(3, 3));
	Container<MyMap<int>::mapType> printContainer1;
	printContainer1.print(maptype1);

	MyMap<double>::mapType maptype2;
	maptype2.insert(make_pair(1, 1.11));
	maptype2.insert(make_pair(2, 2.22));
	maptype2.insert(make_pair(3, 3.33));
	Container<MyMap<double>::mapType> printContainer2;
	printContainer2.print(maptype2);

	MMap<string> maptype3;
	maptype3.insert(make_pair(1, "1.11"));
	maptype3.insert(make_pair(2, "2.22"));
	maptype3.insert(make_pair(3, "3.33"));
	Container<MMap<string>> printContainer3;
	printContainer3.print(maptype3);

	/*
	特性16:委托构造函数和继承构造函数
	   委托构造函数:允许使用同一个类中的一个构造函数调用其他的构造函数，从而简化
	   变量的相关初始化。
	   注意事项：
	       1)链式的构造函数调用不要形成一个闭环，否则会在运行期间抛异常。
		   2)如果要进行多层构造函数的链式调用，建议将构造函数的调用写在初始列表中而
		   不是函数体内，否则编译器会提示形参的重定义。
		   3)在初始化列表中调用了代理构造函数初始化某个类成员变量之后，就不能在初始化
		   列表中再次初始化这个变量了。
	   继承构造函数:c++11中提供的继承构造函数可以让派生类直接使用基类的构造函数，而无需
	   自己在写构造函数，尤其是在基类很多构造函数的情况下，可以极大简化派生类构造函数的
	   编写。
	*/
	ChildBase childBase(520, 13.14, "I love you");
	childBase.func();
	childBase.func(19);
	childBase.func(19, "lily");

	/*
	特性17:列表初始化 类名或者类型名{实参}
	1.统一的初始化
	2.列表初始化细节
	 2.1 聚合体(普通数组本身就是一个聚合体)
	    满足以下条件的类(class、struct、union)可以看作是一个聚合类型
		无用户自定义的构造函数
		无私有或保护的非静态数据成员
		无基类
		无虚函数
		类中不能使用{}和=直接初始化的非静态数据成员(C++14开始就支持了)
	2.2 非聚合体(自定义数组类型就是一个非聚合体)
		满足以下条件的类(class、struct、union)可以看作是一个非聚合类型
	    有自定义的构造函数
		有私有或保护的非静态数据成员
		有基类
		有虚函数
	2.3 std::initializer_list模板类 可以接收多个相同类型的参数
	    1）作为构造函数的参数
		2）作为普通函数的参数
	注意事项：
		结构体中的静态变量z不能使用初始化列表进行初始化，他的初始化遵循静态成员的
		初始化
	*/
	Person p1(520);
	Person p2 = 500;
	//初始化列表方式
	Person p3 = { 520 };
	Person p4{ 520 };
	int p5 = { 1314 };
	int p6{ 1314 };
	int arr1[] = { 1,2,3,4 };
	int arr2[]{1,2,3,4 };
	int *p7 = new int{ 520 };
	int* aar3 = new int[3]{ 1,2,3 };

	//initializer_list用法
	funcPerson({ 1,2,3,4,5 });

	/*
	特性18:可调用对象的包装器、绑定器
	1.可调用对象
	  1)是一个函数指针
	  2)是一个具有operator()成员函数的类对象（仿函数）
	  3)是一个可被转换为函数指针的类对象
	  4)是一个类成员的函数指针或者类成员指针
	2.可调用对象包装器(std::function)
	  #include <functional>
	  std::function<返回值类型(参数类型列表)> diy_name = 可调用对象;
	  注意事项
	    1)类的成员函数，不能直接包装
	3.可调用对象绑定器(std::bind)
	  std::bind用来将可调用对象和其参数一起进行绑定，绑定后的结果可以使用std::function
	  进行保存，并延迟调用到任何我们需要的时候。
	   1）将可调用对象与其参数一起绑定成一个仿函数。
	   2）将多元(参数个数为n，n>1)可调用对象转换为一元或者(n-1)元可调用对象,即只绑定
	   部分参数。
	   //绑定非类成员函数/变量
	   auto f = std::bind(可调用对象地址，绑定的参数/占位符);
	   //绑定类成员函数/变量
	   auto f = std::bind(类函数/成员地址,类实例对象地址，绑定的参数/占位符);
	   std::placeholders::_1是一个占位符,代表这个位置将在函数调用时被传入的第一个参数
	   所替代。
	   绑定器绑定完得到了一个仿函数。
	*/
	Person persons18(11);
	persons18(19, "12112");

	//类的函数指针
	personFuncptr funcptr1 = Person::hello;
	using personFuncPtr1 = void(Person::*)(int,string);
	personFuncPtr1 funcptr2 = &Person::world;

	//类的成员指针
	using personFuncPtr4 = int Person::*;
	personFuncPtr4 funcptr4 = &Person::m_id;

	(persons18.*funcptr2)(20,"ace");
	persons18.*funcptr4 = 100;
	cout << "m_id: " << persons18.m_id << endl;

	//1.包装普通函数
	std::function<void(int, string)> personFunc1 = printPerson;
	personFunc1(1, "ace");
	//2.包装类的静态函数
	std::function<void(int, string)> personFunc2 = Person::hello;
	personFunc2(2, "sabo");
	//3.包装仿函数
	std::function<void(string)> personFunc3 = persons18;
	personFunc3("luffy");
	//4.包装转为函数指针的对象
	std::function<void(int,string)> personFunc4 = Person::hello;
	personFunc4(3,"sabbp");

	A funcitonA(printPerson);
	funcitonA.notify(1,"ace");

	A funcitonB(Person::hello);
	funcitonB.notify(2, "ace");

	A funcitonC(persons18);
	funcitonC.notify(3, "ace");

	bind(printPerson, placeholders::_1, placeholders::_2)(1, "ximi");
	bind(printPerson, 2, placeholders::_2)(3, "ximi");
	for (size_t i = 0; i < 10; i++)
	{
		auto f = bind(output_add, i + 100, i + 200);
		testBind(i, i, f);
		auto f1 = bind(output_add, placeholders::_1, placeholders::_2);
		testBind(i, i, f1);
	}
	//成员函数绑定
	auto bindfunc = bind(&Person::world, &persons18, 520, placeholders::_1);
	bindfunc("1314");
	//绑定成员变量
	auto bindfunc1 = bind(&Person::m_id, &persons18);
	function<int&(void)> bindfunc2 = bind(&Person::m_id, &persons18);
	cout << bindfunc1() << endl;
	bindfunc1() = 666;
	cout<<bindfunc1()<<endl;

    /*
	特性19 右值引用
	c++11中添加了新的类型，称为右值引用，标记为&&
	左值(locate value):指存储在内存中、有明确存储地址(可取地址)的数据。
	右值(read value):是指可以提供数据值的数据(不可取地址)
	右值引用:只允许右值初始化右值引用。
	右值引用作用:能够延长某块内存的存活时间。
	纯右值：非引用返回的临时变量、运算表达式产生的临时变量、原始字面量和lambda表达式等
	将亡值：与右值引用相关的表达式，比如T&&类型函数的返回值，std::move的返回值等
	注意事项(类型推导，&&未定义的引用类型，const T&&表示一个右值引用)
	    1)通过右值推导T&&或者auto &&得到的是一个右值引用类型。
		2)通过非右值（右值引用、左值、左值引用、常量右值引用、常量左值引用）推导
		T&&或者auto && 得到的是一个左值引用类型。
		3）左值和右值是独立于他们类型的，右值引用类型可能是左值也可能是右值。
		4）编译器会将已命名的右值引用视为左值，将未命名的右值引用视为左值。
		5）auto&&或者函数参数类型自动推导的T&&是一个未定的引用类型，它可能是左值
		引用类型也可能是右值引用类型，这取决于初始化的值类型
		6）通过右值推导T&& 或者auto &&得到的是一个右值引用类型，其余都是左值引用
		类型。
	*/
	//左值
	int lvalue = 9;

	//左值引用
	int &lvalRenrence = lvalue;

	//右值 右值引用
	int && rvalRerence = 8;

	//常量左值引用
	const auto & lvalRenrence1 = lvalue;

	//常量右值引用
	const auto && rvalRerence1 = 6;

    //要求右侧的对象是一个临时对象，才会调用移动构造函数
	//如果没有移动构造函数，就会调用拷贝构造函数
	RvReference reference = getObj();
	cout << endl;
	RvReference&& reference1 = getObj();
	printf("m_num address:%p \n", reference1.m_num);

	//如果没有移动构造函数，使用右值引用初始化要求更高一些
	//要求是一个临时的，不能取地址的对象
	cout << endl;
	RvReference&& reference2 = getObj1();
	printf("m_num address:%p \n", reference2.m_num);

	/*
	特性:20 std::move
	作用：使用std::move方法可以将左值转换为右值，使用这个函数并不能移动任何东西，而是
	和移动构造函数一样都具有移动语义，将对象的状态或者所有权从一个对象转移到另一个对象
	只是转移，没有内存拷贝。
	从实现上讲，std::move基本等同于一个类型转换：static_cast<T&&>(lvalue),函数原型如下:
	template<class _Ty>
	_NODISCARD constexpr remove_reference_t<_Ty>&&move(_Ty&& _Arg) noexcept
	{	// forward _Arg as movable
	return (static_cast<remove_reference_t<_Ty>&&>(_Arg));
	}
	*/
	RvReference&& reference3 = move(reference2);
	RvReference&& reference4 = move(reference);

	/*
	特性:21 std::forward
	作用:右值引用类型独立于值的，一个右值引用作为函数参数的形参时，在函数内部转发
	该参数给内部其他函数的时候，它就变成一个左值，并不是原类型了，如果需要按照参数
	原来的类型转发到另一个函数，可以用C++11提供的std::forward()函数，该函数实现的功
	能称为完美转发。
	template<class _Ty>
	_NODISCARD constexpr _Ty&& forward(remove_reference_t<_Ty>& _Arg) noexcept
	{	// forward an lvalue as either an lvalue or an rvalue
	return (static_cast<_Ty&&>(_Arg));
	}
	精简之后的例子：std::forward(T)(t);
	推导规则：
	      当T为左值引用类型时，t将被转移为T类型的左值。
		  当T不是左值引用类型时，t将被转移为T类型的右值。
	*/
	testForward(520);
	int testNum = 1314;
	testForward(testNum);
	testForward(forward<int>(testNum));
	testForward(forward<int&>(testNum));
	testForward(forward<int&&>(testNum));

	/*
	特性22:智能指针
	智能指针是存储指向动态分配(堆)对象指针的类，用于生存期的控制，能够确保在离开指针
	所在的作用域时，自动地销毁动态分配的对象，防止内存泄露，智能指针的核心实现技术是
	引用计数，每使用它一次，内部引用计数加1，每析构一次内部的引用计数减1，减为0时，删
	除指向的堆内存。
	C++11中引入三种类型智能指针，使用这些智能指针需要引用头文件<memory>
	std::shared_ptr:共享的智能指针 语法:std::shared_ptr<T>智能指针名称(创建堆内存)
	初始化方式：
	      1)通过构造函数初始化
		  2)通过拷贝构造函数和移动构造函数初始化
		  3)通过std::make_shared初始化
		  4)通过reset方法初始化
	指定删除器
	     1)当shared_ptr管理数组内存的时候，必须指定删除器，否则内存无法释放
		 2)也可以使用默认删除器函数std::default_delete
	std::unique_ptr:独占的智能指针 语法:std::unique_ptr<T>智能指针名称(创建堆内存)
	    初始化方式
		  1)通过构造函数初始化
		  2)通过move函数初始化
		  3)通过reset方法初始化
    指定删除器 
	std::weak_ptr:弱引用智能指针，它不共享指针，不能操作资源，是用来监视shared_ptr的。
	初始化:
	   //默认构造函数
	   constexpr weak_ptr() noexcept;
	   //拷贝构造函数
	   weak_ptr(const weak_ptr& x) noexcept;
	   template<class U>weak_ptr(const weak_ptr<U>& x) noexcept
	   //通过shared_ptr对象构造
	   template<class U>weak_ptr(const shared_ptr<U>& x) noexcept
	作用：
	      1)返回管理this的shared_ptr（被析构两次）
		  2)解决循环引用的问题
    其他函数
	      1)use_count()当前内存块被多少哥智能指针引用
		  2)expired()  判断观测的资源是否已经被释放
		  3)lock()用来获取管理所监测资源的shared_ptr对象
		  4)reset() 重置弱引用对象，使其不监测任何资源
	*/
	//通过构造函数初始化
	shared_ptr<int> sharedPtr1(new int(3));
	cout << "sharedPtr1 use count: " << sharedPtr1.use_count() << endl;
	//通过拷贝构造函数和移动构造函数初始化
	shared_ptr<int> sharedPtr2 = move(sharedPtr1);
	cout << "sharedPtr1 use count: " << sharedPtr1.use_count() << endl;
	cout << "sharedPtr2 use count: " << sharedPtr2.use_count() << endl;
	shared_ptr<int> sharedPtr3 = sharedPtr2;
	cout << "sharedPtr2 use count: " << sharedPtr2.use_count() << endl;
	cout << "sharedPtr3 use count: " << sharedPtr3.use_count() << endl;
	//通过std::make_shared初始化
	shared_ptr<int> sharedPtr4 = std::make_shared<int>(8);
	shared_ptr<C11Ptr> sharedPtr5 = std::make_shared<C11Ptr>(8);
	shared_ptr<C11Ptr> sharedPtr6 = std::make_shared<C11Ptr>("hello,world");
	//通过reset方法初始化
	sharedPtr6.reset();
	cout << "sharedPtr6 use count: " << sharedPtr6.use_count() << endl;
	sharedPtr5.reset(new C11Ptr("111"));
	cout << "sharedPtr5 use count: " << sharedPtr5.use_count() << endl;

    //获取原始指针
	C11Ptr* c11ptr = sharedPtr5.get();
	c11ptr->setValue(1000);
	c11ptr->print();

	//通过智能指针对象直接操作
	sharedPtr5->setValue(2000);
	sharedPtr5->print();

	shared_ptr<C11Ptr> sharedPtr7(new C11Ptr(100),[](C11Ptr*t){
		//释放内存操作
		cout << "----------------------" << endl;
		delete t;
	});
	sharedPtr7.reset();

	shared_ptr<C11Ptr> sharedPtr8(new C11Ptr[5], [](C11Ptr*t) {
		//释放内存操作
		cout << "----------------------" << endl;
		delete [] t;
	});
	sharedPtr8.reset();

	//使用C++11提供的默认删除器模板函数std::default_delete<T>
	shared_ptr<C11Ptr> sharedPtr9(new C11Ptr[5], std::default_delete<C11Ptr[]>());
	sharedPtr9.reset();

	//通过构造函数初始化
	unique_ptr<int> uniquePtr(new int(9));
	//通过移动构造函数初始化
	unique_ptr<int> uniquePtr1 = move(uniquePtr);
	//通过reset初始化
	uniquePtr1.reset();
	uniquePtr1.reset(new int(10));
	//获取原始指针
	unique_ptr<C11Ptr> uniquePtr2(new C11Ptr());
	C11Ptr* uniquePtr3 = uniquePtr2.get();
	uniquePtr3->setValue(2);
	uniquePtr3->print();
	//指定删除器
	using ptrFunc = void(*)(C11Ptr*);
	unique_ptr<C11Ptr,ptrFunc>uniquePtr4(new C11Ptr("hello"), [](C11Ptr*t) { delete t; });
	unique_ptr<C11Ptr, function<void(C11Ptr*)>>uniquePtr5(new C11Ptr("hello"), [=](C11Ptr*t) { delete t; });
	
	//独占的智能指针可以管理数据类型的地址,能够自动释放，不需要指定删除器
	unique_ptr<C11Ptr[]>uniquePtr6(new C11Ptr[3]);
	//在c++11中shared_ptr不支持下面的写法，c++11以后才支持的
	shared_ptr<C11Ptr[]>uniquePtr7(new C11Ptr[3]);
	
	//弱引用智能指针
	shared_ptr<int> sp(new int);
	weak_ptr<int> wp1;
	weak_ptr<int> wp2(wp1);
	weak_ptr<int> wp3(sp);
	weak_ptr<int> wp4;
	wp4 = sp;
	weak_ptr<int> wp5;
	wp5 = wp3;

	//共享智能指针注意事项
	//1)不能使用一个原始地址初始化多个共享智能指针
	SharedPtr* sharedPtrTest = new SharedPtr;
	shared_ptr<SharedPtr> sharedPtrTest1(sharedPtrTest);
	shared_ptr<SharedPtr> sharedPtrTest2 = sharedPtrTest1;

	//2)函数不能返回管理了this的共享智能指针对象
	//通过继承类模板std::enable_shared_from_this<T>解决
	shared_ptr<SharedPtr> sharedPtrTest3(new SharedPtr);
	cout << "use count:" << sharedPtrTest3.use_count() << endl;
	shared_ptr<SharedPtr> sharedPtrTest4 = sharedPtrTest3->getSharedPtr();
	cout << "use count:" << sharedPtrTest4.use_count() << endl;
	
	//3)循环引用
	testSharedPtr();

    /*
	特性:23 POD(普通旧数据)类型，POD在C++中是非常重要的一个概念，通常用于说明一个类型的
	属性，尤其是用户自定义的类型的属性。
	在C++11中将POD划分为两个基本概念的合集，即平凡的(trivial)和标准布局的(standard layout)
	"平凡"类型满足以下要求：
	  1）拥有平凡的默认构造函数(trivial construct)和析构函数(trival destruct);
	  2) 拥有平凡的拷贝构造函数和移动构造函数。
	  3) 拥有平凡的拷贝赋值运算符和移动赋值运算符。
	  4) 不包含虚函数及虚基类。
	"标准布局"类型满足以下要求：
	  1)所有非静态成员有相同的访问权限(public,private,protected)
	  2)在类或者结构体继承时,满足以下两种情况之一
	    派生类中有非静态成员，基类中包含静态成员(或者基类没有变量)
		派生类中没有非静态成员,基类有非静态成员
	  3)子类中第一个非静态成员的类型与基类不同。
	  4)没有虚函数和虚基类
	  5)所有非静态数据成员均符合标准布局类型，其基类也符合标准布局，这是一个递归定义。
	  对"平凡"类型判断
	  c++11提供的类模板is_trivial 其语法如下：
	   template <class T>struct std::is_trivial;
	  对"标准布局"类型判断
	  c++11提供的类模板is_standard_layout 其语法如下：
	  template <class T>struct std::is_standard_layout;
	 好处：
	     1)字节赋值，代码中我们可以安全地使用memset和memcpy对pod类型进行初始化和拷贝操作
		 2）提供C内存布局兼容，C++程序可以与C函数进行互相操作，因为POD类型的数据在C与C++
		 之间的操作是安全的。
		 3）保证静态初始化的安全有效，静态初始化在很多时候能够提供程序的性能，而POD类型的对象
		 初始化往往更加简单。
	*/
	cout << "SharedPtr is  trivial type? " << std::is_trivial<SharedPtr>::value << endl;
	cout << "SharedPtr is_standard_layout type? " << std::is_standard_layout<SharedPtr>::value << endl;
	
   /*
   特性:24 默认函数控制(=default 与 =delete)
   1.类与默认函数
   在c++中声明自定义的类，编译器会默认帮助程序员生成一些他们未定义的成员函数，这样的函数版本
   被称为"默认函数",默认函数有以下六类：
    1)无参数构造函数:创建类对象
	2)拷贝构造函数:拷贝类对象
	3)移动构造函数:拷贝类对象
	4)拷贝赋值函数:类对象赋值
	5)移动赋值函数:类对象赋值
	6)析构函数:销毁类对象
	在c++11中以上六大函数才可以使用=default修饰。
	注意事项：
	   如果程序对C++类提供的默认函数（上面提到的六大函数）进行了实现，那么可以通过=default将
	   他们再次指定为默认函数，不能使用=default修饰六大函数以外的函数。
   =delete:禁止使用默认生成的函数
       =delete可以修饰六大函数以外的函数 
   */

  /*
  特性:25 扩展的friend语法
  1.语法改进
  在c++11标准中对friend关键字进行了一些改进，以保证更加好用：
   声明一个类为另一个类的友元时，不在需要使用class关键字，并且还可以使用类的别名
   (使用typedef或者using定义)
  2.为类模板声明友元
  */
	Tom tom;
	tom.print();

	Rectangle<Verify> rect(100, 100);
	Circle<Verify> circle(90);
	Verify verify(100, 200, rect);
	Verify verify1(50, circle);

	/*
	特性:26 强类型枚举
	    1)强作用域:强类型枚举成员的名称不会被输出到其父作用域的空间
		2)转换限制:强类型枚举成员的值不可以与整型隐式的转换。
		3)可以指定底层类型:强类型枚举默认的底层类型为int，但可以显示地指定底层类型，具体方法
		为在枚举名称后面加上:type，其中type可以是除了wchar_t以外的任何类型。
	对原有枚举的扩展：
	   1)原有的枚举类型的底层类型在默认情况下，仍然由编译器指定实现，但也可以跟强类型枚举一样
	   显示地由程序员来指定，其指定方式跟强类型枚举一样,都是枚举类型名后面加上:type,其中type
	   可以是除了wchar_t以外的任何类型
	   2)关于作用域，在C++11中，枚举成员的名字除了会自动输出到父作用域，也可以在枚举类型定义
	   的作用域内有效。
	*/
	cout << "red: " << (char)Red << endl;
	cout << "red: " << (char)TestColor::Red << endl;
	cout << "color size: " << sizeof(TestColor) << endl;
	cout << "red: "<<static_cast<int>(Color::Red)<<endl;
	int enumColor = (int)(Color::Red);
	cout << "color size: " << sizeof(Color) << endl;
	cout << "color1 size: " << sizeof(Color1) << endl;
	EnumTest::print();

	/*
	特性:27 非受限联合体
	1.什么是非受限联合体
	  在c++11之前我们使用的联合体是由局限的，主要有以下三点：
	    1)不允许联合体拥有非pod类型成员
		2)不允许联合体拥有静态成员
		3)不允许联合体拥有引用类型成员
	在新的c++11标准中取消了关于联合体对于数据成员类型的限定，规定任务非引用类型都可以成为
	联合体的数据成员。
	2.placement new
	  一般情况下，使用new申请空间时,是从系统的堆中分配空间,申请所得的空间的位置是根据当时
	  内存的实际使用情况决定的，但是，在某些特殊情况下，可能需要在已分配的特定内存创建对象
	  这种操作就叫做placement new即定位放置new
	  定位放置new 操作的语法形式不同于普通new操作：
	    使用new申请内存空间:Base*ptr = new Base;
		使用定位放置new申请内存空间语法：
		  ClassName* ptr = new(定位内存地址)ClassName;
	  注意事项:
	     1)使用定位放置new操作，既可以在栈上生成对象，也可以在堆上生成对象，这取决于定位时
		 指定的内存地址在堆上还是栈上。
		 2)从表面上，定位放置new操作是申请空间，其本质是利用已经申请好的空间，真正的申请
		 空间的工作是在此之前完成的。
		 3)使用定位放置new创建对象时会自动调用对应类的构造函数，但由于对象的空间不会自动释放
		 如果需要释放堆内存需要显示的调用类的析构函数
		 4)使用定位放置new操作骂我们反复动态申请到同一块堆内存，这样可以避免内存的重复创建和
		 销毁，从而提高程序的执行效率(比如网络通信中数据的接收和发送)
	3.匿名非受限联合体
	*/
	UnionTest unionTest;
	unionTest.num1 = 100;
	cout << "static num value:" << unionTest.num << endl;
	cout << "num1 value:" << unionTest.num1 << endl;

	UnionTest unionTest1;
	unionTest1.num = 50;
	unionTest1.print();
	UnionTest::print();
	cout << "static num value:" << unionTest1.num << endl;
	cout << "static num value:" << unionTest.num << endl;

	Student s;
	s.name = "I am student";
	s.t.setText("I am haizeiwang");
	cout << "s.name= " << s.name << endl;
	PersonInfo student(9727);
	PersonInfo local("622820198312341054");
	PersonInfo foreign("japan", "13198603451");
	student.print();
	local.print();
	foreign.print();

	/*
	特性:28 处理日期和时间的chrono库
	chrono库主要包含三种类型的类:时间间隔duration 时钟类clocks 时间点 time point
	1.时间间隔duration
	  duration表示一段时间间隔
	  注意事项:duration的加减法运算有一定的规则，当两个duration始终周期不相同的时候
	  会先统一成一种时钟，然后再进行算术运算，统一的规则如下：
	   假设有ratio<x1,y1>和ratio<x2,y2>两个时钟周期，首先需要求出x1,x2的最大公约数X，
	   然后求出y1和y2的最小公倍数Y，统一之后的时间周期ratio<X,Y>
    2.时间点time_point
	3.时钟clocks
	  1)system_clock:系统时钟,系统时钟可以修改，甚至可以网络对时，因此使用系统时间计算
	  时间整可能不准;
	  2)steady_clock:是固定时钟,相当于秒表，开始计时后，时间只会增长并且不能修改,适用于
	  计算程序耗时;
	  3)high_resolution_clock:和steady_clock是等价的(是它的别名);
	4.转换函数
	  1)duration_cast
	    隐士转换规则:
		 1.如果对时钟周期进行转换,原时钟周期必须能整除目的时钟周期(比如小时到分钟)
		 2.如果是对的时钟周期次数的类型进行转换:低等类型默认可以向高等类型转换(int向double)
		 3.如果时钟周期和时钟周期次数类型都变了，根据第二点进行推导（也就是看时间周期次数类型）
		 4.以上条件都不满足，那么就需要使用duration_cast进行显示转换了。
	  2)time_point_cast
	    作用:对时间点进行转换，因为不同的时间点对象内部的时钟周期period，和周期次数的类型Rep可
		能也是不同的，一般情况下可以进行隐士类型转换。
		duration_cast 用于转换 std::chrono::duration（时间间隔）。
		time_point_cast 内部使用 duration_cast 转换时间点的 time_since_epoch()。
	*/
	printChrono();
	systemClockTest();
	steadyClock();
	durationCastTest();
	timePointTest();

	/*
	特性:30 命名空间-this_thread
	1.get_id():得到当前线程的线程id
	2.sleep_for():阻塞线程一段时间
	3.sleep_util():阻塞线程到某个时间点
	4.yield():主动放弃cpu资源,但是这个变为就绪态的线程马上会参与到下一轮cpu的抢夺战
	中，不排除它能够继续cpu时间片的情况，这个是概率问题。
	线程被创建后有5种状态:创建态、就绪态、运行态、阻塞态(挂起态)、退出态(终止态)
	*/

	/*
	特性:31 C++线程的使用
	c++11中提供的线程类为std::thread
	2.公共成员函数
	 1)get_id() 获取线程id
	 2)join()   阻塞调用线程
	 3)detach() 线程分离函数,主线程不需要负责子线程的资源释放
	   注意事项:线程函数detach()不会阻塞线程，子线程和主线程分离之后,在主线程中就不能
	   再对这个子线程做任何控制了，比如:通过join()阻塞主线程等待子线程中的任务执行完毕
	   或者调用get_id()获取子线程的线程id
	4)joinable() 用于判断主线程和子线程是否有关联（子线程必须有任务函数）
	  返回true:主线程和子线程之间有关联关系
	  返回false:主线程和子线程之间无关联关系
    3.静态函数
	  hardware_concurrency() 返回电脑cpu核心数
	4.C线程库
	*/
	threadTest();

	/*
	特性:32 线程函数 std::call_once()
	保证函数在多线程环境下只能被调用一次，使用call_once()时候需要一个once_flag
	作为传入参数
	*/
	thread sigle1(MySigleTest, "lufei");
	thread sigle2(MySigleTest, "aisi");
	thread sigle3(MySigleTest, "sabo");
	thread sigle4(MySigleTest, "yiming");
	sigle1.join();
	sigle2.join();
	sigle3.join();
	sigle4.join();

	/*
	特性:33 C++线程同步之互斥锁
	互斥锁使用注意事项：
	  1)内存可能涉及多个线程的同时访问，此时需要通过互斥锁对其进行保护。
	  2)使用互斥锁锁住的是和共享数据相关的一个代码块
	  3)在程序中一个共享数据对应多个代码块，在锁这些代码块的时候要用同一把锁，
	  并且程序运行期间不能销毁这把互斥锁。
	在C++11中提供了四种互斥锁:（使用互斥锁时需要知道，互斥锁需要保护的临界资源是什么）
	1.std:mutex:独占互斥锁，不能递归使用
	  1.1成员函数
	     lock():用于函数临界区加锁，并且只有一个线程获得锁的所有权
		 try_lock():用于函数临界区尝试加锁
		 unlock():用于函数临界区解锁，释放锁的所有权
		 lock()和try_lock()的区别在于，try_lock()不会阻塞线程，lock()会阻塞线程
		  1)如果互斥锁是未锁定状态，得到了互斥锁所有权加锁成功，返回true
		  2)如果互斥锁是锁定状态，无法得到互斥锁所有权加锁失败，返回false
	std::timed_mutex:带超时的独占互斥锁，不能递归使用
	     额外成员函数
		   1)try_lock_for 函数是当线程获取不到互斥锁资源的时候，让线程阻塞的一定的时间长度
		   2)try_lock_until函数是当线程获取不到互斥锁资源的时候，让线程阻塞到某一个指定的时间点
	std::recursive_mutex:递归互斥锁，不带超时功能
	     允许一个线程多次获得互斥锁所有权，递归互斥锁可以解决死锁问题
	std::recursive_timed_mutex:带超时的递归互斥锁
	2.std::lock_guard
	  lock_guard是c++11新增的一个类模版，使用这个类，可以简化互斥锁lock()和unlock()
	  写法，同时更安全。
	*/
	mutexTest();
	/*
	特性:34 C++线程同步之条件变量,c++11中提供以下两种条件变量
	condition_variable:需要配合std::unique_lock<std::mutex>进行wait操作，也就是阻塞
	线程的操作
	condition_variable_any:可以任意带有lock()、unlock()语义的mutex搭配使用，也就是说
	有四种：
	     std::mutex:独占非递归互斥锁
		 std::timed_mutex:带超时独占非递归互斥锁
		 std::recursive_mutex:递归互斥锁
		 std::recursive_timed_mutex:带超时的递归互斥锁
	*/
	testProducerConsumer();

	/*
	特性:35 原子变量
	原子指的是一些列不可被cpu上下文交换的机器指令，这些指令组合在一起就形成了原子
	操作，在多核cpu下，当某个cpu核心开始运行原子操作时，会先暂停其他cpu内核对内存
	的操作，以保证原子操作不会被其他cpu内核所干扰
	C++11中提供了原子类型std::atomic<T>,支持修改、读取等操作，还具备较高的并发性。
	原子变量不支持浮点类型和复合类型作为模板参数。
	内存顺序约束:
	    memory_order_relaxed:这是最宽松的规则，它的编译器和cpu不做任何限制，可以乱序
		memory_order_release:释放，设定内存屏障，保证它之前的操作永远在它之前，但是
		它后面的操作可能被重排到它前面
		memory_order_acquire:获取，设定内存屏障，保证它之后的访问永远在它之后，但是它
		之前的操作却有可能被重排到它后面，往往和Release在不同线程中联合使用
		memory_order_consume:改进版本的memory_order_acquire，开销更小
		memory_order_acq_rel:它和Acquire和Release结合,同时拥有它们两提供的保证。比如你要
		对atomic自增1，同时希望该操作之前和之后的读取和写入操作不会被重排。
		memory_order_seq_cst:顺序一致性，memory_order_seq_cst就像是memory_order_acq_rel的
		加强版，它不管原子操作时读取还是写入的操作，只要某个线程有用到memory_order_seq_cst
		的原子操作，线程中读memory_order_seq_cst操作前的数据操作绝对不会被重新排在memory_order_seq_cst
		操作之后，且读memory_order_seq_cst操作后的数据操作绝对不会被重新排在memory_order_seq_cst操作前。
	*/

	testAtomic();
	testCounter();

	/*
	特性:36 线程异步
	1.std::future :获取另一个线程的返回数据
	2.std::promise:是一个协助线程赋值的类，它能够将数据和future对象绑定起来，为了获取
	线程函数中的某个值提供便利。
	  在外部线程中创建的promise对象必须要通过引用的方式传递到子线程，函数中，在实例化
	  子线程对象的时候，如果任务函数的参数是引用类型，那么实参一定要放到std::ref()函数
	  中，表示要传递这个实参的引用到任务函数中。
	3.std::packaged_task:类包装了一个可调用对象包装器对象(可调用对象包装器包装的是可调用
	对象,可调用对象都可以作为函数来使用)，可以对子线程的任务函数进行打包。这个类可以将内部
	包装的函数和future类绑定到一起，以便进行后续的异步调用，它和std::promise有点类似,std::promise
	内部保存一个共享状态的值，而std::packaged_task保存的是一个函数。
	4.std::async:通过这个函数可以直接启动一个子线程并在这个子线程中执行对应的任务函数，
	异步任务执行完成返回的结果也是存储到一个future对象中，当需要获取异步任务执行结果时，只需要
	调用future类中的get()方案即可，如果不关注异步任务的结果，只是简单地等待任务完成的话，
	可以调用future类中的wait()和wait_for()方法。
	  policy:可调用对象执行策略
	  std::launch::async:调用async函数的时候创建新的线程执行任务函数
	  std::launch::deferred:调用async函数时不执行任务函数，直到调用了future的get()或者wait()
	  方法时才去执行任务，这种方式不会创建新的线程。(任务函数在当前线程执行)
	归纳总结：
	  1)使用async()函数，是多线程中最简单的一种方式，不需要自己创建线程对象，并且可以得到
	  子线程函数返回值。
	  2)使用std::promise类，在子线程中可以传出返回值也可以传出其他数据，并且可选择在什么
	  时候将数据从子线程中传递出来，使用起来更加灵活
	  3)使用std::packaged_task类，可以将子线程的任务函数进行打包，并且得到子线程的返回值。
	*/
	
	promise<string> pro;
	//thread promiseThread(promiseFunc, ref(pro));
	thread promiseThread([](promise<string>&p){
		this_thread::sleep_for(chrono::seconds(3));
		p.set_value("I am lucy,be haizewang11....");
		this_thread::sleep_for(chrono::seconds(1));
	},ref(pro));
	future<string> future = pro.get_future();
	string futureStr = future.get();
	cout << "son thread data:" << futureStr << endl;
	promiseThread.join();

	testpackaged_task();

	testAsync();

	getchar();
}