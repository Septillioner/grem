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
				
				if (lstrcmpW(Name.c_str(), pname.c_str()) == 0) {
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

HMODULE grem::GetModuleAddress(String Name) {
	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;
	LPWSTR szModName = new wchar_t[MAX_PATH];

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			
			
			if (K32GetModuleBaseNameW(hProcess, hMods[i], szModName,
				MAX_PATH / sizeof(wchar_t)))
			{
				if (lstrcmpW((const wchar_t*)szModName, Name.c_str()) == 0) {
					return (HMODULE)hMods[i];
				}

			}
		}
	}


	return 0x0;
}

#pragma region WriteMem
bool grem::WriteBool(UINT_PTR Address, bool Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(bool),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteShort(UINT_PTR Address, short Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(short),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteInt(UINT_PTR Address, int Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(int),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteInt64(UINT_PTR Address, long long Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(long long),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteFloat(UINT_PTR Address, float Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(float),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteDouble(UINT_PTR Address, double Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(double),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteByte(UINT_PTR Address, BYTE Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(BYTE),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteBytes(UINT_PTR Address, BYTE* Value,const size_t len) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		Value,
		len,
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteChar(UINT_PTR Address, char Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(char),
		NULL
	) > 0) {
		return true;
	}
	else {
		return false;
	}
}
bool grem::WriteString(UINT_PTR Address, String Value) {
	if (WriteProcessMemory(
		hProcess,
		(LPVOID)Address,
		&Value,
		(UINT_PTR)sizeof(Value),
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
bool grem::ReadBool(UINT_PTR Address) {
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
short grem::ReadShort(UINT_PTR Address) {
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
int grem::ReadInt(UINT_PTR Address) {
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
long long grem::ReadInt64(UINT_PTR Address) {
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
float grem::ReadFloat(UINT_PTR Address) {
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
double grem::ReadDouble(UINT_PTR Address) {
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
BYTE grem::ReadByte(UINT_PTR Address) {
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
BYTE* grem::ReadBytes(UINT_PTR Address, const size_t len) {
	BYTE* Value = new BYTE[len];
	if (!ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		Value,
		len,
		NULL
	)) {
		ReadAccess = 0;
	}
	else {
	}
	return Value;
}
char grem::ReadChar(UINT_PTR Address) {
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
String grem::ReadStringW(UINT_PTR Address, size_t len) {
	wchar_t* Value;
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
String grem::ReadString(UINT_PTR Address, size_t len) {
	char* Value = new char[len+1];
	wchar_t* ValueW = new wchar_t[len+1];
	if (ReadProcessMemory(
		hProcess,
		(LPCVOID)Address,
		&Value,
		len,
		0
	)) {
		const char* s_ = Value;
		mbstowcs(ValueW, s_, len + 1);
		return String(ValueW);
	}
	else {
		ReadAccess = 0;
		return String();
		return String();
	}
}
#pragma endregion
