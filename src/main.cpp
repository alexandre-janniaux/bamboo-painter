#include <SFML/Graphics.hpp>
#include "GameScreenState.h"
#include "MenuScreenState.h"

#include "Stickman.hpp"


int main(int argc, char** argv) {

	sf::RenderWindow window;
	sf::String window_title = "Bamboo Painter";
	sf::VideoMode window_mode (800,600);

	window.create(window_mode, window_title);
	window.setFramerateLimit(60);

	// TODO: meilleur gestion des écrans de jeu
	MenuScreenState menu_screen_state;
	GameScreenState gameScreenState;

	sf::Event event;
	sf::Clock clock;

	StickmanModel model(10.f, 10.f, 10.f, 10.f);

	StickmanEditorView view;
	view.setModel(model);
	view.move(50.f, 50.f);

	while (window.isOpen()) {
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::Closed)
                window.close();
            else 
                 //menu_screen_state.event(window, event);
                 gameScreenState.event(window, event);
	    }
		
		window.clear();
		gameScreenState.render(window);
		//menu_screen_state.render(window);
		window.draw(view);
		window.display();
		gameScreenState.window_update(window);
		gameScreenState.update(clock.getElapsedTime());
		//menu_screen_state.update(clock.getElapsedTime());
		clock.restart();
		
	}
}
