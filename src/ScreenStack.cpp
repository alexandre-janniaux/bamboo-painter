#include "ScreenStack.h"
#include "ScreenState.h"


void ScreenStack::clearStack()
{
	m_stack.clear();
}

void ScreenStack::onDraw(sf::RenderTarget& target)
{
	for(int id : m_stack)
		m_states.at(id)->render(target);
}

void ScreenStack::onEvent(const sf::RenderTarget& target, const sf::Event& event)
{
	for(int id : m_stack) {
		m_states.at(id)->event(target, event);
	}
}

void ScreenStack::onUpdate(sf::Time time)
{
	for(int id : m_stack)
		m_states.at(id)->update(time);
}

void ScreenStack::popState()
{
	if (m_stack.empty())
		return;
	m_states.at(m_stack.back())->onStop();
	m_stack.pop_back();
	
	if (!m_stack.empty())
		m_states.at(m_stack.back())->onActivate();
}

void ScreenStack::pushState(int id)
{
	if (!m_stack.empty())
		m_states.at(m_stack.back())->onPause();
	m_stack.push_back(id);
	m_states.at(id)->onStart();
}

void ScreenStack::registerState(int id, std::unique_ptr<ScreenState> state)
{
	m_states.insert(std::pair<int,std::unique_ptr<ScreenState>>(id, std::move(state)));
}
