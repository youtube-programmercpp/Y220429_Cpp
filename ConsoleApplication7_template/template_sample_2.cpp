#include <Windows.h>
#include <type_traits>
#undef	MessageBox
namespace WindowsApi
{
	template<class T>struct Switch;

	template<>struct Switch< char  > {
		template<class A, class W>static A Select(A a, W w)
		{
			return a;
		}
	};
	template<>struct Switch<wchar_t> {
		template<class A, class W>static W Select(A a, W w)
		{
			return w;
		}
	};
	template<class T>int MessageBox
	( _In_opt_ HWND      hWnd     
	, _In_opt_ const T*  lpText   
	, _In_opt_ const T*  lpCaption
	, _In_     UINT      uType    
	)
	{
		return Switch<T>::Select(MessageBoxA, MessageBoxW)
		( /*_In_opt_ HWND    hWnd     */hWnd     
		, /*_In_opt_ LPCWSTR lpText   */lpText   
		, /*_In_opt_ LPCWSTR lpCaption*/lpCaption
		, /*_In_     UINT    uType    */uType    
		);
	}
}
int main()
{
	WindowsApi::MessageBox(nullptr, "マルチバイト文字列",      "TEST1" , 0);
	WindowsApi::MessageBox(nullptr, L"ワイド文字列"     ,     L"TEST2" , 0);
	WindowsApi::MessageBox(nullptr, TEXT("文字列")      , TEXT("TEST3"), 0);
}
