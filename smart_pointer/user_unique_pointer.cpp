#include <iostream>

template <class T>
class MyUniquePointer
{
public:
	MyUniquePointer(T *p = NULL) { m_p = p; }
	~MyUniquePointer(void) { if (NULL != m_p) delete m_p; }

	// Delete copy constructor and asignment operator
	MyUniquePointer(const MyUniquePointer&) = delete;
	MyUniquePointer& operator= (const MyUniquePointer&) = delete;

	T& operator*() { return *m_p; }
	T* operator->() { return m_p; }

private:
	T* m_p;
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
	MyUniquePointer<int> p1(new int);
	*p1 = 10;

	// MyUniquePointer<int> p2 = p1;	// Error
	// MyUniquePointer<int> p3(p1);		// Error

	MyUniquePointer<MyClass> p(new MyClass());

	p->setValue(200);
	p->showValue();

	return 0;
}