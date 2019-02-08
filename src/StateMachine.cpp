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
, m_context(sf::FloatRect(0,0, 1, 1))
{
   	// Create render window
	m_window.create( sf::VideoMode{SCREEN_WIDTH, SCREEN_HEIGHT}, "Engine Test version lost count", sf::Style::Default);
	sf::Vector2u _size = sf::Vector2u(1040, 768);
	m_window.setSize(_size);
    r_next.create(1040, 768);
    //set the boundaries for the view
    s_next.setTexture(r_next.getTexture());

    n_view.reset(s_next.getLocalBounds());
	// Initialize the engine;
	m_states.push(std::move( build<PlayState>(*this, m_window, m_view, r_next, m_context, false)));// should be intro state unless debugging an other state or debugging with another state.
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
    frametime =m_clock.restart();
    accumulator=sf::Time::Zero;
	// Main loop
	while(running())
	{
        m_window.setView(m_view);

        while (m_window.pollEvent(m_event)) // handle all the events first
            handleEvents(m_event);

		frametime=m_clock.restart();    // also gives the amount of time past since the last restart.
		accumulator += frametime;      // add the time per frame to the time left over

        // Handle the logic
        while(accumulator >= timestep)
        {
            update(timestep);

            // any time left over is brought over to the next step
            accumulator -=timestep;

            //Change the state if necessary
            if (NextState != Status::_null)
                changeState();

            Draw();
        }
        Render();
	}
	// Leaving the scope of State-machine will cleanup the engine
}

void StateMachine::Draw()
{
    // first part of the render cycle
   // move the existing view to the previous one
    s_previous.setTexture(r_next.getTexture());
    r_next.clear();
    m_states.top()->draw();    // Let the state draw to the r_next texture as states keep track of the view
    r_next.display();
    s_next.setTexture(r_next.getTexture());
}

void StateMachine::Render()
{
    alpha.a=sf::Uint8((255*accumulator.asSeconds())/(timestep.asSeconds()));
    s_next.setColor(alpha); // set the transparency to use for blending previous and next frame from the update cycle
    m_window.setView(n_view);

    // graphic cards are highly optimize for a clear, draw and display cycle.
    m_window.clear();                // clear the window, standard part of the drawing cycle
    m_window.draw(s_previous);      // draw the previous view here
    m_window.draw(s_next);         // draw the next frame with transparency "alpha"
 // m_window.draw(s_GUI);         // not implemented yet
    m_window.display();          // display the scene, standard part of the cycle
}

void StateMachine::lastState()
{
    m_resume = true;
}

void StateMachine::setNextState(Status s)
{
    NextState = s;
    // only set the next state as a value since we do not want to change from one state to another unpredictably
}

void StateMachine::changeState()

{
    // build a new state if this is requested
    std::unique_ptr<State> temp;
    bool newstate = false;
    switch (NextState)
    {
    case Status::_intro:
        temp = build<IntroState>(*this, m_window, m_view, r_next, m_context, false);
        newstate=true;
        break;
    case Status::_play:
       temp = build<PlayState>(*this, m_window, m_view, r_next, m_context, false);
       newstate=true;
        break;
    case Status::_menu:
        temp = build<MenuState>(*this, m_window, m_view, r_next, m_context, false);
        newstate=true;
        break;
    case Status::_null:
    default:
        break;
    }

    if( temp->isReplacing() )   // clear the last state IF it's replaced
        m_states.pop();

    if (!m_states.empty())
        m_states.top()->resume();

    if (newstate)
        m_states.push(std::move(temp)); // move the new state to the stack

    setNextState(Status::_null);        // clear the request for a new state
}

void StateMachine::update(sf::Time dt)
{
	// Let the context, GameObjectManager, update the game
	m_context.UpdateAll(dt);
}


void StateMachine::handleEvents(sf::Event event)
{
    if (event.type == sf::Event::Closed)// unless the program quits states handle the events
		quit();

    if (event.type == sf::Event::Resized)
        m_view.setSize(event.size.width, event.size.height);

    m_states.top()->handleEvent(event);
}
