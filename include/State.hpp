#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include "SFML/System/Time.hpp"
#include "SFML/Graphics.hpp"

#include "Status.hpp"

class StateMachine;
class GameObjectManager;

class State
{
public:
    State(StateMachine& machine, sf::RenderWindow& m_window, sf::View& m_view, sf::RenderTexture& next, GameObjectManager& _context, bool replace = false);
	virtual ~State() = default;

	State (const State& ) = delete;
	State& operator= ( const State& ) = delete;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(sf::Event event) = 0;  // looping over multiple events is done by the state machine

	void update(sf::Time t = sf::Time::Zero);

    void draw();

	std::unique_ptr<State> next();

	bool isReplacing();

protected:
    StateMachine& m_machine;
    sf::RenderWindow& m_window;
    sf::View& m_view;
    sf::RenderTexture& r_next;

	bool m_replacing = false;
    GameObjectManager& m_context;

	std::unique_ptr<State> m_next;
};

#endif // STATE_HPP
