/// beatdelay_processor.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "beatdelay.h"
#include "public.sdk/source/vst/vstaudioeffect.h"

namespace impostorem
{

class BeatDelayProcessor : public Steinberg::Vst::AudioEffect
{
public:
    BeatDelayProcessor();
    ~BeatDelayProcessor() SMTG_OVERRIDE;

    static Steinberg::FUnknown* createInstance(void*)
    {
        return (Steinberg::Vst::IAudioProcessor*)new BeatDelayProcessor;
    }

    // AudioEffect overrides:
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

protected:
    /// Initialize audio buffers to the sample rate and max beats
    void initBuffers();
    /// Free the audio buffers
    void freeBuffers();

protected:
    BeatDelay m_beatDelay;                     ///< Beat Delay object

    float* m_buffer[BeatDelay::kNumChannels];  ///< Buffer for audio (Stereo buffers)
    size_t m_curSampleRead;                    ///< Current read position in buffer
    size_t m_curSampleWrite;                   ///< Current write position in buffer
    size_t m_samplesDelay;                     ///< Number of samples to delay by
    size_t m_bufferLength;                     ///< Total length of buffer
    size_t m_sampleRate;                       ///< Sample rate
};

}  // namespace impostorem
