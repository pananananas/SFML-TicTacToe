#include "Algorithm.hpp"
#include "Definitions.hpp"
#include <iostream>


Algorithm:: Algorithm(int playerPiece, GameDataRef data, int size) {
    
    this -> _data = data;
    this -> _size = size;
    this -> playerPiece = playerPiece;
    
    if (playerPiece == O_PIECE)     aiPiece = X_PIECE;
    else                            aiPiece = O_PIECE;
    
//    checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
//    checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
//    checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
//    checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
//    checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
//    checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
//    checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
//    checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
//    checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
//    checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
//    checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
//    checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
//    checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
//    checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
//    checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
//    checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
//    checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
//    checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
//    checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
//    checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
//    checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
//    checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
//    checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
//    checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
    
    
    
    
}

void Algorithm::PlacePiece(int (*gridArray)[6][6], sf::Sprite gridPieces[6][6], int &turn) {
    
    
    
    
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            
         
            
            
            
        }
    }
    
    gridPieces[1][1].setTexture( this -> _data -> assets.GetTexture("O Piece"));
    
    turn = PLAYER_PIECE;
}
