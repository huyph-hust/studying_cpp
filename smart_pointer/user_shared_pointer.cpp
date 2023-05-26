#include <iostream>

template <class T>
class MySharedPointer
{
public:
	MySharedPointer(T *p = NULL)
	{
		m_p = p;
		m_pRefCounter = new uint16_t;
		*m_pRefCounter = 1;
	}

	~MySharedPointer(void)
	{
		std::cout << "Destructor: " << *m_pRefCounter << std::endl;
		if ((*m_pRefCounter) > 0)
			(*m_pRefCounter)--;

		if (0 == *m_pRefCounter)
		{
			std::cout << "Delete counter\n";
			delete m_pRefCounter;
			if (NULL != m_p)
			{
				std::cout << "Delete pointer\n";
				delete m_p;
			}
		}
	}

	// Delete copy constructor and asignment operator
	MySharedPointer(MySharedPointer &ref)
	{
		m_p = ref.m_p;
		m_pRefCounter = ref.m_pRefCounter;
		(*m_pRefCounter)++;
		std::cout << "Copy constructor: " << *m_pRefCounter << std::endl;
	}
	MySharedPointer &operator=(MySharedPointer &ref)
	{
		m_p = ref.m_p;
		m_pRefCounter = ref.m_pRefCounter;
		(*m_pRefCounter)++;

		std::cout << "Asigment operator: " << *m_pRefCounter << std::endl;
	}

	T &operator*() { return *m_p; }
	T *operator->() { return m_p; }
	T *get() { return m_p; }

public:
	uint16_t getCounter()
	{
		return *m_pRefCounter;
	}
private:
	T* m_p;
	uint16_t* m_pRefCounter;
};

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

int main(void)
{
	int *a = new int;
	MySharedPointer<int> p1(a);
	*p1 = 10;
	MySharedPointer<int> p2 = p1;
	MySharedPointer<int> p3(p1);


	MySharedPointer<MyClass> p(new MyClass());

	p->setValue(200);
	p->showValue();

	return 0;
}