/// beatdelay.cpp
///
//
// Copyright (c) 2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "beatdelay.h"

namespace impostorem
{
// clang-format off
// Parameter definitions for MIDIMuck:     Name           Units       Parameter                 Type                  Step   Min                        Max   Def
static const ImpParamDef     kDefBypass(   L"Bypass",     L"",        BeatDelay::kBypassId,     ImpParamType::kInt32,  1.0,  0.0,                         1,    0);
static const ImpParamDef     kDefBeats  (  L"Beats",      L"Beats",   BeatDelay::kBeatsId,      ImpParamType::kInt32,    1,    0, BeatDelay::kMaxDelayBeats,    0);
static const ImpParamDef     kDefImp    (  L"Impostorem", L"",        BeatDelay::kImpostoremId, ImpParamType::kInt32,    1,    0,                         1,    0);
static const ImpParamDef     kDefPlugin (  L"BeatDelay",  L"",        BeatDelay::kBeatDelayId,  ImpParamType::kInt32,    1,    0,                         1,    0);
// clang-format on

/// {TODO} Originally this was a nice table of the above, but for inheritance/overrides we needed to
/// pull the object definitions out and use pointers to pointers... refactor this to something cleaner.
const ImpParamDef* BeatDelay::kParamDefs[] = {&kDefBypass,
                                              &kDefBeats,
                                              &kDefImp,
                                              &kDefPlugin,
                                              // end marker
                                              nullptr};
BeatDelay::BeatDelay()
    : m_Bypass(kParamDefs[kBypassId])
    , m_Beats(kParamDefs[kBeatsId])
    , m_Impostorem(kParamDefs[kImpostoremId])
    , m_BeatDelay(kParamDefs[kBeatDelayId])
{
    IMPTRACE("BeatDelay started");
}

BeatDelay::~BeatDelay() {}
}  // namespace impostorem