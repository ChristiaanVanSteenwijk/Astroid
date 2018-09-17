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

    void handleEvents(sf::Event event);
	void update(sf::Time t);
	void draw();

	bool running() {return m_running;}
	void quit() {m_running = false;}

    void setNextState(Status S);

    void changeState();

	template <typename _state>
	static std::unique_ptr<_state> build( StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& _context, bool replace = true );

	void run();

    unsigned int getHeight();
    unsigned int getWidth();

private:

	bool m_resume;
	bool m_running;

    Status NextState=Status::_null;

    sf::RenderWindow m_window;
    sf::View m_view;
    GameObjectManager m_context;

    sf::Event m_event;

    sf::Clock m_clock;
    sf::Time current;
    sf::Time accumulator=sf::Time::Zero;
    sf::Time newtime;
    sf::Time frametime;
    sf::Time timestep=sf::milliseconds(15); // for the update function
//	DataBase Bootjes = DataBase("Ships.db");
    unsigned int SCREEN_WIDTH = 1500;
    unsigned int SCREEN_HEIGHT = 1000;
    float LEVEL_WIDTH = 1500;
    float LEVEL_HEIGHT = 1000;

    // The stack of states
	std::stack<std::unique_ptr<State>> m_states;
};

template <typename _state>
std::unique_ptr<_state> StateMachine::build( StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& _context, bool replace )
{
	return std::unique_ptr<_state>( new _state( machine, window, view, _context, replace ) );
}

#endif // GAMEENGINE_HPP
