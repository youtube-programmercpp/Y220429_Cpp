#include <string>

template<class T>std::basic_string<T> append_asterisks(const std::basic_string<T>& s)
{
	static const T asterisks[] = { '–', '*', '*', '*', '*', '*', '*', '*', '\0' };
	return s + asterisks;
}

#include <iostream>
int main()
{
	std::cout  << append_asterisks(std:: string( "TEST")) << '\n';// (1)
	std::wcout << append_asterisks(std::wstring(L"TEST")) << '\n';// (2)
}
