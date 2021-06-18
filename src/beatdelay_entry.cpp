/// beatdelay_entry.cpp
///
//
// Copyright (c) 2020-2021 by Michael Ellison
// Licensed under GPL 3, see Readme.md and LICENSE in project.
//

#include "beatdelay_controller.h"
#include "beatdelay_ids.h"
#include "beatdelay_processor.h"
#include "beatdelay_version.h"
#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "BeatDelay"

using namespace Steinberg::Vst;
using namespace impostorem;

BEGIN_FACTORY_DEF("Impostorem", "www.impostorem.com", "mailto:info@impostorem.com")

DEF_CLASS2(INLINE_UID_FROM_FUID(kBeatDelayProcessorUID),
           PClassInfo::kManyInstances,  // cardinality
           kVstAudioEffectClass,        // the component category (do not changed this)
           stringPluginName,            // here the Plug-in name (to be changed)
           Vst::kDistributable,    // means that component and controller could be distributed on different computers
           BeatDelayVST3Category,  // Subcategory for this Plug-in (to be changed)
           FULL_VERSION_STR,       // Plug-in version (to be changed)
           kVstVersionString,      // the VST 3 SDK version (do not changed this, use always this define)
           BeatDelayProcessor::createInstance)  // function pointer called when this component should be instantiated

DEF_CLASS2(INLINE_UID_FROM_FUID(kBeatDelayControllerUID),
           PClassInfo::kManyInstances,           // cardinality
           kVstComponentControllerClass,         // the Controller category (do not changed this)
           stringPluginName "Controller",        // controller name (could be the same than component name)
           0,                                    // not used here
           "",                                   // not used here
           FULL_VERSION_STR,                     // Plug-in version (to be changed)
           kVstVersionString,                    // the VST 3 SDK version (do not changed this, use always this define)
           BeatDelayController::createInstance)  // function pointer called when this component should be instantiated


END_FACTORY
