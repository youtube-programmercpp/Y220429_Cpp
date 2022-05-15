#include <string>

template<class T>using String = std::basic_string<T>;


int main()
{
	String<wchar_t> wide_string  (L"文字列");
	String< char  > narrow_string( "文字列");
	std::basic_string<wchar_t> wide_string2(L"文字列２");
}
