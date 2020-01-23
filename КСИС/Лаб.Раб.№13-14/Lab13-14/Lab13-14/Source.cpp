#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <Winsock.h>
#include <Wsnetbs.h>
#include <Iphlpapi.h>
#pragma comment(lib,"WS2_32.lib")
#pragma comment (lib, "Netapi32.lib")
#pragma comment(lib, "IPHlpApi.Lib")
using namespace std;

bool CheckDNSName(char* dns_name)
{
	for (int i = 0; dns_name[i] != '\0'; i++)
		if (!(dns_name[i] >= 'A' && dns_name[i] <= 'Z' ||
			dns_name[i] >= 'a' && dns_name[i] <= 'z' ||
			dns_name[i] >= '0' && dns_name[i] <= '9' ||
			dns_name[i] == '.' ||
			dns_name[i] == '-')) return false;
	//имя может содержать латинские символы, цифры, точки, тире
		return true;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");
	WSADATA WsaData;
	if (WSAStartup(0x0202, &WsaData) != NULL)
	{
		cout << "WSA Error!" << endl;
		return -1;
	}

	hostent* dns;
	char* host = new char[20];
	SOCKADDR_IN addr;
	SOCKET udp_sock;
	do
	{
		cout << "Host: ";
		cin >> host;
	} while (!CheckDNSName(host));
	dns = gethostbyname(host);
	if (dns == NULL)
	{
		cout << "Не найдено" << endl;
		return -1;
	}

	udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(1234);
	addr.sin_addr.S_un.S_addr =
		*(ULONG*)dns->h_addr_list[0];
	if (sendto(udp_sock, "TESR", 5, NULL, (SOCKADDR*)&addr,
		sizeof(addr)) == NULL)
	{
		cout << "Send" << endl;
		return -1;
	}

	MIB_IPNETTABLE* pTable =
		(MIB_IPNETTABLE*) new char[0xFFFF];
	ULONG cTable = 0xFFFF;
	if (GetIpNetTable(pTable, &cTable, true) != NO_ERROR)
	{
		cout << "MAC not found" << endl;
		return -1;
	}

	for (DWORD i = 0; i < pTable->dwNumEntries; i++)
	{
		if (pTable->table[i].dwAddr ==
			addr.sin_addr.S_un.S_addr
			&& pTable->table[i].dwType != 2)
		{
			printf("IP: %i.%i.%i.%i\nMAC: %X-%X-%X-%X-%X-%X\n",
				(int)addr.sin_addr.S_un.S_un_b.s_b1,
				(int)addr.sin_addr.S_un.S_un_b.s_b2,
				(int)addr.sin_addr.S_un.S_un_b.s_b3,
				(int)addr.sin_addr.S_un.S_un_b.s_b4,
				pTable->table[i].bPhysAddr[0],
				pTable->table[i].bPhysAddr[1],
				pTable->table[i].bPhysAddr[2],
				pTable->table[i].bPhysAddr[3],
				pTable->table[i].bPhysAddr[4],
				pTable->table[i].bPhysAddr[5]);
		}
	}
	closesocket(udp_sock);
	WSACleanup();
	
	return 0;
}