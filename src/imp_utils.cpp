/// imp_utils.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "imp_utils.h"
#include <sstream>
#include <vector>
#include "imp_platform.h"

namespace impostorem
{

void _ImpTrace(const char* file, int line, const char* msg, ...)
{
    // Switch to std::format when available...
    va_list vaArgs;
    va_start(vaArgs, msg);
    va_list vaArgsCopy;
    va_copy(vaArgsCopy, vaArgs);

    int length = std::vsnprintf(NULL, 0, msg, vaArgsCopy);
    va_end(vaArgsCopy);

    std::vector<char> msgBuf(length + 1);
    std::vsnprintf(msgBuf.data(), msgBuf.size(), msg, vaArgs);
    va_end(vaArgs);

    std::string msgString(msgBuf.data(), msgBuf.size() - 1);

    std::stringstream logString;
    logString << file << "(" << line << "): " << msgString << std::endl;

#ifdef _WIN32
    ::OutputDebugStringA(logString.str().c_str());
#else
    printf("%s", logString.c_str());
#endif
}

}  // namespace impostorem