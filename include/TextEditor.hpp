#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "State.hpp"
// kan wachten
class TextEditor : public State
{
    public:
        TextEditor(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& m_context, Script& script, std::string& n_script, DataBase& database, bool _replace = false);
         ~TextEditor();
	void pause();
	void resume();
	// Handle the events in the state
	void handleEvent(sf::Event event);
};

#endif // TEXTEDITOR_H
