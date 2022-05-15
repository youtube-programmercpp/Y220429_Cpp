#include <string>
#include <Windows.h>
std::u8string Wto8(const std::wstring& wstr)
{
	if (const auto cchWideChar = wstr.length()) {
		//長さが 0 ではない
		std::u8string u8str(3 * cchWideChar, '\0');
		//WINBASEAPI
		//_Success_(return != 0)
		//_When_((cchWideChar == -1) && (cbMultiByte != 0), _Post_equal_to_(_String_length_(lpMultiByteStr) + 1))
		//int
		//WINAPI
		u8str.resize(WideCharToMultiByte
		( /*_In_                                           UINT   CodePage         */CP_UTF8
		, /*_In_                                           DWORD  dwFlags          */0
		, /*_In_NLS_string_(cchWideChar)                   LPCWCH lpWideCharStr    */wstr.data()
		, /*_In_                                           int    cchWideChar      */static_cast<int>(cchWideChar)
		, /*_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR  lpMultiByteStr   */LPSTR(& u8str.front())
		, /*_In_                                           int    cbMultiByte      */static_cast<int>(u8str.size())
		, /*_In_opt_                                       LPCCH  lpDefaultChar    */nullptr
		, /*_Out_opt_                                      LPBOOL lpUsedDefaultChar*/nullptr
		));
		return u8str;
	}
	else
		return {};
}

int main()
{
	const auto s = Wto8(L"日本語");
}
