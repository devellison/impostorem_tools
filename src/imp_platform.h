/// imp_platform.h
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

// Note: per MSDN docs, _WIN32 is defined for both Win32 and Win64
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <shellapi.h>
#endif

#include <cstdint>

namespace impostorem
{
/// Open an external URL in a browser
/// \param url - the URL to open
void ImpOpenExternUrl(const char* url);

/// Retrieve an application resource's size and memory address
/// \param resource - resource identifier
/// \param size - ref to receive the resource size
/// \param ptr - ref to receive a pointer to the resource memory
bool GetResource(int resource, size_t& size, int8_t*& ptr);

/// Frees a resource
/// Note: On Windows, this doesn't actually do anything except null the ptr, as the OS frees the resource per MSDN on
/// exit.
///
/// \param ptr - the pointer to the resource memory. Set to nullptr on return.
void FreeResource(int8_t*& ptr);
}  // namespace impostorem