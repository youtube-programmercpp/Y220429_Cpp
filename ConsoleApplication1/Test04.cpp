#include <iostream>
#include <sstream>
#include <map>


struct host_address {
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
};
std::ostream& operator<<(std::ostream& ostm, const host_address& r)
{
	return ostm
		<< static_cast<short>(r.a) << '.'
		<< static_cast<short>(r.b) << '.'
		<< static_cast<short>(r.c) << '.'
		<< static_cast<short>(r.d);
}

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

	std::cout << "�z�X�g��IP ... 0 IP���z�X�g...1\n";
	std::cin >> x;
	if (x == 0) {
		std::string hostmei;
		std::cout << "�z�X�g���́H";
		std::cin >> hostmei;

		it = host_ip.find(hostmei);
		if (it == host_ip.end()) {
			std::cout << hostmei << "�͊Y������\n";
		}
		else {
			std::cout << hostmei << "��" << it->second << "\n";
		}
	}
	else if (x == 1) {
		std::string ipaddr;
		std::cout << "IP�A�h���X�́H";
		std::cin >> ipaddr;

		;
		for (it = host_ip.begin(); it != host_ip.end(); ++it) {
			if ((std::ostringstream() << it->second).str() == ipaddr) {
				break;
			}
		}
		if (it == host_ip.end()) {
			std::cout << ipaddr << "�͊Y������\n";
		}
		else {
			std::cout << ipaddr << "��" << it->first << "\n";
		}

	}
	return 0;
}