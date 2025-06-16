#pragma once
#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;
struct AtomicBase {
	AtomicBase(int n, string s):age(n),name(s){

	}
	int age;
	string name;
};
void testAtomic() {
	atomic<char> c('a');
	atomic_char  cc('b');
	atomic<int> b;
	atomic_init(&b, 9);
	b = 12;
	cc = 'd';
	b.store(88);
	auto ccc = c.exchange('e');

	AtomicBase base(123, "test");
	atomic<AtomicBase*> atc_base(&base);

	cout << "c value:" << c << endl;
	cout << "ccc value: " << ccc << endl;
	cout << "b value: " << b << endl;
	AtomicBase* tmp = atc_base.load();
	cout << "name: " << tmp->name << ",age:" << tmp->age << endl;
}

class Counter {
public:
	void increment() {
		for (int i = 0; i < 100; ++i) {
			//mtx.lock();
			number++;
			cout << "++ increment thread_id: " << this_thread::get_id()
				<< ",number: " << number << endl;
			//mtx.unlock();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	void increment1() {
		for (int i = 0; i < 100; ++i) {
			//mtx.lock();
			number++;
			cout << "++ increment1 thread_id: " << this_thread::get_id()
				<< ",number: " << number << endl;
			//mtx.unlock();
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	}
private:
	atomic_int number=0;
	//int number=0;
	//mutex mtx;
};
void testCounter() {
	Counter c;
	thread t1(&Counter::increment, &c);
	thread t2(&Counter::increment1, &c);
	t1.join();
	t2.join();
}
