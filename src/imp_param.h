/// imp_param.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include <cstdint>
#include <string>
#include "imp_param_def.h"

namespace impostorem
{
static constexpr const int kBypassId = 0;
/// ImpParam - Parameters for plugins
///
/// ImpParams are generic named parameter objects that store a value in a
/// normalized form (0.0 - 1.0) and can translate those values to
/// an integer or floating point value based on a range and step size.
///
/// Mostly intended for use in DAWs or GUIs.
class ImpParam
{
public:
    /// ImpParam constructor from ImpParamDef
    /// \param paramDef - parameter definition
    ImpParam(const ImpParamDef* paramDef);

    /// Retrieve the normalized value
    /// \return float - normalized value for the param (0.0-1.0)
    float getNormal() const;

    /// Set the value from a normalized value
    /// \param newVal - normalized value to set from
    void setNormal(float newVal);

    /// Retrieve the denormalized integer value of the parameter
    /// \return int32_t - denormalized integer parameter value
    int32_t intValue() const;

    /// Retrieve the denormalized floating point value of the parameter
    /// \return float - denormalized floating point parameter value
    float value() const;

protected:
    float              m_normal;    ///< Normalized value of the parameter
    const ImpParamDef* m_paramDef;  ///< Parameter definition
};

}  // namespace impostorem
