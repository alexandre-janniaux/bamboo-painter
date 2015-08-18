#include "Level.h"

Level::Level() {
	bbox = rectangle(0, 0, 3000, 600);
	check_pos.push_back(sf::Vector2f(300, 100));
	// check_pos.push_back(sf::Vector2f(500, 50));
	check_pos.push_back(sf::Vector2f(900, 400));
	check_pos.push_back(sf::Vector2f(2400, 200));
	// start_pos = sf::Vector2f(300, 100);

	boxes.push_back(rectangle(200, 400, 400, 450, 2));
	boxes.push_back(rectangle(400, 260, 450, 450, 3));
	boxes.push_back(rectangle(100, 200, 200, 450, 1));
	boxes.push_back(rectangle(95, 200, 100, 455, 2));
	boxes.push_back(rectangle(200, 200, 205, 455, 2));
	boxes.push_back(rectangle(100, 450, 200, 455, 2));
	boxes.push_back(rectangle(600, 450, 1000, 500, 2));
	boxes.push_back(rectangle(1200, 300, 2500, 350, 2));

	addBorders();
	updateSprites();
}


std::ostream& operator << (std::ostream &os, const Level &level) {
	os << level.bbox << '\n' << level.check_pos << '\n' << level.boxes;
	return os;
}

std::istream& operator >> (std::istream &is, Level &level) {
	is >> level.bbox >> level.check_pos >> level.boxes;
	level.updateSprites();
	return is;
}

Level::Level(std::string path) {
	std::ifstream file;
	file.open(path, std::ios::in);
	// std::cout << file.is_open() << std::endl;
	file >> *this;
	file.close();
	// std::cout << *this;
}

void Level::addBorders() {
	int bordersize = 10;
	boxes.push_back(rectangle(bbox.minp.x - bordersize, bbox.minp.y - 100000,
							 bbox.minp.x, bbox.maxp.y + 100000, 2));
	boxes.push_back(rectangle(bbox.maxp.x, bbox.minp.y - 100000,
							 bbox.maxp.x + bordersize, bbox.maxp.y + 100000, 2));
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
	rectangle checkpoint = rectangle(-10, -10, 10, 10);
	for (unsigned int i = 0; i < check_pos.size(); i++) {
		sf::RectangleShape sprite;
		sprite.setSize(checkpoint.maxp - checkpoint.minp);
		sprite.setFillColor(sf::Color::Green);
		sprite.setPosition(check_pos[i] + checkpoint.minp);
		sprites.push_back(sprite);
	}
}

void Level::render(sf::RenderTarget& target) {
	for (unsigned int i = 0; i < sprites.size(); i++) {
		target.draw(sprites[i]);
	}
}

