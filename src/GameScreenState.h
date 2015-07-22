#include "ScreenState.h"
#include <vector>
#include <SFML/Graphics.hpp>


struct rectangle {
	sf::Vector2f minp, maxp;
	rectangle() {};
	rectangle(sf::Vector2f minp_, sf::Vector2f maxp_) {
		minp = minp_; maxp = maxp_;
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
	void updateSprites();

};
