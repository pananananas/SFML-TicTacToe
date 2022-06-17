#include "StateGame.hpp"
#include "StatePause.hpp"
#include "StateEndGame.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

StateGame:: StateGame(GameDataRef data, int size): _data( data ) { _size = size; }

void StateGame:: InitGridPieces() {
    
    sf::Vector2u tmpSize = this -> _data -> assets.GetTexture("X Piece").getSize();

    for (int i = 0; i < _size ; ++i) {
        for (int j = 0; j < _size; ++j) {
            gridPieces[i][j].setTexture(this -> _data -> assets.GetTexture("X Piece"));
            gridPieces[i][j].setPosition(_grid.getPosition().x + tmpSize.x * i - 7,
                                         _grid.getPosition().y + tmpSize.y * j - 7);
            gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));
        }                                                   // ^ Invisible grid elements
    }
    for (int i = 0; i < _size ; ++i)
        for (int j = 0; j < _size; ++j)
            gridArray[i][j] = EMPTY_PIECE;
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
            if      ( gridLocalTouchPoz.y < gridSectionSize.y * 4 )  row = 4;
            else if ( gridLocalTouchPoz.y < gridSectionSize.y * 5 )  row = 5;
            else                                                     row = 6;
            break;

        default:
            col = 0; row = 0;
            break;
    }

    if ( gridArray[col-1][row-1] == EMPTY_PIECE ) {
        this -> placeTrun(col-1, row-1);
        
//        gridArray[col-1][row-1] = turn;
//
////        if ( PLAYER_PIECE == turn ) {
//
//        gridPieces[col-1][row-1].setTexture( this -> _data -> assets.GetTexture("X Piece"));
//        this -> CheckIfGameWon(turn);
//        turn = AI_PIECE;
////        }
////        else if ( AI_PIECE == turn ) {
////
////            gridPieces[col-1][row-1].setTexture( this -> _data -> assets.GetTexture("O Piece"));
////            this -> CheckIfPlayerWon(turn);
////            turn = PLAYER_PIECE;
////        }
//        gridPieces[col-1][row-1].setColor(sf::Color(255,255,255,255));
    }
}

bool StateGame:: CheckIfGameWon(int turn) {

    switch (_size) {
        case 3:
            Check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn);
            Check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn);
            Check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn);
            Check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn);
            Check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn);
            Check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn);
            Check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn);
            Check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn);
            break;
        case 4:
            Check4PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, turn);
            Check4PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, turn);
            Check4PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, turn);
            Check4PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, turn);
            Check4PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, turn);
            Check4PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, turn);
            Check4PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, turn);
            Check4PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, turn);
            Check4PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, turn);
            Check4PiecesForMatch(0, 3, 1, 2, 2, 1, 3, 0, turn);
            break;
        case 5:
            Check5PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, turn);
            Check5PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, 4, 1, turn);
            Check5PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, 4, 2, turn);
            Check5PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, 4, 3, turn);
            Check5PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, turn);
            Check5PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, turn);
            Check5PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, 1, 4, turn);
            Check5PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, 2, 4, turn);
            Check5PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, 3, 4, turn);
            Check5PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, turn);
            Check5PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, 4, 4, turn);
            Check5PiecesForMatch(0, 4, 1, 3, 2, 2, 3, 1, 4, 0, turn);
            break;
        case 6:
            Check6PiecesForMatch(0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, turn);
            Check6PiecesForMatch(0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, turn);
            Check6PiecesForMatch(0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, turn);
            Check6PiecesForMatch(0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, turn);
            Check6PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, turn);
            Check6PiecesForMatch(0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 5, turn);
            Check6PiecesForMatch(0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, turn);
            Check6PiecesForMatch(1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, turn);
            Check6PiecesForMatch(2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, turn);
            Check6PiecesForMatch(3, 0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, turn);
            Check6PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, turn);
            Check6PiecesForMatch(4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 5, 5, turn);
            Check6PiecesForMatch(0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, turn);
            Check6PiecesForMatch(0, 5, 1, 4, 2, 3, 3, 2, 4, 1, 5, 0, turn);
            break;
        default:
            break;
    }
    
    int emptyNum = _size * _size;       // Check if grid is full
    for ( int i = 0; i < _size; ++i )
        for ( int j = 0; j < _size; ++j )
            if ( EMPTY_PIECE != gridArray[i][j] )    emptyNum--;
    
    
    if ( isGridFull() && (STATE_WON != gameState) && (STATE_LOSE != gameState) )
        gameState = STATE_DRAW;
    
    if ( STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
        
        // GAME OVER
        this -> _data -> machine.AddState(StateRef( new StateEndGame(_data, _size) ), true);
        return true;
    }
    return false;
}



