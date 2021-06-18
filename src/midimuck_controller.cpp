/// midimuck_controller.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "midimuck_controller.h"
#include "imp_platform.h"
#include "midimuck_ids.h"
#include "midimuck_version.h"
#include "pluginterfaces/base/ustring.h"
#include "resource.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "midimuck.hpp"


using namespace Steinberg;
using namespace Steinberg::Vst;

namespace impostorem
{

// MIDIMuckController
MidiMuckController::MidiMuckController()
    : Steinberg::Vst::EditControllerEx1()
    , m_uiResource(IDR_MIDIMUCKUI)
    , m_uiDesc(&m_uiResource)
{
    IMPTRACE("MIDMuckController created");
}

MidiMuckController::~MidiMuckController()
{
    IMPTRACE("MIDMuckController destroyed");
}

tresult PLUGIN_API MidiMuckController::initialize(FUnknown* context)
{
    tresult result = EditControllerEx1::initialize(context);
    if(result != kResultOk)
    {
        return result;
    }

    // Register our parameters from the table.
    const ImpParamDef** defs = &MidiMuck::kParamDefs[0];
    while(*defs)
    {
        m_vstParams[(*defs)->id()] = new ImpVstParameter(*defs);
        parameters.addParameter(m_vstParams[(*defs)->id()]);

        defs++;
    }

    return result;
}

tresult PLUGIN_API MidiMuckController::terminate()
{
    return EditControllerEx1::terminate();
}

tresult PLUGIN_API MidiMuckController::setComponentState(IBStream* state)
{
    if(!state)
        return kResultFalse;

    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs     = &MidiMuck::kParamDefs[0];
    float               tmpFloat = 0.0;

    while(*defs)
    {
        if(streamer.readFloat(tmpFloat) == false)
        {
            return kResultFalse;
        }
        setParamNormalized((*defs)->id(), tmpFloat);

        defs++;
    }
    return kResultOk;
}

Steinberg::tresult PLUGIN_API MidiMuckController::setParamNormalized(Steinberg::Vst::ParamID    tag,
                                                                     Steinberg::Vst::ParamValue value)
{
    switch(tag)
    {
    // If Min/Max would be flipped, raise/lower the one that's NOT being edited currently to match.
    case MidiMuck::kMinNoteId:
        if(value > m_vstParams[MidiMuck::kMaxNoteId]->getNormalized())
        {
            EditControllerEx1::setParamNormalized(MidiMuck::kMaxNoteId, value);
        }
        break;
    case MidiMuck::kMaxNoteId:
        if(value < m_vstParams[MidiMuck::kMinNoteId]->getNormalized())
        {
            EditControllerEx1::setParamNormalized(MidiMuck::kMinNoteId, value);
        }
        break;
    // Handle button presses
    case MidiMuck::kImpostoremId:
        if(value > 0.99)
        {
            ImpOpenExternUrl(stringCompanyUrl);
        }
        break;
    case MidiMuck::kMidiMuckId:
        if(value > 0.99)
        {
            ImpOpenExternUrl(stringSoftwareUrl);
        }
        break;
    default:
        break;
    }

    return EditControllerEx1::setParamNormalized(tag, value);
}

IPlugView* PLUGIN_API MidiMuckController::createView(FIDString name)
{
    IMPTRACE("Create view: %s", name);
    // Create editor views...
    if(FIDStringsEqual(name, Vst::ViewType::kEditor))
    {
        auto* view = new VSTGUI::VST3Editor(&m_uiDesc, this, "view");
        IMPTRACE("Created view for editor at %p", view);
        return view;
    }
    return nullptr;
}

}  // namespace impostorem
