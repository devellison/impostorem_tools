/// imp_param.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "imp_param.h"


namespace impostorem
{


ImpParam::ImpParam(const ImpParamDef* paramDef)
    : m_paramDef(paramDef)
    , m_normal(paramDef->getNormalDefVal())
{}

float ImpParam::getNormal() const
{
    return m_normal;
}
void ImpParam::setNormal(float newVal)
{
    m_normal = newVal;
}

int32_t ImpParam::intValue() const
{
    return static_cast<int32_t>(m_paramDef->denormalize(m_normal));
}

float ImpParam::value() const
{
    return m_paramDef->denormalize(m_normal);
}

}  // namespace impostorem