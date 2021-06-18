/// midimuck_processor.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include <vector>
#include "pluginterfaces/vst/ivstevents.h"
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "midimuck.hpp"

namespace impostorem
{

/// Event/Audio processing class for MIDIMuck VST
class MidiMuckProcessor : public Steinberg::Vst::AudioEffect
{
public:
    MidiMuckProcessor();
    ~MidiMuckProcessor() SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (Steinberg::Vst::IAudioProcessor*)new MidiMuckProcessor;
    }

    // AudioEffect Overrides
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

    /// Delayed events
    /// When the delay is on, we queue events until it's time to pass them through
    struct DelayedEvent
    {
        Steinberg::int64      delay;     ///< Delay time in samples
        Steinberg::Vst::Event theEvent;  ///< Event to send
    };

protected:
    MidiMuck                  m_muck;    ///< Main MIDIMuck logic object
    std::vector<DelayedEvent> m_events;  ///< Event queue for delayed events
};

}  // namespace impostorem
