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
	int points = 0, //������� �����
		numbers = 0;//������� ���� ������
	char* buff;
	buff = new char[3];
	for (int i = 0; ip[i] != '\0'; i++)//����������� IP-�����
	{
		if (ip[i] <= '9' && ip[i] >= '0') //���� ������ �����
		{
			if (numbers > 3) return false; //�� ������ 3
			buff[numbers++] = ip[i];
			//�������� � �����
		}
		else if (ip[i] == '.') //���� ��������� �����
		{
			if (atoi(buff) > 255) return false;
			//������ 255 � ������
			if (numbers == 0) return false;
			//���� ���� ���
			numbers = 0; //�������� ������� ���� ������
			points++;
			buff = new char[3];
		}
		else return false;
	}
	if (points != 3) return false;
	//���� ����� ������ 3 - ������
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
	//��� ����� ��������� ��������� �������, �����, �����, ����
		return true;
}

int GetNetBiosName(char* dwIpAddr)
{
	ADAPTER_STATUS* pStatus; //������ ��������
	NAME_BUFFER* pNames; //��������� ��� NetBios
	NCB ncb; //��������� NetBios
	HANDLE hHeap;
	WORD cbBuffer;
	char* Addr;
	UCHAR rc;
	int i;
	//�������� IP-����� � ��������� ����
	in_addr in;
	if (dwIpAddr == 0) return 0;
	in.s_addr = inet_addr(dwIpAddr);
	Addr = inet_ntoa(in);
	if (!Addr) return 0;
	//�������� ��� ������ LANA
	LANA_ENUM lan_num; //������������ ���� lana
	//�������������/������� ��������� NCB
	ZeroMemory(&ncb, sizeof(NCB));
	ncb.ncb_command = NCBENUM;
	//���������� ��� ��� ���������� LANA_ENUM ���������
	ncb.ncb_buffer = (unsigned char*)&lan_num;
	ncb.ncb_length = sizeof(lan_num); //������
	rc = Netbios(&ncb); //������� �������
	for (i = 0; i < lan_num.length; i++)
		//��� ������� LANA
	{
		//�������������/�������137
		ZeroMemory(&ncb, sizeof(NCB));
		//����� ���� �������� � LANA, ������������� � ���������
		//LANA_ENUM � ������������� ������� NetBIOS-�����
		ncb.ncb_command = NCBRESET;
		ncb.ncb_lana_num = lan_num.lana[i];
		//���������� ����� LAN�
		rc = Netbios(&ncb); //������� �������
		hHeap = GetProcessHeap();
		//����� ��� ������ �������� + ������ ����(255 ����)
		cbBuffer = sizeof(ADAPTER_STATUS)
			+ 255 * sizeof(NAME_BUFFER);
		//�������� ���� ������ ��� ���� � ���������������� 0
		pStatus = (ADAPTER_STATUS*)HeapAlloc
		(hHeap, HEAP_ZERO_MEMORY, cbBuffer);
		if (pStatus == NULL) return 0;
		//�������������/������� ��������� NCB
		ZeroMemory(&ncb, sizeof(NCB));
		ncb.ncb_command = NCBASTAT;
		//������� ������ ��������
		ncb.ncb_lana_num = lan_num.lana[i];//��� i LANA
		ncb.ncb_buffer = (PUCHAR)pStatus;
		ncb.ncb_length = cbBuffer;
		strcpy((char*)ncb.ncb_callname, Addr);//��� IP
		rc = Netbios(&ncb); //������� �������
		if (ncb.ncb_retcode == NRC_GOODRET)
			//���� ���������� ��� NetBios
		{
			pNames = (NAME_BUFFER*)(pStatus + 1);
			printf("\n ����� NetBios:\n");
			for (i = 0; i < pStatus->name_count; i++)
			{
				//������� ��� �� �������
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
		if (!flag) cout << "�������� IP" << endl;
		cout << "������� IP-����� ��� DNS-���: ";
		cin >> host; //������
		if (is_ip = !isalpha(host[0]))
			//���� ������ - �� �����130
			flag = CheckAddr(host);
		//��������� �����
		else
			flag = true;
	} while (!flag);
	if (!is_ip) //���� �����
	{
		do
		{
			if (!flag)
			{
				cout << "�������� DNS-���" << endl;
				cout << "������� DNS-���: ";
				cin >> host; //������
			}
			flag = CheckDNSName(host);
			//��������� DNS
		} while (!flag);
	}
	if (is_ip)
	{
		addr.S_un.S_addr = inet_addr(host); //��������������
		dns = gethostbyaddr((char*)&addr, 4, AF_INET);
		if (dns != NULL) //���� ��������� ���������,
		{
			cout << "DNS ���: " << dns->h_name << endl;
			//������� ��� �����
			while (dns->h_addr_list[i] != 0)
			{
				//������ ������ ������� �����
				addr.S_un.S_addr =
					*(u_long*)dns->h_addr_list[i++];
				cout << " " << inet_ntoa(addr);
			}
		}
		else
		{
			cout << "DNS ��� �� �������..." << endl;
		}
		GetNetBiosName(inet_ntoa(addr));
	}
	else {
		dns = gethostbyname(host);
		if (dns != NULL) {
			cout << "DNS ���: " << dns->h_name << endl;
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
			cout << "DNS ��� �� �������..." << endl;
		}
	}
	WSACleanup();
}