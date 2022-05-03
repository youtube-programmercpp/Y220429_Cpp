#pragma once
template<class T>INT_PTR DialogBoxParamW
( _In_opt_ HINSTANCE hInstance        
, _In_     LPCWSTR   lpTemplateName   
, _In_opt_ HWND      hWndParent       
,          T&&       lambda_expression
)
{
	const auto p = new T{std::move(lambda_expression)};
	return /*WINUSERAPI INT_PTR WINAPI*/DialogBoxParamW
	( /*_In_opt_ HINSTANCE hInstance     */hInstance
	, /*_In_     LPCWSTR   lpTemplateName*/MAKEINTRESOURCEW(IDD_DIALOG1)
	, /*_In_opt_ HWND      hWndParent    */nullptr
	, /*_In_opt_ DLGPROC   lpDialogFunc  */[](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)->INT_PTR
		{
			switch (message) {
			case WM_INITDIALOG:
				SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
				return (*reinterpret_cast<T*>(lParam))
				( /*HWND   hDlg   */hDlg   
				, /*UINT   message*/message
				, /*WPARAM wParam */wParam 
				, /*LPARAM lParam */lParam 
				);
				return true;
			case WM_NCDESTROY:
				(void)(*reinterpret_cast<T*>(GetWindowLongPtr(hDlg, DWLP_USER)))
				( /*HWND   hDlg   */hDlg   
				, /*UINT   message*/message
				, /*WPARAM wParam */wParam 
				, /*LPARAM lParam */lParam 
				);
				delete reinterpret_cast<T*>(GetWindowLongPtrW(hDlg, DWLP_USER));
				return true;
			default:
				if (const auto p = reinterpret_cast<T*>(GetWindowLongPtr(hDlg, DWLP_USER))) {
					return (*p)
					( /*HWND   hDlg   */hDlg   
					, /*UINT   message*/message
					, /*WPARAM wParam */wParam 
					, /*LPARAM lParam */lParam 
					);
				}
				else
					return false;
			}
		}
	, /*_In_     LPARAM    dwInitParam   */LPARAM(p)
	);
}
