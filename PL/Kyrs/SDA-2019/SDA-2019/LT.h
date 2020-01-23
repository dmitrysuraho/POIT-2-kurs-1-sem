#pragma once
#define LEXEMA_FIXSIZE 1			 // ������������� ������ �������
#define LT_MAXSIZE  4096			 // ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX -1	 // ��� �������� ������� ���������������
#define LEX_UNINT		  't'		 // ������� ��� unint
#define LEX_CHAR		  't'		 // ������� ��� char
#define LEX_ID			  'i'		 // ������� ��� ��������������
#define LEX_LITERAL		  'l'		 // ������� ��� ��������
#define LEX_FUNCTION	  'f'		 // ������� ��� function	
#define LEX_IDENTIFICATOR 'd'		 // ������� ��� ident
#define LEX_END		      'e'		 // ������� ��� end
#define LEX_OUT		      'o'		 // ������� ��� out
#define LEX_MAIN          'm'        // ������� ��� main
#define LEX_SEMICOLON	  ';'		 // ������� ��� ;
#define LEX_COMMA		  ','		 // ������� ��� ,
#define LEX_LEFTBRACE	  '{'		 // ������� ��� {
#define LEX_BRACELET	  '}'	     // ������� ��� }
#define LEX_LEFTHESIS	  '('		 // ������� ��� (
#define LEX_RIGHTHESIS	  ')'		 // ������� ��� )
#define LEX_PLUS		  'v'		 // ������� ��� +
#define LEX_STAR		  'v'		 // ������� ��� *
#define LEX_LEFT          'v'        // ������� ��� <<
#define LEX_RIGHT         'v'        // ������� ��� >>
#define LEX_EQUALLY	      '='		 // ������� ��� =
#define LEX_RANDNUM       'i'        // ������� ��� RandNum()
#define LEX_UNICODE       'i'        // ������� ��� Unicode()
#define LEX_FOR           'c'        // ������� ��� for
#define LEX_SQR           '['        // ������� ��� [
#define LEX_SQL           ']'        // ������� ��� ]

namespace LT						 // ������� ������
{
	enum INTORSTR { UNINT = 1, CHAR = 2, DEF = 0 };
	struct Entry					// ������ ������� ������
	{
		char lexema[LEXEMA_FIXSIZE];	// �������
		int sn;						// ����� ������ � �������� ������
		int idxTI;	    			// ������ � ������� ��������������� ��� LT_TI_NULLIDX
		INTORSTR IntOrStr;
		char operators[1];
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