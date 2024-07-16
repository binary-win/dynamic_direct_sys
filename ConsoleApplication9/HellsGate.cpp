#include"HellsGate.h"
#include"structures.h"
#include<iostream>

//from atlasldr
DWORD HASHER(char* funcname) {
	ULONG HASH = 0;
	HASH = 33;
	wchar_t c = 0;
	while ((c = *funcname++))
	{
		if (c >= L'A' && c <= L'Z') {
			c += (int)(L'a' - L'A');
		}
		HASH = c + (HASH << 6) + (HASH << 16) - HASH;

	}
	//printf("%u\n", HASH);
	return HASH;
}



HMODULE modulebase(WCHAR* name)
{	
	PPEB pPeb = (PPEB)__readgsqword(0x60);
	PPEB_LDR_DATA ldr = (PPEB_LDR_DATA)(pPeb->Ldr);
	PLDR_DATA_TABLE_ENTRY dte = (PLDR_DATA_TABLE_ENTRY)ldr->InLoadOrderModuleList.Flink;

	PLIST_ENTRY node= (PLIST_ENTRY)&pPeb->Ldr->InInitializationOrderModuleList.Flink;

		while (dte)
		{
				if (dte->FullDllName.Length != NULL) {
					if (_wcsicmp(dte->FullDllName.Buffer, name)==0) {
						wprintf(L"[+] Found Dll \"%s\" \n\n", dte->FullDllName.Buffer);

						return (HMODULE)dte->DllBase;
					}


					//dte = (PLDR_DATA_TABLE_ENTRY)node->Flink;
					//node= (PLIST_ENTRY)node->Flink;
					dte = *(PLDR_DATA_TABLE_ENTRY*)(dte);
					
				}

				
		}


	return NULL;
}


PVOID GetExportfunc(HMODULE modulebase)
{
	PBYTE base = (PBYTE)modulebase;
	PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)base;
	PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(base + dos->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY exp = (PIMAGE_EXPORT_DIRECTORY)(base + nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	PDWORD addrname=(PDWORD)(base+exp->AddressOfNames);
	PDWORD addrfunc =(PDWORD)(base + exp->AddressOfFunctions);
	PWORD addrordin =(PWORD)(base + exp->AddressOfNameOrdinals);
	
	for (DWORD i = 0; exp->NumberOfFunctions; i++) {
		char* name = (char*)(base + addrname[i]);
		PVOID funcaddr = (PVOID)(base + addrfunc[addrordin[i]]);
		printf("%s:\n Address of functions: %p\n", name,funcaddr);
			//return funcaddr;
		
	}
	return NULL;
}

PVOID GetModuleaddress(HMODULE hmodule, LPCSTR lpApiName) {
	PBYTE pBase = (PBYTE)hmodule;

	PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)pBase;
	PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)(pBase + dos->e_lfanew);
	IMAGE_OPTIONAL_HEADER option = nt->OptionalHeader;

	PIMAGE_EXPORT_DIRECTORY Exp = (PIMAGE_EXPORT_DIRECTORY)(pBase + option.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	DWORD* funcname = (PDWORD)(pBase + Exp->AddressOfNames);
	DWORD* funcaddr = (PDWORD)(pBase + Exp->AddressOfFunctions);
	WORD* funcord = (PWORD)(pBase + Exp->AddressOfNameOrdinals);

	for (DWORD i = 0; i < Exp->NumberOfFunctions; i++) {
		char* names = (char*)(pBase + funcname[i]);
		PVOID address = nullptr;

		if (strcmp(names, lpApiName) == 0) {
			address = (PVOID)(pBase + funcaddr[funcord[i]]);
			std::cout << "[Ordinal " << funcord[i] + 8 << "] NAME: " << names << " - ADDRESS: 0x" << address << std::endl;
			return address;
		}
	}
}


//DWORD Getssn(PVOID addr) {
//	const byte syscall[] = { 0x0F, 0x05 };
//
//
//}







