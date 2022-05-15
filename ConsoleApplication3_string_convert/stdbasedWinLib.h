//---------stdbasedWinLib.h----------
#pragma once
#include <Windows.h>
#include <tchar.h>
#include <string>

namespace stdbasedWinLib {
	using namespace std;
	std::u8string Wto8(const wstring& wstr)
	{
		u8string u8str(WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.size(), NULL, 0, NULL, NULL), u8'\0');
		WideCharToMultiByte(CP_UTF8, 0, wstr.data(), wstr.size(), (LPSTR)u8str.data(), u8str.capacity(), NULL, NULL);
		return std::move(u8str);
	}
}
