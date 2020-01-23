#include "pch.h"
#include "framework.h"
#include <iostream>

extern "C"
{
	int __stdcall getmin(int* mass, int num)
	{
		int min = mass[0];
		for (int i = 0; i < num; i++)
		{
			if (mass[i] < min)
				min = mass[i];
		}
		return min;
	}

	int __stdcall getmax(int* mass, int num)
	{
		int max = mass[0];
		for (int i = 0; i < num; i++)
		{
			if (mass[i] > max)
				max = mass[i];
		}
		return max;
	}

	void __stdcall WriteInConsole(int k)
	{
		std::cout << k << std::endl;
	}
};