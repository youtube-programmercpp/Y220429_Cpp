#include "sample_function.h"
unsigned sample_function::operator()() const
{
	OutputDebugStringA(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ ": ");
	OutputDebugStringA(s.c_str());
	OutputDebugStringA("\n");
	return 0;
}
