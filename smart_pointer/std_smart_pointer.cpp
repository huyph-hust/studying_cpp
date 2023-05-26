#include <iostream>
#include <memory>


class MyClass
{
public:
	void setValue(int val)
	{
		m_value = val;
	}

	void showValue()
	{
		std::cout << "Value: " << m_value << std::endl;
	}
private:
	int m_value;
};

void fun(std::unique_ptr<int> p)
{
	*p = 10;
}

void fun2(std::shared_ptr<MyClass> p)
{
	p.get()->setValue(10);
}

void fun3(std::weak_ptr<MyClass> p)
{
	p.lock()->setValue(100);
}

int main()
{
	std::unique_ptr<int> uniquePtr;
	// fun(uniquePtr); // Error

	std::shared_ptr<MyClass> sharedPtr = std::make_shared<MyClass>();
	sharedPtr = std::make_shared<MyClass>();
	// fun2(sharedPtr);
	// sharedPtr.get()->showValue();
	std::shared_ptr<MyClass> sharedPtr3 = sharedPtr;
	std::cout << "Count: " << sharedPtr.use_count() << std::endl;

	std::weak_ptr<MyClass> weakPtr;
	{
		std::shared_ptr<MyClass> sharedPtr2 = std::make_shared<MyClass>();
		weakPtr = sharedPtr2;
		fun3(weakPtr);
		weakPtr.lock()->showValue();
	}
	if (weakPtr.expired())
        std::cout << "sharedPtr2 is not there\n";

	return 0;
}
