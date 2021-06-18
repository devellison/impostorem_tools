/// imp_param_def.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "imp_param_def.h"


namespace impostorem
{

ImpParamDef::ImpParamDef(const wchar_t* name,
                         const wchar_t* units,
                         ImpParamId     id,
                         ImpParamType   paramType,
                         float          step,
                         float          minVal,
                         float          maxVal,
                         float          defVal)
    : m_name(name)
    , m_units(units)
    , m_id(id)
    , m_paramType(paramType)
    , m_step(step)
    , m_minVal(minVal)
    , m_maxVal(maxVal)
    , m_defVal(defVal)
{}

const std::wstring& ImpParamDef::name() const
{
    return m_name;
}
const std::wstring& ImpParamDef::units() const
{
    return m_units;
}

ImpParamId ImpParamDef::id() const
{
    return m_id;
}
ImpParamType ImpParamDef::type() const
{
    return m_paramType;
}

float ImpParamDef::range() const
{
    return m_maxVal - m_minVal;
}

int ImpParamDef::numSteps() const
{
    return static_cast<int32_t>(floor(range() / m_step));
}

float ImpParamDef::getNormalStepSize() const
{
    return 1.0f / static_cast<float>(numSteps());
}

float ImpParamDef::normalize(float value) const
{
    return (value - m_minVal) / range();
}

float ImpParamDef::denormalize(float value) const
{
    return value * range() + m_minVal;
}

float ImpParamDef::getNormalDefVal() const
{
    return normalize(m_defVal);
}

float ImpParamDef::fromString(const std::wstring& valStr) const
{
    float retVal = 0.0f;
    swscanf(valStr.c_str(), L"%f", &retVal);
    return normalize(retVal);
}

std::wstring ImpParamDef::toString(float normVal) const
{
    wchar_t buffer[32];

    float val = denormalize(normVal);
    switch(m_paramType)
    {
    case ImpParamType::kFloat:
        swprintf(buffer, 32, L"%f", val);
        break;
    case ImpParamType::kInt32:
        swprintf(buffer, 32, L"%d", static_cast<int32_t>(val));
        break;
    }
    std::wstring resultStr = buffer;
    return resultStr;
}

//------------------------------------------------------------------------
// ImpParamDefMod

ImpParamDefMod::ImpParamDefMod(const wchar_t* name,
                               const wchar_t* units,
                               ImpParamId     id,
                               ImpParamType   paramType,
                               float          step,
                               float          minVal,
                               float          maxVal,
                               float          defVal)
    : ImpParamDef(name, units, id, paramType, step, minVal, maxVal, defVal)
{}

// fromString override - interprets "Unchanged" as 0.
float ImpParamDefMod::fromString(const std::wstring& valStr) const
{
    if(valStr == L"Unchanged")
    {
        return normalize(0);
    }
    return ImpParamDef::fromString(valStr);
}

// toString override - returns "Unchanged" for 0 denormalized value.
std::wstring ImpParamDefMod::toString(float normVal) const
{
    float denormalized = denormalize(normVal);
    if(static_cast<int32_t>(denormalized) == 0)
    {
        return L"Unchanged";
    }

    return ImpParamDef::toString(normVal);
}

}  // namespace impostorem