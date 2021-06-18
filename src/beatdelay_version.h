/// beatdelay_version.h
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#pragma once

#include "pluginterfaces/base/fplatform.h"

#define MAJOR_VERSION_STR "1"
#define MAJOR_VERSION_INT 1

#define SUB_VERSION_STR "0"
#define SUB_VERSION_INT 0

#define RELEASE_NUMBER_STR "0"
#define RELEASE_NUMBER_INT 0

#define BUILD_NUMBER_STR "1"
#define BUILD_NUMBER_INT 1
#define FULL_VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR "." BUILD_NUMBER_STR
#define VERSION_STR MAJOR_VERSION_STR "." SUB_VERSION_STR "." RELEASE_NUMBER_STR

#define stringOriginalFilename "BeatDelay.vst3"
#if SMTG_PLATFORM_64
#define stringFileDescription "BeatDelay VST3 (64Bit)"
#else
#define stringFileDescription "BeatDelay VST3"
#endif
#define stringCompanyName "Impostorem\0"
#define stringLegalCopyright "Copyright(c) 2021 Impostorem."
#define stringLegalTrademarks "VST is a trademark of Steinberg Media Technologies GmbH"
#define stringCompanyUrl "www.impostorem.com"
#define stringSoftwareUrl "www.github.com/devellison/impostorem_tools"