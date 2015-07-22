#include "ScreenState.h"


class GameScreenState : public ScreenState {
    public:

    GameScreenState()=default;
    virtual ~GameScreenState()=default;

    void event(const sf::Event& event) override;
    void render(const sf::RenderTarget& target) override;
    void update(const sf::Time& time) override;

};
