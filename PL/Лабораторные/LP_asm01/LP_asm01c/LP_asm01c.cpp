#include <iostream>

using namespace std;

extern "C"
{
	int __stdcall getmin(int*, int);
	int __stdcall getmax(int*, int);
};
	
int main(int argc, char* argv[])
{
	int mass[10] = { 11, 44, 10, 39, 5, 22, 12, 100, 50, 33 };
	int num = 10;
	cout << "getmax - getmin = " << getmax(mass, num) - getmin(mass, num);
	return 0;
}