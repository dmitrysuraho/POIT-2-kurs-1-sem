#pragma once 
#pragma warning(disable : 4996) 
#include<iostream> 

namespace FST {
	struct RELATION { // �����:������ -> ������� ����� �������� �� 
		char symbol; // ������ �������� 
		short nnode; // ����� ������� ������� 
		RELATION(
			char c = 0x00, // ������ �������� 
			short ns = NULL // ����� ��������� 
		);
	};

	struct NODE // ������� ����� 
	{
		short n_relation; // ���������� ����������� ����� 
		RELATION* relations; // ����������� ����� 
		NODE();
		NODE(
			short n, // ���������� ����������� ����� 
			RELATION rel, ... // ������ ����� 
		);
	};

	struct FST { // ������������������� �������� ������� 

		char* string; //�������(������,����������� 0�00) 
		short position; // ������� ������� � ������� 
		short nstates; // ���������� ��������� �������� 
		NODE* nodes; // ���� ���������: [0] -��������� ���������,[nstate-1] - �������� 
		short* rstates; // ��������� ��������� �������� �� ������ ������� 
		FST(
			char* s, //�������(������,����������� 0�00) 
			short ns, // ���������� ��������� �������� 
			NODE n, ... // ������ ���������(���� ���������) 
		);
	};

	bool execute( // ��������� ������������� ������� 
		FST& fst // ������������������� �������� ������� 
	);
}
bool integ(char* c);
bool stri(char* c);
bool funct(char* c);
bool declare(char* c);
bool ret(char* c);
bool pri(char* c);
bool ma(char* c);
bool subs(char* c);
bool strl(char* c);
bool id(char* c);
bool literalinteger(char* c);
bool literalstring(char* c);
