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
	HMODULE GetModuleAddress(String Name);
	DWORD NHPID;
	//Memory Handling
	//Write
	bool WriteBool(UINT_PTR Address, bool Value);
	bool WriteShort(UINT_PTR Address, short Value);
	bool WriteInt(UINT_PTR Address, int Value);
	bool WriteInt64(UINT_PTR Address, long long Value);
	bool WriteFloat(UINT_PTR Address, float Value);
	bool WriteDouble(UINT_PTR Address, double Value);
	bool WriteByte(UINT_PTR Address, BYTE Value);
	bool WriteBytes(UINT_PTR Address, BYTE* Value, const size_t len);
	bool WriteChar(UINT_PTR Address, char Value);
	bool WriteString(UINT_PTR Address, String Value);
	//Read
	bool ReadBool(UINT_PTR Address);
	short ReadShort(UINT_PTR Address);
	int ReadInt(UINT_PTR Address);
	long long ReadInt64(UINT_PTR Address);
	float ReadFloat(UINT_PTR Address);
	double ReadDouble(UINT_PTR Address);
	BYTE ReadByte(UINT_PTR Address);
	BYTE* ReadBytes(UINT_PTR Address, const size_t len);
	char ReadChar(UINT_PTR Address);
	String ReadStringW(UINT_PTR Address, size_t len);
	String ReadString(UINT_PTR Address, size_t len);
};
