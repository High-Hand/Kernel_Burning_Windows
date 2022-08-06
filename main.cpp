// Use C++11

#include <iostream>
#include <thread>
#include <ctime>
#include <windows.h>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::thread;
using std::time;
using std::time_t;


int FUN(time_t end_time) {
	/*
	
	Just add from INT_MIN to INT_MAX.

	*/

	int tmp = INT_MIN;
	while (time(nullptr) <= end_time) {
		if (tmp >= INT_MAX) {
			tmp = INT_MIN;
		}
		else
		{
			++tmp;
		}
	}
	return 0;
}

int main() {
	/*

	threads:   how many numbers of threads should be used in this application.
	duration:  how long this application should keep.
	specific:  specific id of kernel (vector).
	
	*/

	char choise = '0';
	unsigned int threads;
	unsigned int duration;
	std::vector<unsigned int> specific{};

	// check.
	cout << "Use all kernel?(y/Y)" << endl;
	cin >> choise;
	if (choise == 'y'|| choise == 'Y')
	{
		threads = thread::hardware_concurrency();
		for (unsigned int i = 0; i < threads; i++)
		{
			specific.push_back(i);
		}
	}
	else
	{
		// validation.
		cout << endl << "OK, your decision:" << endl;
		cout << "The number of threads:" << endl;
		std::cin >> threads;
		if (threads <= 1 || threads >= thread::hardware_concurrency()) {
			threads = 4;
			cout << endl
				<< "The number of threads should be more than 1 but less than "
				<< thread::hardware_concurrency() << endl
				<< "Now, using 4 threads" << endl << endl;
		}

		cout << "The specific id of kernel:" << endl;
		unsigned int tmp = 0, idx = 0;
		while (idx < threads)
		{
			cin >> tmp;
			if (tmp < 0 || tmp >= thread::hardware_concurrency()) {
				cout << endl
					<< "The specific id of kernel should between 0 and "
					<< thread::hardware_concurrency() - 1 << endl
					<< "Try again:" << endl << endl;
			}
			else
			{
				specific.push_back(tmp);
				idx++;
			}
		}

	}

	cout << endl << "The number of duration:" << endl;
	std::cin >> duration;
	if (duration <= 1 || duration >= 24 * 60 * 60) {
		duration = 60;
		cout << endl
			<< "The number of duration should be more than 1 second but less than 1 day" << endl
			<< "Now, using 60 seconds" << endl << endl;
	}

	// show result.
	cout << endl
		<< "Threads:\t" << threads << " / " << thread::hardware_concurrency() << endl
		<< "id:\t\t";
	for (auto item : specific)
	{
		cout << item << " ";
	}
	cout << endl << "Duration:\t" << duration << "  s" << endl << endl;

	// start tasks with threads.
	for (auto item : specific) {
		auto t = thread(FUN, time(nullptr) + duration);
		SetThreadAffinityMask(t.native_handle(), 1 << (item));
		t.detach();
		cout << "Start thread at kernel:\t" << item << endl;
	}

	// hold the application.
	cout << endl << "Burnning..." << endl;
	Sleep(duration * 1000);
	cout << endl << "Stoped!" << endl;

	return 0;
}
