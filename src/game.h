// Copyright (c) 1981-86 Robert A. Koeneke
// Copyright (c) 1987-94 James E. Wilson
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <vector>
#include <string>
#include <chrono>
#include <memory>

constexpr uint8_t TREASURE_MAX_LEVELS = 50; // Maximum level of magic in dungeon

// Note that the following constants are all related, if you change one, you
// must also change all succeeding ones.
// Also, player_base_provisions[] and store_choices[] may also have to be changed.
constexpr uint16_t MAX_OBJECTS_IN_GAME = 420; // Number of objects for universe
constexpr uint16_t MAX_DUNGEON_OBJECTS = 344; // Number of dungeon objects
constexpr uint16_t OBJECT_IDENT_SIZE = 448;   // 7*64, see object_offset() in desc.cpp, could be MAX_OBJECTS o_o() rewritten

// With LEVEL_MAX_OBJECTS set to 150, it's possible to get compacting
// objects during level generation, although it is extremely rare.
constexpr uint8_t LEVEL_MAX_OBJECTS = 175; // Max objects per level

// definitions for the pseudo-normal distribution generation
constexpr uint16_t NORMAL_TABLE_SIZE = 256;
constexpr uint8_t NORMAL_TABLE_SD = 64; // the standard deviation for the table

/** Time after which a flying message should be updated. */
constexpr long FLYING_MESSAGE_UPDATE_INTERVAL_MS = 100;

/** Remind the player about "stances" feature after receiving N hits while not changing stance. */
constexpr size_t REMIND_ABOUT_STANCES_HIT_COUNT = 30;

// Inventory command screen states.
enum class Screen {
    Blank = 0,
    Equipment,
    Inventory,
    Wear,
    Help,
    Wrong,
};

/** Message that fly (move) on the screen in a specific direction. */
struct FlyingMessage {
    FlyingMessage() = delete;

    /** Clears message from the screen. */
    ~FlyingMessage();

    /**
     * Creates a new flying message and displays it.
     *
     * @param sMessage                   Message to display.
     * @param iCurrentHorizontalPosition X position where the message should be triggered (for example player position)
     * in dungeon coordinates (not screen coordinates). This actual position where the message will be displayed will be slightly different.
     * @param iCurrentVerticalPosition   Y position where the message should be triggered (for example player position)
     * in dungeon coordinates (not screen coordinates). This actual position where the message will be displayed will be slightly different.
     * @param iHorizontalDirection       `1` to move the message to the right, `-1` to the left and `0` to not move horizontally.
     * @param iVerticalDirection         `1` to move the message up, `-1` to move it down and `0` to not move vertically.
     * @param iColor                     Color of the message.
     *
     * @return Created message. Returning `unique_ptr` for easy "move" functions (which I don't have to implement
     * myself) and to avoid running destructor logic multiple times.
     */
    static std::unique_ptr<FlyingMessage> create(const std::string &sMessage, int iCurrentHorizontalPosition, int iCurrentVerticalPosition, int iHorizontalDirection,
                                                 int iVerticalDirection, int iColor);

    /**
     * Moves the message and displays it.
     *
     * @return `true` if the message was updated successfully, `false` if it can no longer be displayed.
     */
    bool update();

    /** Clears message on the current position (replaced it with dungeon tiles). */
    void clearMessageFromScreen();

    /** Message to display and move. */
    std::string sMessage;

    /** Time when the message was created/moved. */
    std::chrono::steady_clock::time_point lastUpdateTime;

    /** `-1` if the message should move to the left, `1` if to the right, `0` if horizontal movement is not used. */
    int iHorizontalDirection = 0;

    /** `-1` if the message should move down, `1` if up, `0` if vertical movement is not used. */
    int iVerticalDirection = 0;

    /** Current horizontal position of the message in dungeon coordinates. */
    int iCurrentHorizontalPosition = 0;

    /** Current vertical position of the message in dungeon coordinates. */
    int iCurrentVerticalPosition = 0;

    /** Color of the message. */
    int iMessageColor = 0;

