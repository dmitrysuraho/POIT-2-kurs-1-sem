#include <iostream>
#include <locale>
#include <cwchar>
#include <locale.h>

#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "PolishNotation.h"
#include "LEX.h"
#include "MFST.h"
#include "GRB.h"
#include "CodeGen.h"
#include "Semant.h"

using namespace std;

bool unint(char* c) {
	FST::FST myfst(
		c,
		6,
		FST::NODE(1, FST::RELATION('u', 1)),
		FST::NODE(1, FST::RELATION('n', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool ch(char* c) {
	FST::FST myfst(
		c,
		5,
		FST::NODE(1, FST::RELATION('c', 1)),
		FST::NODE(1, FST::RELATION('h', 2)),
		FST::NODE(1, FST::RELATION('a', 3)),
		FST::NODE(1, FST::RELATION('r', 4)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool funct(char* c) {
	FST::FST myfst(
		c,
		9,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),
		FST::NODE(1, FST::RELATION('i', 6)),
		FST::NODE(1, FST::RELATION('o', 7)),
		FST::NODE(1, FST::RELATION('n', 8)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool identificator(char* c) {
	FST::FST myfst(
		c,
		6,
		FST::NODE(1, FST::RELATION('i', 1)),
		FST::NODE(1, FST::RELATION('d', 2)),
		FST::NODE(1, FST::RELATION('e', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),
		FST::NODE(1, FST::RELATION('t', 5)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool end(char* c) {
	FST::FST myfst(
		c,
		4,
		FST::NODE(1, FST::RELATION('e', 1)),
		FST::NODE(1, FST::RELATION('n', 2)),
		FST::NODE(1, FST::RELATION('d', 3)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool o(char* c) {
	FST::FST myfst(
		c,
		4,
		FST::NODE(1, FST::RELATION('o', 1)),
		FST::NODE(1, FST::RELATION('u', 2)),
		FST::NODE(1, FST::RELATION('t', 3)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool ma(char* c) {
	FST::FST myfst(
		c,
		5,
		FST::NODE(1, FST::RELATION('m', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('n', 4)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool id(char* c) {
	FST::FST myfst(
		c,
		1,
		FST::NODE(27, FST::RELATION('A', 0), \
			FST::RELATION('B', 0), \
			FST::RELATION('C', 0), \
			FST::RELATION('D', 0), \
			FST::RELATION('E', 0), \
			FST::RELATION('F', 0), \
			FST::RELATION('G', 0), \
			FST::RELATION('H', 0), \
			FST::RELATION('I', 0), \
			FST::RELATION('J', 0), \
			FST::RELATION('K', 0), \
			FST::RELATION('L', 0), \
			FST::RELATION('M', 0), \
			FST::RELATION('N', 0), \
			FST::RELATION('O', 0), \
			FST::RELATION('P', 0), \
			FST::RELATION('Q', 0), \
			FST::RELATION('R', 0), \
			FST::RELATION('S', 0), \
			FST::RELATION('T', 0), \
			FST::RELATION('U', 0), \
			FST::RELATION('V', 0), \
			FST::RELATION('W', 0), \
			FST::RELATION('X', 0), \
			FST::RELATION('Y', 0), \
			FST::RELATION('Z', 0)), \
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool literalunintTEN(char* c) {
	FST::FST myfst(
		c,
		1,
		FST::NODE(10, FST::RELATION('0', 0), \
			          FST::RELATION('1', 0), \
			          FST::RELATION('2', 0), \
			          FST::RELATION('3', 0), \
			          FST::RELATION('4', 0), \
			          FST::RELATION('5', 0), \
			          FST::RELATION('6', 0), \
			          FST::RELATION('7', 0), \
			          FST::RELATION('8', 0), \
			          FST::RELATION('9', 0)), \
		              FST::NODE()
	);
	return (FST::execute(myfst));
}

bool literalunintSIXTEEN(char* c) {
	FST::FST myfst(
		c,
		3,
		FST::NODE(1, FST::RELATION('x', 1)),
		FST::NODE(17, FST::RELATION('0', 1), \
			FST::RELATION('1', 1), \
			FST::RELATION('2', 1), \
			FST::RELATION('3', 1), \
			FST::RELATION('4', 1), \
			FST::RELATION('5', 1), \
			FST::RELATION('6', 1), \
			FST::RELATION('7', 1), \
			FST::RELATION('8', 1), \
			FST::RELATION('9', 1), \
			FST::RELATION('a', 1), \
			FST::RELATION('b', 1), \
			FST::RELATION('c', 1), \
			FST::RELATION('d', 1), \
			FST::RELATION('e', 1), \
			FST::RELATION('f', 1), \
			FST::RELATION('x', 2)), \
		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool literalchar(char* c) {
	FST::FST myfst(
		c,
		3,
		FST::NODE(1, FST::RELATION('"', 1)), \
		FST::NODE(53, 
			FST::RELATION('a', 1), \
			FST::RELATION('b', 1), \
			FST::RELATION('c', 1), \
			FST::RELATION('d', 1), \
			FST::RELATION('e', 1), \
			FST::RELATION('f', 1), \
			FST::RELATION('g', 1), \
			FST::RELATION('h', 1), \
			FST::RELATION('i', 1), \
			FST::RELATION('j', 1), \
			FST::RELATION('k', 1), \
			FST::RELATION('l', 1), \
			FST::RELATION('m', 1), \
			FST::RELATION('n', 1), \
			FST::RELATION('o', 1), \
			FST::RELATION('p', 1), \
			FST::RELATION('q', 1), \
			FST::RELATION('r', 1), \
			FST::RELATION('s', 1), \
			FST::RELATION('t', 1), \
			FST::RELATION('u', 1), \
			FST::RELATION('v', 1), \
			FST::RELATION('w', 1), \
			FST::RELATION('x', 1), \
			FST::RELATION('y', 1), \
			FST::RELATION('z', 1), \
			FST::RELATION('A', 1), \
			FST::RELATION('B', 1), \
			FST::RELATION('C', 1), \
			FST::RELATION('D', 1), \
			FST::RELATION('E', 1), \
			FST::RELATION('F', 1), \
			FST::RELATION('G', 1), \
			FST::RELATION('H', 1), \
			FST::RELATION('I', 1), \
			FST::RELATION('J', 1), \
			FST::RELATION('K', 1), \
			FST::RELATION('L', 1), \
			FST::RELATION('M', 1), \
			FST::RELATION('N', 1), \
			FST::RELATION('O', 1), \
			FST::RELATION('P', 1), \
			FST::RELATION('Q', 1), \
			FST::RELATION('R', 1), \
			FST::RELATION('S', 1), \
			FST::RELATION('T', 1), \
			FST::RELATION('U', 1), \
			FST::RELATION('V', 1), \
			FST::RELATION('W', 1), \
			FST::RELATION('X', 1), \
			FST::RELATION('Y', 1), \
			FST::RELATION('Z', 1), \
			FST::RELATION('"', 2)), \

		FST::NODE()

	);

	return (FST::execute(myfst));
}

bool Uni(char* c) {
	FST::FST myfst(
		c,
		8,
		FST::NODE(1, FST::RELATION('U', 1)),
		FST::NODE(1, FST::RELATION('n', 2)),
		FST::NODE(1, FST::RELATION('i', 3)),
		FST::NODE(1, FST::RELATION('c', 4)),
		FST::NODE(1, FST::RELATION('o', 5)),
		FST::NODE(1, FST::RELATION('d', 6)),
		FST::NODE(1, FST::RELATION('e', 7)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}


bool RandNum(char* c) {
	FST::FST myfst(
		c,
		8,
		FST::NODE(1, FST::RELATION('R', 1)),
		FST::NODE(1, FST::RELATION('a', 2)),
		FST::NODE(1, FST::RELATION('n', 3)),
		FST::NODE(1, FST::RELATION('d', 4)),
		FST::NODE(1, FST::RELATION('N', 5)),
		FST::NODE(1, FST::RELATION('u', 6)),
		FST::NODE(1, FST::RELATION('m', 7)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}

bool fr(char* c) {
	FST::FST myfst(
		c,
		4,
		FST::NODE(1, FST::RELATION('f', 1)),
		FST::NODE(1, FST::RELATION('o', 2)),
		FST::NODE(1, FST::RELATION('r', 3)),

		FST::NODE()
	);
	return (FST::execute(myfst));
}


int wmain(int argc, wchar_t* argv[])
{
	setlocale(LC_ALL, "RUS");

	LT::LexTable t = LT::Create(1000);
	IT::IdTable idif = IT::Create(100);

	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);

		log = Log::getlog(parm.log);
		Log::WriteLine(log, "Тест:", "без ошибок", "");
		Log::WriteLog(log);
		Log::WriteParm(log, parm);

		In::IN in = In::getin(parm.in);
		
		
		LexAnaliz(in, t, idif);
		out = Out::getout(parm.out);

		MFST::Mfst mfst(t, GRB::getGreibach());
		mfst.start(out);
		mfst.savededucation();
		mfst.printrules(out);

		WriteInOut(out, in, t, idif);

		Semant(t, idif, log);

		PolishNotation(t, idif);
		WriteInOut(out, in, t, idif);

		CodeGeneration(t, idif);
		Out::CloseOut(out);
		Log::WriteIn(log, in);
		cout << "Все готово!" << endl;
		
		/*system("C:\\Users\\Dmitry\\Desktop\\labrab\\PL\\Kyrs\\SDA-2019\\SDA-2019\\StartAssembler.bat");*/
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
		cout << "Ошибка! Загляните в log.txt." << endl << endl;
	};
	Log::Close(log);
	LT::Delete(t);
	IT::Delete(idif);
	return 0;
}