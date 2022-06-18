#include "StateGame.hpp"
#include "StatePause.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

StateGame:: StateGame(GameDataRef data, int size): _data( data ) {
    
    _size = size;
    
    switch (_size) {
        case 3:
            _depth = 7;
            break;
        case 4:
            _depth = 4;
            break;
        case 5:
            _depth = 3;
            break;
        case 6:
            _depth = 2;
            break;
        default:
            break;
    }
}

void StateGame:: Init() {

    gameState = STATE_PLAYING;
    turn      = PLAYER_PIECE;           // Starting player
    
    
    this -> _data -> assets.LoadTexture( "Game Background", GAME_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture( "Pause Button", PAUSE_BUTTON );
    this -> _data -> assets.LoadTexture( "Replay Button", RETRY_BUTTON );
    switch (_size)   {
        case 3:
            this -> _data -> assets.LoadTexture("Grid",   GRID_3x3_FILEPATH);
            break;
        case 4:
            this -> _data -> assets.LoadTexture("Grid",   GRID_4x4_FILEPATH);
            break;
        case 5:
            this -> _data -> assets.LoadTexture("Grid",   GRID_5x5_FILEPATH);
            break;
        case 6:
            this -> _data -> assets.LoadTexture("Grid",   GRID_6x6_FILEPATH);
            break;
        default:
            break;
    }
    this -> _data -> assets.LoadTexture("Title Draw", DRAW_TITLE_FILEPATH );
    this -> _data -> assets.LoadTexture("Title X Win", X_WINS_TITLE_FILEPATH );
    this -> _data -> assets.LoadTexture("Title O Win", O_WINS_TITLE_FILEPATH );
    this -> _data -> assets.LoadTexture("X Piece", X_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("O Piece", O_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("X Piece Wins", X_WINNING_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("O Piece Wins", O_WINNING_PIECE_FILEPATH );
    
    _title_Draw.setTexture  ( this -> _data -> assets.GetTexture("Title Draw") );
    _title_O_Win.setTexture ( this -> _data -> assets.GetTexture("Title O Win") );
    _title_X_Win.setTexture ( this -> _data -> assets.GetTexture("Title X Win") );
    _background.setTexture  ( this -> _data -> assets.GetTexture("Game Background") );
    _pauseButton.setTexture ( this -> _data -> assets.GetTexture("Pause Button") );
    _replayButton.setTexture( this -> _data -> assets.GetTexture("Replay Button") );
    _grid.setTexture        ( this -> _data -> assets.GetTexture("Grid") );
    
    this -> _pauseButton.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _pauseButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT)
                                  - (this -> _pauseButton.getGlobalBounds().height * 1.1));
    this -> _replayButton.setPosition((SCREEN_WIDTH/2)
                                  - (this -> _pauseButton.getGlobalBounds().width / 2),
                                    (SCREEN_HEIGHT)
                                  - (this -> _pauseButton.getGlobalBounds().height * 1.1));
    _grid.setPosition( SCREEN_WIDTH  / 2  - _grid.getGlobalBounds().width   / 2,
                       SCREEN_HEIGHT / 2  - _grid.getGlobalBounds().height  / 2 );
    if (_size == 6) {
        this -> _title_X_Win.setPosition(0, -70);
        this -> _title_O_Win.setPosition(0, -70);
        this -> _title_Draw.setPosition(0, -70);
    } else {
        this -> _title_X_Win.setPosition(0, 0);
        this -> _title_O_Win.setPosition(0, 0);
        this -> _title_Draw.setPosition(0, 0);
    }
    InitGridPieces();
}

void StateGame:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if (turn == PLAYER_PIECE) {
            
            if ( this -> _data -> input.IsSpriteClicked(this -> _pauseButton, sf::Mouse::Left, this -> _data -> window) ) {
                this -> _data -> machine.AddState(StateRef( new StatePause(_data, _size) ), false);
                
                
            } else if ( this -> _data -> input.IsSpriteClicked(this -> _grid, sf::Mouse::Left, this -> _data -> window) ) {
                
                this -> PlacePiece();
            }
        }
        else if (turn == AI_PIECE) {
            this -> PlaceAIPiece();
            
        }
        else if (turn == END_GAME)
            if ( this -> _data -> input.IsSpriteClicked(this -> _replayButton, sf::Mouse::Left, this -> _data -> window) )
                this -> _data -> machine.AddState(StateRef( new StateGame(_data, _size) ), true);  // End Game
    }
}

