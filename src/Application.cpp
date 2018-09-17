#include "Application.hpp"

Application::Application()
{
   	// Create render window
	m_window.create( sf::VideoMode{SCREEN_WIDTH, SCREEN_HEIGHT}, "Engine Test v2.1", sf::Style::Titlebar | sf::Style::Close );
	m_window.setView(m_view);
    sf::FloatRect recy(0,0, LEVEL_WIDTH, LEVEL_HEIGHT);
    _context.setBounds(recy);
    m_view.reset(sf::FloatRect(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT));
	// Initialize the engine;
	m_machine.run(m_machine.build<IntroState>(m_machine, m_window, m_view, _context, true));
}

Application::~Application(){};

void Application::run()
{
	// Main loop
	while( m_machine.running())
	{
		m_machine.nextState();
		t0=m_clock.restart();

        while(t0 < Tmax)
        {
            t0-=Tmax;
            m_machine.update(t0);
        }
        m_machine.update(t0);
		m_machine.draw();
	}
	// Leaving the scope of 'Application' will cleanup the engine
}

unsigned int Application::getHeight()
{
    return SCREEN_HEIGHT;
}

unsigned int Application::getWidth()
{
    return SCREEN_WIDTH;
}
