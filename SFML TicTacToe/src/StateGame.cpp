#include "StateGame.hpp"
#include "StatePause.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cmath>

StateGame:: StateGame(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI): _data( data ) {
    _winSize  = winSize;
    _VSAI     = VSAI;
    _isPlayerX = isPlayerX;
    if (_isPlayerX) {
        PlayerPiece = X_PIECE;
        AIPiece     = O_PIECE;
    } else {
        PlayerPiece = O_PIECE;
        AIPiece     = X_PIECE;
    }
    _size = size;
    
    switch (_size) {
        case 3:
            _depth = DEFAULT_DEPTH_3X3;
            break;
        case 4:
            _depth = DEFAULT_DEPTH_4X4;
            break;
        case 5:
            _depth = DEFAULT_DEPTH_5X5;
            break;
        case 6:
            _depth = DEFAULT_DEPTH_6X6;
            break;
        default:
            break;
    }
}

void StateGame:: Init() {

    gameState = STATE_PLAYING;
    if (_isPlayerX)     turn = PlayerPiece;           // Starting player
    else                turn = AIPiece;
    
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
        // if Pause button is clicked
        if (this ->_data ->input.IsSpriteClicked(this->_pauseButton,sf::Mouse::Left,this->_data ->window)) {
            
            this->_data-> machine.AddState(StateRef(new StatePause(_data,_size,_winSize,_isPlayerX,_VSAI)), false);
            
        }
        if (turn == PlayerPiece) {
            // if Grid is clicked
             if (this ->_data->input.IsSpriteClicked(this->_grid,sf::Mouse::Left,this->_data->window)) {
                this -> PlacePiece();
            }
        }
        else if (turn == AIPiece) {
            if (_VSAI)     // if you play VS AI or VS another player
                this -> PlaceAIPiece();
             else     // if Grid is clicked
                if (this ->_data->input.IsSpriteClicked(this ->_grid,sf::Mouse::Left,this->_data ->window))
                    this -> PlacePiece();
        }
        else if (turn == END_GAME)
            if (this->_data->input.IsSpriteClicked(this->_replayButton,sf::Mouse::Left,this->_data->window))
                this->_data->machine.AddState(StateRef(new StateGame(_data, _size, _winSize, _isPlayerX, _VSAI)), true);
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
        this -> DrawTurn(col-1, row-1);
    }
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
                gridArray[i][j] = AIPiece;
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
    this -> DrawTurn(col,row);
}

int  StateGame::MiniMax(int tmpGridArray[6][6], int depth , bool max, int alfa, int beta) {
    
    if (CheckIfGameWon(AIPiece, false))        return  10 - depth;
    if (CheckIfGameWon(PlayerPiece, false))    return -10 + depth;
    if (isGridFull() || (depth == 0))          return   0;
    
    if (max) {      // Max
        int bestScore = -INF;
        for (int i = 0; i < _size; ++i)
            for (int j = 0; j < _size; ++j)
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = AIPiece;
                    int score = MiniMax(tmpGridArray,depth - 1, false, alfa, beta);
                    bestScore = std::max(bestScore, score);
                    tmpGridArray[i][j] = EMPTY_PIECE;
                    alfa = std::max(bestScore, alfa);
                    if (beta <= alfa)   break;      // Ciecie alfa beta
                }
        return bestScore;
    }
    else {          // Mini
        int bestScore = INF;
        for (int i = 0; i < _size; ++i)
            for (int j = 0; j < _size; ++j)
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = PlayerPiece;
                    int score = MiniMax(tmpGridArray,depth - 1, true, alfa, beta);
                    bestScore = std::min(bestScore, score );
                    tmpGridArray[i][j] = EMPTY_PIECE;
                    beta = std::min(bestScore, beta);
                    if (beta <= alfa)   break;      // Ciecie alfa beta
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

void StateGame::DrawTurn(int col, int row) {
    
    gridArray[col][row] = turn;
    if (turn == PlayerPiece)
        if (_isPlayerX)
            gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("X Piece"));
        else
            gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("O Piece"));
    else
        if (_isPlayerX)
            gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("O Piece"));
        else
            gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("X Piece"));
    
    gridPieces[col][row].setColor(sf::Color(255,255,255,255));
    
    if (this -> CheckIfGameWon(turn, true))     turn = END_GAME;
    else            if (turn == PlayerPiece)    turn = AIPiece;
                    else                        turn = PlayerPiece;
    
}

