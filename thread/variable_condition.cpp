#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex m;
std::condition_variable cv;

bool thread1Done = false;
bool thread2Done = false;

void Thread1Hanlder(void)
{
	std::cout << "Enter thread 1\n";
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, []{ return thread2Done; });

	thread1Done = true;
	lk.unlock();

	std::cout << "Thread 1 done\n";

	cv.notify_all();
}

void Thread2Hanlder(void)
{
	std::cout << "Enter thread 2\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	m.lock();
	thread2Done = true;
	m.unlock();
	std::cout << "Thread 2 done\n";

	cv.notify_all();
}

int main(void)
{
	std::cout << "Main program ...\n";

	std::thread t1(Thread1Hanlder);
	std::thread t2(Thread2Hanlder);

	{
		std::cout << "Main thread waiting for thread 1\n";
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, []{ return thread1Done; });
	}

	t1.join();
	t2.join();

	std::cout << "Main exit ...\n";

	return 0;
}