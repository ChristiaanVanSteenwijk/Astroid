#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <memory>
#include <stack>
#include <string>

#include "State.hpp"
#include "IntroState.hpp"

#include "DataBase.hpp"
#include "Script.hpp"

//
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

    void setNextState(Status S);

    void changeState();

	template <typename S>
	void build(bool _replace = true );

    unsigned int getHeight();
    unsigned int getWidth();

    DataBase m_database;
	Script m_script;

private:

	bool m_resume, m_running;

    Status NextState=Status::_null;

    sf::RenderWindow m_window;
    sf::RenderTexture r_next, r_gui;
    sf::Sprite s_next, s_previous, s_gui;
    sf::View m_view, n_view;
    GameObjectManager m_context;

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
    std::unique_ptr<State> _state;
	std::stack<std::unique_ptr<State>> m_states;
};

template <typename S>
void StateMachine::build(bool _replace )
{
    //size_t size, lua_State* L, const char* metatableName,
    size_t size = 500;
    const char* metatableName = "bla";
    lua_State* L = m_script.getState();
   _state = std::unique_ptr<S>( new S( *this, m_window, m_view, m_context, _replace ) );

    if( _state->isReplacing() )   // clear the last state IF it's replaced
        m_states.pop();

   m_states.push(std::move(_state));

}

#endif // GAMEENGINE_HPP
 /*   static int create_account(lua_State *L) {
      double balance = luaL_checknumber(L, 1);
      Account *a = new Account(balance);
      lua_boxpointer(L, a);
      luaL_getmetatable(L, className);
      lua_setmetatable(L, -2);
      return 1;
    }
*/
