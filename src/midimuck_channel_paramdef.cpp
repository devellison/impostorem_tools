/// midimuck_channel_paramdef.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//
#include "midimuck_channel_paramdef.h"

namespace impostorem
{
ChannelParamDef::ChannelParamDef(const wchar_t* name,
                                 const wchar_t* units,
                                 ImpParamId     id,
                                 ImpParamType   paramType,
                                 float          step,
                                 float          minVal,
                                 float          maxVal,
                                 float          defVal)
    : ImpParamDef(name, units, id, paramType, step, minVal, maxVal, defVal)
{}

/// fromString override - interprets "Unchanged" as 0.
float ChannelParamDef::fromString(const std::wstring& valStr) const
{
    if(valStr == L"Unchanged")
    {
        return 0.0;
    }
    return ImpParamDef::fromString(valStr);
}

/// toString override - returns "Unchanged" for 0 value.
std::wstring ChannelParamDef::toString(float normVal) const
{
    if(normVal < getNormalStepSize())
    {
        return L"Unchanged";
    }
    return ImpParamDef::toString(normVal);
}

}  // namespace impostorem
