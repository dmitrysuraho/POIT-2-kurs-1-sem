#include <stack>
#include "LT.h"
#include "PolishNotation.h"
#include <iostream>
using namespace std;

bool PolishNotation(LT::LexTable& lextable)
{
	stack <char> Kolif;
	stack <char> Tex;
	char lex;
	char mass[50];
	for (int i = 0; i < 50; i++)
		mass[i] = '\0';
	int s = 0;
	bool flag = false;
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].lexema[0] == '=')
		{
			Tex.push(lextable.table[i].lexema[0]);
			i++;
			while (lextable.table[i].lexema[0] != '\n')
			{
				if (lextable.table[i].lexema[0] == 'i' || lextable.table[i].lexema[0] == 'l')
					Kolif.push(lextable.table[i].lexema[0]);

				else if (((lextable.table[i].lexema[0] == '+' || lextable.table[i].lexema[0] == '-') && Tex.top() == '=') ||
					((lextable.table[i].lexema[0] == '*' || lextable.table[i].lexema[0] == '/') && Tex.top() == '=') ||
					(lextable.table[i].lexema[0] == '(' && Tex.top() == '=') ||
					((lextable.table[i].lexema[0] == '*' || lextable.table[i].lexema[0] == '/') && (Tex.top() == '+' || Tex.top() == '-')) ||
					(lextable.table[i].lexema[0] == '(' && (Tex.top() == '+' || Tex.top() == '-')) ||
					(lextable.table[i].lexema[0] == '(' && (Tex.top() == '*' || Tex.top() == '/')) ||
					((lextable.table[i].lexema[0] == '+' || lextable.table[i].lexema[0] == '-') && Tex.top() == '(') ||
					((lextable.table[i].lexema[0] == '*' || lextable.table[i].lexema[0] == '/') && Tex.top() == '(') ||
					(lextable.table[i].lexema[0] == '(' && Tex.top() == '('))
					Tex.push(lextable.table[i].lexema[0]);

				else if (((lextable.table[i].lexema[0] == '=') && (Tex.top() == '+' || Tex.top() == '-')) ||
					((lextable.table[i].lexema[0] == '=') && (Tex.top() == '*' || Tex.top() == '/')) ||
					((lextable.table[i].lexema[0] == '+' || lextable.table[i].lexema[0] == '-') && (Tex.top() == '+' || Tex.top() == '-')) ||
					((lextable.table[i].lexema[0] == '+' || lextable.table[i].lexema[0] == '-') && (Tex.top() == '*' || Tex.top() == '/')) ||
					((lextable.table[i].lexema[0] == '*' || lextable.table[i].lexema[0] == '/') && (Tex.top() == '*' || Tex.top() == '/')) ||
					((lextable.table[i].lexema[0] == ')') && (Tex.top() == '+' || Tex.top() == '-')) ||
					((lextable.table[i].lexema[0] == ')') && (Tex.top() == '*' || Tex.top() == '/')))
				{
					Kolif.push(Tex.top());
					Tex.pop();
					i--;
				}

				else if (lextable.table[i].lexema[0] == ')' && Tex.top() == '(')
				{
					Tex.pop();
				}

				else if (lextable.table[i].lexema[0] == ';')
				{
					while (Tex.top() != '=')
					{
						Kolif.push(Tex.top());
						Tex.pop();
					}
					break;
				}
				else if ((lextable.table[i].lexema[0] == ';' && Tex.top() == '(') || (lextable.table[i].lexema[0] == ')' && Tex.top() == '='))
					return false;
				i++;
			}
		}
	}
	while (!Kolif.empty())
	{
		mass[s] = Kolif.top();
		Kolif.pop();
		s++;
	}
	for (int i = s - 1; i >= 0; i--)
	{
		cout << mass[i];
	}
	cout << endl;
	return true;
}