#include "pch.h"
#include "framework.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

extern "C"
{
	void __stdcall WriteInConsoleChar(char ch)
	{
		std::cout << ch << std::endl;
	}
	void __stdcall WriteInConsoleUnint(int un)
	{
		std::cout << un << std::endl;
	}
	int __stdcall RandNum()
	{
		srand(time(NULL));
		int secret = rand() % 20;
		return secret;
	}
	int __stdcall Unicode(char ch)
	{
		return (int)ch;
	}
};
