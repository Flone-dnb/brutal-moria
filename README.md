# Fork info

![](screenshot.png?raw=true)

This fork brings the following changes:
- UI
    - Make visuals more colorful.
    - Display weight in kilograms instead of pounds.
    - HP is now displayed in one row as "CURRENT / MAX" instead of having 2 rows.
    - Level depth is now displayed as `Depth: X` instead of `X feet`.
    - Item properties are now displayed as letters instead of numbers, for example:
        - Instead of `a Small Metal Shield [3,+1]` we have `a Small Metal Shield AC 3+1`.
        - Instead of `a Small Sword 1d6 (+0,+1)` we have `a Small Sword 1d6 (HIT +0, DMG +1)`.
    - `Look` command now also displays approximated health of a creature, for example: `You see a Large Brown Snake (looks wounded).`.
    - When your character hits a creature or a creature hits your character a "flying" message will appear in the direction of the attack with the text of the damage dealt just like in Cataclysm: Dark Days Ahead.
- Gameplay
    - Your inventory/equipment/gold weight now affects how fast you feel hunger.
    - Monsters spawn x2 times more often.
    - Dungeon now has x2 more items.
    - Use CTRL+8 / CTRL+5 / CTRL+2 to change which body part you protect, if a monster attacks in the protected body part 30% of the incoming damage will be blocked, if you will also block the next attack you will block 60% and then 90% (for 3 consecutive blocks, more consecutive blocks will be clamped at 90%).
    - HP regeneration is now 10 times slower but you when you deal damage 20% of that damage will be converted to HP that you will restore.
    - Condition of the armor your character is wearing will now degrade when you take a hit and at some point your armor will break into pieces and disappear. Armor condition is displayed in its description.
- Items
    - Light items (Torch, Lantern, Flask of Oil) are now more expensive and have less "capacity" (turns).
    - Potions of Poison/Confusion/Sleep now last longer.
- Misc
    - All prices are 50% higher compared to the original.

# The Dungeons of Moria

_The Dungeons of Moria_ is a single player dungeon simulation originally
written by Robert Alan Koeneke, with its first public release in 1983.
The game was originally developed using VMS Pascal before being ported to the
C language by James E. Wilson in 1988, and released a _Umoria_.

Moria/Umoria has had many variants over the years, with [_Angband_](http://rephial.org/)
being the most well known. Umoria was also an inspiration for one the most
commercially successful action roguelike games, _Diablo_!

Supported Platforms:

  - Windows
  - macOS
  - Linux

Compiling and limited testing has been done for other Linux based system
including NetBSD 8.1 and Fedora 32.

# Umoria Color

Colour-Umoria was a patch originally written in 1993 by Edouard Poor. In 2020
it was ported by Andrew Weber as a fork of the modernized Umoria restoration
release.

# Compiling Umoria

You will need `ncurses` as well as `CMake` and the C++ build tools for your system.

## macOS and Linux

Change to the `umoria` game directory and enter the following commands at the
terminal:

    $ mkdir build && cd build
    $ cmake ..
    $ make

NOTE: use `make -j $(nproc)` to speed up compilation on Linux.

An `umoria` directory will be created in the current directory containing the
game binary and data files, which can then be moved to any other location, such
as the `home` directory.

## Windows

There are at least 3 ways to compile this project on Windows:

### Using PDCurses

First, clone this repository, then update submodules to pull PDCurses repository:

```
git submodule update --init --recursive
```

then build as usual:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config=Release
cd umoria
move .\Release\umoria.exe umorial.exe
umoria.exe
```

You can change UI scaling by changing your console's font.

### Using Windows Subsystem for Linux (WSL)

In your Windows search bar type `Windows Features` and open up the resulting application. Inside of the opened window check (turn on) `Windows Subsystem for Linux` option and click `OK` (you may be asked to restart your system).

In your Windows search bar type `Microsoft Store` to open up the Microsoft Store app, inside of the Microsoft store search for `Ubuntu` and download/install it. Then after installation in your Windows search bar type `Ubuntu` and open that app (this will open up a terminal). Inside of Ubuntu's terminal use the following commands to prepare for compilation:

```
sudo apt update && sudo apt upgrade
sudo apt install libncurses5-dev libncursesw5-dev cmake build-essential
```

Then do the usual (clone repository and build):

```
git clone <address of this repository>
cd <cloned repository name>
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd umoria
./umoria
```

### Using MSYS2

MinGW is used to provide GCC and GNU Binutils for compiling on the Windows platform.
The easiest solution to get set up is to use the [MSYS2 Installer](http://msys2.github.io/).
Once installed, `pacman` can be used to install `GCC`, `ncurses`, and the
`make`/`cmake` build tools.

At present an environment variable for the MinGW system being compiled on will
need to be specified. This will be either `mingw64` or `mingw32`.

At the command prompt type the following, being sure to add the correct label
to `MINGW=`:

    $ MINGW=mingw64 cmake .
    $ make

To perform an out-of-source build, type the following:

    $ mkdir build
    $ cd build
    $ MINGW=mingw64 cmake ..
    $ make

As with the macOS/Linux builds, all files will be installed into an `umoria` directory.

# Historical Documents

Most of the original document files included in the Umoria 5.6 sources have
been placed in the [historical](historical) directory. You will even find the
old CHANGELOG, which tracks all code changes made between versions 4.81 and
5.5.2 (1987-2008). If you'd like to learn more on the development history of
Umoria, these can make for interesting reading.

There is also the original Moria Manual and FAQ. Although these are a little
outdated now they are certainly worth reading as they contain a lot of
interesting and useful information.

# License Information

Umoria is released under the [GNU General Public License v3.0](LICENSE).

In 2007 Ben Asselstine and Ben Shadwick started the
[_free-moria_](http://free-moria.sourceforge.net/) project to re-license
UMoria 5.5.2 under GPL-2 by obtaining permission from all the contributing
authors. A year later they succeeded in their goal and in late 2008 official
maintainer David Grabiner released Umoria 5.6 under a GPL-3.0-or-later license.
