#include "ScreenState.h"
#include <vector>
#include <SFML/Graphics.hpp>


struct rectangle {
	sf::Vector2f minp, maxp;
	unsigned char color;
	rectangle() {};
	rectangle(sf::Vector2f minp_, sf::Vector2f maxp_, unsigned char color_ = 0) {
		minp = minp_; maxp = maxp_; color = color_;
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


class GameScreenState : public ScreenState {
    public:

    //GameScreenState()=default;
	GameScreenState();
    virtual ~GameScreenState()=default;

    void event(const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    void update(const sf::Time& time) override;

	private:
	std::vector<rectangle> level;
	std::vector<sf::RectangleShape> sprites;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	unsigned char touching_walls[4]; 
	void updateSprites();

};
