#include <SFML/Graphics.hpp>
#include "GameScreenState.h"


int main(int argc, char** argv) {

	sf::RenderWindow window;
	sf::String window_title = "Bamboo Painter";
	sf::VideoMode window_mode (800,600);

	window.create(window_mode, window_title);
	window.setFramerateLimit(60);

    // TODO: meilleur gestion des écrans de jeu
	GameScreenState gameScreenState;

	sf::Event event;
    sf::Clock clock;

	while (window.isOpen()) {
	    while (window.pollEvent(event)) {
	        if (event.type == sf::Event::Closed)
                window.close();
            else 
                gameScreenState.event(event);
	    }

	    window.clear();
	    gameScreenState.render(window);
	    window.display();
        gameScreenState.update(clock.getElapsedTime());
        clock.restart();
	}
}
