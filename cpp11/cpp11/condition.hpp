#pragma once
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;
//任务队列
class TaskQueue {
public:
	//添加数据
	void put(int task){
		lock_guard<mutex> locker(m_mutex);
		while (m_maxSize == m_taskQueue.size())
		{
			m_notFull.wait(m_mutex);
		}
		m_taskQueue.push(task);
		cout << "add task: " << task << ",threadID: " << this_thread::get_id() << endl;
		//唤醒消费者线程
		m_notEmpty.notify_one();
	}
	//取数据
	void take() {
		//函数返回false，阻塞线程
		m_mutex.lock();
		m_notEmpty.wait(m_mutex, [=]() {
			return !m_taskQueue.empty();
		});
		int node = m_taskQueue.front();
		m_taskQueue.pop();
		cout << "delete task: " << node << ",threadID: " << this_thread::get_id() << endl;
		m_mutex.unlock();
		//唤醒生产者线程
		m_notFull.notify_all();
	}
	int taskSize() {
		lock_guard<mutex> locker(m_mutex);
		return m_taskQueue.size();
	}
private:
	int m_maxSize =100;
	queue<int> m_taskQueue;
	mutex m_mutex;
	condition_variable_any m_notFull;  //生产者
	condition_variable_any m_notEmpty; //消费者
};

void testProducerConsumer() {
	thread t1[5];
	thread t2[5];

	TaskQueue taskQ;
	for (int i = 0; i < 5; i++)
	{
		t1[i] = thread(&TaskQueue::put, &taskQ,100 + i);
		t2[i] = thread(&TaskQueue::take,&taskQ);
	}
	for (int i = 0; i < 5; i++)
	{
		t1[i].join();
		t2[i].join(); 
	}
}

