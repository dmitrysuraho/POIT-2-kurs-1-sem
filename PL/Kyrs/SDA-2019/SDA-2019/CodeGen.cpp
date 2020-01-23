#include "CodeGen.h"
#include "IT.h"
#include "LT.h"
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;

void CodeGeneration(LT::LexTable t, IT::IdTable idif)
{
	ofstream file;
	file.open("C:\\Users\\Dmitry\\Desktop\\labrab\\PL\\Kyrs\\SDA-2019\\SDA-2019asm\\SDA-2019asm.asm");
	char RandN[] = { 'R', 'a', 'n', 'd', 'N', 'u', 'm', '\0' };
	char Unicode[] = { 'U', 'n', 'i', 'c', 'o', 'd', 'e', '\0' };
	file << ".586\n.MODEL FLAT, stdcall\nincludelib libucrt.lib\nincludelib kernel32.lib\nExitProcess PROTO : DWORD";
	file << "\n\nUnicode PROTO: DWORD\nRandNum PROTO\nWriteInConsoleChar PROTO: DWORD\nWriteInConsoleUnint PROTO: DWORD\n\n";
	for (int ll = 0; ll < idif.size; ll++)
	{
		if ((idif.table[ll].idtype == IT::F) &&
			(strcmp(idif.table[ll].id, Unicode) != 0) &&
			(strcmp(idif.table[ll].id, RandN) != 0))
		{
			file << idif.table[ll].id << " PROTO";
			int nump = idif.table[ll].numOfPar;
			while (nump != 0)
			{
				ll++;
				nump--;
				if (nump != 0)
				{
					if (idif.table[ll].iddatatype == IT::UNI)
						file << ": DWORD, ";
					else if (idif.table[ll].iddatatype == IT::CH)
						file << ": DWORD, ";
				}

				else if (nump == 0)
				{
					{
						if (idif.table[ll].iddatatype == IT::UNI)
							file << ": DWORD\n";
						else if (idif.table[ll].iddatatype == IT::CH)
							file << ": DWORD\n";
					}
					break;
				}
			}
		}
	}
	file << "\n.STACK 8192\n\n";
	file << ".CONST\n\n";
	for (int i = 0; i < idif.size; i++)
	{
		if (idif.table[i].idtype == IT::L)
		{
			if (idif.table[i].iddatatype == IT::CH)
			{
				file << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vstr.str << ", 0" << "\n";
			}
			else if (idif.table[i].iddatatype == IT::UNI)
			{
				if (idif.table[i].value.vint.predst == IT::TEN)
				{
					file << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Ten << '\n';
				}
				else if (idif.table[i].value.vint.predst == IT::SIXTEEN)
				{
					file << "\t" << idif.table[i].id << " DWORD " << idif.table[i].value.vint.Six << "h\n";
				}
			}
		}
	}
	file << "\n.DATA\n\n";
	for (int i = 0; i < idif.size; i++)
	{

		if ((idif.table[i].idtype == IT::F) &&
			(strcmp(idif.table[i].id, Unicode) != 0) &&
			(strcmp(idif.table[i].id, RandN) != 0))
		{
			if (idif.table[i].iddatatype == IT::UNI)
				file << "\tret_" << idif.table[i].id << " DWORD ?" << '\n';
			else if (idif.table[i].iddatatype == IT::CH)
				file << "\tret_" << idif.table[i].id << " DWORD ?" << '\n';
		}
	}
	for (int i = 0; i < idif.size; i++)
	{

		if (idif.table[i].idtype == IT::V)
		{
			if (idif.table[i].iddatatype == IT::CH)
			{
				file << "\t" << idif.table[i].fun.namefun << idif.table[i].id << " DWORD ?\n";
			}
			else if (idif.table[i].iddatatype == IT::UNI)
			{
				file << "\t" << idif.table[i].fun.namefun << idif.table[i].id << " DWORD ?\n";
			}
		}
	}
	file << "\n.CODE\n\n";
	for (int i = 0; i < t.size; i++)
	{
		if (t.table[i].idxTI < 100)
		{
			if ((idif.table[t.table[i].idxTI].idtype == IT::F) &&
				(strcmp(idif.table[t.table[i].idxTI].id, Unicode) != 0) &&
				(strcmp(idif.table[t.table[i].idxTI].id, RandN) != 0) &&
				(t.table[i - 2].lexema[0] == 'f'))
			{
				IT::Entry lexfun = idif.table[t.table[i].idxTI];
				int fnumer = t.table[i].idxTI;
				int nump = idif.table[t.table[i].idxTI].numOfPar;
				file << idif.table[t.table[i].idxTI].fun.namefun << " PROC ";
				for (int j = 0; j < idif.size; j++)
				{
					if (idif.table[j].idtype == IT::P && (strcmp(idif.table[t.table[i].idxTI].id, idif.table[j].fun.namefun) == 0))
					{
						nump--;
						if (nump != 0)
						{
							if (idif.table[j].iddatatype == IT::UNI)
								file << idif.table[j].id << ": DWORD, ";
							else if (idif.table[j].iddatatype == IT::CH)
								file << idif.table[j].id << ": DWORD, ";
						}

						else if (nump == 0)
						{
							{
								if (idif.table[j].iddatatype == IT::UNI)
									file << idif.table[j].id << ": DWORD\n";
								else if (idif.table[j].iddatatype == IT::CH)
									file << idif.table[j].id << ": DWORD\n";
							}
							break;
						}
					}
				}
				while (t.table[i].lexema[0] != '}')
				{
					if (t.table[i - 1].lexema[0] == '=')
					{
						LT::Entry lex = t.table[i - 2];
						int pos1 = i;
						while (t.table[i].lexema[0] != ';')
						{
							if (t.table[i].lexema[0] == 'i')
							{
								if (idif.table[t.table[i].idxTI].idtype == IT::V)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::P)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::F)
								{
									int numofp = idif.table[t.table[i].idxTI].numOfPar;
									int l = i;
									i++;
									while (t.table[i].lexema[0] != '@')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										i++;
									}
									file << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
									if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
										strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
									{
										file << "\tpush eax\n";
									}
									else
									{
										file << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id;
									}
								}
							}
							if (t.table[i].lexema[0] == 'l')
							{
								file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							if (t.table[i].operators[0] == '+')
							{
								file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '-')
							{
								file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
							}
							else if (t.table[i].operators[0] == '*')
							{
								file << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '>')
							{
								if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
									file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
								else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
									file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '<')
							{
								if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
									file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
								else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
									file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
							}
							i++;
						}
						file << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
					}
					if (t.table[i].lexema[0] == 'c')
					{
						if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::TEN)
							file << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Ten << '\n';
						else if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::SIXTEEN)
							file << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Six << '\n';
						int met = i;
						file << "CYRCLE" << met << ":\n";
						file << "push ecx\n";
						while (t.table[i].lexema[0] != ']')
						{
							if (t.table[i - 1].lexema[0] == '=')
							{
								LT::Entry lex = t.table[i - 2];
								int pos1 = i;
								while (t.table[i].lexema[0] != ';')
								{
									if (t.table[i].lexema[0] == 'i')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::P)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::F)
										{
											int numofp = idif.table[t.table[i].idxTI].numOfPar;
											int l = i;
											i++;
											while (t.table[i].lexema[0] != '@')
											{
												if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
												{
													file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
												}
												else if (idif.table[t.table[i].idxTI].idtype == IT::V)
												{
													file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
												}
												i++;
											}
											file << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
											if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
												strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
											{
												file << "\tpush eax\n";
											}
											else
											{
												file << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
											}
										}
									}
									if (t.table[i].lexema[0] == 'l')
									{
										file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									if (t.table[i].operators[0] == '+')
									{
										file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '-')
									{
										file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
									}
									else if (t.table[i].operators[0] == '*')
									{
										file << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '>')
									{
										if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
											file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
										else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
											file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '<')
									{
										if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
											file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
										else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
											file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
									}
									i++;
								}
								file << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
							}
							if (t.table[i].lexema[0] == 'o')
							{
								file << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
								if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
									file << "\tcall WriteInConsoleChar\n";
								else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
									file << "\tcall WriteInConsoleUnint\n";
							}
							i++;
						}
						file << "pop ecx\n";
						file << "LOOP CYRCLE" << met << '\n';
					}
					if (t.table[i].lexema[0] == 'o')
					{
						file << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
							file << "\tcall WriteInConsoleChar\n";
						else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
							file << "\tcall WriteInConsoleUnint\n";
					}
					if (t.table[i].lexema[0] == 'e')
					{
						if (idif.table[t.table[i + 1].idxTI].idtype == IT::P)
							file << "\tpush " << idif.table[t.table[i + 1].idxTI].id << '\n';
						else
							file << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
						file << "\tpop " << "ret_" << lexfun.id << '\n';
					}
					i++;
				}
				file << "ret\n";
				file << idif.table[fnumer].id << " ENDP\n\n";
			}

			if (t.table[i].lexema[0] == 'm')
			{
				file << "main PROC\nSTART:\n";
				while (t.table[i].lexema[0] != '}')
				{
					if (t.table[i - 1].lexema[0] == '=')
					{
						LT::Entry lex = t.table[i - 2];
						int pos1 = i;
						while (t.table[i].lexema[0] != ';')
						{
							if (t.table[i].lexema[0] == 'i')
							{
								if (idif.table[t.table[i].idxTI].idtype == IT::V)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::P)
								{
									file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
								}
								else if (idif.table[t.table[i].idxTI].idtype == IT::F)
								{
									int numofp = idif.table[t.table[i].idxTI].numOfPar;
									int l = i;
									i++;
									while (t.table[i].lexema[0] != '@')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										i++;
									}
									file << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
									if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
										strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
									{
										file << "\tpush eax\n";
									}
									else
									{
										file << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
									}
								}
							}
							if (t.table[i].lexema[0] == 'l')
							{
								file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
							}
							if (t.table[i].operators[0] == '+')
							{
								file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '-')
							{
								file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
							}
							else if (t.table[i].operators[0] == '*')
							{
								file << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '>')
							{
								if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
									file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
								else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
									file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
							}
							else if (t.table[i].operators[0] == '<')
							{
								if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
									file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
								else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
									file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
							}
							i++;
						}
						file << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
					}
					if (t.table[i].lexema[0] == 'c')
					{
						if (t.table[i + 2].lexema[0] == 'l')
						{
							if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::TEN)
								file << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Ten << '\n';
							else if (idif.table[t.table[i + 2].idxTI].value.vint.predst == IT::SIXTEEN)
								file << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].value.vint.Six << '\n';
						}
						else if (t.table[i + 2].lexema[0] == 'i')
						{
							file << "\tmov ecx, " << idif.table[t.table[i + 2].idxTI].fun.namefun << idif.table[t.table[i + 2].idxTI].id << '\n';
						}
						int met = i;
						file << "CYRCLE" << met << ":\n";
						file << "push ecx\n";
						while (t.table[i].lexema[0] != ']')
						{
							if (t.table[i - 1].lexema[0] == '=')
							{
								LT::Entry lex = t.table[i - 2];
								int pos1 = i;
								while (t.table[i].lexema[0] != ';')
								{
									if (t.table[i].lexema[0] == 'i')
									{
										if (idif.table[t.table[i].idxTI].idtype == IT::V)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::P)
										{
											file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
										}
										else if (idif.table[t.table[i].idxTI].idtype == IT::F)
										{
											int numofp = idif.table[t.table[i].idxTI].numOfPar;
											int l = i;
											i++;
											while (t.table[i].lexema[0] != '@')
											{
												if (idif.table[t.table[i].idxTI].idtype == IT::P || idif.table[t.table[i].idxTI].idtype == IT::L)
												{
													file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
												}
												else if (idif.table[t.table[i].idxTI].idtype == IT::V)
												{
													file << "\tpush " << idif.table[t.table[i].idxTI].fun.namefun << idif.table[t.table[i].idxTI].id << "\n";
												}
												i++;
											}
											file << "\tcall " << idif.table[t.table[l].idxTI].fun.namefun << "\n";
											if (strcmp(idif.table[t.table[l].idxTI].id, RandN) == 0 ||
												strcmp(idif.table[t.table[l].idxTI].id, Unicode) == 0)
											{
												file << "\tpush eax\n";
											}
											else
											{
												file << "\tpush " << "ret_" << idif.table[t.table[l].idxTI].id << '\n';
											}
										}
									}
									if (t.table[i].lexema[0] == 'l')
									{
										file << "\tpush " << idif.table[t.table[i].idxTI].id << "\n";
									}
									if (t.table[i].operators[0] == '+')
									{
										file << "\tpop eax\n\tpop ebx\n\tadd eax, ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '-')
									{
										file << "\tpop eax\n\tpop ebx\n\tsub ebx, eax\n\tpush ebx\n";
									}
									else if (t.table[i].operators[0] == '*')
									{
										file << "\tpop eax\n\tpop ebx\n\tmul ebx\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '>')
									{
										if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
											file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
										else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
											file << "\tpop ebx\n\tpop eax\n\tshr eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
									}
									else if (t.table[i].operators[0] == '<')
									{
										if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::TEN)
											file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Ten << "\n\tpush eax\n";
										else if (idif.table[t.table[i - 1].idxTI].value.vint.predst == IT::SIXTEEN)
											file << "\tpop ebx\n\tpop eax\n\tshl eax, " << idif.table[t.table[i - 1].idxTI].value.vint.Six << "\n\tpush eax\n";
									}
									i++;
								}
								file << "\tpop " << idif.table[lex.idxTI].fun.namefun << idif.table[lex.idxTI].id << "\n";
							}
							if (t.table[i].lexema[0] == 'o')
							{
								file << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
								if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
									file << "\tcall WriteInConsoleChar\n";
								else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
									file << "\tcall WriteInConsoleUnint\n";
							}
							i++;
						}
						file << "pop ecx\n";
						file << "LOOP CYRCLE" << met << '\n';
					}
					if (t.table[i].lexema[0] == 'e')
					{
						file << "\n\tpush " << idif.table[t.table[i + 1].idxTI].id << '\n';
						file << "\tcall ExitProcess\n";
					}
					if (t.table[i].lexema[0] == 'o')
					{
						file << "\tpush " << idif.table[t.table[i + 1].idxTI].fun.namefun << idif.table[t.table[i + 1].idxTI].id << '\n';
						if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::CH)
							file << "\tcall WriteInConsoleChar\n";
						else if (idif.table[t.table[i + 1].idxTI].iddatatype == IT::UNI)
							file << "\tcall WriteInConsoleUnint\n";
					}
					i++;
				}
				file << "main" << " ENDP\n\nend main";
			}
		}
	}
	file.close();
}