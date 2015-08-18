#pragma once 

#include "cpp_std_11.h"

#include <map>
#include <vector>

#include <SFML/System.hpp>

namespace sf {
	struct Event;
	class RenderTarget;
}

class ScreenState;

class ScreenStack
{
	public:
		
		void clearStack();
		
		void onEvent(const sf::RenderTarget& target, const sf::Event& event);
		void onUpdate(sf::Time time);
		void onDraw(sf::RenderTarget& target);
		
		void pushState(int id);
		void popState();
		
		void registerState(int id, std::unique_ptr<ScreenState> state);
		
	private:
		
		std::map<int, std::unique_ptr<ScreenState>> m_states;
		std::vector<int> m_stack;
	
};