void StateGame:: Init() {

    gameState = STATE_PLAYING;
    turn      = PLAYER_PIECE;           // Kto zaczyna

    this -> _data -> assets.LoadTexture( "Game Background", PAUSE_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture( "Pause Button", PAUSE_BUTTON );
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
    this -> _data -> assets.LoadTexture("X Piece", X_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("O Piece", O_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("X Piece Wins", X_WINNING_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture("O Piece Wins", O_WINNING_PIECE_FILEPATH );
    
    _background.setTexture  ( this -> _data -> assets.GetTexture("Game Background") );
    _pauseButton.setTexture ( this -> _data -> assets.GetTexture("Pause Button") );
    _grid.setTexture        ( this -> _data -> assets.GetTexture("Grid") );
    
    _pauseButton.setPosition( this -> _data -> window.getSize().x / 2
                           - _pauseButton.getLocalBounds().width  / 2,
                             _pauseButton.getPosition().y );
    _grid.setPosition( SCREEN_WIDTH  / 2  - _grid.getGlobalBounds().width   / 2,
                       SCREEN_HEIGHT / 2  - _grid.getGlobalBounds().height  / 2 );
    InitGridPieces();
}

void StateGame:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if (turn == PLAYER_PIECE) {
            
            if ( this -> _data -> input.IsSpriteClicked(this -> _pauseButton, sf::Mouse::Left, this -> _data -> window) ) {
                
                this -> _data -> machine.AddState(StateRef( new StatePause(_data, _size) ), false); // Pause
             // false cuz we dont want to replace current state, we only want to pause this one
            

            } else if ( this -> _data -> input.IsSpriteClicked(this -> _grid, sf::Mouse::Left, this -> _data -> window) ) {
            
//                if (STATE_PLAYING == gameState)
                    this -> PlacePiece();

            //         this -> _data -> machine.AddState(StateRef( new StateEndGame(_data, _size) ), true);  // End Game
            }
        }
        else if (turn == AI_PIECE) {
            this -> PlaceAIPiece(gridArray,gridPieces);
            
        }
        else
            std::cout << " It's nobody's turn!!! :c \n";
    }
}

void StateGame:: Update(float dt) { }

void StateGame:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background  );
    this -> _data -> window.draw( this -> _pauseButton );
    this -> _data -> window.draw( this -> _grid        );
    for (int i = 0; i < _size ; ++i)
        for (int j = 0; j < _size; ++j)
            this -> _data -> window.draw( this -> gridPieces[i][j]);
    this -> _data -> window.display();
}

void StateGame:: Check3PiecesForMatch(int x1, int y1, int x2,
                                      int y2, int x3, int y3,
                                      int pieceToCheck) {
    if (pieceToCheck == gridArray[x1][y1] &&
        pieceToCheck == gridArray[x2][y2] &&
        pieceToCheck == gridArray[x3][y3])
    {
        
        std::string winningPieceStr;
        if (O_PIECE == pieceToCheck )   winningPieceStr = "O Piece Wins";
        else                            winningPieceStr = "X Piece Wins";
        
        gridPieces[x1][y1].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x2][y2].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x3][y3].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        
        
        if (PLAYER_PIECE == pieceToCheck)   gameState = STATE_WON;
        else                                gameState = STATE_LOSE;
    }
}

void StateGame:: Check4PiecesForMatch(int x1, int y1, int x2, int y2,
                                      int x3, int y3, int x4, int y4,
                                      int pieceToCheck) {
    if (pieceToCheck == gridArray[x1][y1] &&
        pieceToCheck == gridArray[x2][y2] &&
        pieceToCheck == gridArray[x3][y3] &&
        pieceToCheck == gridArray[x4][y4])
    {
        
        std::string winningPieceStr;
        if (O_PIECE == pieceToCheck )   winningPieceStr = "O Piece Wins";
        else                            winningPieceStr = "X Piece Wins";
        
        gridPieces[x1][y1].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x2][y2].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x3][y3].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x4][y4].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        
        if (PLAYER_PIECE == pieceToCheck)   gameState = STATE_WON;
        else                                gameState = STATE_LOSE;
    }
}

void StateGame:: Check5PiecesForMatch(int x1, int y1, int x2, int y2, int x3,
                                      int y3, int x4, int y4, int x5, int y5,
                                      int pieceToCheck) {
    if (pieceToCheck == gridArray[x1][y1] &&
        pieceToCheck == gridArray[x2][y2] &&
        pieceToCheck == gridArray[x3][y3] &&
        pieceToCheck == gridArray[x4][y4] &&
        pieceToCheck == gridArray[x5][y5])
    {
        std::string winningPieceStr;
        if (O_PIECE == pieceToCheck )   winningPieceStr = "O Piece Wins";
        else                            winningPieceStr = "X Piece Wins";
        
        gridPieces[x1][y1].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x2][y2].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x3][y3].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x4][y4].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x5][y5].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        
        if (PLAYER_PIECE == pieceToCheck)   gameState = STATE_WON;
        else                                gameState = STATE_LOSE;
    }
}

