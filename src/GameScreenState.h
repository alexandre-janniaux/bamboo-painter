#include "ScreenState.h"
#include "Level.h"
#include <vector>
#include <SFML/Graphics.hpp>

class GameScreenState : public ScreenState {
    public:

    //GameScreenState()=default;
	GameScreenState();
    virtual ~GameScreenState()=default;

    void event(const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    void update(const sf::Time& time) override;

	private:
	Level level;
	std::vector<sf::RectangleShape> sprites;
	sf::Vector2f pos;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	unsigned char touching_walls[4];
	void updateSprites();

};
