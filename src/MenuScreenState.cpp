#include "MenuScreenState.h"

void MenuScreenState::event(const sf::RenderTarget& target, const sf::Event& event)
{
	
}

MenuScreenState::MenuScreenState()
{
	//m_view.setCenter();
	m_view.setSize(800,600);
	m_title.setString("BAMBOO PAINTER");
	m_title.setColor(sf::Color::Red);
	auto bounds = m_title.getLocalBounds();
	auto width = bounds.width;
	m_title.setPosition(m_view.getSize().x/2 - width/2, 50);
}

void MenuScreenState::render(sf::RenderTarget& target)
{
	target.setView(m_view);
	target.draw(m_title);
}

void MenuScreenState::update(const sf::Time& time)
{

}

