/// beatdelay_version.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "pluginterfaces/base/fplatform.h"
#include "impostorem_tools.h"

#define stringOriginalFilename "BeatDelay.vst3"
#if SMTG_PLATFORM_64
#define stringFileDescription "BeatDelay VST3 (64Bit)"
#else
#define stringFileDescription "BeatDelay VST3"
#endif
