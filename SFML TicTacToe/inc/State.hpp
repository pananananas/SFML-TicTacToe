#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

namespace Sonar {

class State{
    
public:
    virtual void Init() = 0;
    virtual void HandleInput() = 0;
    virtual void Update();
    virtual void Draw(float dt) = 0;
    
    virtual void Pause()  {};
    virtual void Resume() {};
    
};
    
}





 
