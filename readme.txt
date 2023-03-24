/*  _______         ____    __         ___    ___
 * \    _  \       \    /  \  /       \   \  /   /       '   '  '
 *  |  | \  \       |  |    ||         |   \/   |         .      .
 *  |  |  |  |      |  |    ||         ||\  /|  |
 *  |  |  |  |      |  |    ||         || \/ |  |         '  '  '
 *  |  |  |  |      |  |    ||         ||    |  |         .      .
 *  |  |_/  /        \  \__//          ||    |  |
 * /_______/ynamic    \____/niversal  /__\  /____\usic   /|  .  . ibliotheque
 *                                                      /  \
 *                                                     / .  \
 * readme.txt - General information on DUMB.          / / \  \
 *                                                   | <  /   \_
 *                                                   |  \/ /\   /
 *                                                    \_  /  > /
 *                                                      | \ / /
 *                                                      |  ' /
 *                                                       \__/
 */


**************************
*** DUMB Classic Notes ***
**************************

This fork is intended to help maintain old Allegro 4 projects that use DUMB to
play music. A '-classic' suffix has been added to the include and library names
to avoid conflicts with the newer DUMB 2.x versions.

Old projects that use DUMB with Allegro PACKFILEs will not work with DUMB 2.x.
For these kinds of projects I recommend adding an #ifdef and compiler flag to
help make these projects work with classic Allegro 4 + DUMB installations as
well as modern setups that have DUMB 2.x and DUMB Classic installed.

DUMB Classic will also with with Allegro Legacy.


********************
*** Introduction ***
********************

Thank you for downloading DUMB v0.9.3! You should have the following
documentation:

   readme.txt    - This file
   licence.txt   - Conditions for the use of this software
   release.txt   - Release notes and changes for this and past releases
   docs/
     howto.txt   - Step-by-step instructions on adding DUMB to your project
     faq.txt     - Frequently asked questions and answers to them
     dumb.txt    - DUMB library reference
     deprec.txt  - Information about deprecated parts of the API
     ptr.txt     - Quick introduction to pointers for those who need it
     fnptr.txt   - Explanation of function pointers for those who need it
     modplug.txt - Our official position regarding ModPlug Tracker

This file will help you get DUMB set up. If you have not yet done so, please
read licence.txt and release.txt before proceeding. After you've got DUMB set
up, please refer to the files in the docs/ directory at your convenience. I
recommend you start with howto.txt.


****************
*** Features ***
****************

Here is the statutory feature list:

- Freeware

- Supports playback of IT, XM, S3M and MOD files

- Faithful to the original trackers, especially IT; if it plays your module
  wrongly, please tell me so I can fix the bug! (But please don't complain
  about differences between DUMB and ModPlug Tracker; see docs/modplug.txt)

- Accurate support for low-pass resonant filters for IT files

- Very accurate timing and pitching; completely deterministic playback

- Click removal

- Facility to embed music files in other files (e.g. Allegro datafiles)

- Three resampling quality settings: aliasing, linear interpolation and cubic
  interpolation

- Number of samples playing at once can be limited to reduce processor usage,
  but samples will come back in when other louder ones stop

- All notes will be present and correct even if you start a piece of music in
  the middle

- Option to take longer loading but seek fast to any point before the music
  first loops (seeking time increases beyond this point)

- Audio generated can be used in any way; DUMB does not necessarily send it
  straight to a sound output system

- Can be used with Allegro, can be used without (if you'd like to help make
  DUMB more approachable to people who aren't using Allegro, please contact
  me)

- CMake build script makes it easy to build on any platform that has CMake

- Code should port anywhere that has a C compiler; instructions on compiling it
  manually are available further down


*********************
*** What you need ***
*********************

To use DUMB, you need a C compiler (GCC and MSVC are fine). If you have
Allegro, DUMB can integrate with its audio streams and datafiles, making your
life easier. If you do not wish to use Allegro, you will have to do some work
to get music playing back.

   Allegro - https://liballeg.org
   CMake   - https://cmake.org


**********************************
*** How to set up DUMB Classic ***
**********************************

Create an empty folder where DUMB Classic will be built. Navigate to that
folder. Then type 'cmake ..' to configure the build script. When CMake
completes its process, run 'make' followed by 'make install' to build DUMB
Classic and install it on your system.


