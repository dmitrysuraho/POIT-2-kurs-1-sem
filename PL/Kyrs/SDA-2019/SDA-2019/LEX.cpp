#include "In.h"
#include "IT.h"
#include "LT.h"
#include "FST.h"
#include "Error.h"

using namespace LT;
using namespace IT;

int HEX_TO_DEC(char st[10])
{
	int i, s, k, p;
	s = 0;
	p = strlen(st) - 1;
	for (i = 0; st[i] != '\0'; i++)
	{
		switch (toupper(st[i]))
		{
		case 'A': k = 10; break;
		case 'B': k = 11; break;
		case 'C': k = 12; break;
		case 'D': k = 13; break;
		case 'E': k = 14; break;
		case 'F': k = 15; break;
		case '1': k = 1; break;
		case '2': k = 2; break;
		case '3': k = 3; break;
		case '4': k = 4; break;
		case '5': k = 5; break;
		case '6': k = 6; break;
		case '7': k = 7; break;
		case '8': k = 8; break;
		case '9': k = 9; break;
		case '0': k = 0; break;
		}
		s = s + k * pow(16, p);
		p--;
	}
	return s;
}

void LexAnaliz(In::IN in, LT::LexTable& t, IT::IdTable& idif)
{
	int NumOfLex = 0;
	int str[100];
	int intpr = 0;
	int intmai = 0;
	bool flag = false;
	char c[1000];
	int k = 0;
	int lines = 1;
	int identificators = 0;
	int s = 0;
	char fun[15];
	int funnum = 0;
	int idi = 0;
	char RandN[] = { 'R', 'a', 'n', 'd', 'N', 'u', 'm', '\0' };
	char Unicode[] = { 'U', 'n', 'i', 'c', 'o', 'd', 'e', '\0' };
	for (int i = 0; i < 15; i++)
	{
		fun[i] = '\0';
	}
	for (int i = 0; i < in.size; i++)
	{
		c[i] = '\0';
	}
	for (int i = 0; i < in.size; i++)
	{
		c[k] = in.text[i];
		k++;
		IT::Entry* temp = new IT::Entry;
		for (int i = 0; i < 15; i++)
		{
			temp->id[i] = '\0';
			temp->fun.namefun[i] = '\0';
		}

		if (unint(c) == 1) { LT::Add(t, { LEX_UNINT , lines, LT_TI_NULLIDX, INTORSTR(1), '\0' }); flag = true; }
		if (ch(c) == 1) { LT::Add(t, { LEX_CHAR , lines, LT_TI_NULLIDX, INTORSTR(2), '\0' });  flag = true; }
		if (fr(c) == 1) { LT::Add(t, { LEX_FOR , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' });  flag = true; 
		if (in.text[i + 2] == '0') {
			cout << "Ошибка в выражении цикла" << endl;
			throw ERROR_THROW_IN(178, t.table[t.size - 1].sn, t.size + 2); }
		}
		if (funct(c) == 1) { LT::Add(t, { LEX_FUNCTION , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' });  flag = true; }
		if (identificator(c) == 1) { LT::Add(t, { LEX_IDENTIFICATOR , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (end(c) == 1) { LT::Add(t, { LEX_END , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' });  flag = true; }
		if (o(c) == 1) { LT::Add(t, { LEX_OUT , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (ma(c) == 1)
		{
			LT::Add(t, { LEX_MAIN , lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true;
			for (int i = 0; i < k; i++)
			{
				fun[i] = c[i];
				funnum++;
			}
			/*temp->id[0] = 'm';
			temp->id[1] = 'a';
			temp->id[2] = 'i';
			temp->id[3] = 'n';
			for (int kk = 0; i < funnum; k++)
			{
				temp->fun.namefun[kk] = fun[kk];
			}
			temp->fun.numfun = funnum;
			temp->idtype = IT::F;
			Add(idif, *temp);*/
		}
		if (RandNum(c) == 1)
		{
			if (IsRandNum(idif, c) == TI_NULLIDX)
			{
				LT::Add(t, { LEX_RANDNUM , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
				for (int i = 0; i < 7; i++)
				{
					temp->fun.namefun[i] = RandN[i];
					temp->id[i] = RandN[i];
				}
				temp->numOfid = 12;
				temp->numOfPar = 0;
				temp->iddatatype = IT::IDDATATYPE(1);
				temp->idtype = IT::IDTYPE(2);
				temp->fun.numfun = 12;
				temp->value.vint.Ten = TI_INT_DEFAULT;
				temp->value.vint.Six[0] = TI_STR_DEFAULT;
				temp->value.vstr.len = 0;
				temp->value.vstr.str[0] = TI_STR_DEFAULT;
				IT::Add(idif, *temp);
			}
			else
			{
				LT::Add(t, { LEX_RANDNUM, lines, IsRandNum(idif, c), INTORSTR(0), '\0' }); flag = true;
			}
		}

		if (Uni(c) == 1)
		{
			if (IsUnicode(idif, c) == TI_NULLIDX)
			{
				LT::Add(t, { LEX_UNICODE , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
				for (int i = 0; i < 7; i++)
				{
					temp->fun.namefun[i] = Unicode[i];
					temp->id[i] = Unicode[i];
				}
				temp->numOfid = 7;
				temp->numOfPar = 1;
				temp->iddatatype = IT::IDDATATYPE(1);
				temp->idtype = IT::IDTYPE(2);
				temp->fun.numfun = 7;
				temp->value.vint.Ten = TI_INT_DEFAULT;
				temp->value.vint.Six[0] = TI_STR_DEFAULT;
				temp->value.vstr.len = 0;
				temp->value.vstr.str[0] = TI_STR_DEFAULT;
				IT::Add(idif, *temp);
			}
			else
			{
				LT::Add(t, { LEX_UNICODE , lines, IsUnicode(idif, c), INTORSTR(0), '\0' }); flag = true;
			}
		}

		if (id(c) == 1 && flag == false)
		{
			if ((in.text[i + 1] == '=') || (in.text[i + 1] == '+') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '/') ||
				(in.text[i + 1] == '*') || (in.text[i + 1] == ' ') ||
				(in.text[i + 1] == ';') || (in.text[i + 1] == '(') ||
				(in.text[i + 1] == ')') || (in.text[i + 1] == ','))
			{
				if (k >= 1 && k <= ID_MAXSIZE)
				{
					if ((IsId(idif, c) == TI_NULLIDX) ||
						((IsId(idif, c) != TI_NULLIDX) && t.table[t.size - 1].lexema[0] == 't'))
					{
						LT::Add(t, { LEX_ID , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
						/*if ((IsId(idif, c) != TI_NULLIDX) && (t.table[t.size - 2].lexema[0] == 't'))
						{
							for (int i = IsId(idif, c); i < idif.size; i++)
							{
								if ((strcmp(fun, idif.table[i].fun.namefun) == 0) && (idif.table[i].idtype != 2) && (strcmp(idif.table[i].id, c) == 0))
								{
									std::cout << "Переопределение переменной" << std::endl;
									throw ERROR_THROW(114);
								}
							}
						}*/
						/*if (IsId(idif, c) == TI_NULLIDX && t.table[t.size - 2].lexema[0] != 't' && t.table[t.size - 2].lexema[0] != 'f')
						{
							std::cout << "Переменная не определена" << std::endl;
							throw ERROR_THROW(117);
						}
						else if (IsId(idif, c) == TI_NULLIDX && t.table[t.size - 2].lexema[0] == 'f' && t.table[t.size - 3].lexema[0] != 't')
						{
							std::cout << "Функция не определена" << std::endl;
							throw ERROR_THROW(118);
						}*/
						for (int i = 0; i < k; i++)
						{
							temp->id[i] = c[i];
							s++;
						}
						temp->numOfid = s;
						s = 0;
						if (t.table[t.size - 3].lexema[0] == 'f')
						{
							temp->idtype = IT::IDTYPE(2);
							if (t.table[t.size - 2].IntOrStr == 1)
							{
								temp->iddatatype = IT::IDDATATYPE(1);
							}
							else if (t.table[t.size - 2].IntOrStr == 2)
							{
								temp->iddatatype = IT::IDDATATYPE(2);
							}
							for (int i = 0; i < k; i++)
							{
								fun[i] = c[i];
								funnum++;
							}
						}
						for (int i = 0; i < funnum; i++)
						{
							temp->fun.namefun[i] = fun[i];
						}
						temp->fun.numfun = funnum;
						if (t.table[t.size - 2].lexema[0] == 't' && temp->idtype != 2)
						{
							if (t.table[t.size - 2].IntOrStr == 1)
							{
								temp->iddatatype = IT::IDDATATYPE(1);
							}
							if (t.table[t.size - 2].IntOrStr == 2)
							{
								temp->iddatatype = IT::IDDATATYPE(2);
							}
							if (t.table[t.size - 3].lexema[0] == 'd')
							{
								temp->idtype = IT::IDTYPE(1);
							}
							else
							{
								temp->idtype = IT::IDTYPE(3);
							}
						}
						if (temp->iddatatype == IT::CH)
						{
							temp->value.vstr.len = 0;
							temp->value.vstr.str[0] = TI_STR_DEFAULT;
						}
						else if (temp->iddatatype == IT::UNI)
						{
							temp->value.vint.Ten = TI_INT_DEFAULT;
							temp->value.vint.Six[0] = TI_STR_DEFAULT;
						}
						IT::Add(idif, *temp);
					}
					else
					{
						for (int i = IsId(idif, c); i < idif.size; i++)
						{
							idi = -1;
							if (((strcmp(fun, idif.table[i].fun.namefun) == 0) &&
								(idif.table[i].idtype != 2) &&
								strcmp(idif.table[i].id, c) == 0) ||
								((strcmp(idif.table[i].id, idif.table[i].fun.namefun) == 0) &&
								(strcmp(idif.table[i].id, c) == 0)))
							{
								idi = i;
								break;
							}
						}
						LT::Add(t, { LEX_ID , lines, idi, INTORSTR(0), '\0' }); flag = true;
					}
				}
			}
		}
		if (literalunintTEN(c) == 1)
		{
			if ((in.text[i + 1] == ' ') || (in.text[i + 1] == ';') ||
				(in.text[i + 1] == '(') || (in.text[i + 1] == ')') ||
				(in.text[i + 1] == ',') || (in.text[i + 1] == '+') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '*') ||
				(in.text[i + 1] == '/'))
			{
				for (int i = 0; i < k; i++)
				{
					str[i] = c[i] - '0';
				}
				int num = 1;
				int n = 0;
				for (int i = 0; i < k; i++)
				{
					n += num * str[k - i - 1];
					num *= 10;
				}
				if (IsLitUnintTEN(idif, n, k) == TI_NULLIDX)
				{
					LT::Add(t, { LEX_LITERAL , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
					if (NumOfLex < 10)
					{
						temp->id[0] = 'L';
						temp->id[1] = NumOfLex + '0';
						NumOfLex++;
					}
					else if (NumOfLex % 10 != 0)
					{
						int ost = NumOfLex % 10;
						temp->id[0] = 'L';
						temp->id[1] = ((NumOfLex - ost) / 10) + '0';
						temp->id[2] = ost + '0';
						NumOfLex++;
					}
					else
					{
						temp->id[0] = 'L';
						temp->id[1] = (NumOfLex / 10) + '0';
						temp->id[2] = '0';
						NumOfLex++;
					}
					temp->numOfid = 2;
					temp->iddatatype = IT::IDDATATYPE(1);
					temp->idtype = IT::IDTYPE(4);
					temp->value.vint.predst = IT::PR(1);
					temp->value.vint.Ten = n;

					IT::Add(idif, *temp);
				}
				else
				{
					LT::Add(t, { LEX_LITERAL , lines, IsLitUnintTEN(idif, n, k), INTORSTR(0), '\0' }); flag = true;
				}
			}
		}

		if (literalunintSIXTEEN(c) == 1)
		{
			if (((in.text[i + 1] == ' ') || (in.text[i + 1] == ';') ||
				(in.text[i + 1] == '(') || (in.text[i + 1] == ')') ||
				(in.text[i + 1] == ',') || (in.text[i + 1] == '+') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '*') ||
				(in.text[i + 1] == '/')) && k <= 10)
			{
				int numb = 0;
				char st[10];
				for (int i = 0; i < 10; i++)
					st[i] = '\0';
				for (int i = 1; i < k - 1; i++)
				{
					st[numb] = c[i];
					numb++;
				}
				for (int l = 0; l < 10; l++)
					temp->value.vint.Six[l] = '\0';

				/*numb = HEX_TO_DEC(st);*/
				if (IsLitUnintSIXTEEN(idif, st) == TI_NULLIDX)
				{
					LT::Add(t, { LEX_LITERAL , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
					if (NumOfLex < 10)
					{
						temp->id[0] = 'L';
						temp->id[1] = NumOfLex + '0';
						NumOfLex++;
					}
					else if (NumOfLex % 10 != 0)
					{
						int ost = NumOfLex % 10;
						temp->id[0] = 'L';
						temp->id[1] = ((NumOfLex - ost) / 10) + '0';
						temp->id[2] = ost + '0';
						NumOfLex++;
					}
					else
					{
						temp->id[0] = 'L';
						temp->id[1] = (NumOfLex / 10) + '0';
						temp->id[2] = '0';
						NumOfLex++;
					}
					temp->numOfid = 2;
					temp->iddatatype = IT::IDDATATYPE(1);
					temp->idtype = IT::IDTYPE(4);
					temp->value.vint.predst = IT::PR(2);
					for (int j = 0; j < numb; j++)
					{
						temp->value.vint.Six[j] = st[j];
					}
					IT::Add(idif, *temp);
				}
				else
				{
					LT::Add(t, { LEX_LITERAL , lines, IsLitUnintSIXTEEN(idif, st), INTORSTR(0), '\0' }); flag = true;
				}
			}
		}

		if (literalchar(c) == 1)
		{
			if ((in.text[i + 1] == ' ') || (in.text[i + 1] == ';') ||
				(in.text[i + 1] == '(') || (in.text[i + 1] == ')') ||
				(in.text[i + 1] == ',') || (in.text[i + 1] == '+') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '*') ||
				(in.text[i + 1] == '/'))
			{
				if (IsLitChar(idif, c) == TI_NULLIDX)
				{
					LT::Add(t, { LEX_LITERAL , lines, identificators, INTORSTR(0), '\0' }); identificators++; flag = true;
					if (NumOfLex < 10)
					{
						temp->id[0] = 'L';
						temp->id[1] = NumOfLex + '0';
						NumOfLex++;
					}
					else if (NumOfLex % 10 != 0)
					{
						int ost = NumOfLex % 10;
						temp->id[0] = 'L';
						temp->id[1] = ((NumOfLex - ost) / 10) + '0';
						temp->id[2] = ost + '0';
						NumOfLex++;
					}
					else
					{
						temp->id[0] = 'L';
						temp->id[1] = (NumOfLex / 10) + '0';
						temp->id[2] = '0';
						NumOfLex++;
					}
					temp->numOfid = 2;
					temp->numOfid = idif.table[idif.size - 1].numOfid;
					temp->iddatatype = IT::IDDATATYPE(2);
					temp->idtype = IT::IDTYPE(4);
					temp->value.vstr.len = k;
					int j = 0;
					for (int i = 0; i < k; i++)
					{
						temp->value.vstr.str[i] = c[i];
					}
					temp->value.vstr.str[k] = '\0';
					IT::Add(idif, *temp);
				}
				else
				{
					LT::Add(t, { LEX_LITERAL , lines, IsLitChar(idif, c), INTORSTR(0), '\0' }); flag = true;
				}
			}
		}

		if (strcmp(c, "<<") == 0) { LT::Add(t, { LEX_LEFT, lines, LT_TI_NULLIDX, INTORSTR(0), '<' }); flag = true; }
		if (strcmp(c, ">>") == 0) { LT::Add(t, { LEX_RIGHT, lines, LT_TI_NULLIDX, INTORSTR(0), '>' }); flag = true; }
		if (c[k - 1] == ';') { LT::Add(t, { LEX_SEMICOLON, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == ',') { LT::Add(t, { LEX_COMMA, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == ')') { LT::Add(t, { LEX_RIGHTHESIS, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == '+') { LT::Add(t, { LEX_PLUS, lines, LT_TI_NULLIDX, INTORSTR(0), '+' }); flag = true; }
		if (c[k - 1] == '*') { LT::Add(t, { LEX_STAR, lines, LT_TI_NULLIDX, INTORSTR(0), '*' }); flag = true; }
		if (c[k - 1] == '=') { LT::Add(t, { LEX_EQUALLY, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == '{') { LT::Add(t, { LEX_LEFTBRACE, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == '}')
		{
			LT::Add(t, { LEX_BRACELET, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true;
			for (int i = 0; i < funnum; i++)
			{
				fun[i] = '\0';
			}
			funnum = 0;
		}
		if (c[k - 1] == '[') { LT::Add(t, { LEX_SQR, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == ']') { LT::Add(t, { LEX_SQL, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == '(') { LT::Add(t, { LEX_LEFTHESIS, lines, LT_TI_NULLIDX, INTORSTR(0), '\0' }); flag = true; }
		if (c[k - 1] == ' ')
		{
			flag = true;
			if (c[0] == '"')
			{
				flag = false;
			}
		}


		if (c[k - 1] == ' ' || c[k - 1] == ',' ||
			c[k - 1] == '(' || c[k - 1] == ')' ||
			c[k - 1] == ';' || c[k - 1] == '\n'|| 
			c[k - 1] == '{' || c[k - 1] == '}' ||
			c[k - 1] == '+' || c[k - 1] == '*' ||
			c[k - 1] == '[' || c[k - 1] == ']' ||
			c[k - 1] == '=')
		{
			if (k > 1)
			{
				std::cout << "Нераспознанная лексема" << std::endl;
				throw ERROR_THROW_IN(113, lines, t.size - 1);
			}
		}


		if (c[k - 1] == '\n') { lines++; flag = true; }

		if (flag)
		{
			for (int i = 0; i < k; i++)
			{
				c[i] = '\0';
			}
			k = 0;
			flag = false;
		}
		delete temp;
	}
	int numofpar = 0;
	int numfun;
	for (int i = 0; i < idif.size; i++)
	{
		if ((idif.table[i].idtype == IT::F) &&
		(strcmp(idif.table[i].id, Unicode) != 0) &&
			(strcmp(idif.table[i].id, RandN) != 0))
		{
			numfun = i;
			i++;
			for (int k = 0; k < 20; k++)
				idif.table[numfun].parType[k] = 0;
			while (idif.table[i].idtype == IT::P && 
				strcmp(idif.table[numfun].id, idif.table[i].fun.namefun) == 0)
			{
				if (idif.table[i].iddatatype == IT::CH)
				{
					idif.table[numfun].parType[numofpar] = 2;
				}
				else if (idif.table[i].iddatatype == IT::UNI)
				{
					idif.table[numfun].parType[numofpar] = 1;
				}
				numofpar++;
				i++;
			}
			i--;
			idif.table[numfun].numOfPar = numofpar;
			numofpar = 0;
		}
	}
	lines++;
	Add(t, { '$', lines, LT_TI_NULLIDX , INTORSTR(0), '\0' });
}