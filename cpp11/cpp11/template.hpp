#include <iostream>
#include <string>
#include <map>
using namespace std;
template <typename T>
class Container {
public:
	void print(T&t) {
		auto it = t.begin();
		for (; it != t.end(); ++it)
		{
			cout << it->first << ", " << it->second << endl;
		}
	}
};

template<typename T=int>
void func(T t) {
	cout << " current value: " << t << endl;
}

template<typename T = long, typename U = int>
void mytest(T t = 'A', U u = 'B') {
	cout << "t: " << t <<" ,u:"<<u<<endl;
}