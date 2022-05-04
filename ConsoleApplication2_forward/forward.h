#include <Windows.h>
#include <process.h>
#include <utility>
#include <memory>
#include <type_traits>
namespace forward {
	//
	//	std::forward Žg—p”Å
	//
	template<class T>uintptr_t _beginthreadex
	( _In_opt_  void      * _Security        
	, _In_      unsigned    _StackSize       
	,           T        && function         
	, _In_      unsigned    _InitFlag        
	, _Out_opt_ unsigned  * _ThrdAddr        
	)
	{
		typedef std::remove_reference_t<T> T2;
		auto _ArgList = std::make_unique<T2>(std::forward<T>(function));
		if (const auto hThread = /*_Success_(return != 0) _ACRTIMP uintptr_t __cdecl*/::_beginthreadex
		( /*_In_opt_  void                    * _Security    */_Security    
		, /*_In_      unsigned                  _StackSize   */_StackSize   
		, /*_In_      _beginthreadex_proc_type  _StartAddress*/[](void* _ArgList)->unsigned
			{
				return (*std::unique_ptr<T2>{static_cast<T2*>(_ArgList)})();
			}
		, /*_In_opt_  void                    * _ArgList     */_ArgList.get()
		, /*_In_      unsigned                  _InitFlag    */_InitFlag    
		, /*_Out_opt_ unsigned                * _ThrdAddr    */_ThrdAddr    
		)) {
			(void)_ArgList.release();
			return hThread;
		}
		else
			return {};
	}
	void test_lambda_copy_capture();
	void test_lval();
}