void StateGame:: Update(float dt) { }

void StateGame:: Draw(float dt) {
    
    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background );
    this -> _data -> window.draw( this -> _grid );
    for (int i = 0; i < _size ; ++i)
        for (int j = 0; j < _size; ++j)
            this -> _data -> window.draw( this -> gridPieces[i][j]);
    
    if      (STATE_DRAW  == gameState)  this -> _data -> window.draw( this -> _title_Draw  );
    else if (STATE_X_WON == gameState)  this -> _data -> window.draw( this -> _title_X_Win );
    else if (STATE_O_WON == gameState)  this -> _data -> window.draw( this -> _title_O_Win );
    if    (STATE_PLAYING != gameState)  this -> _data -> window.draw( this -> _replayButton);
    else                                this -> _data -> window.draw( this -> _pauseButton );
    
    this -> _data -> window.display();
}

void StateGame:: InitGridPieces() {
    
    sf::Vector2u tmpSize = this -> _data -> assets.GetTexture("X Piece").getSize();

    for (int i = 0; i < _size ; ++i) {
        for (int j = 0; j < _size; ++j) {
            gridArray[i][j] = EMPTY_PIECE;
            gridPieces[i][j].setTexture(this -> _data -> assets.GetTexture("X Piece"));
            gridPieces[i][j].setPosition(_grid.getPosition().x + tmpSize.x * i - 7,
                                         _grid.getPosition().y + tmpSize.y * j - 7);
            gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));
        }                                                   // ^ Invisible grid elements
    }
}

void StateGame:: PlacePiece() {
    
    sf::Vector2i touchPoint = this -> _data -> input.GetMousePosition( this -> _data -> window );
    sf::FloatRect gridSize  = _grid.getGlobalBounds();
    sf::Vector2f gapOutsideOfGrid  = sf::Vector2f((SCREEN_WIDTH  - gridSize.width)  / 2,
                                                  (SCREEN_HEIGHT - gridSize.height) / 2 );
    sf::Vector2f gridLocalTouchPoz = sf::Vector2f( touchPoint.x  - gapOutsideOfGrid.x,
                                                   touchPoint.y  - gapOutsideOfGrid.y );
    sf::Vector2f gridSectionSize   = sf::Vector2f( gridSize.width  / _size,
                                                   gridSize.height / _size );
    int col, row;
    switch (_size) {    // Checking what place was clicked for different sizes
        case 3:
            if      ( gridLocalTouchPoz.x < gridSectionSize.x )      col = 1;    // Cols
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 2 )  col = 2;
            else                                                     col = 3;
            if      ( gridLocalTouchPoz.y < gridSectionSize.y )      row = 1;    // Rows
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 2 )  row = 2;
            else                                                     row = 3;
            break;

        case 4:
            if      ( gridLocalTouchPoz.x < gridSectionSize.x )      col = 1;    // Cols
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 2 )  col = 2;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 3 )  col = 3;
            else                                                     col = 4;
            if      ( gridLocalTouchPoz.y < gridSectionSize.y )      row = 1;    // Rows
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 2 )  row = 2;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 3 )  row = 3;
            else                                                     row = 4;
            break;

        case 5:
            if      ( gridLocalTouchPoz.x < gridSectionSize.x )      col = 1;    // Cols
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 2 )  col = 2;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 3 )  col = 3;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 4 )  col = 4;
            else                                                     col = 5;
            if      ( gridLocalTouchPoz.y < gridSectionSize.y )      row = 1;    // Rows
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 2 )  row = 2;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 3 )  row = 3;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 4 )  row = 4;
            else                                                     row = 5;
            break;

        case 6:
            if      ( gridLocalTouchPoz.x < gridSectionSize.x )      col = 1;    // Cols
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 2 )  col = 2;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 3 )  col = 3;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 4 )  col = 4;
            else if ( gridLocalTouchPoz.x < gridSectionSize.x * 5 )  col = 5;
            else                                                     col = 6;
            
            if      ( gridLocalTouchPoz.y < gridSectionSize.y )      row = 1;    // Rows
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 2 )  row = 2;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 3 )  row = 3;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 4 )  row = 4;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 5 )  row = 5;
            else                                                     row = 6;
            break;

        default:
            col = 0; row = 0;
            break;
    }

    if ( gridArray[col-1][row-1] == EMPTY_PIECE ) {
        this -> placeTrun(col-1, row-1);
    }
}

