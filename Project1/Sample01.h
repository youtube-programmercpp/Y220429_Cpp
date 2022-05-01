void OnOK(HWND hDlg);
struct host_address {
	int address;
	static constexpr unsigned short ipv4size = 4;
	static_assert(sizeof address >= ipv4size, "Must be able to store IPv4 address");
	bool operator==(const host_address& r) const noexcept;
};
#include <map>
#include <istream>
std::istream& operator>>(std::istream& istm, host_address& r);
