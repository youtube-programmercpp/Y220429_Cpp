#include <tchar.h>
int main()
{
	const _TCHAR* const p = _T("ABC");//文字列リテラル
	const _TCHAR ch       = _T('X');//文字リテラル
	//ビルド設定「文字セット」で
	//「Unicode 文字セットを使用する」TCHAR, _TCHAR → wchar_t
	//「マルチ バイト文字セットを使用する」TCHAR, _TCHAR → char
	// _T マクロは古くは MFC 用、その後、MFC と C ランタイムライブラリ用
	// TEXT マクロは Win32 API 用
}
