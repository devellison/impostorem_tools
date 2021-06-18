/// imp_utils.h
///
///
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

namespace impostorem
{

/// _ImpTrace - generic debugging function, outputs to DebugOutputString on windows.
///             Meant to be used via the IMPTRACE() macro.
///
/// \param file - ASCIIZ string with filename
/// \param line - the line number of the call
/// \param msg - printf-style formatting message
/// \param ... - formatting arguments for msg
void _ImpTrace(const char* file, int line, const char* msg, ...);


/// IMPTRACE debug message macro
/// Sends traces with file/line to debug output using printf-style formatting
///
/// \param msg - printf-style formatting message
/// \param ... - formatting arguments
#define IMPTRACE(msg, ...) _ImpTrace(__FILE__, __LINE__, msg, ##__VA_ARGS__)

}  // namespace impostorem
