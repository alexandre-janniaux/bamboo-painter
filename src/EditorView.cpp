#include "EditorView.h"
#include <iostream>

void EditorView::push_event(const sf::RenderTarget& target, const sf::Event& event)
{

	if (event.type == sf::Event::MouseButtonPressed)
	{
		m_addActive = true;
		m_lastPoint = target.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                std::cout << "view" << target.getView().getCenter().x << std::endl;
	}
	else if (event.type == sf::Event::MouseButtonReleased && m_addActive) 
	{
		m_addActive = false;
		// TODO: callback
	}
		
}

void EditorView::render(sf::RenderTarget& target)
{
	if (m_addActive) {
                std::cout << "view2" << target.getView().getCenter().x << std::endl;
		auto coords = target.mapPixelToCoords(m_mousePoint);
		sf::RectangleShape shape;
		shape.setPosition(m_lastPoint);
                auto c = coords - m_lastPoint;
                shape.setSize(c);
                shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1.f);
		
		//std::cout << coords.x << "///" << coords.y << std::endl;
		//std::cout << c.x << "/" << c.y << std::endl;
		
 		target.draw(shape);
	}
}

void EditorView::update_mouse(const sf::Vector2i& mouse_pos)
{
	m_mousePoint = mouse_pos;
}
