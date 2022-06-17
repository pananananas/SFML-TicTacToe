#pragma once

const int INF = 2147483647;

#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT 1500

#define SPLASH_STATE_SHOW_TIME 0.7

// Backgrounds
#define SPLASH_SCENE_BACKGROUND_FILEPATH    "Resources/UI/Splash_back.png"
#define MAIN_MENU_BACKGROUND_FILEPATH       "Resources/UI/Menu 2.png"
#define MAIN_MENU_TITLE_FILEPATH            "Resources/UI/Title.png"
#define PAUSE_TITLE_FILEPATH                "Resources/UI/Title_Pause.png"
#define SETTINGS_TITLE_FILEPATH             "Resources/UI/Title_Settings.png"
#define GAME_BACKGROUND_FILEPATH            "Resources/UI/Game 2.png"
#define PAUSE_BACKGROUND_FILEPATH           "Resources/UI/Game.png"
#define SETTINGS_BACKGROUND_FILEPATH        "Resources/UI/Menu.png"

// Buttons UI
#define MAIN_MENU_PLAY_BUTTON               "Resources/UI/Play Button.png"
#define MAIN_MENU_PLAY_BUTTON_OUTER         "Resources/UI/Play Button.png"
#define MAIN_MENU_SETTINGS_BUTTON           "Resources/UI/Settings Button.png"
#define PAUSE_BUTTON                        "Resources/UI/Pause_Button.png"
#define RESUME_BUTTON                       "Resources/UI/Play Button.png"
#define HOME_BUTTON                         "Resources/UI/Home Button.png"
#define RETRY_BUTTON                        "Resources/UI/Retry Button.png"
#define PLUS_BUTTON                         "Resources/UI/Plus_Button.png"
#define MINUS_BUTTON                        "Resources/UI/Minus_Button.png"
#define NUMBER_DISPLAY_3                    "Resources/UI/Pause Button.png"
#define NUMBER_DISPLAY_4                    "Resources/UI/Home Button.png"
#define NUMBER_DISPLAY_5                    "Resources/UI/Resume Button.png"
#define NUMBER_DISPLAY_6                    "Resources/UI/Pause Button.png"

// Grid UI
#define GRID_3x3_FILEPATH                   "Resources/UI/Grid.png"
#define GRID_4x4_FILEPATH                   "Resources/UI/Grid 4.png"
#define GRID_5x5_FILEPATH                   "Resources/UI/Grid 5.png"
#define GRID_6x6_FILEPATH                   "Resources/UI/Grid 6.png"

// Piece UI
#define X_PIECE_FILEPATH                    "Resources/UI/X.png"
#define O_PIECE_FILEPATH                    "Resources/UI/O.png"
#define X_WINNING_PIECE_FILEPATH            "Resources/UI/X_Win.png"
#define O_WINNING_PIECE_FILEPATH            "Resources/UI/O_Win.png"

// Piece numbers
#define X_PIECE             1
#define O_PIECE            -1
#define EMPTY_PIECE         2
#define PLAYER_PIECE        X_PIECE
#define AI_PIECE            O_PIECE

// State numbers
#define STATE_PLAYING       98
#define STATE_PAUSED        97
#define STATE_WON           96
#define STATE_LOSE          95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING    93
#define STATE_DRAW          92


// Depth for MinMax
#define TIE        3
