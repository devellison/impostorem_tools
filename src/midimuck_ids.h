/// midimuck_ids.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace impostorem
{
static const Steinberg::FUID kMidiMuckProcessorUID(0xA925E5B0, 0xB4515980, 0x9C56F011, 0x9704E97C);
static const Steinberg::FUID kMidiMuckControllerUID(0x1CD19F85, 0xD8FE591A, 0xA252BFC6, 0x37E6B411);

#define MIDIMuckVST3Category "Instrument"

}  // namespace impostorem
