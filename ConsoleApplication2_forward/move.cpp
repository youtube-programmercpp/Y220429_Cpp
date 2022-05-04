#include "move.h"
#include "sample_function.h"
#include <string>
#include <iostream>
void move::test_lambda_copy_capture()
{
	const std::string s{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*> hThread
	{ HANDLE(/*template<class T>uintptr_t */move::_beginthreadex
		( /*_In_opt_  void      * _Security        */nullptr
		, /*_In_      unsigned    _StackSize       */0
		, /*          T        && lambda_expression*/[s]()->unsigned
			{
				OutputDebugStringA(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ ": ");
				OutputDebugStringA(s.c_str());
				OutputDebugStringA("\n");
				return 0;
			}
		, /*_In_      unsigned    _InitFlag        */0
		, /*_Out_opt_ unsigned  * _ThrdAddr        */nullptr
		))
	, CloseHandle
	};
	(void)WaitForSingleObject(hThread.get(), INFINITE);
	std::cout << __FUNCTION__ ": " << s << '\n';
}
#if 0
void move::test_lval()
{
	sample_function x;
	std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(CloseHandle)*> hThread
	{ HANDLE(/*template<class T>uintptr_t */move::_beginthreadex
		( /*_In_opt_  void      * _Security        */nullptr
		, /*_In_      unsigned    _StackSize       */0
		, /*          T        && function         */x
		, /*_In_      unsigned    _InitFlag        */0
		, /*_Out_opt_ unsigned  * _ThrdAddr        */nullptr
		))
	, CloseHandle
	};
	(void)WaitForSingleObject(hThread.get(), INFINITE);
	std::cout << __FUNCTION__ ": " << x.s << '\n';
}
#endif
