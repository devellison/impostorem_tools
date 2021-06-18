/// imp_platform.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "imp_platform.h"


#ifdef _WIN32

// Win64 only right now.
extern HINSTANCE ghInst;

namespace impostorem
{

void ImpOpenExternUrl(const char* url)
{
    ShellExecuteA(0, 0, url, 0, 0, SW_SHOW);
}

bool GetResource(int resource, size_t& size, int8_t*& ptr)
{
    HINSTANCE hInst = ghInst;  // ::GetModuleHandle(NULL);
    HRSRC     hres  = ::FindResource(hInst, MAKEINTRESOURCE(resource), L"UIDESC");
    if(NULL == hres)
    {
        return false;
    }

    // per MSDN, resHandle is a fake HGLOBAL and does not need to be released later.
    HGLOBAL resHandle = ::LoadResource(hInst, hres);
    if(NULL == resHandle)
    {
        return false;
    }

    size = ::SizeofResource(hInst, hres);
    ptr  = reinterpret_cast<int8_t*>(::LockResource(resHandle));
    return true;
}


void FreeResource(int8_t*& ptr)
{
    if(ptr)
    {
        // Per MSDN, no need to free loaded/locked resources.
        ptr = nullptr;
    }
}

}  // namespace impostorem
#endif  // _WIN32
