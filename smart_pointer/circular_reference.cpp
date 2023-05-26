#include <iostream>
#include <memory>

using namespace std;
#if 0
class B;

class A
{
public:
	shared_ptr<B> spB;

	A() {}

	~A() { cout <<"A destructor \n"; }
};

class B
{
public:
	shared_ptr<A> spA;

	B() {}

	~B() { cout << "B destructor \n"; }
};

int main()
{
	shared_ptr<A> a(new A());
	shared_ptr<B> b(new B());

	a->spB = static_cast<shared_ptr<B>>(b); // spB points to b
	b->spA = static_cast<shared_ptr<A>>(a); // spA points to a

	return 0;
}
#else
class B;

class A
{
public:
	weak_ptr<B> spB;

	A() {}

	~A() { cout <<"A destructor \n"; }
};

class B
{
public:
	weak_ptr<A> spA;

	B() {}

	~B() { cout << "B destructor \n"; }
};

int main()
{
	shared_ptr<A> a(new A());
	shared_ptr<B> b(new B());

	a->spB = static_cast<shared_ptr<B>>(b); // spB points to b
	b->spA = static_cast<shared_ptr<A>>(a); // spA points to a

	return 0;
}
#endif