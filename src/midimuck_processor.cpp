/// midimuck_processor.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "midimuck_processor.h"
#include "base/source/fstreamer.h"
#include "midimuck_ids.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"


using namespace Steinberg;

namespace impostorem
{
MidiMuckProcessor::MidiMuckProcessor()
    : m_muck()
{
    IMPTRACE("MidiMuckProcessor created");
    setControllerClass(kMidiMuckControllerUID);
}

MidiMuckProcessor::~MidiMuckProcessor() 
{
    IMPTRACE("MidiMuckProcessor destroyed");
}

tresult PLUGIN_API MidiMuckProcessor::initialize(FUnknown* context)
{
    tresult result = AudioEffect::initialize(context);
    if(result != kResultOk)
    {
        return result;
    }

    addEventInput(STR16("Event In"), 16);
    addEventOutput(STR16("Event Out"), 16);
    return kResultOk;
}

tresult PLUGIN_API MidiMuckProcessor::terminate()
{
    return AudioEffect::terminate();
}

tresult PLUGIN_API MidiMuckProcessor::setActive(TBool state)
{
    return AudioEffect::setActive(state);
}

tresult PLUGIN_API MidiMuckProcessor::process(Vst::ProcessData& data)
{
    // Get parameter strings
    if(data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
        for(int32 index = 0; index < numParamsChanged; index++)
        {
            if(auto* paramQueue = data.inputParameterChanges->getParameterData(index))
            {
                Vst::ParamValue value;
                int32           sampleOffset;
                int32           numPoints = paramQueue->getPointCount();

                int32 paramId = paramQueue->getParameterId();
                if(paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue)
                {
                    m_muck.m_params[paramId]->setNormal(value);
                    break;
                }
            }
        }
    }

    // Process events
    int32 eventCount = data.inputEvents->getEventCount();
    for(int32 i = 0; i < eventCount; ++i)
    {
        Vst::Event e;
        if(kResultOk == data.inputEvents->getEvent(i, e))
        {
            float delay = 0.0f;

            switch(e.type)
            {
            // Right now we're ONLY processing note on/off events for Pianoshooter.  We may want to delay most events
            // if that functionality is extended....
            case Steinberg::Vst::Event::kNoteOnEvent:
                delay = m_muck.muckNote(
                    e.noteOn.pitch, e.noteOn.channel, data.processContext->tempo, data.processContext->sampleRate);
                break;
            case Steinberg::Vst::Event::kNoteOffEvent:
                delay = m_muck.muckNote(
                    e.noteOn.pitch, e.noteOn.channel, data.processContext->tempo, data.processContext->sampleRate);
                break;
            }

            // Delay < 0 means skip it.
            if(delay >= 0.0)
            {
                if(delay < FLT_EPSILON)
                {
                    if(kResultOk != data.outputEvents->addEvent(e))
                    {
                        IMPTRACE("Send event failed.");
                    }
                }
                else
                {
                    DelayedEvent de;
                    de.delay    = delay;
                    de.theEvent = e;
                    m_events.push_back(de);
                }
            }
        }
    }


    // Shoot out any events we've gotten
    auto iter = m_events.begin();
    while(iter != m_events.end())
    {
        iter->delay -= data.numSamples;
        if(iter->delay <= 0)
        {
            data.outputEvents->addEvent(iter->theEvent);
            iter = m_events.erase(iter);
            continue;
        }
        ++iter;
    }

    return kResultOk;
}

tresult PLUGIN_API MidiMuckProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
{
    return AudioEffect::setupProcessing(newSetup);
}

tresult PLUGIN_API MidiMuckProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
    // by default kSample32 is supported
    if(symbolicSampleSize == Vst::kSample32)
        return kResultTrue;

    return kResultFalse;
}

tresult PLUGIN_API MidiMuckProcessor::setState(IBStream* state)
{
    // Load a preset
    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs = &MidiMuck::kParamDefs[0];

    float tmpFloat = 0.0;

    while(*defs)
    {
        if(streamer.readFloat(tmpFloat) == false)
        {
            return kResultFalse;
        }
        m_muck.m_params[(*defs)->id()]->setNormal(tmpFloat);

        defs++;
    }

    return kResultOk;
}

tresult PLUGIN_API MidiMuckProcessor::getState(IBStream* state)
{
    // save preset
    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs = &MidiMuck::kParamDefs[0];

    while(*defs)
    {
        if(streamer.writeFloat(m_muck.m_params[(*defs)->id()]->getNormal()) == false)
        {
            return kResultFalse;
        }

        defs++;
    }


    return kResultOk;
}

}  // namespace impostorem