*********************************************
*** Downloading music or writing your own ***
*********************************************

If you would like to compose your own music modules, then this section should
help get you started.

The best programs for the job are the trackers that pioneered the file
formats:

   Impulse Tracker - IT files - http://www.lim.com.au/ImpulseTracker/
   Fast Tracker II - XM files - http://www.fasttracker2.com/
   Scream Tracker 3 - S3M files - No official site known, please use Google

MOD files come from the Amiga; I do not know what PC tracker to recommend for
editing these. If you know of one, let me know! In the meantime, I would
recommend using a more advanced file format. However, don't convert your
existing MODs just for the sake of it.

Fast Tracker II is Shareware. It offers a very flashy interface and has a
game embedded, but the IT file format is more powerful and better defined. By
all means try them both and see which you prefer; it is largely a matter of
taste (and, in some cases, religion). Impulse Tracker and Scream Tracker 3
are Freeware, although you can donate to Impulse Tracker and receive a
slightly upgraded version. DUMB is likely to be at its best with IT files.

These editors are DOS programs. Users of DOS-incapable operating systems may
like to try ModPlug Tracker, but should read docs/modplug.txt before using it
for any serious work. If you use a different operating system, or if you know
of any module editors for Windows that are more faithful to the original
trackers' playback, please give me some links so I can put them here!

   ModPlug Tracker - http://www.modplug.com/

If you have an x86 Linux system with VGA-compatible hardware (which covers
all PC graphics cards I've ever seen), you should be able to get Impulse
Tracker running with DOSEMU. You will have to give it access to the VGA ports
and run it in a true console, as it will not work with the X-based VGA
emulation. I personally added the SB16 emulation to DOSEMU, so you can even
use filters! However, it corrupts samples alarmingly often when saving on my
system - probably a DOSEMU issue. If you set this up, I am curious to know
whether it works for you.

   DOSEMU - http://www.dosemu.org/

BEWARE OF WINAMP! Although it's excellent for MP3s, it is notorious for being
one of the worst module players in existence; very many modules play wrongly
with it. There are plug-ins available to improve Winamp's module support, for
example WSP.

   Winamp - http://www.winamp.com/
   WSP - http://www.spytech.cz/index.php?sec=demo

(There is a Winamp plug-in that uses DUMB, but it is unreliable. If anyone
would like to work on it, please get in touch.)

While I am at it I should also point out that Winamp is notorious for
containing security flaws. Install it at your own risk, and if it is your
work computer, check with your boss first!

Samples and instruments are the building blocks of music modules. You can
download samples at

   http://www.tump.net/

If you would like to download module files composed by other people, check
the following sites:

   http://www.modarchive.com/
   http://www.scene.org/
   http://www.tump.net/
   http://www.homemusic.cc/main.php
   http://www.modplug.com/

Once again, if you know of more sites where samples or module files are
available for download, please let me know.

If you wish to use someone's music in your game, please respect the
composer's wishes. In general, you should ask the composer. Music that has
been placed in the Public Domain can be used by anyone for anything, but it
wouldn't do any harm to ask anyway if you know who the author is. In many
cases the author will be thrilled, so don't hesitate!

A note about converting modules from one format to another, or converting
from MIDI: don't do it, unless you are a musician and are prepared to go
through the file and make sure everything sounds the way it should! The
module formats are all slightly different, and MIDI is very different;
converting from one format to another will usually do some damage.

Instead, it is recommended that you allow DUMB to interpret the original file
as it sees fit. DUMB may make mistakes (it does a lot of conversion on
loading), but future versions of DUMB will be able to rectify these mistakes.
On the other hand, if you convert the file, the damage is permanent.


***********************
*** Contact details ***
***********************

If you have trouble with DUMB, or want to contact me for any other reason, my
e-mail address is given below. Please do get in touch, even if I appear to
have disappeared!

If you wish to chat online about something, perhaps on IRC, that can most
likely be arranged. Send me an e-mail.


******************
*** Conclusion ***
******************


This is the conclusion.


Original Author

Ben Davis
entheh@users.sf.net


DUMB Classic Fork

Todd Cope
todd@tcubedsoftware.com
