//----------Main.cpp---------
#include "stdbasedWinLib.h"
using namespace std;
int main()
{
	using namespace stdbasedWinLib;
	wstring wstr(L"Wide to utf8");
	u8string u8str(move(Wto8(wstr)));
}
