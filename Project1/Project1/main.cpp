#include <iostream>
#include <string>
#include <functional>

using namespace std;

void print1(const string& name, int num1, int num2)
{
	cout << name << endl;
	cout << num1 << endl;
	cout << num2 << endl;
}

int main(void)
{
	auto f = bind(&print1, "Hello", placeholders::_1, placeholders::_2);
	auto f2 = bind(&print1, "Hello", placeholders::_2, placeholders::_1);

	f(1, 2);
	f(1, 2);

	return 0;
}
