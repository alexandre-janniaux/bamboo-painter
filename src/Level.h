#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>

template <typename T>
std::ostream& operator << (std::ostream &os, const std::vector<T> &v) {
	os << v.size() << '\n';
	for (unsigned int i = 0; i < v.size(); i++) {
		os << v[i] << '\n';
	}
	return os;
}

template <typename T>
std::istream& operator >> (std::istream &is, std::vector<T> &v) {
	v.clear();
	size_t size;
	is >> size;
	//std::cout << size << std::endl;
	v.resize(size);
	for (unsigned int i = 0; i < size; i++) {
		is >> v[i];
	}
	return is;
}

inline std::ostream& operator << (std::ostream &os, const sf::Vector2f &v) {
	return os << v.x << ' ' << v.y;
}

inline std::istream& operator >> (std::istream &is, sf::Vector2f &v) {
	return is >> v.x >> v.y;
}

struct rectangle {
	sf::Vector2f minp, maxp;
	unsigned char color;
	rectangle() {};
	rectangle(sf::Vector2f minp_, sf::Vector2f maxp_, unsigned char color_ = 0) {
		minp = minp_; maxp = maxp_; color = color_;
	};
	rectangle(float minx, float miny, float maxx, float maxy, unsigned char color_ = 0) {
		minp.x = minx; minp.y = miny; maxp.x = maxx; maxp.y = maxy; color = color_;
	};
	const inline bool contains(const sf::Vector2f &p) const {
		return (minp.x <= p.x) && (p.x <= maxp.x) &&
			(minp.y <= p.y) && (p.y <= maxp.y);
	};
	const inline bool intersects(const rectangle &other) const {
		return !(
			(other.maxp.x < minp.x) || (maxp.x < other.minp.x) ||
			(other.maxp.y < minp.y) || (maxp.y < other.minp.y)
		);
	};
	inline sf::Vector2f center() {
		return sf::Vector2f((minp.x + maxp.x) / 2., (minp.y + maxp.y) / 2.);
	};
	rectangle operator + (const sf::Vector2f &p) {
		return rectangle(minp + p, maxp + p, color);
	};
	inline void operator += (const sf::Vector2f &p) {
		minp += p; maxp += p;
	};
	inline void movex (float d) {
		minp.x += d; maxp.x += d;
	};
	inline void movey (float d) {
		minp.y += d; maxp.y += d;
	};
};


inline std::ostream& operator << (std::ostream &os, const rectangle &rect) {
	os << rect.minp << ' ' << rect.maxp << ' ' << (unsigned int) rect.color;
	return os;
}

inline std::istream& operator >> (std::istream &is, rectangle &rect) {
	unsigned int c;
	is >> rect.minp >> rect.maxp >> c;
	rect.color = (unsigned char) c;
	return is;
}


class Level {
	public:
	Level();
	Level(std::string path);
	virtual ~Level()=default;

	void render(sf::RenderTarget& target);

	sf::Vector2f start_pos;
	rectangle bbox;
	std::vector<rectangle> boxes;
	std::vector<sf::Vector2f> check_pos;
	void updateSprites();

	private:
	void addBorders();
	std::vector<sf::RectangleShape> sprites;
};

std::ostream& operator << (const Level &level, std::ostream &os);
std::istream& operator >> (Level &level, std::istream &is);
