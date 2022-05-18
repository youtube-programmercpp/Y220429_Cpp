#define	_CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
int main()
{
	const auto original_flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	_CrtSetDbgFlag(original_flags | _CRTDBG_LEAK_CHECK_DF);
	malloc(512);

}
