#pragma once
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>


struct GameData {
    
    StateMachine      machine;
    sf::RenderWindow  window;
    AssetManager      assets;
    InputManager      input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game {
    
    const float  dt = 1.0f / 60.0f;      // Frame rate
    sf::Clock   _clock;
    GameDataRef _data = std::make_shared<GameData>();
    
    void Run();
    
public:
    Game(int width, int height, std::string title);
};
