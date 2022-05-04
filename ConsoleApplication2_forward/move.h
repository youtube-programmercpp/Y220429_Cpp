#include <Windows.h>
#include <process.h>
#include <memory>
#include <type_traits>
namespace move {
	//
	//	std::move �g�p��
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
		* lambda_expression �������ɂ̓����_�����^������O��ƂȂ��Ă���
		* lambda_expression �������ɍ��Ӓl�Q�Ƃ��^������� new T �̂Ƃ���ŃG���[�ɂȂ�
		*/
		const auto _ArgList = new T{ std::move(lambda_expression) };
		/*
		* lambda_expression �������ɍ��Ӓl�Q�Ƃ��^����ꂽ�Ƃ����l������Ȃ��
		* std::remove_reference_t<T> �^�̃C���X�^���X�� new ����K�v������B
		* ���������������ꍇ�� std::move �ł� lambda_expression �̓��e���ړ����Ă��܂�
		* lambda_expression �͔����k�ƂȂ�B���̂悤�Ȏ��Ԃ͍��Ӓl�Q�Ƃ�^���Ă���
		* �Ăяo�����ɂ����ė\�z�O�̂��ƂƂȂ�B
		* ����āAlambda_expression �������ɍ��Ӓl�Q�Ƃ��^�����邱�Ƃ�\������ꍇ��
		*�i���R�Alambda_expression �Ƃ������O���s�K���ƂȂ�j
		* std::move �ł͂Ȃ� std::forward �ɂ���ē��e��]�����ׂ��ł���B
		* �`����`
		* 2022/05/03(��) �̃��C�u�Œ��Ղ��������җl����̂��w�E�͏�L�̂悤�Ɏ󂯗��߂܂����B
		* ���̓x�͑�ϗL�v�Ȃ��w�E�𒸑Ղ��A���肪�Ƃ��������܂����B
		* �`���l�с`
		* �������Ă݂Ă݂܂��ƁA�܂�����������O�̕����Ƃ����ׂ����x���ōl�������������Ă���A
		* �����̎��M��Ƃ������ɂ��̃e���v���[�g�֐��𑨂��Ă���܂��������g�ɂ����܂��āA
		* ����͔��ɒp�����������Ƃł���Ɣ��Ȃ��Ă��鎟��ł��B
		* �����������������F�l�ɂ͑�ς����f�����������܂����B
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
