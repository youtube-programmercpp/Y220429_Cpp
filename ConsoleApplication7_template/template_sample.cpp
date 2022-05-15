#include <Windows.h>
#include <type_traits>
#undef	MessageBox
namespace WindowsApi
{
	template<class T, std::enable_if_t<std::is_same<T, char>::value, bool> = true>int MessageBox
	( _In_opt_ HWND    hWnd     
	, _In_opt_ LPCSTR  lpText   
	, _In_opt_ LPCSTR  lpCaption
	, _In_     UINT    uType    
	)
	{
		return MessageBoxA
		( /*_In_opt_ HWND    hWnd     */hWnd     
		, /*_In_opt_ LPCWSTR lpText   */lpText   
		, /*_In_opt_ LPCWSTR lpCaption*/lpCaption
		, /*_In_     UINT    uType    */uType    
		);
	}
	template<class T, std::enable_if_t<std::is_same<T, wchar_t>::value, bool> = true>int MessageBox
	( _In_opt_ HWND    hWnd     
	, _In_opt_ LPCWSTR lpText   
	, _In_opt_ LPCWSTR lpCaption
	, _In_     UINT    uType    
	)
	{
		return MessageBoxW
		( /*_In_opt_ HWND    hWnd     */hWnd     
		, /*_In_opt_ LPCWSTR lpText   */lpText   
		, /*_In_opt_ LPCWSTR lpCaption*/lpCaption
		, /*_In_     UINT    uType    */uType    
		);
	}
}

int main()
{
	WindowsApi::MessageBox<char   >(nullptr, "マルチバイト文字列",      "TEST1" , 0);
	WindowsApi::MessageBox<wchar_t>(nullptr, L"ワイド文字列"     ,     L"TEST2" , 0);
	WindowsApi::MessageBox<TCHAR  >(nullptr, TEXT("文字列")      , TEXT("TEST3"), 0);
}
