// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

// Store data

// clang-format off
#include "headers.h"

// Price offset to modify all prices at once. Don't make too high to avoid type overflow.
constexpr int8_t po = 50;

// Buying and selling adjustments for character race VS store owner race
uint8_t race_gold_adjustments[PLAYER_MAX_RACES][PLAYER_MAX_RACES] = {
    //Hum,      HfE,      Elf,      Hal,      Gno,      Dwa,      HfO,      HfT
    { 100 + po, 105 + po, 105 + po, 110 + po, 113 + po, 115 + po, 120 + po, 125 + po}, // Human
    { 110 + po, 100 + po, 100 + po, 105 + po, 110 + po, 120 + po, 125 + po, 130 + po}, // Half-Elf
    { 110 + po, 105 + po, 100 + po, 105 + po, 110 + po, 120 + po, 125 + po, 130 + po}, // Elf
    { 115 + po, 110 + po, 105 + po,  95 + po, 105 + po, 110 + po, 115 + po, 130 + po}, // Halfling
    { 115 + po, 115 + po, 110 + po, 105 + po,  95 + po, 110 + po, 115 + po, 130 + po}, // Gnome
    { 115 + po, 120 + po, 120 + po, 110 + po, 110 + po,  95 + po, 125 + po, 135 + po}, // Dwarf
    { 115 + po, 120 + po, 125 + po, 115 + po, 115 + po, 130 + po, 110 + po, 115 + po}, // Half-Orc
    { 110 + po, 115 + po, 115 + po, 110 + po, 110 + po, 130 + po, 110 + po, 110 + po}, // Half-Troll
};

// game_objects[] index of objects that may appear in the store
uint16_t store_choices[MAX_STORES][STORE_MAX_ITEM_TYPES] = {
    // General Store
    {
        366, 365, 364,  84,  84, 365, 123, 366, 365, 350, 349, 348, 347,
        346, 346, 345, 345, 345, 344, 344, 344, 344, 344, 344, 344, 344,
    },
    // Armory
    {
        94,  95,  96, 109, 103, 104, 105, 106, 110, 111, 112, 114, 116,
        124, 125, 126, 127, 129, 103, 104, 124, 125, 91,  92,  95,  96,
    },
    // Weaponsmith
    {
        29, 30, 34, 37, 45, 49, 57, 58, 59, 65, 67, 68, 73,
        74, 75, 77, 79, 80, 81, 83, 29, 30, 80, 83, 80, 83,
    },
    // Temple
    {
        322, 323, 324, 325, 180, 180, 233, 237, 240, 241, 361, 362, 57,
        58,  59, 260, 358, 359, 265, 237, 237, 240, 240, 241, 323, 359,
    },
    // Alchemy shop
    {
        173, 174, 175, 351, 351, 352, 353, 354, 355, 356, 357, 206, 227,
        230, 236, 252, 253, 352, 353, 354, 355, 356, 359, 363, 359, 359,
    },
    // Magic-User store
    {
        318, 141, 142, 153, 164, 167, 168, 140, 319, 320, 320, 321, 269,
        270, 282, 286, 287, 292, 293, 294, 295, 308, 269, 290, 319, 282,
    },
};
