#include "FST.h"
#include "Out.h"
#include "Error.h"
#include "Parm.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"

#include <ctime>
#include <cstdlib>
#include "MFST.h"
#include "GRB.h"

using namespace LT;

void LexAnaliz(In::IN in, LT::LexTable &t, IT::IdTable &idif)
{
	int num = 1;
	int str[100];
	int intpr = 0;
	int intmai = 0;
	bool flag = false;
	char c[1000];
	int k = 0;
	int lines = 1;
	int identificators = 0;
	int s = 0;
	char fun[5];
	int funnum = 0;
	int idi = 0;
	char SUBSTR[] = { 's', 'u', 'b', 's', 't', 'r', '\0' };
	char STRLEN[] = { 's', 't', 'r', 'l', 'e', 'n', '\0' };
	for (int i = 0; i < 5; i++)
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
		for (int i = 0; i < 10; i++)
		{
			temp->id[i] = '\0';
			temp->fun.namefun[i] = '\0';
		}

		if (integ(c) == 1) { Add(t, { LEX_INTEGER , lines, LT_TI_NULLIDX, INTORSTR(1) }); flag = true; }
		if (stri(c) == 1) { Add(t, { LEX_STRING , lines, LT_TI_NULLIDX, INTORSTR(2) });  flag = true; }
		if (funct(c) == 1) { Add(t, { LEX_FUNCTION , lines, LT_TI_NULLIDX, INTORSTR(0) });  flag = true; }
		if (declare(c) == 1) { Add(t, { LEX_DECLARE , lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (ret(c) == 1) { Add(t, { LEX_RETURN , lines, LT_TI_NULLIDX, INTORSTR(0) });  flag = true; }
		if (pri(c) == 1) { Add(t, { LEX_PRINT , lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (ma(c) == 1)
		{
			Add(t, { LEX_MAIN , lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true;
			for (int i = 0; i < k; i++)
			{
				fun[i] = c[i];
				funnum++;
			}
		}
		if (subs(c) == 1)
		{
			if (IsSubstr(idif, c) == TI_NULLIDX)
			{
				Add(t, { LEX_SUBSTR , lines, identificators, INTORSTR(0) }); identificators++; flag = true;
				if (t.table[t.size - 3].lexema[0] != 't')
				{
					std::cout << "Функция SUBSTR не определена" << std::endl;
					throw ERROR_THROW(115);
				}
				for (int i = 0; i < 6; i++)
				{
					temp->fun.namefun[i] = SUBSTR[i];
					temp->id[i] = SUBSTR[i];
				}
				temp->fun.numfun = 6;
				temp->numOfid = 6;
				temp->iddatatype = IT::IDDATATYPE(2);
				temp->idtype = IT::IDTYPE(2);
				temp->value.vint = TI_INT_DEFAULT;
				temp->value.vstr.len = 0;
				temp->value.vstr.str[0] = TI_STR_DEFAULT;
				IT::Add(idif, *temp);
			}
			else
			{
				Add(t, { LEX_SUBSTR , lines, IsSubstr(idif, c), INTORSTR(0) }); flag = true;
			}
		}
		if (strl(c) == 1)
		{
			if (IsStrlen(idif, c) == TI_NULLIDX)
			{
				Add(t, { LEX_STRLEN , lines, identificators, INTORSTR(0) }); identificators++; flag = true;
				if (t.table[t.size - 3].lexema[0] != 't')
				{
					std::cout << "Функция STRLEN не определена" << std::endl;
					throw ERROR_THROW(116);
				}
				for (int i = 0; i < 6; i++)
				{
					temp->fun.namefun[i] = STRLEN[i];
					temp->id[i] = STRLEN[i];
				}
				temp->fun.numfun = 6;
				temp->numOfid = 6;
				temp->iddatatype = IT::IDDATATYPE(1);
				temp->idtype = IT::IDTYPE(2);
				temp->value.vint = TI_INT_DEFAULT;
				temp->value.vstr.len = 0;
				temp->value.vstr.str[0] = TI_STR_DEFAULT;
				IT::Add(idif, *temp);
			}
			else
			{
				Add(t, { LEX_STRLEN , lines, IsStrlen(idif, c), INTORSTR(0) }); flag = true;
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
						Add(t, { LEX_ID , lines, identificators, INTORSTR(0) }); identificators++; flag = true;
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
						if (t.table[t.size - 2].lexema[0] == 'f')
						{
							temp->idtype = IT::IDTYPE(2);
							if (t.table[t.size - 3].IntOrStr == 1)
							{
								temp->iddatatype = IT::IDDATATYPE(1);
							}
							if (t.table[t.size - 3].IntOrStr == 2)
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
						if (t.table[t.size - 2].lexema[0] == 't')
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
								if (strcmp(idif.table[idif.size - 1].id, SUBSTR) == 0 ||
									strcmp(idif.table[idif.size - 2].id, SUBSTR) == 0 ||
									strcmp(idif.table[idif.size - 3].id, SUBSTR) == 0)
								{
									for (int i = 0; i < 6; i++)
									{
										temp->fun.namefun[i] = SUBSTR[i];
									}
									temp->fun.numfun = 6;
								}
								else if (strcmp(idif.table[idif.size - 1].id, STRLEN) == 0)
								{
									for (int i = 0; i < 6; i++)
									{
										temp->fun.namefun[i] = STRLEN[i];
									}
									temp->fun.numfun = 6;
								}
							}
						}

						temp->value.vint = TI_INT_DEFAULT;
						temp->value.vstr.len = 0;
						temp->value.vstr.str[0] = TI_STR_DEFAULT;
						IT::Add(idif, *temp);
					}
					else
					{
						for (int i = IsId(idif, c); i < idif.size; i++)
						{
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
						Add(t, { LEX_ID , lines, idi, INTORSTR(0) }); flag = true;
						/*for (int i = 0; i < idif.table[idi].numOfid; i++)
						{
							temp->id[i] = idif.table[idi].id[i];
							s++;
						}
						temp->numOfid = s;
						s = 0;
						for (int i = 0; i < idif.table[idi].fun.numfun; i++)
						{
							temp->fun.namefun[i] = idif.table[idi].fun.namefun[i];
						}
						temp->fun.numfun = idif.table[idi].fun.numfun;
						temp->iddatatype = idif.table[idi].iddatatype;
						temp->idtype = idif.table[idi].idtype;*/
						/*temp->value.vint = TI_INT_DEFAULT;
						temp->value.vstr.len = 0;
						temp->value.vstr.str[0] = TI_STR_DEFAULT;

						IT::Add(idif, *temp);*/
					}
				}
			}
		}
		if (literalinteger(c) == 1)
		{
			if ((in.text[i + 1] == ' ') || (in.text[i + 1] == ';') ||
				(in.text[i + 1] == '(') || (in.text[i + 1] == ')') ||
				(in.text[i + 1] == ',') || (in.text[i + 1] == 'v') ||
				(in.text[i + 1] == '-') || (in.text[i + 1] == '*') ||
				(in.text[i + 1] == '/'))
			{
				for (int i = 0; i < k; i++)
				{
					str[i] = c[i] - '0';
				}
				if (IsLitInt(idif, str, k) == TI_NULLIDX)
				{
					Add(t, { LEX_LITERAL , lines, identificators, INTORSTR(0) }); identificators++; flag = true;
					temp->iddatatype = IT::IDDATATYPE(1);
					temp->idtype = IT::IDTYPE(4);
					temp->value.vint = 0;
					for (int i = 0; i < k; i++)
					{
						temp->value.vint += num * str[k - i - 1];
						num *= 10;
					}
					num = 1;
					IT::Add(idif, *temp);
				}
				else
				{
					Add(t, { LEX_LITERAL , lines, IsLitInt(idif, str, k), INTORSTR(0) }); flag = true;
				}
			}
		}
		if (literalstring(c) == 1)
		{
			if ((in.text[i + 1] == ';') || (in.text[i + 1] == '(') ||
				(in.text[i + 1] == ')') || (in.text[i + 1] == ','))
			{
				if (IsLitStr(idif, c) == TI_NULLIDX)
				{
					Add(t, { LEX_LITERAL , lines, identificators, INTORSTR(0) }); identificators++; flag = true;
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
					Add(t, { LEX_LITERAL , lines, IsLitStr(idif, c), INTORSTR(0) }); flag = true;
				}
			}
		}

		if (c[k - 1] == ';') { Add(t, { LEX_SEMICOLON, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == ',') { Add(t, { LEX_COMMA, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == ')') { Add(t, { LEX_RIGHTHESIS, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '+') { Add(t, { LEX_PLUS, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '-') { Add(t, { LEX_MINUS, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '*') { Add(t, { LEX_STAR, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '/') { Add(t, { LEX_DIRSLASH, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '=') { Add(t, { LEX_EQUALLY, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '{') { Add(t, { LEX_LEFTBRACE, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
		if (c[k - 1] == '}')
		{
			Add(t, { LEX_BRACELET, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true;
			for (int i = 0; i < funnum; i++)
			{
				fun[i] = '\0';
			}
			funnum = 0;
		}
		if (c[k - 1] == '(') { Add(t, { LEX_LEFTHESIS, lines, LT_TI_NULLIDX, INTORSTR(0) }); flag = true; }
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
			c[k - 1] == ';' || c[k - 1] == '\n')
		{
			if (k > 1 && c[0] != '"')
			{
				std::cout << "Нераспознанная лексема" << std::endl;
				throw ERROR_THROW(113);
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
}