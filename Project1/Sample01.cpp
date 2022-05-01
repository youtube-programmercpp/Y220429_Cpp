#include <windows.h>
#include "resource.h"
#include "Sample01.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits.h>
#include <cstdint>


bool host_address::operator==(const host_address& r) const noexcept
{
	return reinterpret_cast<const std::int32_t&>(address) == reinterpret_cast<const std::int32_t&>(r.address);
}


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



void OnOK(HWND hDlg)
{
	const auto hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	if (const auto length = GetWindowTextLengthA(hEdit)) {
		std::string buf(length, '\0');
		buf.resize(GetWindowTextA(hEdit, &buf.front(), length + 1));

		const auto& host_ip = *reinterpret_cast<const std::map<std::string, host_address>*>(GetWindowLongPtrW(hDlg, DWLP_USER));

		host_address a;
		if (std::istringstream(buf) >> a) {
			//入力されたのは IP アドレスである
			if (const auto p = mode<1>::find(host_ip, a))
				SetDlgItemTextA(hDlg, IDC_EDIT_Result, p->c_str());
		}
		else {
			//入力されたのはホスト名であるとする
			if (const auto p = mode<0>::find(host_ip, buf))
				SetDlgItemTextA(hDlg, IDC_EDIT_Result, (std::ostringstream() << *p).str().c_str());
		}
	}
}
