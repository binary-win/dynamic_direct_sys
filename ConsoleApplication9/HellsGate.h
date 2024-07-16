#pragma once
#include<Windows.h>
#include<stdio.h>




struct SYSCALL_INFO
{
	DWORD ssn;
	PVOID addr;
};




DWORD HASHER(char* funcname);
HMODULE  modulebase(WCHAR*);
PVOID GetExportfunc(HMODULE);
PVOID  GetModuleaddress(HMODULE hmodule, LPCSTR lpApiName);






