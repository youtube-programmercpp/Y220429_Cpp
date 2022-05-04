#pragma once
#include <Windows.h>
#include <string>
struct sample_function {
	std::string s{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	unsigned operator()() const;
};
