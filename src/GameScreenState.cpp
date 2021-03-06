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
	advancement = 0;
	my_color = 1;
	level = Level("./example.lvl");
	resetPos();
	updateSprites();
}

void GameScreenState::resetPos() {
	pos = level.check_pos[advancement];
	velocity = sf::Vector2f(0, 0);
	acceleration = sf::Vector2f(0, 0);
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
}

void GameScreenState::event(const sf::RenderTarget& target, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		my_color = (my_color + 1) % 3;
		updateSprites();
	}
	m_editor.push_event(target, event);
}

void GameScreenState::updateSprites() {
	sprites.clear();
	sprites.resize(1);

	sf::RectangleShape sprite;
	sprite.setSize(sf::Vector2f(40, 40));
	//sprite.setFillColor(sf::Color::Red);
	const sf::Color colors[3] = {sf::Color::Blue, sf::Color::Black, sf::Color::Yellow};
	sprite.setFillColor(colors[my_color]);
	sprite.setPosition(pos - sf::Vector2f(20, 20));
	sprites.push_back(sprite);
}

void GameScreenState::updateView(sf::RenderTarget& target) {
	sf::Vector2f size = (sf::Vector2f)target.getSize();
	sf::Vector2f center
		(clamp(pos.x, level.bbox.minp.x + size.x / 2,
			level.bbox.maxp.x - size.x / 2),
		clamp(pos.y, level.bbox.minp.y + size.y / 2,
			level.bbox.maxp.y - size.y / 2));
	m_view.setCenter(center);
	m_view.setSize(size);
	target.setView(m_view);
}

void GameScreenState::render(sf::RenderTarget& target) {
	updateSprites();
	updateView(target);
	target.clear(sf::Color::White);
	level.render(target);
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
	m_editor.render(target);
}


const float TIME_SPEED = 1;
void GameScreenState::update(const sf::Time& time) {
	float s = time.asSeconds() * TIME_SPEED;
	sf::Vector2f offset = velocity * s + ((float) 0.5) * s * s * acceleration;
	pos += offset;
	m_view.move(offset);
	sf::Vector2f oldv = velocity + ((float) 0.5) * s * acceleration;
	velocity += s * acceleration;
	acceleration = sf::Vector2f(0, 240);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = std::min(velocity.x + (float)400 * s, (float)200);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = std::max(velocity.x - (float)400 * s, (float)-200);
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
	rectangle me = rectangle(pos - sf::Vector2f(20, 20), pos + sf::Vector2f(20, 20));
	for (unsigned char i = 0; i < 4; i++) touching_walls[i] = 0;
	#define icolor(box) ((unsigned char)(((box).color - my_color + 3) % 3 + 1))
	for (unsigned int i = 0; i < level.boxes.size(); i++) {
		if (icolor(level.boxes[i]) < 2) continue; // Not solid
		if (level.boxes[i].intersects(me_ex)) {
			if (me_ey.maxp.x >= level.boxes[i].maxp.x) {
				if (me_ey.minp.x >= level.boxes[i].maxp.x + oldv.x * s) {
					float d = std::max(level.boxes[i].maxp.x - me_ex.minp.x, (float)0);
					pos.x += d;
					m_view.move(d,0);
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
			if (me_ey.minp.x <= level.boxes[i].minp.x) {
				if (me_ey.maxp.x <= level.boxes[i].minp.x + oldv.x * s) {
					float d = std::min(level.boxes[i].minp.x - me_ex.maxp.x, (float)0);
					pos.x += d;
					m_view.move(d,0);
					me_ex.movex(d);
					me_ey.movex(d);
				}
			}
		}
		if (level.boxes[i].intersects(me_ey)) {
			if (me_ex.maxp.y >= level.boxes[i].maxp.y) {
				if (me_ex.minp.y >= level.boxes[i].maxp.y + oldv.y * s) {
					float d = std::max(level.boxes[i].maxp.y - me_ey.minp.y, (float)0);
					pos.y += d;
					m_view.move(0.f,d);
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
			if (me_ex.minp.y <= level.boxes[i].minp.y) {
				if (me_ex.maxp.y <= level.boxes[i].minp.y + oldv.y * s) {
					float d = std::min(level.boxes[i].minp.y - me_ey.maxp.y, (float)0); 
					pos.y += d;
					m_view.move(0.f,d);
					me_ex.movey(d);
					me_ey.movey(d);
				}
			}
		}
	}
	
	for (unsigned int i = 0; i < level.boxes.size(); i++) {
		if (level.boxes[i].intersects(me_ex)) {
			if (me_ey.minp.x >= level.boxes[i].minp.x) {
				touching_walls[LEFT] = std::max(touching_walls[LEFT], icolor(level.boxes[i]));
			}
			if (me_ey.maxp.x <= level.boxes[i].maxp.x) {
				touching_walls[RIGHT] = std::max(touching_walls[RIGHT], icolor(level.boxes[i]));
			}
		}
		if (level.boxes[i].intersects(me_ey)) {
			if (me_ex.minp.y >= level.boxes[i].minp.y) {
				touching_walls[TOP] = std::max(touching_walls[TOP], icolor(level.boxes[i]));
			}
			if (me_ex.maxp.y <= level.boxes[i].maxp.y) {
				touching_walls[BOTTOM] = std::max(touching_walls[BOTTOM], icolor(level.boxes[i]));
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
			if (velocity.x > 0) {
				velocity.x = std::max((float)0, velocity.x - (float)100 * s);
			} else {
				velocity.x = std::min((float)0, velocity.x + (float)100 * s);
			}
			break;
		case 3:
			velocity.y = std::min(velocity.y, -velocity.y);
			acceleration.y = std::min(acceleration.y, (float)0);
			break;
		default: break;
	}
	if (touching_walls[TOP] >= 2 && touching_walls[BOTTOM] >= 2) {
		velocity.y = 0;
		acceleration.y = 0;
	}
	if (touching_walls[LEFT] >= 2 && touching_walls[RIGHT] >= 2) {
		velocity.x = 0;
		acceleration.x = 0;
	}
    
	velocity.x *= pow(0.2, s);

	rectangle checkpoint = rectangle(-10, -10, 10, 10);
	for (unsigned int i = level.check_pos.size() - 1; i > advancement; i--) {
		if (me.intersects(checkpoint + level.check_pos[i])) {
			advancement = i;
			break;
		}
	}
	
	if (pos.y > level.bbox.maxp.y) {
		kill();
	}
}

void GameScreenState::kill() {
	resetPos();
}

void GameScreenState::window_update(const sf::RenderWindow& window)
{
	m_editor.update_mouse(sf::Mouse::getPosition(window));
}
