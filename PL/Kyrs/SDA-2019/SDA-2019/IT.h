#pragma once
#define ID_MAXSIZE 2 // ������������ ���������� �������� � ��������������
#define TI_MAXSIZE 4096 // ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000 // �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT 0x00 // �������� �� ��������� ��� ���� string
#define TI_NULLIDX 0xffffffff // ��� �������� ������� ���������������
#define TI_STR_MAXSIZE 255

using namespace std;

namespace IT // ������� ���������������
{
	enum IDDATATYPE { UNI = 1, CH = 2 }; // ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // ���� ���������������: ����������, �������, ��������, �������
	enum PR { TEN = 1, SIXTEEN = 2 };
	struct Entry // ������ ������� ���������������
	{
		/*int idxfirstLE; */   // ������ ������ ������ � ������� ������
		char id[15]; // ������������� (������������� ��������� �� ID_MAXSIZE)
		int numOfid;
		int numOfPar;
		int parType[20];
		IDDATATYPE iddatatype; // ��� ������
		IDTYPE idtype; // ��� ��������������
		struct FUNCTION
		{
			char namefun[15];
			int numfun;
		}fun;
		union
		{
			struct
			{
				PR predst;
				int Ten;
				char Six[10];
			}vint;
			struct
			{
				int len; // ���������� �������� � string
				char str[TI_STR_MAXSIZE - 1]; // ������� string
			}vstr; // �������� string
		}value; // �������� ���������������
	};

	struct IdTable // ��������� ������� ����������������
	{
		int maxsize; // ������� ������� ��������������� < LT_MAXSIZE
		int size; // ������� ������ ������� ��������������� < maxsize
		Entry* table; // ������ ����� ������� ���������������
	};
	IdTable Create( // ������� ������� ���������������
		int size // ������� ������� ��������������� < LT_MAXSIZE
	);
	void Add( // �������� ������ � ������� ���������������
		IdTable& idxtable, // ��������� ������� ���������������
		Entry entry // ������ ������� ���������������
	);

	Entry GetEntry( // �������� ������ ������� ���������������
		IdTable& idtable, // ��������� ������� ���������������
		int n // ����� ���������� ������
	);
	int IsId( // �������: ����� ������( ���� ����), TI_NULLIDX( ���� ���)
		IdTable& idtable, // ��������� ������� ���������������
		char id[10] //�������������
	);

	int IsRandNum(IdTable& idtable, char id[100]);

	int IsUnicode(IdTable& idtable, char id[100]);

	int IsLitChar(IdTable& idtable, char id[100]);

	int IsLitUnintTEN(IdTable& idtable, int numb, int k);

	int IsLitUnintSIXTEEN(IdTable& idtable, char numb[10]);

	void Delete(IdTable& lextable); // ������� ������� ��������������� (���������� ������)
};