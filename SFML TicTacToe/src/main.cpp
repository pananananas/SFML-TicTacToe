#include "State.hpp"

#define SCREEN_WIDTH  1024
#define SCREEN_HEIGHT 1024


int main(){
    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "TicTacToe");
    while(window.isOpen()){
        sf::Event event;
        
        while (window.pollEvent(event)){
            
            switch (event.type) {
                    
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                    
                default:
                    break;
            }
        }
        int UsunMniePozniej = 0;
        window.clear();
        // draw the objects
        window.display();
        
    }
    return EXIT_SUCCESS;
    
}
