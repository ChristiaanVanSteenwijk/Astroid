#include "TextEditor.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "State.hpp"
#include "StateMachine.hpp"

#include <memory>
#include <iostream>

TextEditor::TextEditor(StateMachine& machine, sf::RenderWindow& window, sf::View& view, GameObjectManager& context, Script& script, std::string& Script, DataBase& database, bool _replace)
: State{machine, window, view, context, script, Script, database, _replace}
{
    //ctor
}

TextEditor::~TextEditor()
{
    //dtor
}
void TextEditor::pause()
{
	std::cout << "text Pause" << std::endl;
}

void TextEditor::resume()
{
	std::cout << "text Resume" << std::endl;
}
void TextEditor::handleEvent(sf::Event event)
{
    switch( event.type )
		{
			case sf::Event::KeyPressed:
				switch( event.key.code )
				{
					case sf::Keyboard::Escape:
						m_machine.lastState();
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
}

