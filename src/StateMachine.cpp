#include "StateMachine.hpp"

#include <iostream>
#include <memory>

#include "State.hpp"
#include "IntroState.hpp"
#include "MenuState.hpp"
#include "PlayState.hpp"
#include "DataBase.hpp"

StateMachine::StateMachine()
: m_resume{ false }
, m_running{ false }
{
   	// Create render window
	m_window.create( sf::VideoMode{SCREEN_WIDTH, SCREEN_HEIGHT}, "Engine Test version lost count", sf::Style::Titlebar | sf::Style::Close );
	m_window.setView(m_view);
    //set the boundaries for the quad tree
    m_context = (sf::FloatRect(0,0, LEVEL_WIDTH, LEVEL_HEIGHT));
    m_view.reset(sf::FloatRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
	// Initialize the engine;
	m_states.push(std::move( build<PlayState>(*this, m_window, m_view, m_context, false)));// should be intro state unless debugging an other state.
	// send the first state to the stack
    m_running = true;
    setNextState(Status::_null);
	std::cout << "StateMachine Init" << std::endl;
}

StateMachine::~StateMachine()
{

}

void StateMachine::run()
{
    current =m_clock.restart();
    accumulator=sf::Time::Zero;
	// Main loop
	while(running())
	{
        while (m_window.pollEvent(m_event))
            handleEvents(m_event);

      //  newtime=m_clock.getElapsedTime();
		frametime=m_clock.restart();
		accumulator += frametime;

        // Handle the logic
        while(accumulator >= timestep)
        {
            update(timestep);
            accumulator -=timestep;

            //Change the state if necessary
            if (NextState != Status::_null)
                changeState();
        }

       //render the scene
		draw();
		//draw(lag/timestep) and extrapolate?
            // schemes found seems to interpolate from the future.
            // seems rather odd

	}
	// Leaving the scope of 'Application' will cleanup the engine
}

void StateMachine::lastState()
{
    m_resume = true;
}

void StateMachine::setNextState(Status s)
{
    NextState = s;
}
void StateMachine::changeState()

{
    //std::cout<<"Changing state"<<std::endl;
    std::unique_ptr<State> temp;
    bool newstate = false;
    switch (NextState)
    {
    case Status::_intro:
        temp = build<IntroState>(*this, m_window, m_view, m_context, true);
        newstate=true;
        break;
    case Status::_play:
       temp = build<PlayState>(*this, m_window, m_view, m_context, true);
       newstate=true;
        break;
    case Status::_menu:
        temp = build<MenuState>(*this, m_window, m_view, m_context, false);
        newstate=true;
        break;
    case Status::_null:
    default:
        break;
    }

    if( temp->isReplacing() )
        m_states.pop();

    if (!m_states.empty())
        m_states.top()->resume();

    if (newstate)
        m_states.push(std::move(temp));

    setNextState(Status::_null);
}

void StateMachine::update(sf::Time t)
{
	// Let the context, GameObjectManager, update the game
	m_context.UpdateAll(t);
}

void StateMachine::draw()
{
	// Let the state draw the screen
	m_states.top()->draw();
}

void StateMachine::handleEvents(sf::Event event)
{
    if (event.type== sf::Event::Closed)
		quit();
    m_states.top()->handleEvent(event);
}
