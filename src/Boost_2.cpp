
// A member function defines the new thread process.
// The mutex controls the access to a variable that is used by both threads.

//#include "pch.h"
#include <iostream>
#include <boost/thread/thread.hpp>

class myClass {

	boost::thread t_obj;
	boost::mutex mut;

	char var;

public:
	myClass() {
		boost::thread t_obj = boost::thread(&myClass::thread_2, this);
		main_thread();
	};
	~myClass() {
		t_obj.join();
		std::cout << "[end B]";
	};

	void main_thread() {
		for (int i = 0; i < 1000; i++) {
			mut.lock();
			var = '-';
			std::cout << var;
			mut.unlock();
		}
		std::cout << "[end A]";
	};
	void thread_2() {
		for (int i = 0; i < 1000; i++) {
			mut.lock();
			var = 'X';
			std::cout << var;
			mut.unlock();
		}
	};
};

int boost_2() {

	myClass obj;

}

