#include <iostream>
#include <memory>

using namespace std;

/* Do not intermingle raw pointer and shared_ptr while handling a dynamic storage.*/
int main()
{
	int *mem = new int(786);

	{
		shared_ptr<int> sec = make_shared(mem);

	} // storage deleted

	// mem left as a dangling pointer

	return 0;
}

/* Assigning raw pointer to two different shared_ptr. */
void fun()
{
	int *i = new int(90);

	shared_ptr<int> sp = static_cast<shared_ptr<int>>(i); // sp points to i

	{
		shared_ptr<int> sp1 = static_cast<shared_ptr<int>>(i); // sp1 points to i
	}

	cout << *sp; // undefined
}

/* Circular reference */
// Refer: circular_reference.cpp

/* Involving shared_ptr with a class data member whose object is dynamically allocated */
class Database
{
public:
	string name;
	int age;

	Database(string nam ="", int ag = 0) : name(nam), age(ag) {}

	~Database() {}
};

int main()
{
	Database *dat = new Database("Happy", 5);

	{
		shared_ptr<string> new_name = shared_ptr<string>(&(dat->name)); // new_name points to dat storage
		*new_name = "Sad";
	}

	delete dat; // error!

	return 0;
}