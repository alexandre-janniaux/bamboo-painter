#include "Level.h"

Level::Level() {
	bbox = rectangle(0, 0, 3000, 600);
	start_pos = sf::Vector2f(300, 100);

	boxes.push_back(rectangle(200, 400, 400, 450, 2));
	boxes.push_back(rectangle(400, 260, 450, 450, 3));
	boxes.push_back(rectangle(100, 200, 200, 450, 1));
	boxes.push_back(rectangle(95, 200, 100, 455, 2));
	boxes.push_back(rectangle(200, 200, 205, 455, 2));
	boxes.push_back(rectangle(100, 450, 200, 455, 2));
	boxes.push_back(rectangle(600, 450, 1000, 500, 2));
	boxes.push_back(rectangle(1200, 300, 2500, 350, 2));

	boxes.push_back(rectangle(0, 0, 3000, 2, 3));
	boxes.push_back(rectangle(0, 0, 2, 600, 3));
	boxes.push_back(rectangle(2998, 0, 3000, 600, 3));
	boxes.push_back(rectangle(0, 598, 3000, 600, 3));

	updateSprites();
}

void Level::updateSprites() {
	sprites.clear();
	sprites.resize(boxes.size());
	static sf::Color colors[4] =
		{sf::Color::White,
		 sf::Color::Blue,
		 sf::Color::Black,
		 sf::Color::Yellow};
	for (unsigned int i = 0; i < boxes.size(); i++) {
		sf::RectangleShape sprite;
		sprite.setSize(boxes[i].maxp - boxes[i].minp);
		sprite.setFillColor(colors[boxes[i].color]);
		sprite.setPosition(boxes[i].minp);
		sprites.push_back(sprite);
	}
}

void Level::render(sf::RenderTarget& target) {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}
