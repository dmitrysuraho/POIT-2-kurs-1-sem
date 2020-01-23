#pragma once 
#pragma warning(disable : 4996) 
#include<iostream> 

namespace FST {
	struct RELATION { // ребро:символ -> вершина графа перехода КА 
		char symbol; // символ перехода 
		short nnode; // номер смежной вершины 
		RELATION(
			char c = 0x00, // символ перехода 
			short ns = NULL // новое состояние 
		);
	};

	struct NODE // вершина графа 
	{
		short n_relation; // колияество инцидентных ребер 
		RELATION* relations; // инцидентные ребра 
		NODE();
		NODE(
			short n, // количество инцидентных ребер 
			RELATION rel, ... // список ребер 
		);
	};

	struct FST { // недетерминированный конечный автомат 

		char* string; //цепочка(строка,завершается 0х00) 
		short position; // текущая позиция в цепочке 
		short nstates; // количество состояний автомата 
		NODE* nodes; // граф переходов: [0] -начальное состояние,[nstate-1] - конечное 
		short* rstates; // возможные состояния автомата на данной позиции 
		FST(
			char* s, //цепочка(строка,завершается 0х00) 
			short ns, // количество состояний автомата 
			NODE n, ... // список состояний(граф переходов) 
		);
	};

	bool execute( // выполнить распознование цепочки 
		FST& fst // недетерминированный конечный автомат 
	);
}
bool unint(char* c);
bool ch(char* c);
bool Uni(char* c);
bool funct(char* c);
bool identificator(char* c);
bool end(char* c);
bool o(char* c);
bool ma(char* c);
bool RandNum(char* c);
bool id(char* c);
bool literalunintTEN(char* c);
bool literalunintSIXTEEN(char* c);
bool literalchar(char* c);
bool fr(char* c);
