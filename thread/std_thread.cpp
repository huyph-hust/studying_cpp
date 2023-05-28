#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

// build command: g++ std_thread.cpp -std=c++11 -pthread; ./a.out

void threadHandler1(int param)
{
	for (int i = 0; i < param; i++)
	{
		std::cout << "threadHandler1: " << i << std::endl;
		// std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main(void)
{
	std::cout << "Thread...\n";
	int a = 3;
	std::thread *pT1 = new std::thread(std::ref(threadHandler1), 34);

	std::unique_ptr<std::thread> pT1 = std::make_unique<std::thread>(threadHandler1, std::ref(a));
	// std::thread pT1(threadHandler1, 3);
	pT1->join();

	return 0;
}