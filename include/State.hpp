#ifndef STATE_HPP
#define STATE_HPP

#include <memory>

#include "SFML/System/Time.hpp"
#include "SFML/Graphics.hpp"
#include "Script.hpp"
#include "DataBase.hpp"

class StateMachine;
class GameObjectManager;
class lua_State;

class State : public Scriptable
{
public:
    State(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& context, Script& script, std::string& Script, DataBase& database, bool _replace = false);
	virtual ~State() = default;

    friend void swap(State& first, State& second);    //swap

    State(State& other);             //Copy Ctor
    State& operator=(State& other); //copy assignment

    State(State&& other);       //move constructor
    State& operator=(State&&); //move assignment

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(sf::Event event) = 0;  // looping over multiple events is done by the state machine

	void update(sf::Time t);

    void draw(sf::RenderTarget& target);
    void drawFeedback(sf::RenderTarget& target);

	std::unique_ptr<State> next();
	//virtual void register_table(lua_State* L, struct _struct){};

	bool isReplacing();
    GameObjectManager& m_context;

protected:
    StateMachine& m_machine;
    sf::RenderWindow& m_window;
    sf::View& m_view;

	Script m_script;
    std::string n_script;

    DataBase m_database;

	bool m_replacing;

	std::unique_ptr<State> m_next;
};

#endif // STATE_HPP
