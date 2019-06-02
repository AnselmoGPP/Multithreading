
// A global function defines the new thread process.
// The mutex controls the access to a variable that is used by both threads.

//#include "pch.h"
#include <iostream>
#include <boost/thread/thread.hpp>

void sec_thread();									// Thread process
boost::mutex mut;										// Mutex creation
char var;												// Variable accessed by both threads (access controled with mutex)

int boost_1() {

	//boost::thread t_obj;
	//boost::thread t_obj = boost::thread(sec_thread);	// Thread creation: Use this when you want to create the thread object at some point and start the second thread at another point (second thread starts when object is defined).
	boost::thread t_obj(sec_thread);						// Thread creation (second thread starts immediately)

	for (int i = 0; i < 1000; i++) {
		mut.lock();
		var = '-';
		std::cout << var;
		mut.unlock();
	}
	std::cout << "[end A]";

	t_obj.join();											// Thread end
	std::cout << "[end B]";

	//boost::thread some_thread = boost::thread(&C_client::my_thread, this);	// Thread creation (for member functions)
	//void C_client::my_thread() {				// <<< Thread (local function)
	//	for (;;) Receiver();
	//}
}

void sec_thread() {

	for (int i = 0; i < 1000; i++) { 
		mut.lock();
		var = 'X';
		std::cout << var;
		mut.unlock();
	}
}
