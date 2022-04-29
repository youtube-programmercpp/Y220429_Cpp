#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

struct host_address {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	bool operator==(const host_address& r) const noexcept
	{
		return a == r.a
		&&     b == r.b
		&&     c == r.c
		&&     d == r.d
		;
	}
};
std::ostream& operator<<(std::ostream& ostm, const host_address& r)
{
	return ostm
		<< static_cast<short>(r.a) << '.'
		<< static_cast<short>(r.b) << '.'
		<< static_cast<short>(r.c) << '.'
		<< static_cast<short>(r.d);
}
void mode_0(const std::map<std::string, host_address>& host_ip)
{
	std::string hostmei;
	std::cout << "ホスト名は？";
	std::cin >> hostmei;

	const auto it = host_ip.find(hostmei);
	if (it == host_ip.end())
		std::cout << hostmei << "は該当無し" << "\n";
	else
		std::cout << hostmei << "は" << it->second << "\n";
}
void mode_1(const std::map<std::string, host_address>& host_ip)
{
	std::string ipaddr;
	std::cout << "IPアドレスは？";
	std::cin >> ipaddr;

	const auto it = std::find_if(host_ip.begin(), host_ip.end(), [&ipaddr](const auto& r)
		{
			return (std::ostringstream() << r.second).str() == ipaddr;
		});
	if (it == host_ip.end())
		std::cout << ipaddr << "は該当無し\n";
	else
		std::cout << ipaddr << "は" << it->first << "\n";
}
int main(void)
{
	std::map<std::string, host_address> host_ip;

	host_ip["host1"] = { 101, 102, 103, 104 };
	host_ip["host2"] = { 105, 106, 107, 108 };
	host_ip["host3"] = { 109, 110, 111, 112 };

	for (const auto& r : host_ip)
		std::cout << r.first << ":" << r.second << std::endl;


	std::cout << "ホスト→IP ... 0 IP→ホスト...1\n";
	int x;
	if (std::cin >> x) {

		static void (* const a[])(const std::map<std::string, host_address>&host_ip)
			= 
		{ mode_0
		, mode_1
		}
		;
		if (0 <= x && x <= 1)
			(*a[x])(host_ip);
	}
	return 0;
}
