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

	int IsLitStr(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].value.vstr.str, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsLitInt(IdTable& idtable, int id[100], int k)
	{
		int numb = 0;
		int num = 1;
		for (int i = 0; i < k; i++)
		{
			numb += num * id[k - i - 1];
			num *= 10;
		}
		num = 1;
		for (int i = 0; i < idtable.size; i++) {
			if (idtable.table[i].value.vint == numb && idtable.table[i].idtype == 4)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsSubstr(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	int IsStrlen(IdTable& idtable, char id[100])
	{
		for (int i = 0; i < idtable.size; i++) {
			if (strcmp(idtable.table[i].id, id) == 0)
				return i;
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable) {
		for (int i = idtable.size; i > 0; i--)
			delete& (idtable.table[i]);
		delete& idtable;
	}
}