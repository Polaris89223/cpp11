#include <iostream>
#include <string>
#include <list>
using namespace std;
template<typename T>
class MyContainer
{
public:
	void print(T&t){
		for (m_it = t.begin(); m_it != t.end(); ++m_it) {
			cout << "Value: " << *m_it << endl;
		}
	}
private:
	decltype(T().begin()) m_it;
};
