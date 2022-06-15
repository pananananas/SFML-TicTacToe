#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"


class Algorithm {
    
    void CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCkeck,
                      int(*gridArray)[6][6], sf::Sprite gridPieces[6][6]);
    void CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[6][6], sf::Sprite gridPieces[6][6]);
    int aiPiece;
    int playerPiece;
//    std::vector<std::array<int, 6>> checkMatchVector;
    GameDataRef _data;
    int _size;
    
public:
    Algorithm() {};
    Algorithm(int playerPiece, GameDataRef data, int size);
    
    void PlacePiece( int(*gridArray)[6][6], sf::Sprite gridPieces[6][6], int &turn);
    
};
