#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1, m2;
int a = 0;

void thread1Hanlder(void)
{
	m1.lock();
	m2.lock();
	a++;
	m1.unlock();
	m2.unlock();
}

void thread2Hanlder(void)
{
	m2.lock();
	m1.lock();
	a++;
	m2.unlock();
	m1.unlock();
}

int main(void)
{
	std::cout << "Main program ...\n";

	std::thread t1(thread1Hanlder);
	std::thread t2(thread2Hanlder);

	t1.join();
	t2.join();
	std::cout << "Main program Exit ...\n";


	return 0;
}