#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>
#include <limits.h>
#include <cstdint>
struct host_address {
	int address;
	static constexpr unsigned short ipv4size = 4;
	static_assert(sizeof address >= ipv4size, "Must be able to store IPv4 address");
	bool operator==(const host_address& r) const noexcept
	{
		return reinterpret_cast<const std::int32_t&>(address) == reinterpret_cast<const std::int32_t&>(r.address);
	}
};
std::ostream& operator<<(std::ostream& ostm, const host_address& r)
{
#define	first reinterpret_cast<const unsigned char*>(&r.address)
	auto p = first;
	ostm << static_cast<short>(*p);
	while (++p < &first[host_address::ipv4size])
		ostm << '.' << static_cast<short>(*p);
#undef	first
	return ostm;
}
std::istream& operator>>(std::istream& istm, host_address& r)
{
	const auto read = [](std::istream& istm, unsigned char* p)->std::istream&
	{
		short value;
		if (istm >> value) {
			if (0 <= value && value <= UCHAR_MAX)
				*p = static_cast<unsigned char>(value);
			else
				istm.setstate(std::ios_base::failbit);
		}
		return istm;
	};
#define	first reinterpret_cast<unsigned char*>(&r.address)
	auto p = first;
	read(istm, p);
	while (++p < &first[host_address::ipv4size]) {
		char ch;
		if (istm >> ch) {
			if (ch == '.')
				read(istm, p);
			else
				istm.setstate(std::ios_base::failbit);
		}
		else
			break;
	}
#undef	first
	return istm;
}
template<int x>struct mode;

template<>struct mode<0> {
	using key_type = std::string;
	static const char prompt[];

	static const host_address* find(const std::map<std::string, host_address>& host_ip, const key_type& key_data)
	{
		const auto it = host_ip.find(key_data);
		if (it == host_ip.end())
			return nullptr;
		else
			return &it->second;
	}
};
template<>struct mode<1> {
	using key_type = host_address;
	static const char prompt[];
	static const std::string* find(const std::map<std::string, host_address>& host_ip, const key_type& key_data)
	{
		const auto it = std::find_if(host_ip.begin(), host_ip.end(), [&key_data](const auto& r)
			{
				return r.second == key_data;
			});
		if (it == host_ip.end())
			return nullptr;
		else
			return &it->first;
	}
};
const char mode<0>::prompt[] = "ホスト名は？";
const char mode<1>::prompt[] = "IPアドレスは？";

template<int x>void mode_x(const std::map<std::string, host_address>& host_ip)
{
	typename mode<x>::key_type key_data;
	std::cout << mode<x>::prompt;
	std::cin >> key_data;

	if (const auto p = mode<x>::find(host_ip, key_data))
		std::cout << key_data << "は" << *p << "\n";
	else
		std::cout << key_data << "は該当無し" << "\n";
}
int main(void)
{
	std::map<std::string, host_address> host_ip;
	std::istringstream("101.102.103.104") >> host_ip["host1"];
	std::istringstream("105.106.107.108") >> host_ip["host2"];
	std::istringstream("109.110.111.112") >> host_ip["host3"];

	for (const auto& r : host_ip)
		std::cout << r.first << ":" << r.second << std::endl;


	std::cout << "ホスト→IP ... 0 IP→ホスト...1\n";
	int x;
	if (std::cin >> x) {

		static void (* const a[])(const std::map<std::string, host_address>&host_ip)
			= 
		{ mode_x<0>
		, mode_x<1>
		}
		;
		if (0 <= x && x <= 1)
			(*a[x])(host_ip);
	}
	return 0;
}
