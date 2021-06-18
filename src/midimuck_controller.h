/// midimuck_controller.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "base/source/fstreamer.h"
#include "base/source/fstring.h"
#include "imp_resource.h"
#include "imp_vstparameter.h"
#include "pluginterfaces/base/ibstream.h"
#include "vstgui/uidescription/delegationcontroller.h"
#include "vstgui/uidescription/uidescription.h"
#include "midimuck.hpp"

namespace impostorem
{

/// Controller / UI for MIDIMuck
class MidiMuckController : public Steinberg::Vst::EditControllerEx1
{
public:
    /// MIDIMuck VST Controller constructor
    MidiMuckController();
    ~MidiMuckController() SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void*)
    {
        IMPTRACE("CreateInstance MIDIMuckController");
        return (Steinberg::Vst::IEditController*)new MidiMuckController;
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
    ImpVstParameter*      m_vstParams[MidiMuck::kNumParameters];  ///< Parameter table
    ImpResource           m_uiResource;                           ///< UI definition resource
    VSTGUI::UIDescription m_uiDesc;                               ///< UI definition
};

}  // namespace impostorem
