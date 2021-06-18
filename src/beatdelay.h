/// beatdelay.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include <cstring>
#include <vector>
#include "imp_param.h"
#include "imp_utils.h"

namespace impostorem
{

/// BeatDelay core class.... BeatDelay is pretty simple, so we're
/// Mostly storing values here so far.  Main functionality is in the processing class.
class BeatDelay
{
public:
    /// Max delay in beats
    constexpr static const int kMaxDelayBeats = 64;
    /// Default sample rate
    constexpr static const int kDefSampleRate = 44100;
    /// For now, only supporting stereo
    constexpr static const int kNumChannels = 2;

    /// Static table of parameter definitions used in MIDIMuck
    /// This needs to be in sync with the enum (invalid not in table, Bypass should be first, etc.)
    static const ImpParamDef* kParamDefs[];

    /// Parameter Ids for MIDIMuck
    enum ParamIds : int32_t
    {
        kInvalid = impostorem::kBypassId - 1,
        kBypassId,      ///< Bypass
        kBeatsId,       ///< Number of beats to delay
        kImpostoremId,  ///< Impostorem button/website
        kBeatDelayId,   ///< BeatDelay button/github website
        //-----------------------
        kNumParameters  ///< Total number of parameters
    };

    BeatDelay();           ///< BeatDelay constructor
    virtual ~BeatDelay();  ///< BeatDelay dtor

    ImpParam m_Bypass;      ///< Bypass button
    ImpParam m_Beats;       ///< Number of beats to delay
    ImpParam m_Impostorem;  ///< Impostorem button
    ImpParam m_BeatDelay;   ///< BeatDelay Plugin Button

    /// Table of pointers to parameter objects
    ImpParam* m_params[kNumParameters] = {&m_Bypass,&m_Beats, &m_Impostorem, &m_BeatDelay};
};
}  // namespace impostorem