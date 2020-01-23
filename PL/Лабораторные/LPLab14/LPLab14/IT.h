#pragma once
#define ID_MAXSIZE 5 // ������������ ���������� �������� � ��������������
#define TI_MAXSIZE 4096 // ������������ ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT 0x00000000 // �������� �� ��������� ��� ���� integer
#define TI_STR_DEFAULT 0x00 // �������� �� ��������� ��� ���� string
#define TI_NULLIDX 0xffffffff // ��� �������� ������� ���������������
#define TI_STR_MAXSIZE 255


namespace IT // ������� ���������������
{
	enum IDDATATYPE { INT = 1, STR = 2 }; // ���� ������ ���������������: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // ���� ���������������: ����������, �������, ��������, �������
	struct Entry // ������ ������� ���������������
	{
		/*int idxfirstLE; */   // ������ ������ ������ � ������� ������
		char id[10]; // ������������� (������������� ��������� �� ID_MAXSIZE)
		int numOfid;
		IDDATATYPE iddatatype; // ��� ������
		IDTYPE idtype; // ��� ��������������
		struct FUNCTION
		{
			char namefun[10];
			int numfun;
		}fun;
		union
		{
			int vint; // �������� integer
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

	int IsLitStr(
		IdTable& idtable,
		char id[100]
	);

	int IsLitInt(
		IdTable& idtable,
		int id[100],
		int k
	);

	int IsSubstr(
		IdTable& idtable,
		char id[100]
	);

	int IsStrlen(
		IdTable& idtable,
		char id[100]
	);

	void Delete(IdTable& lextable); // ������� ������� ��������������� (���������� ������)
};