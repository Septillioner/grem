#pragma once
#include <string>
#include<Windows.h>
#include <psapi.h>
#include <future>
#include <stdio.h>
#include <iostream>
#ifndef UNICODE  
typedef std::string String;
#else
typedef std::wstring String;
#endif

class grem {
public:
	grem();
	grem(String Name);
	grem(DWORD PID);
	//Process Handling
	HANDLE hProcess;
	BOOL ReadAccess = true;
	BOOL WriteAccess = true;
	BOOL HandleProcessByID(DWORD PID);
	BOOL HandleProcessByName(String  Name);
	BOOL GetPIDByName(String Name, DWORD *PID);
	BOOL GetProcessNameByPID(DWORD PID, TCHAR* szProcessName);
	DWORD GetModuleAddress(String Name);
	DWORD NHPID;
	//Memory Handling
	//Write
	bool WriteBool(DWORD Address, bool Value);
	bool WriteShort(DWORD Address, short Value);
	bool WriteInt(DWORD Address, int Value);
	bool WriteInt64(DWORD Address, long long Value);
	bool WriteFloat(DWORD Address, float Value);
	bool WriteDouble(DWORD Address, double Value);
	bool WriteByte(DWORD Address, BYTE Value);
	bool WriteChar(DWORD Address, char Value);
	bool WriteString(DWORD Address, String Value);
	//Read
	bool ReadBool(DWORD Address);
	short ReadShort(DWORD Address);
	int ReadInt(DWORD Address);
	long long ReadInt64(DWORD Address);
	float ReadFloat(DWORD Address);
	double ReadDouble(DWORD Address);
	BYTE ReadByte(DWORD Address);
	char ReadChar(DWORD Address);
	String ReadString(DWORD Address, size_t len);
};
