#include "Include.h"

uintptr_t BaseModuless;
uintptr_t Engine;
char* namess[64];
class BaseM {
public:
	uintptr_t Base(){
		return BaseModuless = (uintptr_t)GetModuleHandle("client.dll");
	}
	uintptr_t Engine() {
		return BaseModuless = (uintptr_t)GetModuleHandle("engine.dll");
	}
	DWORD GetLocalPlayer() {
	
		
		return *(DWORD*)(Base() + dwLocalPlayer);
		
		
	}
	DWORD GetHealth() {
		return *(DWORD*)((DWORD)this + m_iHealth);
	}
	int GetFlag(){
		return *(int*)(GetLocalPlayer() + m_fFlags);

	}
	int IdAccaount() {
		return *(int*)((int)this + m_iAccountID);
	}
};