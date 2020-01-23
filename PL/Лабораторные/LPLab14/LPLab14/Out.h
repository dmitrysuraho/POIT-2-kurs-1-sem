#pragma once
#pragma warning(disable : 4996)
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"

#include "LT.h"
#include "IT.h"

namespace Out
{
	struct OUT
	{
		wchar_t outfile[PARM_MAX_SIZE];
		std::wofstream* stream;
	};

	static OUT INITOUT = { L"", NULL };
	OUT getout(wchar_t outfile[]);
	void WriteInOut(OUT out, In::IN in, LT::LexTable &t, IT::IdTable &idif);
	void CloseOut(OUT out);
}