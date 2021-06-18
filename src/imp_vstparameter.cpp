/// midimuck_vstparameter.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "imp_vstparameter.h"
#include "pluginterfaces/base/ustring.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace impostorem
{

ImpVstParameter::ImpVstParameter(const ImpParamDef* def)
    : m_def(def)
{
    Steinberg::UString(info.title, USTRINGSIZE(info.title)).assign(USTRING(m_def->name().c_str()));
    Steinberg::UString(info.units, USTRINGSIZE(info.units)).assign(USTRING(m_def->units().c_str()));

    info.id                     = m_def->id();
    info.defaultNormalizedValue = m_def->getNormalDefVal();

    info.flags = ParameterInfo::kCanAutomate;
    if(info.id == impostorem::kBypassId)
        info.flags |= ParameterInfo::kIsBypass;

    info.stepCount = m_def->numSteps();
    info.unitId    = kRootUnitId;

    setNormalized(m_def->getNormalDefVal());
}

void ImpVstParameter::toString(ParamValue normValue, String128 string) const
{
    Steinberg::String str = m_def->toString(valueNormalized).c_str();
    str.copyTo(string);
}

bool ImpVstParameter::fromString(const TChar* string, ParamValue& normValue) const
{
    normValue = m_def->fromString(string);
    return kResultOk;
}


}  // namespace impostorem
