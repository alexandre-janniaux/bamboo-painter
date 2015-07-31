#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

// TODO: separer classe rectangle
#include "Level.h"

class EditorView
{
	public:
	EditorView()=default;
	~EditorView()=default;
	
	void push_event(const sf::RenderTarget& target, const sf::Event& event);
	void render(sf::RenderTarget& target);
	
	void update_mouse(const sf::Vector2i& mouse_pos);
		
	private:
	bool m_addActive=false;
	sf::Vector2f m_lastPoint;
	sf::Vector2i m_mousePoint;
	//std::vector<std::function<rectangle>> m_callbacksAddRect;
	
};