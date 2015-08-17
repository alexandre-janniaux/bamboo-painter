
#pragma once

namespace sf {
    struct Event;
    struct Time;
    class RenderTarget;
	class RenderWindow;
}

class ScreenState {
    public:
	
	enum ScreenStateType {
		Menu,
		Game,
		PauseGame
	};
    
    ScreenState()=default;
    virtual ~ScreenState()=default;    

    virtual void event(const sf::RenderTarget& target, const sf::Event& event)=0;
    virtual void render(sf::RenderTarget& target)=0;
    virtual void update(const sf::Time& time)=0;
    virtual void window_update(const sf::RenderWindow& window){};
	
	virtual void onStart(){};
    virtual void onActivate(){};
	virtual void onPause(){};
	virtual void onStop(){};
	

};
