/// beatdelay_ids.h
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
static const Steinberg::FUID kBeatDelayProcessorUID(0x9C51EF86, 0x4373559F, 0xA9EFD2C6, 0x0CE69F17);
static const Steinberg::FUID kBeatDelayControllerUID(0x499D6F0B, 0xE563524D, 0x966336E8, 0x039798C4);

#define BeatDelayVST3Category "Fx"

}  // namespace impostorem
