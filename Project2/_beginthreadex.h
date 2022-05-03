#pragma once
template<class T>uintptr_t _beginthreadex
( _In_opt_  void                     * _Security        
, _In_      unsigned                   _StackSize       
,           T                       && lambda_expression
, _In_      unsigned                   _InitFlag        
, _Out_opt_ unsigned                 * _ThrdAddr        
)
{
	const auto _ArgList = new T{ std::move(lambda_expression) };

	if (const auto hThread = /*_Success_(return != 0) _ACRTIMP uintptr_t __cdecl*/_beginthreadex
	( /*_In_opt_  void                     * _Security    */_Security    
	, /*_In_      unsigned                   _StackSize   */_StackSize   
	, /*_In_      _beginthreadex_proc_type   _StartAddress*/[](void* _ArgList)->unsigned
		{
			return (*std::unique_ptr<T>{static_cast<T*>(_ArgList)})();
		}
	, /*_In_opt_  void                     * _ArgList     */_ArgList
	, /*_In_      unsigned                   _InitFlag    */_InitFlag    
	, /*_Out_opt_ unsigned                 * _ThrdAddr    */_ThrdAddr    
	))
		return hThread;
	else {
		delete _ArgList;
		return {};
	}
}
