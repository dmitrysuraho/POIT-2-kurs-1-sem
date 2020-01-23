#include "Semant.h"

void Semant(LT::LexTable t, IT::IdTable idif, Log::LOG log)
{
	char ma[] = { 'm', 'a', 'i', 'n', '\0' };
	char RandN[] = { 'R', 'a', 'n', 'd', 'N', 'u', 'm', '\0' };
	char Unicode[] = { 'U', 'n', 'i', 'c', 'o', 'd', 'e', '\0' };

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i' &&
			idif.table[t.table[i].idxTI].idtype != IT::P &&
			idif.table[t.table[i].idxTI].idtype != IT::F &&
			t.table[i - 1].lexema[0] != 't')
		{
			IT::Entry lex = idif.table[t.table[i].idxTI];
			int pos = i;
			int lll = 0;
			bool flag = false;
			while (lll <= i)
			{
				if (strcmp(idif.table[t.table[lll].idxTI].id, lex.id) == 0 &&
					strcmp(idif.table[t.table[lll].idxTI].fun.namefun, lex.fun.namefun) == 0 &&
					t.table[lll - 1].lexema[0] == 't')
				{
					flag = true; break;
				}
				lll++;
			}
			if (!flag)
			{
				cout << "Необъявленный идентификатор" << endl;
				throw ERROR_THROW_IN(172, t.table[i].sn, (i + 1));
			}
		}
		else if (t.table[i].lexema[0] == 'i')
		{
			if (t.table[i].idxTI < 0)
			{
				cout << "Необъявленный идентификатор" << endl;
				throw ERROR_THROW_IN(172, t.table[i].sn, (i + 1));
			}
		}
		
	}

	for (int i = 0; i < t.size; i++)
	{
		if (idif.table[t.table[i].idxTI].idtype == IT::F || t.table[i].lexema[0] == 'm')
		{
			i++;
			IT::Entry lex;
			int lll;
			while (t.table[i].lexema[0] != '}')
			{
				if (t.table[i].lexema[0] == 'i' &&
					t.table[i - 1].lexema[0] == 't')
				{
					lex = idif.table[t.table[i].idxTI];
					lll = i + 1;
					while (t.table[lll].lexema[0] != '}')
					{
						if (t.table[lll].lexema[0] == 'i' &&
							t.table[lll - 1].lexema[0] == 't' &&
							strcmp(lex.id, idif.table[t.table[lll].idxTI].id) == 0)
						{
							cout << "Повторное объявление идентификатора" << endl;
							throw ERROR_THROW_IN(171, t.table[lll].sn, (lll + 1));
						}
						lll++;
					}
				}
				i++;
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'c')
		{
			if (t.table[i + 3].lexema[0] != ')')
			{
				cout << "Ошибка в выражении цикла" << endl;
				throw ERROR_THROW_IN(178, t.table[i].sn, (i + 4));
			}
			else if (idif.table[t.table[i + 2].idxTI].iddatatype == IT::CH)
			{
				cout << "Ошибка в выражении цикла" << endl;
				throw ERROR_THROW_IN(178, t.table[i].sn, (i + 3));
			}
			//while (t.table[i].lexema[0] != ']')
			//{
			//	if (t.table[i].lexema[0] == 'e'/* || t.table[i].lexema[0] == 'o'*/)
			//	{
			//		cout << "Ошибка в выражении цикла" << endl;
			//		throw ERROR_THROW_IN(178, t.table[i].sn, (i + 1));
			//	}
			//	i++;
			//}
		}
	}

	for (int i = 0; i < idif.size; i++)
	{
		if (idif.table[i].idtype == IT::L &&
			idif.table[i].iddatatype == IT::CH &&
			idif.table[i].value.vstr.len != 3)
		{
			cout << "Попытка присваивания идентификатору символьного типа тип строковый" << endl;
			throw ERROR_THROW(177);
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i' &&
			t.table[i + 1].lexema[0] == '=')
		{
			IT::Entry id = idif.table[t.table[i].idxTI];
			i += 2;
			while (t.table[i].lexema[0] != ';')
			{
				if (id.iddatatype != idif.table[t.table[i].idxTI].iddatatype &&
					(t.table[i].lexema[0] == 'l' || t.table[i].lexema[0] == 'i') &&
					(idif.table[t.table[i - 2].idxTI].idtype != IT::F && t.table[i - 1].lexema[0] != ','))
				{
					cout << "Несоответствие типов в выражении" << endl;
					throw ERROR_THROW_IN(176, t.table[i].sn, (i + 1));
				}
				i++;
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (idif.table[t.table[i].idxTI].idtype == IT::F)
		{
			IT::Entry id = idif.table[t.table[i].idxTI];
			while (t.table[i].lexema[0] != '}')
			{
				if (t.table[i].lexema[0] == 'e' &&
					strcmp(idif.table[t.table[i + 1].idxTI].fun.namefun, ma) != 0 &&
					idif.table[t.table[i + 1].idxTI].iddatatype != id.iddatatype)
				{
					cout << "Несоответствие типа функции и возвращаемого значения" << endl;
					throw ERROR_THROW_IN(170, t.table[i].sn, (i + 1));
				}
				i++;
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i' &&
			t.table[i - 2].lexema[0] != 'f' &&
			idif.table[t.table[i].idxTI].idtype == IT::F)
		{
			IT::Entry lex = idif.table[t.table[i].idxTI];
			int num = 0;
			i++;
			while (t.table[i].lexema[0] != ')')
			{
				if (t.table[i].lexema[0] == 'i' || t.table[i].lexema[0] == 'l')
				{
					num++;
				}
				i++;
			}
			if (lex.numOfPar != num)
			{
				cout << "Неверное количество параметров, передаваемых в функцию" << endl;
				throw ERROR_THROW_IN(174, t.table[i].sn, (i + 1));
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i' &&
			idif.table[t.table[i].idxTI].idtype == IT::V &&
			t.table[i - 1].lexema[0] != 't' &&
			t.table[i + 1].lexema[0] != '=')
		{
			IT::Entry lex = idif.table[t.table[i].idxTI];
			LT::Entry lex2 = t.table[i];
			int l = 0;
			bool flag = false;
			while (l <= i)
			{
				if (strcmp(idif.table[t.table[l].idxTI].id, lex.id) == 0 &&
					strcmp(idif.table[t.table[l].idxTI].fun.namefun, lex.fun.namefun) == 0 &&
					t.table[l + 1].lexema[0] == '=' &&
					t.table[l].sn != lex2.sn)
				{
					flag = true; break;
				}
				l++;
			}
			if (!flag)
			{
				cout << "Работа с идентификатором, которому не присвоено значение" << endl;
				throw ERROR_THROW_IN(175, t.table[i].sn, (i + 1));
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (idif.table[t.table[i].idxTI].idtype == IT::F &&
			t.table[i - 2].lexema[0] != 'f' &&
			(t.table[i - 1].lexema[0] == 'e' || t.table[i - 1].lexema[0] == 'o'))
		{
			cout << "Выражение начинается со знака '='" << endl;
			throw ERROR_THROW_IN(179, t.table[i].sn, (i + 1));
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i' &&
			idif.table[t.table[i].idxTI].idtype == IT::F &&
			t.table[i - 2].lexema[0] != 'f' &&
			strcmp(idif.table[t.table[i].idxTI].id, Unicode) != 0 &&
			strcmp(idif.table[t.table[i].idxTI].id, RandN) != 0)
		{
			IT::Entry lex = idif.table[t.table[i].idxTI];
			i++;
			int k = 0;
			bool flag[20];
			for (int lll = 0; lll < 20; lll++)
				flag[lll] = false;
			while (t.table[i].lexema[0] != ')')
			{
				if ((t.table[i].lexema[0] == 'i' || t.table[i].lexema[0] == 'l'))
				{
					if (idif.table[t.table[i].idxTI].iddatatype == lex.parType[k])
					{
						flag[k] = true;
					}
					k++;
				}
				i++;
			}
			for (int m = 0; m < k; m++)
			{
				if (!flag[m])
				{
					cout << "Ошибка в параметрах, передаваемых в функцию" << endl;
					throw ERROR_THROW_IN(173, t.table[i].sn, (i + 1));
				}
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (strcmp(idif.table[t.table[i].idxTI].id, Unicode) == 0)
		{
			if (idif.table[t.table[i + 2].idxTI].iddatatype != IT::CH)
			{
				cout << "Ошибка в параметрах, передаваемых в функцию" << endl;
				throw ERROR_THROW_IN(173, t.table[i].sn, (i + 1));
			}
		}
		else if (strcmp(idif.table[t.table[i].idxTI].id, RandN) == 0)
		{
			if (t.table[i + 2].lexema[0] != ')')
			{
				cout << "Ошибка в параметрах, передаваемых в функцию" << endl;
				throw ERROR_THROW_IN(173, t.table[i].sn, (i + 1));
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'v')
		{
			bool flag = false;
			int pos = (i + 1);
			while (t.table[i].lexema[0] != 'e' && t.table[i].lexema[0] != 'o')
			{
				if (t.table[i].lexema[0] == '=')
				{
					flag = true; break;
				}
				i--;
			}
			if (!flag)
			{
				cout << "Выражение начинается со знака '='" << endl;
				throw ERROR_THROW_IN(179, t.table[i].sn, (i + 1));
			}
			i = pos;
		}
	}

	/*for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'c')
		{
			while (t.table[i].lexema[0] != ']')
			{
				if (idif.table[t.table[i].idxTI].idtype == IT::F)
				{
					cout << "Ошибка в выражении цикла" << endl;
					throw ERROR_THROW_IN(178, t.table[i].sn, (i + 1));
				}
				i++;
			}
		}
	}*/

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'v')
		{
			if (idif.table[t.table[i - 1].idxTI].iddatatype == IT::CH ||
				idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
			{
				cout << "Ошибка в выражении" << endl;
				ERROR_THROW_IN(122, t.table[i].sn, (i + 1));
			}
		}
	}

	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].lexema[0] == 'i')
		{
			if (idif.table[t.table[i].idxTI].idtype == IT::F &&
				t.table[i - 2].lexema[0] == 'f')
			{
				i++;
				while (t.table[i].lexema[0] != '}')
				{
					if (idif.table[t.table[i].idxTI].idtype == IT::F &&
						strcmp(idif.table[t.table[i].idxTI].id, Unicode) != 0 &&
						strcmp(idif.table[t.table[i].idxTI].id, RandN) != 0)
					{
						cout << "Ошибка в инструкциях или конструкциях" << endl;
						throw ERROR_THROW_IN(121, t.table[i].sn, (i + 1));
					}
					i++;
				}
			}
		}
	}
}