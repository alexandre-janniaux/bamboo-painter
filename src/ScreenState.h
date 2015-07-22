
#pragma once

namespace sf {
    struct Event;
    struct Time;
    class RenderTarget;
}

class ScreenState {
    public:
    
    ScreenState()=default;
    virtual ~ScreenState()=default;    

    virtual void event(const sf::Event& event)=0;
    virtual void render(const sf::RenderTarget& target)=0;
    virtual void update(const sf::Time& time)=0;

};
