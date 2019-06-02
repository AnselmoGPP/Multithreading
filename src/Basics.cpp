
// Select which type of socket implementation you want to test by uncommenting the corresponding function call in main().

/*
	Notes:
		Once you've started a thread, you need to explicitly decide whether to wait for it to finish (join()) or leave it to
		run on its own (detach()). If you don't decide before the std::thread object is destroyed, your program is terminated
		(std::thread destructor calls std::terminate()).
*/

//#include "pch.h"
#include <iostream>
#include <thread>

// ------------------------------------

void second_thread() {
	for (int i = 0; i < 1000; i++) std::cout << 'X';
}

class callable_type {
public:
	void operator() () const {
		for (int i = 0; i < 1000; i++) std::cout << 'X';
	}
};

class thread_guard {

	std::thread & myThread;
public:
	explicit thread_guard(std::thread & thr) : myThread(thr) { };
	~thread_guard() {
		if (myThread.joinable()) myThread.join();
	}

	thread_guard(thread_guard const &) = delete;
	thread_guard & operator=(thread_guard const &) = delete;
};

// ------------------------------------

class myClass {
	std::thread thr_obj;
	void thr_function() {
		for (int i = 0; i < 100; i++) std::cout << 'X';
	}
public:
	myClass() {
		thr_obj = std::thread(&myClass::thr_function, this);
		for (int i = 0; i < 100; i++) std::cout << '-';
		thr_obj.join();
	}
};

void thread_from_a_function__join() {
	std::thread my_thread(second_thread);
	for (int i = 0; i < 1000; i++) std::cout << '-';
	std::cout << my_thread.joinable();	// True if thread object is joinable. False if it is not.
	my_thread.join();					// Once a thread object calls join(), it cannot call join() again. joinable() = false;
	std::cout << my_thread.joinable();
}

void thread_from_a_function__detach() {
	std::thread my_thread(second_thread);
	for (int i = 0; i < 5; i++) std::cout << '-';
	my_thread.detach();
}

void thread_from_a_callable_type_object() {
	callable_type obj;
	std::thread my_thread(obj);
	for (int i = 0; i < 1000; i++) std::cout << '-';
	my_thread.join();
}

void thread_from_a_callable_type_declaration() {
	std::thread my_thread((callable_type()));
	for (int i = 0; i < 1000; i++) std::cout << '-';
	my_thread.join();
}

void thread_from_a_lambda_expression() {
	std::thread my_thread([] { for (int i = 0; i < 1000; i++) std::cout << 'X';	} );
	for (int i = 0; i < 1000; i++) std::cout << '-';
	my_thread.join();
}

void waiting_but_an_exception_occurs_Exception() {
	callable_type obj;
	std::thread myThread(obj);

	try { 
		for (int i = 0; i < 1000; i++) std::cout << '-'; 
	}
	catch (...) { 
		myThread.join(); 
		throw;
	}

	myThread.join();
}

void waiting_but_an_exception_occurs_RAII() {

	callable_type obj;
	std::thread myThread(obj);
	thread_guard tg(myThread);
	for (int i = 0; i < 1000; i++) std::cout << '-';
}

void detach_thread_to_handle_other_docs() {
	
	char letter;
	
	if (std::cin >> letter) {
		std::thread thr(detach_thread_to_handle_other_docs);
		thr.detach();
		for (int i = 0; i < 10; i++) {
			std::cout << letter << " ";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	std::this_thread::sleep_for(std::chrono::seconds(60));
}

// ------------------------------------

int main() {

	std::cout << "Multithreading testing" << std::endl;

// Basic thread management -----
	//myClass obj;
	thread_from_a_function__join();
	//thread_from_a_function__detach();
	//thread_from_a_callable_type_object();
	//thread_from_a_callable_type_declaration();
	//thread_from_a_lambda_expression();
	//waiting_but_an_exception_occurs_Exception();
	//waiting_but_an_exception_occurs_RAII();
	//detach_thread_to_handle_other_docs();

// Passing arguments -----


}


