#include "GameScreenState.h"
#include <algorithm>
#include <SFML/Graphics.hpp>

//const int TOP = 1;
//const int BOTTOM = 2;
//const int LEFT = 4;
//const int RIGHT = 8;
const unsigned char TOP = 0;
const unsigned char BOTTOM = 1;
const unsigned char LEFT = 2;
const unsigned char RIGHT = 3;

inline float clamp(float x, float min, float max) {
	 return std::max(std::min(x, max), min);
}

GameScreenState::GameScreenState() {
	pos = sf::Vector2f(300, 100);
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	level_bbox = rectangle(0, 0, 3000, 600);
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
	level.push_back(rectangle(200, 400, 400, 450, 2));
	level.push_back(rectangle(400, 260, 450, 450, 3));
	level.push_back(rectangle(100, 200, 200, 450, 1));
	level.push_back(rectangle(95, 200, 100, 455, 2));
	level.push_back(rectangle(200, 200, 205, 455, 2));
	level.push_back(rectangle(100, 450, 200, 455, 2));
	level.push_back(rectangle(600, 450, 1000, 500, 2));
	level.push_back(rectangle(1200, 300, 2500, 350, 2));

	level.push_back(rectangle(0, 0, 3000, 2, 3));
	level.push_back(rectangle(0, 0, 2, 600, 3));
	level.push_back(rectangle(2998, 0, 3000, 600, 3));
	level.push_back(rectangle(0, 598, 3000, 600, 3));
	updateSprites();
}

void GameScreenState::event(const sf::Event& event) {

}

void GameScreenState::updateSprites() {
	sprites.clear();
	sprites.resize(level.size() + 1);
	static sf::Color colors[4] = {sf::Color::White, sf::Color::Blue, sf::Color::Black, sf::Color::Yellow};
	for (unsigned int i = 0; i < level.size(); i++) {
		sf::RectangleShape sprite;
		//sf::Sprite sprite;
		//sf::Texture tex;
		sprite.setSize(level[i].maxp - level[i].minp);
		sprite.setFillColor(colors[level[i].color]);
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
	sf::View view = target.getDefaultView();
	sf::Vector2f size = view.getSize();
	sf::Vector2f center
		(clamp(pos.x, level_bbox.minp.x + size.x / 2,
			level_bbox.maxp.x - size.x / 2),
		clamp(pos.y, level_bbox.minp.y + size.y / 2,
			level_bbox.maxp.y - size.y / 2));
	view.setCenter(center);
	target.setView(view);
	target.clear(sf::Color::White);
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}


void GameScreenState::update(const sf::Time& time) {
	float s = time.asSeconds();
	pos += velocity * s + ((float) 0.5) * s * s * acceleration;
	sf::Vector2f oldv = velocity + ((float) 0.5) * s * acceleration;
	velocity += s * acceleration;
	acceleration = sf::Vector2f(0, 240);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = std::min(velocity.x + 400 * s, (float)200);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = std::max(velocity.x - 400 * s, (float)-200);
	} else {
		//velocity.x = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		switch (touching_walls[BOTTOM]) {
			case 1:
				velocity.y -= 500 * s;
				break;
			case 2:
			case 3:
				velocity.y -= 150;
		}
	}
	velocity.x = std::max(std::min(velocity.x, (float)1500), (float)-1500);
	velocity.y = std::max(std::min(velocity.y, (float)1500), (float)-1500);
	rectangle me_ex = rectangle(pos - sf::Vector2f(20, 19.9), pos + sf::Vector2f(20, 19.9));
	rectangle me_ey = rectangle(pos - sf::Vector2f(19.9, 20), pos + sf::Vector2f(19.9, 20));
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
	for (unsigned int i = 0; i < level.size(); i++) {
		if (level[i].color < 2) continue; // Not solid
		if (level[i].intersects(me_ex)) {
			if (me_ey.maxp.x >= level[i].maxp.x) {
				if (me_ey.minp.x >= level[i].maxp.x + oldv.x * s) {
					float d = std::max(level[i].maxp.x - me_ex.minp.x, (float)0);
					pos.x += d;
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
			if (me_ey.minp.x <= level[i].minp.x) {
				if (me_ey.maxp.x <= level[i].minp.x + oldv.x * s) {
					float d = std::min(level[i].minp.x - me_ex.maxp.x, (float)0);
					pos.x += d;
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
		}
		if (level[i].intersects(me_ey)) {
			if (me_ex.maxp.y >= level[i].maxp.y) {
				if (me_ex.minp.y >= level[i].maxp.y + oldv.y * s) {
					float d = std::max(level[i].maxp.y - me_ey.minp.y, (float)0);
					pos.y += d;
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
			if (me_ex.minp.y <= level[i].minp.y) {
				if (me_ex.maxp.y <= level[i].minp.y + oldv.y * s) {
					float d = std::min(level[i].minp.y - me_ey.maxp.y, (float)0); 
					pos.y += d;
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
		}
	}
	
	for (unsigned int i = 0; i < level.size(); i++) {
		if (level[i].intersects(me_ex)) {
			if (me_ey.minp.x >= level[i].minp.x) {
				touching_walls[LEFT] = std::max(touching_walls[LEFT], level[i].color);
			}
			if (me_ey.maxp.x <= level[i].maxp.x) {
				touching_walls[RIGHT] = std::max(touching_walls[RIGHT], level[i].color);
			}
		}
		if (level[i].intersects(me_ey)) {
			if (me_ex.minp.y >= level[i].minp.y) {
				touching_walls[TOP] = std::max(touching_walls[TOP], level[i].color);
			}
			if (me_ex.maxp.y <= level[i].maxp.y) {
				touching_walls[BOTTOM] = std::max(touching_walls[BOTTOM], level[i].color);
			}
		}
	}
	float visc = 0.01;
	switch (touching_walls[LEFT]) {
		case 1:
			if (velocity.x < 0) velocity.x *= pow(visc, s);
			break;
		case 2:
			velocity.x = std::max(velocity.x, (float)0);
			acceleration.x = std::max(acceleration.x, (float)0);
			break;
		case 3:
			velocity.x = std::max(velocity.x, -velocity.x);
			acceleration.x = std::max(acceleration.x, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[RIGHT]) {
		case 1:
			if (velocity.x > 0) velocity.x *= pow(visc, s);
			break;
		case 2:
			velocity.x = std::min(velocity.x, (float)0);
			acceleration.x = std::min(acceleration.x, (float)0);
			break;
		case 3:
			velocity.x = std::min(velocity.x, -velocity.x);
			acceleration.x = std::min(acceleration.x, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[TOP]) {
		case 1:
			if (velocity.y < 0) velocity.y *= pow(visc, s);
			break;
		case 2:
			velocity.y = std::max(velocity.y, (float)0);
			acceleration.y = std::max(acceleration.y, (float)0);
			break;
		case 3:
			velocity.y = std::max(velocity.y, -velocity.y);
			acceleration.y = std::max(acceleration.y, (float)0);
			break;
		default: break;
	}
	switch (touching_walls[BOTTOM]) {
		case 1:
			if (velocity.y > 0) velocity.y *= pow(visc, s);
			break;
		case 2:
			velocity.y = std::min(velocity.y, (float)0);
			acceleration.y = std::min(acceleration.y, (float)0);
			break;
		case 3:
			velocity.y = std::min(velocity.y, -velocity.y);
			acceleration.y = std::min(acceleration.y, (float)0);
			break;
		default: break;
	}
}