  private:
    /**
     * Initializes a flying message.
     *
     * @param sMessage                   Message to display.
     * @param iCurrentHorizontalPosition Starting X position of the message in dungeon coordinates (not screen coordinates).
     * @param iCurrentVerticalPosition   Starting Y position of the message in dungeon coordinates (not screen coordinates).
     * @param iHorizontalDirection       `1` to move the message to the right, `-1` to the left and `0` to not move horizontally.
     * @param iVerticalDirection         `-1` to move the message up, `1` to move it down and `0` to not move vertically.
     * @param iColor                     Color of the message.
     */
    FlyingMessage(const std::string &sMessage, int iCurrentHorizontalPosition, int iCurrentVerticalPosition, int iHorizontalDirection, int iVerticalDirection, int iColor);

    /**
     * Looks if the message can fit in the screen according to its current position
     * and cuts it and/or slightly moves if needed.
     *
     * @return `true` if message can still be displayed, `false` if the message can no longer be displayed.
     */
    bool adjustMessageToScreenBounds();
};

typedef struct Game_t {
    /** Messages that needs to be moved on the screen. */
    std::vector<std::unique_ptr<FlyingMessage>> vFlyingMessages;

    uint32_t magic_seed = 0; // Seed for initializing magic items (Potions, Wands, Staves, Scrolls, etc.)
    uint32_t town_seed = 0;  // Seed for town generation

    bool character_generated = false; // Don't save score until character generation is finished
    bool character_saved = false;     // Prevents save on kill after saving a character
    bool character_is_dead = false;   // `true` if character has died

    bool total_winner = false; // Character beat the Balrog

    bool teleport_player = false;  // Handle teleport traps
    bool player_free_turn = false; // Player has a free turn, so do not move creatures

    bool to_be_wizard = false; // Player requests to be Wizard - used during startup, when -w option used
    bool wizard_mode = false;  // Character is a Wizard when true
    int16_t noscore = 0;       // Don't save a score for this game. -CJS-

    bool use_last_direction = false;  // `true` when repeat commands should use last known direction
    char doing_inventory_command = 0; // Track inventory commands -CJS-
    char last_command = ' ';          // Save of the previous player command
    int command_count = 0;            // How many times to repeat a specific command -CJS-

    /** How much hits player received without changing his stance (because the player maybe forgot about this feature). */
    size_t iHitsTakenWithoutChangingStance = 0;

    vtype_t character_died_from = {'\0'}; // What the character died from: starvation, Bat, etc.

    struct {
        int16_t current_id = 0; // Current treasure heap ptr
        Inventory_t list[LEVEL_MAX_OBJECTS]{};
    } treasure;

    // Keep track of the state of the current screen (inventory, equipment, help, etc.).
    struct {
        Screen current_screen_id = Screen::Blank;
        int screen_left_pos = 0;
        int screen_bottom_pos = 0;
        int wear_low_id = 0;
        int wear_high_id = 0;
    } screen;
} Game_t;

extern Game_t game;

extern int16_t sorted_objects[MAX_DUNGEON_OBJECTS];
extern uint16_t normal_table[NORMAL_TABLE_SIZE];
extern int16_t treasure_levels[TREASURE_MAX_LEVELS + 1];

void seedsInitialize(uint32_t seed);
void seedSet(uint32_t seed);
void seedResetToOldSeed();
int randomNumber(int max);
int randomNumberNormalDistribution(int mean, int standard);
void setGameOptions();
bool validGameVersion(uint8_t major, uint8_t minor, uint8_t patch);
bool isCurrentGameVersion(uint8_t major, uint8_t minor, uint8_t patch);

int getRandomDirection();
bool getDirectionWithMemory(char *prompt, int &direction);
bool getAllDirections(const char *prompt, int &direction);

void exitProgram();
void abortProgram(const char *msg);

// game object management
int popt();
void pusht(uint8_t treasure_id);
int itemGetRandomObjectId(int level, bool must_be_small);

// game files
bool initializeScoreFile();
void displaySplashScreen();
void displayTextHelpFile(const std::string &filename);
void displayDeathFile(const std::string &filename);
void outputRandomLevelObjectsToFile();
bool outputPlayerCharacterToFile(char *filename);

// game death
void endGame();

// save/load
bool saveGame();
bool loadGame(bool &generate);
void setFileptr(FILE *file);

// game_run.cpp
// (includes the playDungeon() main game loop)
void startMoria(int seed, bool start_new_game);