void StateGame:: Check6PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3,
                                      int x4, int y4, int x5, int y5, int x6, int y6,
                                      int pieceToCheck) {
    if (pieceToCheck == gridArray[x1][y1] &&
        pieceToCheck == gridArray[x2][y2] &&
        pieceToCheck == gridArray[x3][y3] &&
        pieceToCheck == gridArray[x4][y4] &&
        pieceToCheck == gridArray[x5][y5] &&
        pieceToCheck == gridArray[x6][y6])
    {
        std::string winningPieceStr;
        if (O_PIECE == pieceToCheck )   winningPieceStr = "O Piece Wins";
        else                            winningPieceStr = "X Piece Wins";
        
        gridPieces[x1][y1].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x2][y2].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x3][y3].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x4][y4].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x5][y5].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        gridPieces[x6][y6].setTexture( this -> _data -> assets.GetTexture(winningPieceStr));
        
        if (PLAYER_PIECE == pieceToCheck)   gameState = STATE_WON;
        else                                gameState = STATE_LOSE;
    }
}




void StateGame::PlaceAIPiece(int tmpGridArray[6][6], sf::Sprite gridPieces[6][6]) {
    
    int col = 0, row = 0;
    int bestScore = -INF;
    
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            
            if ( gridArray[i][j] == EMPTY_PIECE ) {
                gridArray[i][j] = AI_PIECE;
                
                int score = MiniMax(gridArray, 0, false );
                gridArray[i][j] = EMPTY_PIECE;
                std:: cout << "\n Score: "<< score << " At: "<<i<<","<<j << "\n ";
                if ( bestScore < score ) {
                    
                    bestScore = score;
                    
                    col = i;
                    row = j;
                    std:: cout << "\n col: "<< col;
                    std:: cout << "\n row: "<< row << "\n ";
                }
            }
        }
    }
    this -> placeTrun(col,row);
    
    std:: cout << "\n Best Score: " << bestScore ;
    std:: cout << "\n BEST MOVE HERE:  " << col << "," << row;
//    gridArray[col][row] = turn;
//    gridPieces[col][row].setTexture( this -> _data -> assets.GetTexture("O Piece"));
//    gridPieces[col][row].setColor(sf::Color(255,255,255,255));
//    this -> CheckIfGameWon(turn);
//    turn = PLAYER_PIECE;
}


//void StateGame::PlaceAIPiece() {
//
//    int Naj = -INF;
//    int row = -1;
//    int col = -1;
//
//    for (int i = 0; i < _size; i++)
//        for (int j = 0; j < _size; j++)
//            if (gridArray[i][j] == EMPTY_PIECE)
//            {
//                gridArray[i][j] = AI_PIECE;
//                int Ruch = MiniMax(gridArray, 0, false);
//                gridArray[i][j] = EMPTY_PIECE;
//                if (Ruch > Naj) {
//                    row = i;
//                    col = j;
//                    Naj = Ruch;
//                }
//            }
//
//
//    this -> placeTrun(row,col);
//}

int StateGame::MiniMax(int tmpGridArray[6][6], int depth , bool max) {
    
    int result = this -> checkWinner();
    if (result != 0)        return result;
    if (isGridFull())       return 0;
    
    if (max) {      // Max
        int bestScore = -INF;
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = AI_PIECE;
                    bestScore = std::max(bestScore, MiniMax(tmpGridArray,depth + 1, false));
                    tmpGridArray[i][j] = EMPTY_PIECE;
                }
            }
        }
        return bestScore;
    } else {        // Mini
        int bestScore = INF;
        for (int i = 0; i < _size; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (tmpGridArray[i][j] == EMPTY_PIECE) {
                    tmpGridArray[i][j] = PLAYER_PIECE;
                    bestScore = std::min(bestScore, MiniMax(tmpGridArray,depth + 1, true));
                    tmpGridArray[i][j] = EMPTY_PIECE;
                }
            }
        }
        return bestScore;
    }
}

int StateGame:: checkWinner() {
    
    int winner = 0;
    
    if (this -> isGridFull())       winner = 99;   // Tie
    
    for (int i = 0; i < _size; ++i) {
        if (gridArray[i][0] == gridArray[i][1] == gridArray[i][2])  winner = gridArray[i][0];
        if (gridArray[0][i] == gridArray[1][i] == gridArray[2][i])  winner = gridArray[0][i];
    }
    
    if (gridArray[0][0] == gridArray[1][1] == gridArray[2][2])      winner = gridArray[0][0];
    if (gridArray[2][0] == gridArray[1][1] == gridArray[0][2])      winner = gridArray[2][0];
//    std :: cout << " \n WINNERRRRRRRRRR = " << winner;
    return winner;
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
    this -> CheckIfGameWon(turn);
    
    if (turn == PLAYER_PIECE)   turn = AI_PIECE;
    else                        turn = PLAYER_PIECE;
}
