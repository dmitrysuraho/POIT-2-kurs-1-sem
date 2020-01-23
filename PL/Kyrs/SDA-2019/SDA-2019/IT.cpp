#include "IT.h"

#include <cstring>

namespace IT
{
	IdTable Create(int size) {
		Entry* entries = new Entry[size];
		IdTable mytable = IdTable { size, 0, entries };
		return mytable;
	}


	void Add(IdTable& idtable, Entry entry) {
		Entry* entries = idtable.table;
		entries[idtable.size] = entry;
		idtable.size++;
	}

	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[10]) {
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsLitChar(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].value.vstr.str, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsLitUnintTEN(IdTable& idtable, int numb, int k)
	{
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].value.vint.Ten == numb && idtable.table[i].idtype == 4)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsLitUnintSIXTEEN(IdTable& idtable, char numb[10])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].value.vint.Six, numb) == 0 && idtable.table[i].idtype == 4)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsRandNum(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsUnicode(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		delete[] idtable.table;
	}
}