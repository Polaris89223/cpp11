#pragma once
#include <iostream>
#include <chrono> 
using namespace std;
using namespace chrono;
void printChrono() {
	//hour
	duration<int, ratio<3600>>hour(1);
	chrono::hours h(1);
	//min
	duration<int, ratio<60>>min(1);
	chrono::minutes m(1);
	//sec
	duration<int, ratio<1>>sec(1);
	chrono::seconds s(1);
	duration<double> sec1(2.5);
	//msec
	duration<int, ratio<1,1000>>msec(1);
	chrono::milliseconds msec1(1);
	//micro
	duration<int, ratio<1, 1000000>>micro(1);
	chrono::microseconds micro1(1);
	//nsec
	duration<int, ratio<1, 1000000000>>nsec(1);
	chrono::nanoseconds nsec1(5);

	cout << "sec1 count:" << sec1.count() << endl;
	cout << "nsec1 count:" << nsec1.count() << endl;

	chrono::minutes minutes1(9);
	chrono::minutes minutes2(8);
	minutes1++;
	minutes2--;
	chrono::minutes diff = minutes1 - minutes2;
	duration<int, ratio<60, 1>> t1(10);
	duration<int, ratio<1,1>>t2(60);
	chrono::seconds t3 = t1 - t2;

	duration<int, ratio<9, 7>> d1(3);
	duration<int, ratio<6, 5>>d2(1);
	duration<int, ratio<3,35>> d3 = d1 - d2;
	cout << "t3 count:" << t3.count() << endl;
	cout << "d3 count:" << d3.count() << endl;
}

void systemClockTest() {
	//创建时间点对象
	system_clock::time_point epoch;
	chrono::hours h(10 * 24);
	system_clock::time_point epoch1 = epoch + h;
	system_clock::time_point epoch2(epoch + h);

	//当前时间
	system_clock::time_point nowTime = system_clock::now();
	//时间点->时间段(单位秒)
	time_t allSec = system_clock::to_time_t(nowTime);
	cout << "now time: " << ctime(&allSec) << endl;
	system_clock::time_point tp = system_clock::from_time_t(allSec);
}
void steadyClock() {
	auto p1 = steady_clock::now();
	for (size_t i = 0; i < 1000; i++)
	{
		cout << "*";
	}
	cout << endl;
	auto p2 = steady_clock::now();
	auto d1 = p2 - p1;
	cout << "count: " << d1.count() << endl;
	high_resolution_clock::now();
}

void durationCastTest(){
	//分钟->小时
	hours h = duration_cast<hours>(minutes(60));
	//小时->分钟
	minutes m1 = hours(1);

	//浮点->整形
	using myDouble = duration<double>;
	seconds ss =duration_cast<seconds>(myDouble(2.5));
	//整形->浮点
	myDouble dd = seconds(9);

	duration<int, ratio<1, 100>>t1(100);
	duration<double, ratio<1, 1000>>t2(12.56);

	duration<int, ratio<1, 100>>t3 = duration_cast<duration<int, ratio<1, 100>>>(t2);
	duration<double, ratio<1, 1000>>t4 = t1;
}
template<typename Duration>
using MyTimePoint = time_point<system_clock, Duration>;
void timePointTest() {
	//基于秒的时间点
	MyTimePoint<chrono::seconds> mpoint(chrono::seconds(1));
	MyTimePoint<milliseconds> millpoint(milliseconds(1));
	MyTimePoint<milliseconds> ms = mpoint;
	MyTimePoint<chrono::seconds> seconds = time_point_cast<chrono::seconds>(millpoint);
}
