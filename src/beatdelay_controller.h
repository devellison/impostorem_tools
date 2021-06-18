/// beatdelay_controller.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "beatdelay.h"
#include "imp_resource.h"
#include "imp_vstparameter.h"
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "vstgui/uidescription/uidescription.h"

namespace impostorem
{

class BeatDelayController : public Steinberg::Vst::EditControllerEx1
{
public:
    BeatDelayController();

    ~BeatDelayController() SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (Steinberg::Vst::IEditController*)new BeatDelayController;
    }

    // IPluginBase overrides
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;

    // EditController overrides
    Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setParamNormalized(Steinberg::Vst::ParamID    tag,
                                                     Steinberg::Vst::ParamValue value) SMTG_OVERRIDE;

    DEFINE_INTERFACES
    END_DEFINE_INTERFACES(EditController)
    DELEGATE_REFCOUNT(EditController)

protected:
    ImpVstParameter*      m_vstParams[BeatDelay::kNumParameters];  ///< Parameter table
    ImpResource           m_uiResource;
    VSTGUI::UIDescription m_uiDesc;
};

}  // namespace impostorem
