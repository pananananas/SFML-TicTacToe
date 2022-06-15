#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "StateMainMenu.hpp"
#include "Algorithm.hpp"


class StateGame: public State {
    
    GameDataRef _data;
    sf::Sprite  _background;
    sf::Sprite  _pauseButton;
    sf::Sprite  _grid;
    int          turn;
    int          gameState;
    int         _size;
    int          gridArray[6][6];
    sf::Sprite   gridPieces[6][6];
    void    InitGridPieces();
    void    PlacePiece();
    bool    CheckIfGameWon(int turn);
    void    Check3PiecesForMatch(int x1, int y1, int x2,
                                 int y2, int x3, int y3,
                                 int pieceToCheck);
    void    Check4PiecesForMatch(int x1, int y1, int x2, int y2,
                                 int x3, int y3, int x4, int y4,
                                 int pieceToCheck);
    void    Check5PiecesForMatch(int x1, int y1, int x2, int y2, int x3,
                                 int y3, int x4, int y4, int x5, int y5,
                                 int pieceToCheck);
    void    Check6PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3,
                                 int x4, int y4, int x5, int y5, int x6, int y6,
                                 int pieceToCheck);
    
    int checkWinner();
    bool isGridFull();
    
    
    Algorithm   AI;
public:
    
    
    StateGame(GameDataRef data, int size);
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw(float dt);
    
    void PlaceAIPiece( int tmpGridArray[6][6], sf::Sprite gridPieces[6][6], int &turn);
    int  MiniMax(    int tmpgridArray[6][6], int depth , bool max);
};



//int minimax(char board[3][3], int depth, bool isMax)
//{
//    int score = evaluate(board);
//    if (score == 10)                return score;
//    if (score == -10)               return score;
////    if (isMovesLeft(board)==false)  return 0;
// 
//    if (isMax) {
//        int best = -1000;
//        for (int i = 0; i<3; i++) {
//            for (int j = 0; j<3; j++) {
//                if (board[i][j]=='_') {
//
//                    board[i][j] = player;
//                    best = max( best, minimax(board, depth+1, !isMax) );
//                    board[i][j] = '_';
//                }
//            }
//        }
//        return best;
//    } else {
//        int best = 1000;
//        for (int i = 0; i<3; i++) {
//            for (int j = 0; j<3; j++) {
//                if (board[i][j]=='_') {
//                    
//                    board[i][j] = opponent;
//                    best = min(best, minimax(board, depth+1, !isMax));
//                    board[i][j] = '_';
//                }
//            }
//        }
//        return best;
//    }
//}