bool StateGame:: CheckIfGameWon(int turn, bool End) {
    
    int flag = 0;
    switch (_size) {
        case 3: {
            
//            int Tab1[12]{0, 0, 1, 0, 2, 0};
//            if (CheckPieces(Tab1, turn, End))    flag++;
//            int Tab2[12]{0, 1, 1, 1, 2, 1};
//            if (CheckPieces(Tab2, turn, End))    flag++;
//            int Tab3[12]{0, 2, 1, 2, 2, 2};
//            if (CheckPieces(Tab3, turn, End))    flag++;
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{0, i, 1, i, 2, i};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            int Tab4[12]{0, 0, 0, 1, 0, 2};
//            if (CheckPieces(Tab4, turn, End))    flag++;
//            int Tab5[12]{1, 0, 1, 1, 1, 2};
//            if (CheckPieces(Tab5, turn, End))    flag++;
//            int Tab6[12]{2, 0, 2, 1, 2, 2};
//            if (CheckPieces(Tab6, turn, End))    flag++;
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{i, 0, i, 1, i, 2};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
            int Tab1[12]{0, 0, 1, 1, 2, 2};
            if (CheckPieces(Tab1, turn, End))    flag++;
            int Tab2[12]{0, 2, 1, 1, 2, 0};
            if (CheckPieces(Tab2, turn, End))    flag++;
            
//            if (Check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn, End)) flag++;
//            if (Check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn, End)) flag++;
//            if (Check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn, End)) flag++;
//            if (Check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn, End)) flag++;
//            if (Check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn, End)) flag++;
//            if (Check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn, End)) flag++;
//            if (Check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn, End)) flag++;
//            if (Check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn, End)) flag++;
            break;
        }
        case 4: {
//            Check4PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, turn);
//            Check4PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, turn);
//            Check4PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, turn);
//            Check4PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{0, i, 1, i, 2, i, 3, i};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check4PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, turn);
//            Check4PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, turn);
//            Check4PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, turn);
//            Check4PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{i, 0, i, 1, i, 2, i, 3};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check4PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, turn);
//            Check4PiecesForMatch(0, 3, 1, 2, 2, 1, 3, 0, turn);
            
            int Tab1[12]{0, 0, 1, 1, 2, 2, 3, 3};
            if (CheckPieces(Tab1, turn, End))    flag++;
            int Tab2[12]{0, 3, 1, 2, 2, 1, 3, 0};
            if (CheckPieces(Tab2, turn, End))    flag++;
            break;
        }
        case 5: {
//            Check5PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, turn);
//            Check5PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, 4, 1, turn);
//            Check5PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, 4, 2, turn);
//            Check5PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, 4, 3, turn);
//            Check5PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{0, i, 1, i, 2, i, 3, i, 4, i};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check5PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, turn);
//            Check5PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, 1, 4, turn);
//            Check5PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, 2, 4, turn);
//            Check5PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, 3, 4, turn);
//            Check5PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{i, 0, i, 1, i, 2, i, 3, i, 4};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check5PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, 4, 4, turn);
//            Check5PiecesForMatch(0, 4, 1, 3, 2, 2, 3, 1, 4, 0, turn);
            
            int Tab1[12]{0, 0, 1, 1, 2, 2, 3, 3, 4, 4};
            if (CheckPieces(Tab1, turn, End))    flag++;
            int Tab2[12]{0, 4, 1, 3, 2, 2, 3, 1, 4, 0};
            if (CheckPieces(Tab2, turn, End))    flag++;
            
            break;
        }
        case 6: {
//            Check6PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, turn);
//            Check6PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, turn);
//            Check6PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, turn);
//            Check6PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, turn);
//            Check6PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, turn);
//            Check6PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 5, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{0, i, 1, i, 2, i, 3, i, 4, i, 5, i};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check6PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, turn);
//            Check6PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, turn);
//            Check6PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, turn);
//            Check6PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, turn);
//            Check6PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, turn);
//            Check6PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 5, 5, turn);
            
            for (int i = 0; i < _size; ++i) {
                int Tab[12]{i, 0, i, 1, i, 2, i, 3, i, 4, i, 5};
                if (CheckPieces(Tab, turn, End))    flag++;
            }
            
//            Check6PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, turn);
//            Check6PiecesForMatch(0, 5, 1, 4, 2, 3, 3, 2, 4, 1, 5, 0, turn);
            
            int Tab1[12]{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
            if (CheckPieces(Tab1, turn, End))    flag++;
            int Tab2[12]{0, 5, 1, 4, 2, 3, 3, 2, 4, 1, 5, 0};
            if (CheckPieces(Tab2, turn, End))    flag++;
            
            break;
        }
    }
    
//    int emptyNum = _size * _size;       // Check if grid is full
//    for ( int i = 0; i < _size; ++i )
//        for ( int j = 0; j < _size; ++j )
//            if ( EMPTY_PIECE != gridArray[i][j] )    emptyNum--;
    
    if (End == true)
        if ( isGridFull() && (STATE_X_WON != gameState) && (STATE_O_WON != gameState) )
            gameState = STATE_DRAW;
    
    if (flag != 0 || STATE_DRAW == gameState || STATE_X_WON == gameState || STATE_O_WON == gameState)
        return true;
    
    return false;
}

bool StateGame:: CheckPieces(int Tab[12], int piece, bool End) {

    switch (_size) {
        case 3:
            if (piece == gridArray[Tab[0]][Tab[1]] && piece == gridArray[Tab[2]][Tab[3]] &&
                piece == gridArray[Tab[4]][Tab[5]]) {
                
                if (End == true)   DrawWinningPieces(Tab, piece);
                return true;
            }
            break;
        case 4:
            if (piece == gridArray[Tab[0]][Tab[1]] && piece == gridArray[Tab[2]][Tab[3]] &&
                piece == gridArray[Tab[4]][Tab[5]] && piece == gridArray[Tab[6]][Tab[7]]) {
                
                if (End == true)   DrawWinningPieces(Tab, piece);
                return true;
            }
            break;
        case 5:
            if (piece == gridArray[Tab[0]][Tab[1]] && piece == gridArray[Tab[2]][Tab[3]] &&
                piece == gridArray[Tab[4]][Tab[5]] && piece == gridArray[Tab[6]][Tab[7]] &&
                piece == gridArray[Tab[8]][Tab[9]]) {
                
                if (End == true)   DrawWinningPieces(Tab, piece);
                return true;
            }
            break;
        case 6:
            if (piece == gridArray[Tab[0]][Tab[1]] && piece == gridArray[Tab[2]][Tab[3]] &&
                piece == gridArray[Tab[4]][Tab[5]] && piece == gridArray[Tab[6]][Tab[7]] &&
                piece == gridArray[Tab[8]][Tab[9]] && piece == gridArray[Tab[10]][Tab[11]]) {
                
                if (End == true)   DrawWinningPieces(Tab, piece);
                return true;
            }
            break;
    }
    return false;
}

void StateGame::PlaceAIPiece() {
    
    int col = -1, row = -1;
    int bestScore = -INF;
    int alfa      = -INF;
    int beta      =  INF;
    int score     =    0;

    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            
            if ( gridArray[i][j] == EMPTY_PIECE ) {
                gridArray[i][j] = AI_PIECE;
                score = MiniMax(gridArray, _depth, false, alfa, beta);
                std:: cout << "\n Score: "<< score << " At: "<< i << "," << j << "\n ";
                if ( bestScore < score ) {
                    bestScore = score;
                    col = i;
                    row = j;
                    std:: cout << "\n Best score update: " << bestScore;
                    std:: cout << "\n col: "<< col;
                    std:: cout << "\n row: "<< row << "\n ";
                }
                gridArray[i][j] = EMPTY_PIECE;
            }
        }
    }
    this -> placeTrun(col,row);
}


