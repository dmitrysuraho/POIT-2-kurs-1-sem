#include <Windows.h>
#include <lmcons.h>
#include <iostream>
#include <locale.h>

using namespace std;

void main()
{
	setlocale(LC_CTYPE, "rus");

	int n;
	char dd[4];
	DWORD dr = GetLogicalDrives();

	for (int i = 0; i < 26; i++)
	{
		n = ((dr >> i) & 0x00000001);
		if (n == 1)
		{
			dd[0] = char(65 + i); dd[1] = ':'; dd[2] = '\ ';
				dd[3] = 0;
			cout << "Available disk drives : " << dd << endl;
		}
	}

	cout << endl;

	int d;
	d = GetDriveType("c:\ " );
		if (d == DRIVE_UNKNOWN)
			cout << " UNKNOWN" << endl;
	if (d == DRIVE_NO_ROOT_DIR)
		cout << " DRIVE NO ROOT DIR" << endl;
	if (d == DRIVE_REMOVABLE)
		cout << " REMOVABLE" << endl;
	if (d == DRIVE_FIXED)
		cout << " FIXED" << endl;
	if (d == DRIVE_REMOTE)
		cout << " REMOTE" << endl;
	if (d == DRIVE_CDROM)
		cout << " CDROM" << endl;
	if (d == DRIVE_RAMDISK)
		cout << " RAMDISK" << endl;

	cout << endl;

	char VolumeNameBuffer[100];
	char FileSystemNameBuffer[100];
	unsigned long VolumeSerialNumber;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(
		"c:\ ",
		VolumeNameBuffer,
		100,
		&VolumeSerialNumber,
		NULL, //&MaximumComponentLength,
		NULL, //&FileSystemFlags,
		FileSystemNameBuffer,
		100
	);
	if (GetVolumeInformationFlag != 0)
	{
		cout << " Volume Name is " << VolumeNameBuffer << endl;
		cout << " Volume Serial Number is " << VolumeSerialNumber << endl;
		cout << " File System is " << FileSystemNameBuffer << endl;
	}
	else
		cout << " Not Present (GetVolumeInformation)" << endl;


	cout << endl;


	DWORD FreeBytesAvailable;
	DWORD TotalNumberOfBytes;
	DWORD TotalNumberOfFreeBytes;

	BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
		"d:\ ",
		(PULARGE_INTEGER)& FreeBytesAvailable,
		(PULARGE_INTEGER)& TotalNumberOfBytes,
		(PULARGE_INTEGER)& TotalNumberOfFreeBytes
	);

	if (GetDiskFreeSpaceFlag != 0)
	{
		cout << " Total Number Of Free Bytes = " << (unsigned long)TotalNumberOfFreeBytes << "( " << double(unsigned long(TotalNumberOfFreeBytes)) / 1024 / 1000 << " Mb )" << endl;

		cout << " Total Number Of Bytes = " << (unsigned long)TotalNumberOfBytes << "( " << double(unsigned long(TotalNumberOfBytes)) / 1024 / 1000
			<< " Mb )" << endl;
	}
	else
		cout << " Not Present (GetDiskFreeSpace)" << endl;

	cout << endl;

	// The MemoryStatus structure is 32 bytes long.
    // It should be 32.
    // 78 percent of memory is in use.
    // There are 65076 total Kbytes of physical memory.
    // There are 13756 free Kbytes of physical memory.
    // There are 150960 total Kbytes of paging file.
    // There are 87816 free Kbytes of paging file.
    // There are 1fff80 total Kbytes of virtual memory.
    // There are 1fe770 free Kbytes of virtual memory.

#define DIV 1024
#define WIDTH 7
	char divisor[2] = "K";
	MEMORYSTATUS stat;

	GlobalMemoryStatus(&stat);
	printf("The MemoryStatus structure is %ld bytes long\n", stat.dwLength);
	printf("It should be %d\n", sizeof(stat));
	printf("%ld percent of memory is in use\n", stat.dwMemoryLoad);
	printf("There are %*ld total %sbytes of physical memory\n", WIDTH, stat.dwTotalPhys / DIV, divisor);
	printf("There are %*ld free %sbytes of physical memory\n", WIDTH, stat.dwAvailPhys / DIV, divisor);
	printf("There are %*ld total %sbytes of paging file\n", WIDTH, stat.dwTotalPageFile / DIV, divisor);
	printf("There are %*ld free %sbytes of paging file\n", WIDTH, stat.dwAvailPageFile / DIV, divisor);
	printf("There are %*lx total %sbytes of virtual memory\n", WIDTH, stat.dwTotalVirtual / DIV, divisor);
	printf("There are %*lx free %sbytes of virtual memory\n", WIDTH, stat.dwAvailVirtual / DIV, divisor);

	cout << endl;

	char ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	unsigned long len_ComputerName = MAX_COMPUTERNAME_LENGTH + 1;
	char UserName[UNLEN + 1];
	unsigned long len_UserName = UNLEN + 1;

	BOOL comp = GetComputerName(
		ComputerName,
		&len_ComputerName
	);
	if (comp != 0)
		cout << "Computer Name is " << ComputerName << endl;
	else
		cout << "Computer Name is NOT FOUND !!! " << endl;

	comp = GetUserNameA(UserName, &len_UserName);
	if (comp != 0)
		cout << "User Name is " << UserName << endl;
	else
		cout << "User Name is NOT FOUND !!! " << endl;

	cout << endl;

	char path[100];

	GetSystemDirectory(path, 100);
	cout << "System Directory is " << path << endl;

	GetTempPath(100, path);
	cout << "Temp path is " << path << endl;

	GetWindowsDirectory(path, 100);
	cout << "Windows directory is " << path << endl;

	GetCurrentDirectory(100, path);
	cout << "Current directory is " << path << endl;
	
	system("pause");
}