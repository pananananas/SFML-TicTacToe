#pragma once

const int INF = 2147483647;

// Window size
#define SCREEN_WIDTH  1000
#define SCREEN_HEIGHT 1500

// Time
#define SPLASH_STATE_SHOW_TIME 1

// Default values
#define DEFAULT_SIZE            3
#define DEFAULT_WIN_SIZE        3
#define DEFAULT_IS_PLAYER_X     false
#define DEFAULT_VS_AI           false

// Best depth values for grid sizes
#define DEFAULT_DEPTH_3X3       9
#define DEFAULT_DEPTH_4X4       7
#define DEFAULT_DEPTH_5X5       8
#define DEFAULT_DEPTH_6X6       3

// Backgrounds
#define SPLASH_SCENE_BACKGROUND_FILEPATH    "Resources/UI/Splash_back.png"
#define MAIN_MENU_BACKGROUND_FILEPATH       "Resources/UI/Menu 2.png"
#define GAME_BACKGROUND_FILEPATH            "Resources/UI/Game 2.png"
#define PAUSE_BACKGROUND_FILEPATH           "Resources/UI/Game.png"
#define SETTINGS_BACKGROUND_FILEPATH        "Resources/UI/Menu.png"

// Titles
#define MAIN_MENU_TITLE_FILEPATH            "Resources/UI/Title.png"
#define PAUSE_TITLE_FILEPATH                "Resources/UI/Title_Pause.png"
#define SETTINGS_TITLE_FILEPATH             "Resources/UI/Title_Settings.png"
#define GRID_SIZE_TITLE_FILEPATH            "Resources/UI/Title_Grid_Size.png"
#define X_WINS_TITLE_FILEPATH               "Resources/UI/Title_X_Win.png"
#define O_WINS_TITLE_FILEPATH               "Resources/UI/Title_O_Win.png"
#define DRAW_TITLE_FILEPATH                 "Resources/UI/Title_Draw.png"

// Buttons UI
#define BUTTON_BACKGROUND                   "Resources/UI/Button Background 2.png"
#define MAIN_MENU_PLAY_BUTTON               "Resources/UI/Play Button.png"
#define MAIN_MENU_PLAY_BUTTON_OUTER         "Resources/UI/Play Button.png"
#define MAIN_MENU_SETTINGS_BUTTON           "Resources/UI/Settings Button.png"
#define PAUSE_BUTTON                        "Resources/UI/Pause_Button.png"
#define RESUME_BUTTON                       "Resources/UI/Play Button.png"
#define HOME_BUTTON                         "Resources/UI/Home Button.png"
#define RETRY_BUTTON                        "Resources/UI/Replay_Button.png"
#define PLUS_BUTTON                         "Resources/UI/Plus_Button.png"
#define MINUS_BUTTON                        "Resources/UI/Minus_Button.png"
#define AI_BUTTON                           "Resources/UI/AI Player 2.png"
#define P_BUTTON                            "Resources/UI/P Player 2.png"
#define X_BUTTON                            "Resources/UI/Choose X 2.png"
#define O_BUTTON                            "Resources/UI/Choose O 2.png"
#define NUMBER_DISPLAY_3                    "Resources/UI/Display_3.png"
#define NUMBER_DISPLAY_4                    "Resources/UI/Display_4.png"
#define NUMBER_DISPLAY_5                    "Resources/UI/Display_5.png"
#define NUMBER_DISPLAY_6                    "Resources/UI/Display_6.png"
#define WIN_DISPLAY_3                       "Resources/UI/Win_3.png"
#define WIN_DISPLAY_4                       "Resources/UI/Win_4.png"
#define WIN_DISPLAY_5                       "Resources/UI/Win_5.png"
#define WIN_DISPLAY_6                       "Resources/UI/Win_6.png"

// Grid UI
#define GRID_3x3_FILEPATH                   "Resources/UI/Grid 3.png"
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
#define O_PIECE             2   // wczesniej -1
#define EMPTY_PIECE         0   // wczesniej  8
//#define PLAYER_PIECE        X_PIECE
//#define AI_PIECE            O_PIECE

// State numbers
#define STATE_PLAYING       98
#define STATE_PAUSED        97
#define STATE_X_WON         96
#define STATE_O_WON         95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING    93
#define STATE_DRAW          92
#define END_GAME            91
#define TIE                  3
