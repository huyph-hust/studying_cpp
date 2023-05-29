#include <iostream>
#include <thread>
#include <mutex>

class Bank
{
public:
	Bank()
	: m_balance(0)
	{
	}

	void addMoney(int amount)
	{
		m_MutexBalance.lock();
		m_balance += amount;
		std::cout << "addMoney: " << amount << std::endl;
		m_MutexBalance.unlock();
	}

	void withdraw(int amount)
	{
		std::lock_guard<std::mutex> guard(m_MutexBalance);
		if (m_balance >= amount)
		{
			m_balance -= amount;
			std::cout << "withdraw: " << amount << std::endl;

		}
		else
		{
			std::cout << "Not enough money to withdraw\n";
		}
	}

	void printBalance()
	{
		std::cout << "Balance: " << m_balance << std::endl;
	}

private:
	int m_balance;
	std::mutex m_MutexBalance;
};

int main(void)
{
	std::cout << "Main program ...\n";
	Bank b;
	std::thread t1([&]()
	{
		// std::this_thread::sleep_for(std::chrono::seconds(1));
		b.addMoney(200);
		b.withdraw(100);
	});

	std::thread t2([&]()
	{
		b.withdraw(100);
		b.addMoney(100);
	});

	t1.join();
	t2.join();

	b.printBalance();

	return 0;
}