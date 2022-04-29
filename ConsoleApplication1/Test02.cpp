#include <iostream>
struct IpAddress {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;

};
std::ostream& operator<<(std::ostream& ostm, const IpAddress& r)
{
	return ostm
		<< static_cast<short>(r.a) << '.'
		<< static_cast<short>(r.b) << '.'
		<< static_cast<short>(r.c) << '.'
		<< static_cast<short>(r.d);
}
int main()
{
	IpAddress a1{ 101,102,103,104 };
	IpAddress a2{ 105,106,107,108 };

	std::cout << a1 << '\n';
	std::cout << a2 << '\n';
}
