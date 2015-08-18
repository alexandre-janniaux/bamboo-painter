#include "cpp_std_11.h"

#include <SFML/Graphics.hpp>
#include "GameScreenState.h"
#include "MenuScreenState.h"
#include "ScreenStack.h"


int main(int argc, char** argv) 
{
	sf::RenderWindow window;
	sf::String window_title = "Bamboo Painter";
	sf::VideoMode window_mode (800,600);

	window.create(window_mode, window_title);
	window.setFramerateLimit(60);
	
	ScreenStack screenStack;
	screenStack.registerState(ScreenState::Menu, make_unique<MenuScreenState>());
	screenStack.registerState(ScreenState::Game, make_unique<GameScreenState>());
	
	screenStack.pushState(ScreenState::Game);

	sf::Event event;
    sf::Clock clock;

	while (window.isOpen()) {
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::Closed)
                window.close();
            else 
				//menu_screen_state.event(window, event);
                screenStack.onEvent(window, event);
	    }
		
	    window.clear();
	    screenStack.onDraw(window);
		//menu_screen_state.render(window);
	    window.display();
		//screenStack.window_update(window);
		screenStack.onUpdate(clock.getElapsedTime());
		//menu_screen_state.update(clock.getElapsedTime());
        clock.restart();
		
	}
}
