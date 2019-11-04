#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <memory>
#include <stack>
#include <string>

#include "State.hpp"
#include "IntroState.hpp"

#include "DataBase.hpp"
#include "Script.hpp"


namespace sf
{
	class RenderWindow;
	class Event;
}

enum struct Status
{
    _null,
    _intro,
    _menu,
    _play,
    _spaceCombat
};

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

    void chooseNextState(Status S, std::string _name = "void", std::string _script = "default.lua");

	template <typename S>
        void build(bool _replace = true );

    unsigned int getHeight();
    unsigned int getWidth();

	Script m_script;
    DataBase m_database;

private:

    void ChangeState();

    Status NextState=Status::_null;

    sf::RenderWindow m_window;
    sf::RenderTexture r_next, r_gui;
    sf::Sprite s_next, s_previous, s_gui;
    sf::View m_view, n_view;
    GameObjectManager m_context;

    std::string n_script;
    std::string state_name;

	bool m_resume, m_running;

    sf::Event m_event;

    sf::Clock m_clock;
    sf::Time accumulator=sf::Time::Zero;    //left over time from the update function
    sf::Time frametime;
    sf::Time timestep=sf::milliseconds(30); // for the update function
    sf::Color alpha=sf::Color::White;

    unsigned int SCREEN_WIDTH = 1500;
    unsigned int SCREEN_HEIGHT = 1000;
    float LEVEL_WIDTH = 4500;
    float LEVEL_HEIGHT = 3000;

    // The stack of states
    std::unique_ptr<State> m_state;
	std::stack<std::unique_ptr<State>> m_states;
};

template <typename S>
void StateMachine::build(bool _replace)
{
    m_state =std::unique_ptr<S> (new(m_script.getLuaState(), state_name) S(*this, m_window, m_view, m_context, m_script, n_script, m_database, _replace));
    m_state->m_context = m_context;
    if( _replace)   // clear the last state IF it's replaced
        m_states.pop();

    m_states.push(std::move(m_state));
}

#endif // GAMEENGINE_HPP
