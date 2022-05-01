// Project1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "Project1.h"
#include <string>
#include "Sample01.h"

#if 0
void OnOK(HWND hDlg)
{
	const auto hEdit = GetDlgItem(hDlg, IDC_EDIT1);
	if (const auto length = GetWindowTextLengthA(hEdit)) {
		std::string buf(length, '\0');
		buf.resize(GetWindowTextA(hEdit, &buf.front(), length + 1));
		//MessageBoxA(hDlg, ('"' + buf + '"').c_str(), "入力内容", 0);
		SetDlgItemTextA(hDlg, IDC_EDIT_Result, buf.c_str());
	}
}
#endif

#include <sstream>
#include <fstream>
std::map<std::string, host_address> ReadMap(std::ifstream&& file)
{
	host_address a;
	std::string b;
	std::map<std::string, host_address> host_ip;
	while (file >> a >> b)
		host_ip[b] = a;
	return host_ip;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{
	auto host_ip = ReadMap(std::ifstream("hosttable.txt"));

	/*WINUSERAPI INT_PTR WINAPI*/DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */nullptr
	, /*_In_opt_ DLGPROC   lpDialogFunc  */[](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)->INT_PTR
		{
			switch (message) {
			case WM_INITDIALOG:
				SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
				return true;
			case WM_COMMAND:
				switch (LOWORD(wParam)) {
				case IDOK:
					OnOK(hDlg);
					return true;
				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return true;
				case IDC_EDIT1:
					if (HIWORD(wParam) == EN_CHANGE) {
						SetDlgItemTextW(hDlg, IDC_EDIT_Result, L"");
						return true;
					}
					else
						return false;
				default:
					return false;
				}
			default:
				return false;
			}
		}
	, /*_In_     LPARAM    dwInitParam   */LPARAM(& host_ip)
	);
}
