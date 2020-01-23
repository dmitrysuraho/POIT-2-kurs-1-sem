#pragma once
#define LEXEMA_FIXSIZE 1			// ������������� ������ �������
#define LT_MAXSIZE  4096			// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX 0xfffffff		// ��� �������� ������� ���������������
#define LEX_INTEGER		't'			// ������� ��� integer
#define LEX_STRING		't'			// ������� ��� string
#define LEX_ID			'i'			// ������� ��� ��������������
#define LEX_LITERAL		'l'			// ������� ��� ��������
#define LEX_FUNCTION	'f'			// ������� ��� function	
#define LEX_DECLARE		'd'			// ������� ��� declare
#define LEX_RETURN		'r'			// ������� ��� return
#define LEX_PRINT		'p'			// ������� ��� print
#define LEX_MAIN        'm'         // ������� ��� main
#define LEX_SEMICOLON	';'			// ������� ��� ;
#define LEX_COMMA		','			// ������� ��� ,
#define LEX_LEFTBRACE	'{'			// ������� ��� {
#define LEX_BRACELET	'}'			// ������� ��� }
#define LEX_LEFTHESIS	'('			// ������� ��� (
#define LEX_RIGHTHESIS	')'			// ������� ��� )
#define LEX_PLUS		'v'			// ������� ��� +
#define LEX_MINUS		'v'			// ������� ��� -
#define LEX_STAR		'v'			// ������� ��� *
#define LEX_DIRSLASH	'v'			// ������� ��� /
#define LEX_EQUALLY	    '='			// ������� ��� =
#define LEX_SUBSTR      'i'         // ������� ��� substr()
#define LEX_STRLEN      'i'         // ������� ��� strlen()

namespace LT						// ������� ������
{
	enum INTORSTR { INTEGER = 1, STRING = 2, DEF = 0 };
	struct Entry					// ������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE];	// �������
		int sn;						    // ����� ������ � �������� ������
		int idxTI;	    			    // ������ � ������� ��������������� ��� LT_TI_NULLIDX
		INTORSTR IntOrStr;
	};

	struct LexTable					// ��������� ������� ������
	{
		int maxsize;				// ������� ������� ������ < LT_MAXSIZE
		int size;					// ������� ������ ������� ������ < maxsize
		Entry* table;				// ������ ����� ������� ������
	};
	LexTable Create(				// ������� ������� ������
		int size				// ������� ������� ������ < LT_MAXSIZE
	);
	void Add(						// �������� ������ � ������� ������
		LexTable& lextable,			// ��������� ������ ������
		Entry entry					// ������ ������� ������
	);

	Entry GetEntry(					// �������� ������ ������� ������
		LexTable& lextable,		// ��������� ������� ������
		int n					// ����� ���������� ������
	);
	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)
};