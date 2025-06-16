#pragma once
#include <iostream>
#include <mutex>
#include <thread>
using namespace chrono;
using namespace std;
class MutexBase {
public:
	void increment(int count) {
		for (size_t i = 0; i < count; i++)
		{
			//mutex.lock();
			{
				lock_guard<recursive_mutex>helper(mx);
				//lock_guard<mutex>helper(mx);
				++number;
				cout << "++current number: " << number << endl;
			}
			//mutex.unlock();
			this_thread::sleep_for(chrono::milliseconds(500));
		}
	}
	void decrement(int count) {
		for (size_t i = 0; i < count; i++)
		{
			//mutex.lock();
			{
				lock_guard<recursive_mutex>helper(mx);
				//lock_guard<mutex> helper(mx);
				increment(2);
				--number;
				cout << "--current number: " << number << endl;
			}
			//mutex.unlock();
			this_thread::yield();
		}
	}
	void work() {
		while (true)
		{
			bool ret = tmx.try_lock_for(chrono::milliseconds(100));
			if (ret) {
				count++;
				this_thread::sleep_for(chrono::milliseconds(500));
				cout << "acquire lock,thread ID:" << this_thread::get_id() << endl;
				tmx.unlock();
				break;
			}
			else {
				cout << "not acquire lock,thread ID:" << this_thread::get_id() << endl;
				this_thread::sleep_for(chrono::milliseconds(50));
			}
		}
	}
private:
	int number = 999;
	//mutex mx;
	recursive_mutex mx;
	int count = 0;
	timed_mutex tmx;
};
void mutexTest() {
	MutexBase b;
	thread t1(&MutexBase::increment, &b, 10);
	thread t2(&MutexBase::decrement, &b, 10);
	t1.join();
	t2.join();

	thread t3(&MutexBase::work,&b);
	thread t4(&MutexBase::work,&b);
	t3.join();
	t4.join();
}
