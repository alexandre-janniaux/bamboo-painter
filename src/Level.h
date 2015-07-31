#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

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
	inline void operator += (const sf::Vector2f &p) {
		minp += p; maxp += p;
	};
	inline void movex (float d) {
		minp.x += d; maxp.x += d;
	}
	inline void movey (float d) {
		minp.y += d; maxp.y += d;
	}
};

class Level {
	public:
	Level();
	virtual ~Level()=default;

	void render(sf::RenderTarget& target);

	sf::Vector2f start_pos;
	rectangle bbox;
	std::vector<rectangle> boxes;

	private:
	void updateSprites();
	std::vector<sf::RectangleShape> sprites;
};