#include <iostream>
struct sample {
	~sample()
	{
		std::cout << __FUNCTION__ "\n";

	}
};


void f() noexcept
{
	sample x;
	try {
		throw 123;//int 型のデータを投入
	}
	catch (int i) {
		std::cerr << "例外が投入されました。値は " << i << "です。\n";
	}
}
void a() noexcept
{
	sample x;
	f();
}
void b() noexcept
{
	sample x;
	a();
}
void c()
{
	sample x;
	b();
}
int main()
{
	int x;
	try {
		c();
	}
	catch (int i) {
		x = i;
	}
}
