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
    this -> _data -> assets.LoadTexture( "X Piece", X_PIECE_FILEPATH );
    this -> _data -> assets.LoadTexture( "O Piece", O_PIECE_FILEPATH );
    
    
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

        if ( this -> _data -> input.IsSpriteClicked(this -> _pauseButton, sf::Mouse::Left, this -> _data -> window) ){
            this -> _data -> machine.AddState(StateRef( new StatePause(_data, _size) ), false); // Pause
                                                                              // false cuz we dont want to replace current state, we only want to pause this one
            
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