int StateGame::MiniMax(int tmpGridArray[6][6], int depth , bool max, int alfa, int beta) {
    
    if (CheckIfGameWon(AI_PIECE, false))        return  10 - depth;
    if (CheckIfGameWon(PLAYER_PIECE, false))    return -10 + depth;
    if (isGridFull() || (depth == 0))           return   0;
    
    if (max) {      // Max
        int bestScore = -INF;
        for (int i = 0; i < _size; ++i)
            for (int j = 0; j < _size; ++j)
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = AI_PIECE;
                    int score = MiniMax(tmpGridArray,depth - 1, false, alfa, beta);
                    bestScore = std::max(bestScore, score);
                    tmpGridArray[i][j] = EMPTY_PIECE;
                    alfa = std::max(score, alfa);
//                    if (beta <= alfa)   break; // Ciecie alfa beta
                }
        return bestScore;
    }
    else {          // Mini
        int bestScore = INF;
        for (int i = 0; i < _size; ++i)
            for (int j = 0; j < _size; ++j)
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = PLAYER_PIECE;
                    int score = MiniMax(tmpGridArray,depth - 1, true, alfa, beta);
                    bestScore = std::min(bestScore, score );
                    tmpGridArray[i][j] = EMPTY_PIECE;
                    beta = std::min(score, beta);
//                    if (beta <= alfa)   break; // Ciecie alfa beta
                }
        return bestScore;
    }
}

