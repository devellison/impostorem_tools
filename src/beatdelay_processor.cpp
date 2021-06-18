/// beatdelay_processor.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "beatdelay_processor.h"
#include "base/source/fstreamer.h"
#include "beatdelay_ids.h"
#include "imp_utils.h"
#include "pluginterfaces/vst/ivstevents.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

using namespace Steinberg;

namespace impostorem
{

BeatDelayProcessor::BeatDelayProcessor()
    : Steinberg::Vst::AudioEffect()
    , m_beatDelay()
    , m_buffer{0, 0}
    , m_curSampleRead(0)
    , m_curSampleWrite(0)
    , m_samplesDelay(0)
    , m_bufferLength(0)
    , m_sampleRate(BeatDelay::kDefSampleRate)
{
    IMPTRACE("BeatDelayProcessor created");
    setControllerClass(kBeatDelayControllerUID);
}

BeatDelayProcessor::~BeatDelayProcessor()
{
    freeBuffers();
    IMPTRACE("BeatDelayProcessor destroyed");
}

void BeatDelayProcessor::freeBuffers()
{
    for(int i = 0; i < BeatDelay::kNumChannels; ++i)
    {
        if(m_buffer[i])
        {
            delete[] m_buffer[i];
            m_buffer[i] = 0;
        }
    }
    m_bufferLength   = 0;
    m_curSampleRead  = 0;
    m_curSampleWrite = 0;
}

void BeatDelayProcessor::initBuffers()
{
    freeBuffers();

    m_bufferLength = BeatDelay::kDefSampleRate * BeatDelay::kMaxDelayBeats;
    IMPTRACE("Initializing buffers. Delay Buffer size: %d", m_bufferLength);

    for(int i = 0; i < BeatDelay::kNumChannels; ++i)
    {
        m_buffer[i] = new float[m_bufferLength];  // should be sample rate
        memset(m_buffer[i], 0, m_bufferLength * sizeof(float));
    }
}

tresult PLUGIN_API BeatDelayProcessor::setupProcessing(Vst::ProcessSetup& newSetup)
{
    // Make sure to update buffer sizes if we change sample rates
    if ((m_sampleRate != newSetup.sampleRate) || (m_bufferLength == 0))
    {
        m_sampleRate = newSetup.sampleRate;
        initBuffers();
    }

    return AudioEffect::setupProcessing(newSetup);
}


tresult PLUGIN_API BeatDelayProcessor::initialize(FUnknown* context)
{
    tresult result = AudioEffect::initialize(context);
    if(result != kResultOk)
    {
        return result;
    }

    // Right now for simplicity, we ONLY support stereo in/out.
    addAudioInput(STR16("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
    addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

    return kResultOk;
}

tresult PLUGIN_API BeatDelayProcessor::terminate()
{
    return AudioEffect::terminate();
}

tresult PLUGIN_API BeatDelayProcessor::setActive(TBool state)
{
    return AudioEffect::setActive(state);
}

tresult PLUGIN_API BeatDelayProcessor::process(Vst::ProcessData& data)
{
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
                    m_beatDelay.m_params[paramId]->setNormal(value);
                    break;
                }
            }
        }
    }

    float secondsDelay = m_beatDelay.m_Beats.intValue() * (60.0f / data.processContext->tempo);
    int   samplesDelay = secondsDelay * data.processContext->sampleRate;

    if(m_samplesDelay != samplesDelay)
    {
        m_samplesDelay   = samplesDelay;
        m_curSampleWrite = (m_curSampleRead + m_samplesDelay) % m_bufferLength;
    }

    // Copy incoming
    size_t samplesLeft   = data.numSamples;
    size_t samplesCopied = 0;
    size_t srcOffset     = 0;

    if(samplesLeft + m_curSampleWrite > m_bufferLength)
    {
        samplesCopied = m_bufferLength - m_curSampleWrite;
        for(int i = 0; i < BeatDelay::kNumChannels; ++i)
        {
            memcpy(m_buffer[i] + m_curSampleWrite, data.inputs[0].channelBuffers32[i], samplesCopied * sizeof(float));
        }

        samplesLeft -= samplesCopied;
        m_curSampleWrite = 0;
        srcOffset += samplesCopied;
    }

    for(int i = 0; i < BeatDelay::kNumChannels; ++i)
    {
        memcpy(m_buffer[i] + m_curSampleWrite,
               data.inputs[0].channelBuffers32[i] + srcOffset,
               samplesLeft * sizeof(float));
    }

    m_curSampleWrite += samplesLeft;


    // Copy outgoing
    samplesLeft      = data.numSamples;
    samplesCopied    = 0;
    size_t dstOffset = 0;

    if(samplesLeft + m_curSampleRead > m_bufferLength)
    {
        samplesCopied = m_bufferLength - m_curSampleRead;

        for(int i = 0; i < BeatDelay::kNumChannels; ++i)
        {
            memcpy(data.outputs[0].channelBuffers32[i] + dstOffset,
                   m_buffer[i] + m_curSampleRead,
                   samplesCopied * sizeof(float));
        }
        samplesLeft -= samplesCopied;
        m_curSampleRead = 0;
        dstOffset += samplesCopied;
    }

    for(int i = 0; i < BeatDelay::kNumChannels; ++i)
    {
        memcpy(data.outputs[0].channelBuffers32[i] + dstOffset,
               m_buffer[i] + m_curSampleRead,
               samplesLeft * sizeof(float));
    }
    m_curSampleRead += samplesLeft;

    return kResultOk;
}

tresult PLUGIN_API BeatDelayProcessor::canProcessSampleSize(int32 symbolicSampleSize)
{
    // by default kSample32 is supported
    if(symbolicSampleSize == Vst::kSample32)
        return kResultTrue;

    return kResultFalse;
}

tresult PLUGIN_API BeatDelayProcessor::setState(IBStream* state)
{
    // Load a preset
    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs = &BeatDelay::kParamDefs[0];

    float tmpFloat = 0.0;

    while(*defs)
    {
        if(streamer.readFloat(tmpFloat) == false)
        {
            return kResultFalse;
        }
        m_beatDelay.m_params[(*defs)->id()]->setNormal(tmpFloat);

        defs++;
    }

    return kResultOk;
}

tresult PLUGIN_API BeatDelayProcessor::getState(IBStream* state)
{
    // save preset
    IBStreamer streamer(state, kLittleEndian);

    const ImpParamDef** defs = &BeatDelay::kParamDefs[0];

    while(*defs)
    {
        if(streamer.writeFloat(m_beatDelay.m_params[(*defs)->id()]->getNormal()) == false)
        {
            return kResultFalse;
        }

        defs++;
    }

    return kResultOk;
}

}  // namespace impostorem
