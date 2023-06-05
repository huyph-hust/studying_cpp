#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <functional>

// build command: g++ std_thread.cpp -std=c++11 -pthread; ./a.out

void threadHandler1(int param)
{
	for (int i = 0; i < param; i++)
	{
		std::cout << "threadHandler1: " << i << std::endl;
		// std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


class A
{
public:
	A()
	: m_ExitThread(false),
	m_pThread(nullptr)
	{
	}

	~A()
	{
		stop();

	}

	void run()
	{
		std::cout << "run" << std::endl;
		m_pThread = std::make_unique<std::thread>(std::bind(&A::threadHandler, this));
	}

	void stop()
	{
		m_ExitThread = true;
		if (m_pThread->joinable())
		{
			m_pThread->join();
		}
	}

private:
	void threadHandler(void)
	{
		while (false == m_ExitThread)
		{
			std::cout << "threadHandler" << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		std::cout << "Thread exited \n";
	}

private:
	std::unique_ptr<std::thread> m_pThread;
	bool m_ExitThread;
};

int main(void)
{
	std::cout << "Thread...\n";
	int a = 3;
	// std::thread *pT1 = new std::thread(std::ref(threadHandler1), 34);

	// std::unique_ptr<std::thread> pT2 = std::make_unique<std::thread>(threadHandler1, std::ref(a));
	// std::thread pT1(threadHandler1, 3);
	// pT1->join();

	A ma;
	ma.run();
	std::this_thread::sleep_for(std::chrono::seconds(10));

	return 0;
}