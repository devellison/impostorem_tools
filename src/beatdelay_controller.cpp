/// beatdelay_controller.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "beatdelay_controller.h"
#include "base/source/fstreamer.h"
#include "base/source/fstring.h"
#include "beatdelay.h"
#include "beatdelay_ids.h"
#include "imp_platform.h"
#include "beatdelay_version.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"
#include "resource.h"
#include "vstgui/plugin-bindings/vst3editor.h"

using namespace Steinberg;
using namespace Steinberg::Vst;

namespace impostorem
{


BeatDelayController::BeatDelayController()
    : Steinberg::Vst::EditControllerEx1()
    , m_uiResource(IDR_BEATDELAYUI)
    , m_uiDesc(&m_uiResource)
{
    IMPTRACE("BeatDelayController created.");
}

BeatDelayController::~BeatDelayController()
{
        IMPTRACE("BeatDelayController destroyed");
}

tresult PLUGIN_API BeatDelayController::initialize(FUnknown* context)
{
    tresult result = EditControllerEx1::initialize(context);
    if(result != kResultOk)
    {
        return result;
    }

    // Register our parameters from the table.
    const ImpParamDef** defs = &BeatDelay::kParamDefs[0];
    while(*defs)
    {
        m_vstParams[(*defs)->id()] = new ImpVstParameter(*defs);
        parameters.addParameter(m_vstParams[(*defs)->id()]);

        defs++;
    }
    return result;
}

tresult PLUGIN_API BeatDelayController::terminate()
{
    return EditControllerEx1::terminate();
}

tresult PLUGIN_API BeatDelayController::setComponentState(IBStream* state)
{
    if(!state)
        return kResultFalse;



    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs     = &BeatDelay::kParamDefs[0];
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

Steinberg::tresult PLUGIN_API BeatDelayController::setParamNormalized(Steinberg::Vst::ParamID    tag,
                                                            Steinberg::Vst::ParamValue value)
{
    switch(tag)
    {
    // Handle button presses
    case BeatDelay::kImpostoremId:
        if(value > 0.99)
        {
            ImpOpenExternUrl(stringCompanyUrl);
        }
        break;
    case BeatDelay::kBeatDelayId:
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

IPlugView* PLUGIN_API BeatDelayController::createView(FIDString name)
{
    IMPTRACE("Create view: %s", name);
    if(FIDStringsEqual(name, Vst::ViewType::kEditor))
    {
        auto* view = new VSTGUI::VST3Editor(&m_uiDesc, this, "view");
        IMPTRACE("Created view for editor at %p", view);
        return view;
    }
    return nullptr;
}

}  // namespace impostorem
