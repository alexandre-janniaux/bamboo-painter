#include "GameScreenState.h"

#include <SFML/Graphics.hpp>


GameScreenState::GameScreenState() {
	level.push_back(rectangle(sf::Vector2f(200, 200), sf::Vector2f(400, 400)));
	updateSprites();
}

void GameScreenState::event(const sf::Event& event) {

}

void GameScreenState::updateSprites() {
	sprites.clear();
	sprites.resize(level.size());
	for (unsigned int i = 0; i < level.size(); i++) {
		sf::RectangleShape sprite;
		//sf::Sprite sprite;
		//sf::Texture tex;
		sprite.setSize(level[i].maxp - level[i].minp);
		sprite.setFillColor(sf::Color::Black);
		//sprite.setTextureRect(sf::IntRect(0, 0,
		//	(int)(level[i].maxp.x - level[i].minp.x),
		//	(int)(level[i].maxp.y - level[i].minp.y)));
		//tex.create((int)(level[i].maxp.x - level[i].minp.x),
		//			(int)(level[i].maxp.y - level[i].minp.y));
		//sprite.setTexture(tex);
		sprite.setPosition(level[i].minp);
		sprites.push_back(sprite);
	}
}

void GameScreenState::render(sf::RenderTarget& target) {
	target.clear(sf::Color::White);
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}


void GameScreenState::update(const sf::Time& time) {

}
