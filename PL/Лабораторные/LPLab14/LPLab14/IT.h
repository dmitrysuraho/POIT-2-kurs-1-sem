#pragma once
#define ID_MAXSIZE 5 // максимальное количество символов в идентификаторе
#define TI_MAXSIZE 4096 // максимальное количество строк в таблице идентификаторов
#define TI_INT_DEFAULT 0x00000000 // значение по умолчанию дл€ типа integer
#define TI_STR_DEFAULT 0x00 // значение по умолчанию дл€ типа string
#define TI_NULLIDX 0xffffffff // нет элемента таблицы идентификаторов
#define TI_STR_MAXSIZE 255


namespace IT // таблица идентификаторов
{
	enum IDDATATYPE { INT = 1, STR = 2 }; // типы данных идентификаторов: integer, string
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 }; // типы идентификаторов: переменна€, функци€, параметр, литерал
	struct Entry // строка таблицы идентификаторов
	{
		/*int idxfirstLE; */   // индекс первой строки в таблице лексем
		char id[10]; // идентификатор (автоматически усекаетс€ до ID_MAXSIZE)
		int numOfid;
		IDDATATYPE iddatatype; // тип данных
		IDTYPE idtype; // тип идентификатора
		struct FUNCTION
		{
			char namefun[10];
			int numfun;
		}fun;
		union
		{
			int vint; // значение integer
			struct
			{
				int len; // количество символов в string
				char str[TI_STR_MAXSIZE - 1]; // символы string
			}vstr; // значение string
		}value; // значение иденттификатора
	};

	struct IdTable // экземпл€р таблицы индентификаторов
	{
		int maxsize; // Ємкость таблицы идентификаторов < LT_MAXSIZE
		int size; // текущий размер таблицы идентификаторов < maxsize
		Entry* table; // массив строк таблицы идентификаторов
	};
	IdTable Create( // создать таблицу идентификаторов
		int size // Ємкость таблицы идентификаторов < LT_MAXSIZE
	);
	void Add( // добавить строку в таблицу идентификаторов
		IdTable& idxtable, // экземпл€р таблицы идентификаторов
		Entry entry // строка таблицы идентификаторов
	);

	Entry GetEntry( // получить строку таблицы идентификаторов
		IdTable& idtable, // экземпл€р таблицы идентификаторов
		int n // номер получаемой строки
	);
	int IsId( // возврат: номер строки( если есть), TI_NULLIDX( если нет)
		IdTable& idtable, // экземпл€р таблицы идентификаторов
		char id[10] //идентификатор
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

	void Delete(IdTable& lextable); // удалить таблицу идентификаторов (освободить пам€ть)
};