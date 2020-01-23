#include "Parm.h"
#include "Error.h"
#include <wchar.h>

namespace Parm
{
	PARM getparm(int argc, wchar_t* argv[])
	{
		bool in = false, out = false, log = false;
		PARM prmtr;
		wchar_t* ptr;
		for (int i = 1; i < argc; i++)
		{
			if (wcslen(argv[i]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(104);
			}
		}
		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(argv[i], PARM_IN))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_IN);
				wcscpy_s(prmtr.in, ptr);
				in = true;
			}
			if (wcsstr(argv[i], PARM_OUT))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_OUT);
				wcscpy_s(prmtr.out, ptr);
				out = true;
			}
			if (wcsstr(argv[i], PARM_LOG))
			{
				ptr = argv[i];
				ptr += wcslen(PARM_LOG);
				wcscpy_s(prmtr.log, ptr);
				log = true;
			}
		}
		if (!in)
		{
			throw ERROR_THROW(100);
		}
		if (!out)
		{
			wcscpy_s(prmtr.out, prmtr.in);
			wcscat_s(prmtr.out, PARM_OUT_DEFAULT_EXT);
		}
		if (!log)
		{
			wcscpy_s(prmtr.log, prmtr.in);
			wcscat_s(prmtr.log, PARM_LOG_DEFAULT_EXT);
		}
		return prmtr;
	}
}