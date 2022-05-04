#include <Windows.h>
#include <process.h>
#include <memory>
#include <type_traits>
namespace move {
	//
	//	std::move 使用版
	//
	template<class T>uintptr_t _beginthreadex
	( _In_opt_  void      * _Security        
	, _In_      unsigned    _StackSize       
	,           T        && lambda_expression
	, _In_      unsigned    _InitFlag        
	, _Out_opt_ unsigned  * _ThrdAddr        
	)
	{
		/*
		* lambda_expression 引き数にはラムダ式が与えられる前提となっている
		* lambda_expression 引き数に左辺値参照が与えられると new T のところでエラーになる
		*/
		const auto _ArgList = new T{ std::move(lambda_expression) };
		/*
		* lambda_expression 引き数に左辺値参照が与えられたときを考慮するならば
		* std::remove_reference_t<T> 型のインスタンスを new する必要がある。
		* しかしそうした場合の std::move では lambda_expression の内容が移動してしまい
		* lambda_expression は抜け殻となる。そのような事態は左辺値参照を与えている
		* 呼び出し側において予想外のこととなる。
		* よって、lambda_expression 引き数に左辺値参照が与えられることを予期する場合は
		*（当然、lambda_expression という名前も不適当となる）
		* std::move ではなく std::forward によって内容を転送すべきである。
		* ～お礼～
		* 2022/05/03(火) のライブで頂戴した視聴者様からのご指摘は上記のように受け留めました。
		* この度は大変有益なご指摘を頂戴し、ありがとうございました。
		* ～お詫び～
		* こうしてみてみますと、まったく当たり前の部分というべきレベルで考慮が抜け落ちており、
		* ある種の自信作という風にこのテンプレート関数を捉えておりました私自身におきまして、
		* これは非常に恥ずかしいことであると反省している次第です。
		* ご視聴いただいた皆様には大変ご迷惑をおかけしました。
		*/
		if (const auto hThread = /*_Success_(return != 0) _ACRTIMP uintptr_t __cdecl*/::_beginthreadex
		( /*_In_opt_  void                    * _Security    */_Security    
		, /*_In_      unsigned                  _StackSize   */_StackSize   
		, /*_In_      _beginthreadex_proc_type  _StartAddress*/[](void* _ArgList)->unsigned
			{
				return (*std::unique_ptr<T>{static_cast<T*>(_ArgList)})();
			}
		, /*_In_opt_  void                    * _ArgList     */_ArgList     
		, /*_In_      unsigned                  _InitFlag    */_InitFlag    
		, /*_Out_opt_ unsigned                * _ThrdAddr    */_ThrdAddr    
		))
			return hThread;
		else {
			delete _ArgList;
			return {};
		}
	}
	void test_lambda_copy_capture();
	void test_lval();
}
