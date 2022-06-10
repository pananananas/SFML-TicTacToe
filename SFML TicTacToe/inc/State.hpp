#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

namespace Game {

class State{
    
public:
    virtual void Init() = 0;            // Initialization of the state
    virtual void HandleInput() = 0;     // Handling all input in that state
    virtual void Update() = 0;          // Update game with input from the user
    virtual void Draw(float dt) = 0;    // Draw app dt - time difference between frames for smooth gameplay
    
    virtual void Pause()  {};
    virtual void Resume() {};
    
    
};

}
