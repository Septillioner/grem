#include "grem.h"

grem::grem() {

}
grem::grem(String Name) {
	this->HandleProcessByName(Name);
}
grem::grem(DWORD PID) {
	this->HandleProcessByID(PID);
}
BOOL grem::HandleProcessByID(DWORD PID) {
	if (PID != NULL) {
		this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		NHPID = PID;
		return true;
	}
	else {
		return false;
	}
}
BOOL grem::HandleProcessByName(String Name) {
	DWORD PID;
	if (this->GetPIDByName(Name, &PID)) {
		this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
		NHPID = PID;
		return true;
	}
	else {
		return false;
	}
}
BOOL grem::GetPIDByName(String Name, DWORD *PID) {
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return 1;
	}
	cProcesses = cbNeeded / sizeof(DWORD);
	for (i = 0; i < cProcesses; i++)
	{
		if (aProcesses[i] != 0)
		{
			TCHAR processName[MAX_PATH];
			if (this->GetProcessNameByPID(aProcesses[i], processName)) {
				String pname(processName);
				if (Name == pname) {
					*PID = aProcesses[i];
					return true;
				}
			}
		}
	}
	return false;
}
BOOL grem::GetProcessNameByPID(DWORD processID, TCHAR* szProcessName)
{

	BOOL bRC = FALSE;

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				MAX_PATH);

			bRC = TRUE;
		}
	}

	CloseHandle(hProcess);

	return bRC;
}

DWORD grem::GetModuleAddress(String Name) {
	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];


			if (K32GetModuleBaseNameA(hProcess, hMods[i], szModName,
				sizeof(szModName) / sizeof(TCHAR)))
			{
				String modulename(szModName);
				if (strcmp(modulename.c_str(), Name.c_str()) == 0) {
					return (DWORD)hMods[i];
				}

			}
		}
	}


	return 0x0;
}

#pragma region WriteMem
bool grem::WriteBool(DWORD Address, bool Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(bool),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteShort(DWORD Address, short Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(short),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteInt(DWORD Address, int Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(int),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteInt64(DWORD Address, long long Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(long long),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteFloat(DWORD Address, float Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(float),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteDouble(DWORD Address, double Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(double),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteByte(DWORD Address, BYTE Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(BYTE),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteChar(DWORD Address, char Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(char),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteString(DWORD Address, String Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(DWORD)sizeof(Value),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
#pragma endregion

#pragma region ReadMem
bool grem::ReadBool(DWORD Address) {
	short Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(bool),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return 0;
	}
}
short grem::ReadShort(DWORD Address) {
	short Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(short),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return 0;
	}
}
int grem::ReadInt(DWORD Address) {
	int Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(int),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return 0;
	}
}
long long grem::ReadInt64(DWORD Address) {
	long long Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(long long),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return 0;
	}
}
float grem::ReadFloat(DWORD Address) {
	float Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(float),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return (float)0;
	}
}
double grem::ReadDouble(DWORD Address) {
	double Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(double),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return (double)0;
	}
}
BYTE grem::ReadByte(DWORD Address) {
	BYTE Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(BYTE),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return (BYTE)0;
	}
}
char grem::ReadChar(DWORD Address) {
	char Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		sizeof(char),
		NULL
	)) {
		return Value;
	}
	else {
		ReadAccess = 0;
		return (char)0;
	}
}
String grem::ReadString(DWORD Address, size_t len) {
	char* Value;
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		len,
		0
	)) {
		return String(Value);
	}
	else {
		ReadAccess = 0;
		return String();
		return String();
	}
}
#pragma endregion
