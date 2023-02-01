#include "Include.h"
#include "Features.hpp"

BOOL WINAPI ThreadMain(HMODULE module) {
    //Fetures
   
    Start::Start();
  
    return FALSE;
}

BOOL APIENTRY DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    LPVOID lpvReserved
) {
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ThreadMain, 0, 0, 0);
    case DLL_PROCESS_DETACH:
        break;
    
    }
    return TRUE;
}