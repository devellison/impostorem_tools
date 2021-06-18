/// midimuck.h
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
/// Core logic class for the MIDIMuck plugin.
///
/// MidiMuck acts as a stream processor for MIDI data, transforming it based on the current parameters.
class MidiMuck
{
public:
    /// Static table of parameter definitions used in MIDIMuck
    /// This needs to be in sync with the enum (invalid not in table, Bypass should be first, etc.)
    static const ImpParamDef* kParamDefs[];

    /// Parameter Ids for MIDIMuck
    enum ParamIds : int32_t
    {
        kInvalid = impostorem::kBypassId - 1,  ///< Not a valid parameter
        kBypassId,                             ///< General bypass
        kOctaveId,                             ///< Octave shift, +/- 10
        kDelayId,                              ///< Delay in beats
        kChannelId,                            ///< Channel mod - 0=unchanged, 1-16 is new channel
        kMinNoteId,                            ///< Minimum note to processes
        kMaxNoteId,                            ///< Maximum note to process
        kImpostoremId,                         ///< Impostorem button
        kMidiMuckId,                           ///< MIDIMuck button
        //------------
        kNumParameters  ///< Number of parameters
    };

    MidiMuck();           ///< MidiMuck constructor
    virtual ~MidiMuck();  ///< MidiMuck destructor

    /// muckNote processes a note in-place based on current parameters, and returns the time until the event should be
    /// sent.
    /// \param pitch - ref to MIDI pitch of the note (in/out)
    /// \param channel - ref to MIDI channel of the note (in/out)
    /// \param tempo - current tempo in BPM
    /// \param sampleRate - sampleRate we're processing at
    /// \return float - time (in samples) until the event should be sent. If negative, don't pass through.
    float muckNote(int16_t& pitch, int16_t& channel, float tempo, float sampleRate);

    ImpParam m_Bypass;      /// Bypass button
    ImpParam m_Octave;      /// Octave shift
    ImpParam m_Delay;       /// Delay in beats
    ImpParam m_Channel;     /// Target channel
    ImpParam m_MinNote;     /// Min note to accept
    ImpParam m_MaxNote;     /// Max note to accept
    ImpParam m_Impostorem;  /// Impostorem button
    ImpParam m_MidiMuck;    /// MidiMuck Button

    /// Table of pointers to parameter objects
    ImpParam* m_params[kNumParameters] =
        {&m_Bypass, &m_Octave, &m_Delay, &m_Channel, &m_MinNote, &m_MaxNote, &m_Impostorem, &m_MidiMuck};

protected:
};
}  // namespace impostorem