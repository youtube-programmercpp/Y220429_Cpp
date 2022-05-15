#include <Windows.h>
#undef	MessageBox
namespace WindowsApi
{
	inline int MessageBox
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
	inline int MessageBox
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
	WindowsApi::MessageBox(nullptr, "マルチバイト文字列",      "TEST1" , 0);
	WindowsApi::MessageBox(nullptr, L"ワイド文字列"     ,     L"TEST2" , 0);
	WindowsApi::MessageBox(nullptr, TEXT("文字列")      , TEXT("TEST3"), 0);
}
