#pragma once

#define SCREEN_WIDTH  768
#define SCREEN_HEIGHT 1136

#define SPLASH_STATE_SHOW_TIME 0.5

// Backgrounds
#define SPLASH_SCENE_BACKGROUND_FILEPATH    "Resources/UI/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH       "Resources/UI/Main Menu Background.png"
#define MAIN_MENU_TITLE_FILEPATH            "Resources/UI/Game Title.png"
#define GAME_BACKGROUND_FILEPATH            "Resources/UI/Main Menu Background.png"
#define PAUSE_BACKGROUND_FILEPATH           "Resources/UI/Main Menu Background.png"

// Buttons UI
#define MAIN_MENU_PLAY_BUTTON               "Resources/UI/Play Button.png"
#define MAIN_MENU_PLAY_BUTTON_OUTER         "Resources/UI/Play Button Outer.png"
#define PAUSE_BUTTON                        "Resources/UI/Pause Button.png"
#define RESUME_BUTTON                       "Resources/UI/Resume Button.png"
#define HOME_BUTTON                         "Resources/UI/Home Button.png"

// Piece UI
#define X_PIECE_FILEPATH                    "Resources/U/X.png"
#define O_PIECE_FILEPATH                    "Resources/U/O.png"
#define X_WINNING_PIECE_FILEPATH            "Resources/U/X Win.png"
#define O_WINNING_PIECE_FILEPATH            "Resources/U/O Win.png"

// Piece numbers
#define X_PIECE             8
#define O_PIECE             0
#define EMPTY_PIECE        -1
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
