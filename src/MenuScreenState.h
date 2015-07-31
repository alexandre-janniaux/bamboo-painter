#pragma once

#include "ScreenState.h"
#include <SFML/Graphics.hpp>


class MenuScreenState : public ScreenState {
	public:
	MenuScreenState();
	virtual ~MenuScreenState()=default;

	void event(const sf::RenderTarget& target, const sf::Event& event) override;
	void render(sf::RenderTarget& target) override;
	void update(const sf::Time& time) override;

	private:
	sf::View m_view;
	sf::Text m_title;

};


