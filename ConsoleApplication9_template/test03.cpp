template<class T>struct AW;

template<>struct AW<char> {
	template<class A, class W>static A Select(A a, W w)
	{
		return a;
	}
};
template<>struct AW<wchar_t> {
	template<class A, class W>static W Select(A a, W w)
	{
		return w;
	}
};
#include <iostream>
#include <Windows.h>

#define	AWLiteral(T, s)	AW<T>::Select(s, _CRT_WIDE(s))
#define	AWWinApi(T, api)	AW<T>::Select(api##A, api##W)

int main()
{
	std::wcout << AWLiteral(wchar_t, "•¶Žš—ñ") << '\n';
	AWWinApi(wchar_t, MessageBox);
}