bool StateGame::isGridFull() {
    
    int tmp = _size * _size;
    for (int i = 0; i < _size; ++i)
        for (int j = 0; j < _size; ++j)
            if ( EMPTY_PIECE != gridArray[i][j] )   tmp--;
    
    if ( tmp == 0 )     return true;
    else                return false;
}

void StateGame::placeTrun(int col, int row) {
    
    gridArray[col][row] = turn;
    if (turn == PLAYER_PIECE)
        gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("X Piece"));
    else
        gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("O Piece"));
    
    gridPieces[col][row].setColor(sf::Color(255,255,255,255));
    
    if (this -> CheckIfGameWon(turn, true))     turn = END_GAME;
    else            if (turn == PLAYER_PIECE)   turn = AI_PIECE;
                    else                        turn = PLAYER_PIECE;
    
}

void StateGame::DrawWinningPieces(int Tab[12], int winner) {
    std::string name;
    if (O_PIECE == winner )   name = "O Piece Wins";
    else                      name = "X Piece Wins";
    switch (_size) {
        case 3:
            gridPieces[Tab[0]][Tab[1]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[2]][Tab[3]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            break;
        case 4:
            gridPieces[Tab[0]][Tab[1]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[2]][Tab[3]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            break;
        case 5:
            gridPieces[Tab[0]][Tab[1]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[2]][Tab[3]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[8]][Tab[9]].setTexture( this -> _data -> assets.GetTexture(name));
            break;
        case 6:
            gridPieces[Tab[0]][Tab[1]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[2]][Tab[3]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[8]][Tab[9]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[10]][Tab[11]].setTexture( this -> _data -> assets.GetTexture(name));
            break;
        default:
            break;
    }
    if (PLAYER_PIECE == winner)   gameState = STATE_X_WON;
    else                          gameState = STATE_O_WON;
}
