#include "StateGame.hpp"
#include "StatePause.hpp"
#include "StateEndGame.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

StateGame:: StateGame(GameDataRef data, int size): _data( data ) { _size = size; }

void StateGame:: InitGridPieces() {
    
    sf::Vector2u tmpSize = this -> _data -> assets.GetTexture("X Piece").getSize();

    for (int i = 0; i < _size ; ++i) {
        for (int j = 0; j < _size; ++j) {
            gridPieces[i][j].setTexture(this -> _data -> assets.GetTexture("X Piece"));
            gridPieces[i][j].setPosition(_grid.getPosition().x + tmpSize.x * i - 7,
                                         _grid.getPosition().y + tmpSize.y * j - 7);
            gridPieces[i][j].setColor(sf::Color(255, 255, 255, 0));
        }
    }
}

void StateGame:: PlacePiece() {
    
    //  Vector with 2 int
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
        gridArray[col-1][row-1] = turn;
        if ( PLAYER_PIECE == turn ) {

            gridPieces[col-1][row-1].setTexture( this -> _data -> assets.GetTexture("X Piece"));
            this -> CheckIfPlayerWon(turn);
            turn = AI_PIECE;
        }
        else if ( AI_PIECE == turn ) {

            gridPieces[col-1][row-1].setTexture( this -> _data -> assets.GetTexture("O Piece"));
            this -> CheckIfPlayerWon(turn);
            turn = PLAYER_PIECE;
        }
        gridPieces[col-1][row-1].setColor(sf::Color(255,255,255,255));
    }
}

void StateGame:: CheckIfPlayerWon(int turn) {
                                // ROZPISZ TO SOBIE
    Check3PiecesForMatch(0, 0, 1, 0, 2, 0, turn);
    Check3PiecesForMatch(0, 1, 1, 1, 2, 1, turn);
    Check3PiecesForMatch(0, 2, 1, 2, 2, 2, turn);
    Check3PiecesForMatch(0, 0, 0, 1, 0, 2, turn);
    Check3PiecesForMatch(1, 0, 1, 1, 1, 2, turn);
    Check3PiecesForMatch(2, 0, 2, 1, 2, 2, turn);
    Check3PiecesForMatch(0, 0, 1, 1, 2, 2, turn);
    Check3PiecesForMatch(0, 2, 1, 1, 2, 0, turn);
    
    int emptyNum = _size * _size;
    
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            
            if ( EMPTY_PIECE != gridArray[i][j]) {
                --emptyNum;
            }
            
        }
    }
    if ( (emptyNum == 0) && (STATE_WON != gameState) && (STATE_LOSE != gameState) ) {
        
        gameState = STATE_DRAW;
        
    }
    
    if ( STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
        
        // GAME OVER
//        this -> _data -> machine.AddState(StateRef( new StateEndGame(_data, _size) ), true);
    }
    std::cout << gameState << std:: endl;
    
}

void StateGame:: Check3PiecesForMatch(int x1, int y1,
                                      int x2, int y2,
                                      int x3, int y3,
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

void StateGame:: Init() {

    gameState = STATE_PLAYING;
    turn      = PLAYER_PIECE;

    this -> _data -> assets.LoadTexture( "Game Background", PAUSE_BACKGROUND_FILEPATH);
    this -> _data -> assets.LoadTexture( "Pause Button", PAUSE_BUTTON );
    switch (_size) {
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
    
    _background.setTexture(  this -> _data -> assets.GetTexture("Game Background") );
    _pauseButton.setTexture( this -> _data -> assets.GetTexture("Pause Button") );
    _grid.setTexture(        this -> _data -> assets.GetTexture("Grid") );
    
    _pauseButton.setPosition( this -> _data -> window.getSize().x / 2
                           - _pauseButton.getLocalBounds().width  / 2,
                             _pauseButton.getPosition().y );
    _grid.setPosition( SCREEN_WIDTH / 2  - _grid.getGlobalBounds().width   / 2,
                       SCREEN_HEIGHT / 2  - _grid.getGlobalBounds().height  / 2 );

    
    InitGridPieces();
    for (int i = 0; i < _size ; ++i) {
        for (int j = 0; j < _size; ++j) {
            gridArray[i][j] = EMPTY_PIECE;
            
        }
    }
}

void StateGame:: HandleInput() {

    sf::Event event;

    while (this -> _data -> window.pollEvent(event)) {

        if (sf::Event::Closed == event.type)
            this -> _data -> window.close();

        if ( this -> _data -> input.IsSpriteClicked(this -> _pauseButton, sf::Mouse::Left, this -> _data -> window) ) {
            this -> _data -> machine.AddState(StateRef( new StatePause(_data, _size) ), false); // Pause
                // false cuz we dont want to replace current state, we only want to pause this one
            

        } else if ( this -> _data -> input.IsSpriteClicked(this -> _grid, sf::Mouse::Left, this -> _data -> window) ) {
            
            if (STATE_PLAYING == gameState) {
                this -> PlacePiece();
            }
            //         this -> _data -> machine.AddState(StateRef( new StateEndGame(_data, _size) ), true);  // End Game
            
        }
    }
}

void StateGame:: Update(float dt) {

}

void StateGame:: Draw(float dt) {

    this -> _data -> window.clear();
    this -> _data -> window.draw( this -> _background);
    this -> _data -> window.draw( this -> _pauseButton);
    this -> _data -> window.draw( this -> _grid);
    for (int i = 0; i < _size ; ++i) {
        for (int j = 0; j < _size; ++j) {
            this -> _data -> window.draw( this -> gridPieces[i][j]);
        }
    }
    this -> _data -> window.display();
}


