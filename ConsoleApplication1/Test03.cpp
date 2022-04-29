#include <iostream>
#include <sstream>
#include <map>


class host_address {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;

public:
	friend std::ostream& operator<<(std::ostream& ostm, const host_address& r)
	{
		return ostm
			<< static_cast<short>(r.a) << '.'
			<< static_cast<short>(r.b) << '.'
			<< static_cast<short>(r.c) << '.'
			<< static_cast<short>(r.d);
	}
	//コンストラクタ
	host_address
	( unsigned char a
	, unsigned char b
	, unsigned char c
	, unsigned char d
	) noexcept
		: /*unsigned char a;*/a{a}
		, /*unsigned char b;*/b{b}
		, /*unsigned char c;*/c{c}
		, /*unsigned char d;*/d{d}
	{
		//
	}
	//デフォルトコンストラクタ
	host_address() noexcept
		: host_address
			{ /*unsigned char a*/0
			, /*unsigned char b*/0
			, /*unsigned char c*/0
			, /*unsigned char d*/0
			}
	{
	}
	//コピーコンストラクタ
	host_address(const host_address& r) noexcept
		: host_address
			{ /*unsigned char a*/r.a
			, /*unsigned char b*/r.b
			, /*unsigned char c*/r.c
			, /*unsigned char d*/r.d
			}
	{
	}
	//代入演算子
	host_address& operator=(const host_address& r) noexcept
	{
		a = /*unsigned char a*/r.a;
		b = /*unsigned char b*/r.b;
		c = /*unsigned char c*/r.c;
		d = /*unsigned char d*/r.d;
		return *this;
	}

};

int main(void)
{
	std::map<std::string, host_address> host_ip;
	
	host_ip["host1"] = { 101, 102, 103, 104 };
	host_ip["host2"] = { 105, 106, 107, 108 };
	host_ip["host3"] = { 109, 110, 111, 112 };
	
	std::map<std::string, host_address>::iterator it;

	it = host_ip.begin();
	while (it != host_ip.end())
	{
		std::cout << it->first << ":";
		std::cout << it->second << std::endl;

		++it;
	}


	int x;

	std::cout << "ホスト→IP ... 0 IP→ホスト...1\n";
	std::cin >> x;
	if (x == 0) {
		std::string hostmei;
		std::cout << "ホスト名は？";
		std::cin >> hostmei;

		it = host_ip.find(hostmei);
		if (it == host_ip.end()) {
			std::cout << hostmei << "は該当無し\n";
		}
		else {
			std::cout << hostmei << "は" << it->second << "\n";
		}
	}
	else if (x == 1) {
		std::string ipaddr;
		std::cout << "IPアドレスは？";
		std::cin >> ipaddr;

		;
		for (it = host_ip.begin(); it != host_ip.end(); ++it) {
			if ((std::ostringstream() << it->second).str() == ipaddr) {
				break;
			}
		}
		if (it == host_ip.end()) {
			std::cout << ipaddr << "は該当無し\n";
		}
		else {
			std::cout << ipaddr << "は" << it->first << "\n";
		}

	}
	return 0;
}
