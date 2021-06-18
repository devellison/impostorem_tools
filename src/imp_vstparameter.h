/// imp_vstparameter.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "imp_param.h"
#include "pluginterfaces/vst/ivstmidicontrollers.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace impostorem
{

/// Bridge between Steinberg's Parameters and our internal ones.
class ImpVstParameter : public Steinberg::Vst::Parameter
{
public:
    /// Constructor
    /// The param definition should be from a static table and exist for the lifetime of the ImpVstParameter.
    /// If that changes, it needs to make a copy
    ImpVstParameter(const ImpParamDef* def);
    void toString(Steinberg::Vst::ParamValue normValue, Steinberg::Vst::String128 string) const SMTG_OVERRIDE;
    bool fromString(const Steinberg::Vst::TChar* string, Steinberg::Vst::ParamValue& normValue) const SMTG_OVERRIDE;

protected:
    const ImpParamDef* m_def;  ///< Pointer to parameter definition (must exist for lifetime of parameter!)
};


}  // namespace impostorem
