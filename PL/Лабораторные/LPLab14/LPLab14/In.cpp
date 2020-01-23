#include "In.h"
#include "Error.h"
#include "Parm.h"
#include <fstream>

using namespace std;

namespace In
{
	unsigned char arr[IN_MAX_LEN_TEXT];
	int size = 0;
	IN getin(wchar_t infile[])
	{
		IN in;
		ifstream file;
		unsigned char minys = '-';
		unsigned char A = 'À';
		unsigned char slesh = '|';
		unsigned char sleshN = '\n';
		char a;
		in.lines = 0;
		in.size = 0;
		in.ignor = 0;
		unsigned int code;
		file.open(infile);
		if (!file)
		{
			throw ERROR_THROW(110);
		}
		else
		{
			while (file.get(a))
			{
				if (a == IN_CODE_ENDL)
				{
					in.lines++;
				}
				if (in.code[(unsigned char)a] == 1024)
				{
					in.size++;
					arr[size] = a;
					size++;
				}
				else if (in.code[(unsigned char)a] == 2048)
				{
					throw ERROR_THROW_IN(111, in.lines, in.size);
				}
				else if (in.code[(unsigned char)a] == 4096)
				{
					in.ignor++;
				}
				else if ((unsigned char)a == (int)A)
				{
					in.size++;
					arr[size] = minys;
					size++;
				}
				else if ((unsigned char)a == (int)sleshN)
				{
					in.size++;
					arr[size] = slesh;
					size++;
				}
			}
		}
		file.close();
		in.lines++;
		in.text = arr;
		return in;
	}
}
