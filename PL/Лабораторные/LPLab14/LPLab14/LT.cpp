#include "LT.h"
#include <cstring>
#include <iostream>
int n = 0;

namespace LT
{
	LexTable Create(int size)
	{
		Entry* entry = new Entry[size];
		LexTable t = LexTable{ size, 0, entry };
		return t;
	}

	void Add(LexTable& lextable, Entry entry) 
	{
		lextable.table[lextable.size] = entry;
		lextable.size++;
	}

	Entry GetEntry(LexTable& lextable, int n) 
	{
		return lextable.table[n];
	}


	void Delete(LexTable& lextable) 
	{
		for (int i = lextable.size; i > 0; i--)
			delete& (lextable.table[i]);
		delete& lextable;
	}
}