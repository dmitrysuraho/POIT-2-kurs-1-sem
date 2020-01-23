#include "FST.h"
#include "Out.h"
#include "Error.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

#include <ctime>
#include <cstdlib>

using namespace LT;

namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT out;
		out.stream = new std::wofstream(outfile);
		if (!out.stream)
		{
			throw ERROR_THROW(112);
		}
		else
		{
			wcscpy_s(out.outfile, outfile);
			return out;
		}
	}

	void WriteInOut(OUT out, In::IN in, LT::LexTable &t, IT::IdTable &idif)
	{
		*out.stream << endl << endl << "------------LexTable and IdTable------------\n";
		for (int i = 0; i < t.table[t.size - 1].sn; i++)
		{
			if ((i + 1) < 10)
			{
				*out.stream << '0' << i + 1 << ' ';
			}
			else
			{
				*out.stream << i + 1 << ' ';

			}
			for (int j = 0; j < t.size; j++)
			{
				if (t.table[j].sn == (i + 1))
				{
					*out.stream << t.table[j].lexema[0];
				}
			}
			*out.stream << '\n';
		}
		*out.stream << '\n';

		*out.stream << "Имя       " << "Тип данных           " << "Тип идентификатора       " << "Функция     Литерал\n";
		*out.stream << "----------------------------------------------------------------------------\n";
		for (int i = 0; i < idif.size; i++)
		{
			*out.stream << idif.table[i].id;

			*out.stream << '\t' << "    ";
			if (idif.table[i].iddatatype == 1)
			{
				*out.stream << "unint";
			}
			else
			{
				*out.stream << "char";
			}
			*out.stream << '\t' << '\t' << "    ";
			if (idif.table[i].idtype == 1)
			{
				*out.stream << "переменная";
			}
			if (idif.table[i].idtype == 2)
			{
				*out.stream << "функция";
			}
			if (idif.table[i].idtype == 3)
			{
				*out.stream << "параметр";
			}
			if (idif.table[i].idtype == 4)
			{
				*out.stream << "литерал";
			}
			*out.stream << '\t' << "          ";
			for (int j = 0; j < idif.table[i].fun.numfun; j++)
			{
				*out.stream << idif.table[i].fun.namefun[j];
			}
			*out.stream << '\t' << "     ";
			if (idif.table[i].idtype == 4)
			{
				if (idif.table[i].iddatatype == 1)
				{
					if (idif.table[i].value.vint.predst == 1)
						*out.stream << idif.table[i].value.vint.Ten;
					if (idif.table[i].value.vint.predst == 2)
						*out.stream << idif.table[i].value.vint.Six;
				}
				else
				{
					for (int j = 0; j < idif.table[i].value.vstr.len; j++)
					{
						*out.stream << idif.table[i].value.vstr.str[j];
					}
				}
			}
			*out.stream << '\n';
			*out.stream << "----------------------------------------------------------------------------\n";
		}
	}
	void CloseOut(OUT out)
	{
		out.stream->close();
	}
}