#include "GameScreenState.h"
#include <algorithm>
#include <SFML/Graphics.hpp>


GameScreenState::GameScreenState() {
	pos = sf::Vector2f(300, 100);
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	level.push_back(rectangle(sf::Vector2f(200, 200), sf::Vector2f(400, 250)));
	updateSprites();
}

void GameScreenState::event(const sf::Event& event) {

}

void GameScreenState::updateSprites() {
	sprites.clear();
	sprites.resize(level.size() + 1);
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
	sf::RectangleShape sprite;
	sprite.setSize(sf::Vector2f(40, 40));
	sprite.setFillColor(sf::Color::Red);
	sprite.setPosition(pos - sf::Vector2f(20, 20));
	sprites.push_back(sprite);
}

void GameScreenState::render(sf::RenderTarget& target) {
	updateSprites();
	target.clear(sf::Color::White);
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}


void GameScreenState::update(const sf::Time& time) {
	float s = time.asSeconds();
	pos = pos + velocity * s;
	sf::Vector2f oldv = velocity;
	velocity = velocity + s * acceleration;
	acceleration = sf::Vector2f(0, 80);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = 100;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -100;
	} else {
		velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (velocity.y == 0) velocity.y = -100; // FIXME
	}
	rectangle me_ex = rectangle(pos - sf::Vector2f(20, 19.9), pos + sf::Vector2f(20, 19.9));
	rectangle me_ey = rectangle(pos - sf::Vector2f(19.9, 20), pos + sf::Vector2f(19.9, 20));
	for (unsigned int i = 0; i < level.size(); i++) {
		//if (!level[i].intersects(me_ex)) continue;
		//if (!((level[i].minp.x > me.maxp.x) || (me.minp.x > level[i].maxp.x))) {
		if (level[i].intersects(me_ex)) {
			if (me_ey.minp.x >= level[i].minp.x) {
				if (me_ey.minp.x >= level[i].maxp.x + oldv.x * s)
					pos.x += std::max(level[i].maxp.x - me_ex.minp.x, (float)0);
				velocity.x = std::max(velocity.x, (float)0);
				acceleration.x = std::max(acceleration.x, (float)0);
			}
			if (me_ey.maxp.x <= level[i].maxp.x) {
				if (me_ey.maxp.x <= level[i].minp.x + oldv.x * s)
					pos.x += std::min(level[i].minp.x - me_ex.maxp.x, (float)0);
				velocity.x = std::min(velocity.x, (float)0);
				acceleration.x = std::min(acceleration.x, (float)0);
			}
		}
		//if (!((level[i].minp.y > me.maxp.y) || (me.minp.y > level[i].maxp.y))) {
		if (level[i].intersects(me_ey)) {
			if (me_ex.minp.y >= level[i].minp.y) {
				if (me_ex.minp.y >= level[i].maxp.y + oldv.y * s)
					pos.y += std::max(level[i].maxp.y - me_ey.minp.y, (float)0);
				velocity.y = std::max(velocity.y, (float)0);
				acceleration.y = std::max(acceleration.y, (float)0);
			}
			if (me_ex.maxp.y <= level[i].maxp.y) {
				if (me_ex.maxp.y <= level[i].minp.y + oldv.y * s)
					pos.y += std::min(level[i].minp.y - me_ey.maxp.y, (float)0);
				velocity.y = std::min(velocity.y, (float)0);
				acceleration.y = std::min(acceleration.y, (float)0);
			}
		}
	}
}
