#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include "SFML/System/Time.hpp"
#include "SFML/Graphics.hpp"

class StateMachine;
class GameObjectManager;
class lua_State;

class State
{
public:
    State(StateMachine& machine, sf::RenderWindow& window, sf::View& m_view, GameObjectManager& _context, bool replace = false);
	virtual ~State() = default;
   // void* operator new(size_t size, lua_State* L, const char* metatableName); size_t size, lua_State* L, const char* metatableName,

	State (const State& ) = delete;
	State& operator= ( const State& ) = delete;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvent(sf::Event event) = 0;  // looping over multiple events is done by the state machine

	void update(sf::Time t);

    void draw(sf::RenderTarget& target);
    void drawFeedback(sf::RenderTarget& target);

	std::unique_ptr<State> next();

	bool isReplacing();

	//int PlaceGameObject(lua_State* L);

protected:
    StateMachine& m_machine;
    sf::RenderWindow& m_window;
    sf::View& m_view;
  //  sf::RenderTexture& r_next; commented out since the state machine passes the textures to the drawing function directly

	bool m_replacing = false;
    GameObjectManager& m_context;

	std::unique_ptr<State> m_next;
};

#endif // STATE_HPP
