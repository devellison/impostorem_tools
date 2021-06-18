# Impostorem Tools


## Licensing
Copyright (c) 2020-2021 by Michael Ellison (<a href="https://www.impostorem.com">Impostorem</a>)

See <a href="LICENSE">LICENSE</a> file for full GPLv3 license details.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

The Impostorem Tools include VST-compatible plugins and use the VST3 SDK under the GPLv3 license.   
VST is a registered trademark of Steinberg Media Technologies GmbH.

- VST3 SDK: https://github.com/steinbergmedia/vst3sdk
![VST Logo and Trademark](doc/images/VST_Compatible_Logo_Steinberg_with_TM_negative.png)


## About
Impostorem Tools are tools I use to play with music and video stuffs.
They currently include VST-compatible plugins for use with the Pianoshooter visualizer.
- <b>MIDIMuck</b>:  <a href="http://www.midi.org">MIDI</a> utility knife for transforming / delaying / filtering MIDI
- <b>BeatDelay</b>: Delays an audio stream by a number of beats (to synch it with video from Pianoshooter)

<a href="https://github.com/devellison/pianoshooter">PianoShooter</a> is available at https://github.com/devellison/pianoshooter.

Pianoshooter is a plugin for <a href="https://www.image-line.com/fl-studio-learning/fl-studio-online-manual/html/plugins/ZGameEditor%20Visualizer.htm">ZGameEditor Visualizer</a>
in <a href="https://www.image-line.com">FLStudio</a>.

Currently only tested on Win64.  May port to Mac OSX when time allows (only a few points beyond project creation that need to be hit).

## MIDIMuck
MIDIMuck is a VST plugin that takes a MIDI / Event stream as input, transforms it,
then outputs the modified stream.  Its main purpose is to take a copy of the input 
MIDI used to play an instrument and tweak it to look nice in Pianoshooter.

Main features:
- <b>Octave shift</b> - make the notes appear in the octave you want in Pianoshooter
- <b>Delay</b> - in some cases, you may want to delay the MIDI to synch with audio.
  Usually though you'll want to use the BeatDelay plugin instead to delay the 
  raw audio itself.
- <b>Channel shift</b> - Allows you to tweak the channel for coloring effects.  If 0,
  the channel is left alone. Otherwise the input MIDI is output on the selected channel.
- <b>Min/Max Note</b> - You can set the minimum and maximum notes from a MIDI stream to
  pass through.  This is especially useful if you want to ignore key switches so
  they aren't displayed in PianoShooter.

Set MIDIMuck to be a generator, but chain it in patcher. Docs/videos on usage soon.

## BeatDelay
BeatDelay delays the audio stream the set number of beats without adding additional effects.

This is useful when using Pianoshooter in the Player mode, where the MIDI is output
when the note should be created - you delay the sound until it actually hits the
piano key to provide a synchronized video to the audio.

## Building
- Currently only tested with Microsoft Visual C++ 2017 Community. If you're using
  a different version, you'll want to change the cmake commands and upgrade the
  projects accordingly.

- First, get and build vst3sdk (I build it in an `./externals` directory)
<pre>
   mkdir externals
   cd externals
   # I've had some issues with the recursive using SSH, so currently using https.
   # git clone --recursive git@github.com:steinbergmedia/vst3sdk.git
   git clone --recursive https://github.com/steinbergmedia/vst3sdk.git
   cd vst3sdk   

   git checkout v3.7.2_build_28
   git submodule update
   
   mkdir build
   cd build
   cmake.exe -G "Visual Studio 15 2017" -DSMTG_CREATE_BUNDLE_FOR_WINDOWS=OFF -DSMTG_ADD_VST3_PLUGINS_SAMPLE=OFF -DSMTG_ADD_VSTGUI=ON -DSMTG_CREATE_PLUGIN_LINK=OFF -DSMTG_USE_STATIC_CRT=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\vstsdk -A x64 ..
   cmake --build . --config Release
</pre>
- Then build the impostorem_tools.sln solution. You can do this in the GUI if desired,
  but it works fine from the command-line._
<pre>
di   cd ..\..\..\win
   msbuild impostorem_tools.sln /t:Rebuild /p:Configuration=Release
</pre>