void StateGame::DrawWinningPieces(int Tab[12], int winner) {
    std::string name;
    if (O_PIECE == winner )   name = "O Piece Wins";
    else                      name = "X Piece Wins";
    switch (_winSize) {
        case 3:
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[8]][Tab[9]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[10]][Tab[11]].setTexture( this -> _data -> assets.GetTexture(name));
            break;
        case 4:
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[8]][Tab[9]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[10]][Tab[11]].setTexture( this -> _data -> assets.GetTexture(name));
//            std:: cout << "\n x1 = " << Tab[4] << ", y1 = " << Tab[5];
//            std:: cout << "\n x2 = " << Tab[6] << ", y2 = " << Tab[7];
//            std:: cout << "\n x3 = " << Tab[8] << ", y3 = " << Tab[9];
//            std:: cout << "\n x4 = " << Tab[10] << ", y4 = " << Tab[11];
            
            break;
        case 5:
            gridPieces[Tab[2]][Tab[3]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[4]][Tab[5]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[6]][Tab[7]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[8]][Tab[9]].setTexture( this -> _data -> assets.GetTexture(name));
            gridPieces[Tab[10]][Tab[11]].setTexture( this -> _data -> assets.GetTexture(name));
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
    if (PlayerPiece == winner)      if (_isPlayerX)     gameState = STATE_X_WON;
                                    else                gameState = STATE_O_WON;
    else                            if (_isPlayerX)     gameState = STATE_O_WON;
                                    else                gameState = STATE_X_WON;
}

bool StateGame::CheckIfGameWon(int turn, bool End) {
    
    int won = 0;
    
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++) {
            
            for (int l = 0; l < _winSize; l++) {            // Poziom
                if (gridArray[i + l][j] == turn) {
                    if (l == _winSize - 1) {
                        won = turn;
                        if (End == true) {
                            int Tab[12]{i+l-5, j, i+l-4, j, i+l-3, j, i+l-2, j, i+l-1, j, i+l, j};
                            DrawWinningPieces(Tab, turn);
                        }
                    }
                } else break;
            }
            
            for (int l = 0; l < _winSize; l++) {            // Pion
                if (gridArray[i][j + l] == turn) {
                    if (l == _winSize - 1) {
                        won = turn;
                        if (End == true) {
                            int Tab[12]{i, j+l-5, i, j+l-4, i, j+l-3, i, j+l-2, i, j+l-1, i, j+l};
                            DrawWinningPieces(Tab, turn);
                        }
                    }
                } else break;
            }
            for (int l = 0; l < _winSize; l++) {            // Skos
                if (gridArray[i + l][j + l] == turn) {
                    if (l == _winSize - 1) {
                        won = turn;
                        if (End == true) {
                            int Tab[12]{i+l-5, j+l-5, i+l-4, j+l-4, i+l-3, j+l-3, i+l-2, j+l-2, i+l-1, j+l-1, i+l, j+l};
                            DrawWinningPieces(Tab, turn);
                        }
                    }
                } else break;
            }
            for (int l = 0; l < _winSize; l++) {            // Skos2
                if (gridArray[i + l][j - l] == turn) {
                    if (l == _winSize - 1) {
                        won = turn;
                        if (End == true) {
                            int Tab[12]{i+l-5, j-l+5, i+l-4, j-l+4, i+l-3, j-l+3, i+l-2, j-l+2, i+l-1, j-l+1, i+l, j-l};
                            DrawWinningPieces(Tab, turn);
                        }
                    }
                } else break;
            }
        }
    
    if (End == true)
        if ( isGridFull() && (STATE_X_WON != gameState) && (STATE_O_WON != gameState) )
            gameState = STATE_DRAW;
    
    if (won != 0 || STATE_DRAW == gameState || STATE_X_WON == gameState || STATE_O_WON == gameState)
        return true;
    
    return false;
}
