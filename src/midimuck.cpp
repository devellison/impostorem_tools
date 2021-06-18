/// midimuck.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "midimuck.hpp"

namespace impostorem
{
// clang-format off
// Parameter definitions for MIDIMuck:     Name           Units       Parameter               Type                  Step   Min   Max   Def
static const ImpParamDef     kDefBypass(   L"Bypass",     L"",        MidiMuck::kBypassId,    ImpParamType::kInt32,  1.0,  0.0,    1,    0);
static const ImpParamDefMod  kDefOctave(   L"Octave",     L"octaves", MidiMuck::kOctaveId,    ImpParamType::kInt32,    1,  -10,   10,    0);
static const ImpParamDefMod  KDefDelay(    L"Delay",      L"beats",   MidiMuck::kDelayId,     ImpParamType::kInt32,    2,  0.0,   48,    0);
static const ImpParamDefMod  kDefChannel(  L"Channel",    L"channel", MidiMuck::kChannelId,   ImpParamType::kInt32,    1,  0.0,   16,    0);
static const ImpParamDef     kDefMinNote(  L"MinNote",    L"",        MidiMuck::kMinNoteId,   ImpParamType::kInt32,    1,    0,  128,   44);
static const ImpParamDef     kDefMaxNote(  L"MaxNote",    L"",        MidiMuck::kMaxNoteId,   ImpParamType::kInt32,    1,    0,  128,  104);
static const ImpParamDef     kDefImp    (  L"Impostorem", L"",        MidiMuck::kImpostoremId,ImpParamType::kInt32,    1,    0,    1,    0);
static const ImpParamDef     kDefMuck   (  L"MidiMuck",   L"",        MidiMuck::kMidiMuckId,  ImpParamType::kInt32,    1,    0,    1,    0);
// clang-format on

/// {TODO} Originally this was a nice table of the above, but for inheritance/overrides we needed to
/// pull the object definitions out and use pointers to pointers... refactor this to something cleaner.
const ImpParamDef* MidiMuck::kParamDefs[] = {&kDefBypass,
                                                     &kDefOctave,
                                                     &KDefDelay,
                                                     &kDefChannel,
                                                     &kDefMinNote,
                                                     &kDefMaxNote,
                                                     &kDefImp,
                                                     &kDefMuck,
                                                     // end marker
                                                     nullptr};
MidiMuck::MidiMuck()
    : m_Bypass(kParamDefs[kBypassId])
    , m_Octave(kParamDefs[kOctaveId])
    , m_Delay(kParamDefs[kDelayId])
    , m_Channel(kParamDefs[kChannelId])
    , m_MinNote(kParamDefs[kMinNoteId])
    , m_MaxNote(kParamDefs[kMaxNoteId])
    , m_Impostorem(kParamDefs[kImpostoremId])
    , m_MidiMuck(kParamDefs[kMidiMuckId])
{
    IMPTRACE("MIDIMuck created");
}

MidiMuck::~MidiMuck() 
{
    IMPTRACE("MIDIMuck destroyed");
}

float MidiMuck::muckNote(int16_t& pitch, int16_t& channel, float tempo, float sampleRate)
{
    // Return neg to skip out of range notes.
    if((pitch < m_MinNote.intValue()) || (pitch > m_MaxNote.intValue()))
    {
        return -1.0;
    }

    // Raise up/lower by octave
    pitch += static_cast<int16_t>(m_Octave.intValue() * 12);

    // Reset pitch into min/max range w/o changing note letter
    while(pitch > 127)
    {
        pitch -= 12;
    }

    while(pitch < 0)
    {
        pitch += 12;
    }

    // 0 is leave alone, 1-16 = channels 0-15
    if(m_Channel.intValue() != 0)
    {
        channel = static_cast<int16_t>(m_Channel.intValue() - 1);
    }


    float timeUntil = 0.0f;
    if(m_Delay.intValue() > 0)
    {
        // number of seconds to delay
        float delaySec = ((float)m_Delay.intValue()) * (60.0f / tempo);

        // number of samples
        float delaySamples = sampleRate * delaySec;

        timeUntil = delaySamples;
    }
    return timeUntil;
}

}  // end namespace impostorem