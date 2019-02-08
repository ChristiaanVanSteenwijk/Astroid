#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <memory>
#include <stack>
#include <string>

#include "State.hpp"
#include "Status.hpp"
#include "IntroState.hpp"
//
namespace sf
{
	class RenderWindow;
	class Event;
}
class State;
class GameObjectManager;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void run(std::unique_ptr<State> state);

//	void nextState();
	void lastState();

    void run(); // calls handle events, update and draw in order

    void handleEvents(sf::Event event);
	void update(sf::Time dt);

	void Draw();
	void Render();

	bool running() {return m_running;}
	void quit() {m_running = false;}

    void setNextState(Status S);

    void changeState();

	template <typename _state>
	static std::unique_ptr<_state> build( StateMachine& machine, sf::RenderWindow& window, sf::View& view, sf::RenderTexture& next, GameObjectManager& _context, bool _replace = true );

    unsigned int getHeight();
    unsigned int getWidth();

private:

	bool m_resume;
	bool m_running;

    Status NextState=Status::_null;

    sf::RenderWindow m_window;
    sf::RenderTexture r_next;
    sf::Sprite s_next, s_previous, s_GUI;
    sf::View m_view, n_view;
    GameObjectManager m_context;

    sf::Event m_event;

    sf::Clock m_clock;
    sf::Time accumulator=sf::Time::Zero;    //left over time from the update function
    sf::Time frametime;
    sf::Time timestep=sf::milliseconds(50); // for the update function
    sf::Color alpha=sf::Color::White;
//	DataBase Bootjes = DataBase("Ships.db");
    unsigned int SCREEN_WIDTH = 1500;
    unsigned int SCREEN_HEIGHT = 1000;
    float LEVEL_WIDTH = 4500;
    float LEVEL_HEIGHT = 3000;

    // The stack of states
	std::stack<std::unique_ptr<State>> m_states;
};

template <typename _state>
std::unique_ptr<_state> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, sf::View& view, sf::RenderTexture& next, GameObjectManager& _context, bool _replace )
{
	return std::unique_ptr<_state>( new _state( machine, window, view, next, _context, _replace ) );
}

#endif // GAMEENGINE_HPP
