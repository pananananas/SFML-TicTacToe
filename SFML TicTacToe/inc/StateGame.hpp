#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"

class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _grid;
    sf::Sprite  _title_X_Win;
    sf::Sprite  _title_O_Win;
    sf::Sprite  _title_Draw;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    sf::Sprite  _replayButton;
    sf::Sprite   gridPieces[6][6];
    int   gridArray[6][6];
    int   gameState;
    int   turn;
    int  _size;
    int  _depth;
    int  _winSize;
    bool _VSAI;
    bool _isPlayerX;
    int   PlayerPiece;
    int   AIPiece;
    void InitGridPieces();
    bool isGridFull();
    void PlacePiece();
    void PlaceAIPiece();
    void placeTrun(int col, int row);
    bool CheckIfGameWon(int turn, bool End);
    void DrawWinningPieces(int Tab[12], int winner);
    int  MiniMax(int tmpgridArray[6][6], int depth , bool max, int alfa, int beta);
//    bool CheckPieces(int Tab[12], int piece, bool End);
//    void DrawWinningPieces(int Tab[12], int winner);
//    bool CheckIfGameWonOld(int turn, bool End);
    
public:
    StateGame(GameDataRef data, int size, int winSize, bool isPlayerX, bool VSAI);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
};
