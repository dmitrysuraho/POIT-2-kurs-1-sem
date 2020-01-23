#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <Winsock.h>
#include <Wsnetbs.h>
#include <locale>

#pragma comment(lib,"WS2_32.lib")
#pragma comment (lib, "Netapi32.lib")

using namespace std;

bool CheckAddr(char* ip)
{
	int points = 0, //счетчик точек
		numbers = 0;//счетчик цифр октета
	char* buff;
	buff = new char[3];
	for (int i = 0; ip[i] != '\0'; i++)//просмотреть IP-адрес
	{
		if (ip[i] <= '9' && ip[i] >= '0') //если только цифры
		{
			if (numbers > 3) return false; //не больше 3
			buff[numbers++] = ip[i];
			//записать в буфер
		}
		else if (ip[i] == '.') //если следующий октет
		{
			if (atoi(buff) > 255) return false;
			//больше 255 – ошибка
			if (numbers == 0) return false;
			//если цифр нет
			numbers = 0; //обнулить счетчик цифр октета
			points++;
			buff = new char[3];
		}
		else return false;
	}
	if (points != 3) return false;
	//если точек меньше 3 - ошибка
	if (numbers == 0 || numbers > 3) return false;
	return true;
}
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

int GetNetBiosName(char* dwIpAddr)
{
	ADAPTER_STATUS* pStatus; //Статус адаптера
	NAME_BUFFER* pNames; //Структура имя NetBios
	NCB ncb; //Структура NetBios
	HANDLE hHeap;
	WORD cbBuffer;
	char* Addr;
	UCHAR rc;
	int i;
	//Получаем IP-адрес в строковом виде
	in_addr in;
	if (dwIpAddr == 0) return 0;
	in.s_addr = inet_addr(dwIpAddr);
	Addr = inet_ntoa(in);
	if (!Addr) return 0;
	//Получить все номера LANA
	LANA_ENUM lan_num; //перечисление всех lana
	//Инициализация/очистка структуры NCB
	ZeroMemory(&ncb, sizeof(NCB));
	ncb.ncb_command = NCBENUM;
	//определить код для заполнения LANA_ENUM структуры
	ncb.ncb_buffer = (unsigned char*)&lan_num;
	ncb.ncb_length = sizeof(lan_num); //размер
	rc = Netbios(&ncb); //вызвать функцию
	for (i = 0; i < lan_num.length; i++)
		//для каждого LANA
	{
		//Инициализация/очистка137
		ZeroMemory(&ncb, sizeof(NCB));
		//Сброс всех сведений о LANA, перечисленных в структуре
		//LANA_ENUM и использование первого NetBIOS-имени
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lan_num.lana[i];
		//установить номер LANА
		rc = Netbios(&ncb); //вызвать функцию
		hHeap = GetProcessHeap();
		//буфер под статус адаптера + список имен(255 имен)
		cbBuffer = sizeof(ADAPTER_STATUS)
			+ 255 * sizeof(NAME_BUFFER);
		//выделить блок памяти для кучи и инициализировать 0
		pStatus = (ADAPTER_STATUS*)HeapAlloc
		(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
		if (pStatus == NULL) return 0;
		//Инициализация/очистка структуры NCB
		ZeroMemory(&ncb, sizeof(NCB));
		ncb.ncb_command = NCBASTAT;
		//извлечь статус адаптера
		ncb.ncb_lana_num = lan_num.lana[i];//для i LANA
		ncb.ncb_buffer = (PUCHAR)pStatus;
		ncb.ncb_length = cbBuffer;
		strcpy((char*)ncb.ncb_callname, Addr);//для IP
		rc = Netbios(&ncb); //вызвать функцию
		if (ncb.ncb_retcode == NRC_GOODRET)
			//если определено имя NetBios
		{
			pNames = (NAME_BUFFER*)(pStatus + 1);
			printf("\n Имена NetBios:\n");
			for (i = 0; i < pStatus->name_count; i++)
			{
				//вывести имя на консоль
				pNames->name[15] = '\0';
				printf("%d: %s\n", i + 1, pNames->name);
				pNames++;
			}
		}
		HeapFree(hHeap, 0, pStatus);
	}
	return 0;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	WSADATA WsaData;
	struct hostent* dns;
	struct hostent* netbios;
	char* host = new char[16];
	int i = 0;
	bool flag = true;
	bool is_ip = true;
	in_addr addr;
	if (WSAStartup(0x0202, &WsaData) == NULL)
		cout << "WSA done!" << endl;
	do
	{
		if (!flag) cout << "Неверный IP" << endl;
		cout << "Введите IP-адрес или DNS-имя: ";
		cin >> host; //ввести
		if (is_ip = !isalpha(host[0]))
			//если первый - не буква130
			flag = CheckAddr(host);
		//проверить адрес
		else
			flag = true;
	} while (!flag);
	if (!is_ip) //если буква
	{
		do
		{
			if (!flag)
			{
				cout << "Неверное DNS-имя" << endl;
				cout << "Введите DNS-имя: ";
				cin >> host; //ввести
			}
			flag = CheckDNSName(host);
			//проверить DNS
		} while (!flag);
	}
	if (is_ip)
	{
		addr.S_un.S_addr = inet_addr(host); //преобразование
		dns = gethostbyaddr((char*)&addr, 4, AF_INET);
		if (dns != NULL) //если структура заполнена,
		{
			cout << "DNS имя: " << dns->h_name << endl;
			//выводим имя хоста
			while (dns->h_addr_list[i] != 0)
			{
				//выодим список адресов хоста
				addr.S_un.S_addr =
					*(u_long*)dns->h_addr_list[i++];
				cout << " " << inet_ntoa(addr);
			}
		}
		else
		{
			cout << "DNS имя не найдено..." << endl;
		}
		GetNetBiosName(inet_ntoa(addr));
	}
	else {
		dns = gethostbyname(host);
		if (dns != NULL) {
			cout << "DNS имя: " << dns->h_name << endl;
			while (dns->h_addr_list[i] != 0)
			{
				addr.S_un.S_addr =
					*(u_long*)dns->h_addr_list[i++];
				cout << " " << inet_ntoa(addr) << endl;
			}
			addr.S_un.S_addr =
				*(u_long*)dns->h_addr_list[0];
			GetNetBiosName(inet_ntoa(addr));
		}
		else {
			cout << "DNS имя не найдено..." << endl;
		}
	}
	WSACleanup();
}