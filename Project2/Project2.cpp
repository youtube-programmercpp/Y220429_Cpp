// Project2.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "Project2.h"
#include <process.h>
#include <memory>
#include <exception>
#include <CommCtrl.h>
#pragma comment(lib, "comctl32")
#include "_beginthreadex.h"
#include "DialogBoxParamW.h"

#define	WM_USER_END	(WM_USER + 0x1000)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	if (const std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*> hStopEvent
		{ /*WINBASEAPI _Ret_maybenull_ HANDLE WINAPI*/CreateEventW
			( /*_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes*/nullptr
			, /*_In_     BOOL                  bManualReset     */true
			, /*_In_     BOOL                  bInitialState    */false
			, /*_In_opt_ LPCWSTR               lpName           */nullptr
			)
		, CloseHandle
		})
	{
		std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*> hThread{ nullptr, CloseHandle };

		(void)/*WINUSERAPI INT_PTR WINAPI*/DialogBoxParamW
		( /*_In_opt_ HINSTANCE hInstance     */hInstance
		, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
		, /*_In_opt_ HWND      hWndParent    */nullptr
		, /*_In_opt_ DLGPROC   lpDialogFunc  */[&hStopEvent, &hThread](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)->INT_PTR
			{
				switch (message) {
				case WM_INITDIALOG:
					return true;
				case WM_USER_END://裏スレッドから送られてきた終了メッセージ
					EndDialog(hDlg, IDCANCEL);
					return true;
				case WM_COMMAND:
					switch (LOWORD(wParam)) {
					case IDOK:
						hThread.reset(HANDLE(_beginthreadex(nullptr, 0, [hDlg, &hStopEvent]()->unsigned
							{
								//裏スレッド
								const auto hProgress = GetDlgItem(hDlg, IDC_PROGRESS1);
								constexpr auto limit = 100;
								SendMessage(hProgress, PBM_SETRANGE32, 0, limit);
								for (int value = 0;; ++value) {
									SendMessage(hProgress, PBM_SETPOS, value, 0);
									if (WaitForSingleObject(hStopEvent.get(), 100) == WAIT_OBJECT_0)
										return EXIT_SUCCESS;
									else if (value == limit)
										break;
									else
										continue;
								}
								PostMessage(hDlg, WM_USER_END, 0, 0);
								return EXIT_SUCCESS;
							}
						, 0, nullptr)));
						EnableWindow(GetDlgItem(hDlg, IDOK), false);
						return true;
					case IDCANCEL:
						(void)SetEvent(hStopEvent.get());
						EndDialog(hDlg, IDCANCEL);
						return true;
					default:
						return false;
					}
				default:
					return false;
				}
			}
		);
		if (hThread)
			(void)WaitForSingleObject(hThread.get(), INFINITE);
	}
}
