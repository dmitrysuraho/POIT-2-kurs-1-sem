#include <stack>
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"
#include <iostream>
using namespace std;

void PolishNotation(LT::LexTable& lextable, IT::IdTable idif)
{
	stack <LT::Entry> Kolif;
	stack <LT::Entry> Tex;
	int lex;
	int lex2;
	for (int j = 0; j < lextable.size; j++)
	{
		if (lextable.table[j].lexema[0] == '=')
		{
			LT::Entry* mass = new LT::Entry[50];

			Tex.push(lextable.table[j]);
			j++;
			lex = j;
			while (lextable.table[j].lexema[0] != '\n')
			{                           
				if (lextable.table[j].lexema[0] == 'i' || lextable.table[j].lexema[0] == 'l')
				{
					Kolif.push(lextable.table[j]);
					if (((lextable.table[j - 1].lexema[0] == '(' && lextable.table[j + 1].lexema[0] == ')') && idif.table[lextable.table[j - 2].idxTI].idtype == IT::F) ||
						(lextable.table[j - 1].lexema[0] == ',' && lextable.table[j + 1].lexema[0] == ')') || 
						(idif.table[lextable.table[j].idxTI].idtype == IT::F && lextable.table[j + 2].lexema[0] == ')'))
					{
						LT::Entry lexem;
						lexem.lexema[0] = '@';
						lexem.sn = lextable.table[j].sn;
						Kolif.push(lexem);
					}
				}
				/*else if (lextable.table[j].lexema[0] == 'i' && lextable.table[j + 1].lexema[0] == '(' && (lextable.table[j + 2].lexema[0] == 'i' || lextable.table[j + 2].lexema[0] == 'l') && lextable.table[j + 3].lexema[0] == ')')
				{
					for (int t = j; t < 4; t++, j++)
					{
						Kolif.push(lextable.table[t]);
					}
				}*/                // ÏÐÀÂÈËÎ 1
				else if (((lextable.table[j].operators[0] == '+' || lextable.table[j].operators[0] == '-') && Tex.top().lexema[0] == '=') ||
					((lextable.table[j].operators[0] == '*' || lextable.table[j].operators[0] == '/') && Tex.top().lexema[0] == '=') ||
					(lextable.table[j].lexema[0] == '(' && Tex.top().lexema[0] == '=') ||
					((lextable.table[j].operators[0] == '*' || lextable.table[j].operators[0] == '/') && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					(lextable.table[j].lexema[0] == '(' && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					(lextable.table[j].lexema[0] == '(' && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].operators[0] == '+' || lextable.table[j].operators[0] == '-') && Tex.top().lexema[0] == '(') ||
					((lextable.table[j].operators[0] == '*' || lextable.table[j].operators[0] == '/') && Tex.top().lexema[0] == '(') ||
					(lextable.table[j].lexema[0] == '(' && Tex.top().lexema[0] == '(') ||
					((lextable.table[j].operators[0] == '>' || lextable.table[j].operators[0] == '<') && Tex.top().lexema[0] == '=') ||
					((lextable.table[j].operators[0] == '>' || lextable.table[j].operators[0] == '<') && Tex.top().lexema[0] == '(') ||
					(lextable.table[j].lexema[0] == '(' && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')) ||
					((lextable.table[j].operators[0] == '*' || lextable.table[j].operators[0] == '/') && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')))
					Tex.push(lextable.table[j]);
				                   // ÏÐÀÂÈËÎ 2
				else if (((lextable.table[j].lexema[0] == '=') && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					((lextable.table[j].lexema[0] == '=') && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].operators[0] == '+' || lextable.table[j].operators[0] == '-') && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					((lextable.table[j].operators[0] == '+' || lextable.table[j].operators[0] == '-') && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].operators[0] == '*' || lextable.table[j].operators[0] == '/') && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].lexema[0] == ')') && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					((lextable.table[j].lexema[0] == ')') && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].operators[0] == '>' || lextable.table[j].operators[0] == '<') && (Tex.top().operators[0] == '+' || Tex.top().operators[0] == '-')) ||
					((lextable.table[j].operators[0] == '>' || lextable.table[j].operators[0] == '<') && (Tex.top().operators[0] == '*' || Tex.top().operators[0] == '/')) ||
					((lextable.table[j].operators[0] == '>' || lextable.table[j].operators[0] == '<') && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')) ||
					((lextable.table[j].lexema[0] == ')') && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')) ||
					((lextable.table[j].operators[0] == '+' || lextable.table[j].operators[0] == '-') && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')) ||
					((lextable.table[j].lexema[0] == '=') && (Tex.top().operators[0] == '>' || Tex.top().operators[0] == '<')))
				{
					Kolif.push(Tex.top());
					Tex.pop();
					j--;
				}
				                    // ÏÐÀÂÈËÎ 3
				else if (lextable.table[j].lexema[0] == ')' && Tex.top().lexema[0] == '(')
				{
					Tex.pop();
				}
				                    // ÏÐÀÂÈËÎ 4
				else if (lextable.table[j].lexema[0] == ';')
				{
					while (Tex.top().lexema[0] != '=')
					{
						Kolif.push(Tex.top());
						Tex.pop();
					}
					lex2 = j;
					break;
				}
				j++;
			}
			while (!Tex.empty())
			{
				Tex.pop();
			}
			int s = 0;
			while (!Kolif.empty())
			{
				mass[s] = Kolif.top();
				Kolif.pop();
				s++;
			}
			int k = 0;
			for (int m = lex, k = s - 1; m < lex2; m++, k--)
			{
				lextable.table[m] = mass[k];
			}
			delete mass;
		}
	}
}