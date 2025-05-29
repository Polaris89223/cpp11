#include <iostream>
#include <string>
#include <map>
using namespace std;
class T1
{
public:
	static int get() {
		return 10;
   }
};

class T2
{
public:
	static string get() {
		return "auto test";
	}
};

template<typename T>
void autoFunc(void) {
	auto ret = T::get();
	cout << "ret: " << ret << endl;
}

template<typename T,typename U>
void autoFunc1(void) {
	U ret = T::get();
	cout << "ret: " << ret << endl;
}