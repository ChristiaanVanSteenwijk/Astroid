#include "MassEngine.hpp"
#include <cmath>
#include <iostream>

MassEngine::MassEngine()
{
    //ctor
}

MassEngine::MassEngine(float mass, float Power, float Rudder, float radius)
    :m_Mass(mass), m_Radius(radius), m_EnginePower(Power), m_Rudder(Rudder)
{
    //ctor
}

MassEngine::~MassEngine()
{
    //dtor
}
/*
MassEngine::MassEngine(const MassEngine& other)
{
    //copy ctor
}
*/

void MassEngine::Update(sf::Time dt)
{
    c_power = m_EnginePower*m_EngineSetting/m_MaxEsetting;
    c_velocity += c_power*dt.asSeconds()/(m_Mass);
    c_velocity = (c_velocity > max_velocity) ? max_velocity : c_velocity;
    c_velocity = (c_velocity < min_velocity) ? min_velocity : c_velocity;

    s_power = S_EnginePower*s_Setting/Max_s_Setting;
    c_strave += s_power*dt.asSeconds()/m_Mass;
    c_strave = (c_strave > max_strave) ? max_strave : c_strave;
    c_strave = (c_strave < -max_strave) ? -max_strave : c_strave;

    c_Amoment=m_Rudder*m_RudderSetting/m_maxRsetting;
    c_angle += c_Amoment*dt.asSeconds()/(m_Mass*m_Radius*m_Radius);
    if (c_angle>360)
        c_angle-=360;
    if (c_angle < 0 )
        c_angle += 360;

    float dx= cos(c_angle*M_PI/180);
    float dy= sin(c_angle*M_PI/180);

    _speed.x = c_velocity*-dx + c_strave*-dy ;
    _speed.y = c_velocity*-dy + c_strave*dx ;

    // updated after the settings are modified by either the AI or the player so it's on when it counts
    m_RudderSetting=0;

    m_EngineSetting=0;

    s_Setting=0;
}

void MassEngine::Output()
{
    std::cout<<"c_Amoment "<<c_Amoment << " c_angle "<< c_angle << " Rudder " << m_RudderSetting << std::endl;
}

MassEngine& MassEngine::operator=(const MassEngine& rhs)
{
    if (this == &rhs) return *this; //handle self assignment
    //assignment operator
    return *this;
}

void MassEngine::SetRudderSetting(int val)
{
    m_RudderSetting = val;
    m_RudderSetting = (m_RudderSetting >= m_maxRsetting) ? m_maxRsetting : m_RudderSetting;
    m_RudderSetting = (m_RudderSetting <= -m_maxRsetting) ? -m_maxRsetting : m_RudderSetting;
    timeRudder=timedelay;
}

void MassEngine::IncRudderSetting(int val)
{
    m_RudderSetting += val;
    m_RudderSetting = (m_RudderSetting >= m_maxRsetting) ? m_maxRsetting : m_RudderSetting;
    timeRudder=timedelay;
}

void MassEngine::DecRudderSetting(int val)
{
    m_RudderSetting -= val;
    m_RudderSetting = (m_RudderSetting <= -m_maxRsetting) ? -m_maxRsetting : m_RudderSetting;
    timeRudder=timedelay;
}

void MassEngine::setdelay(sf::Time delay)
{
    timedelay=delay;
}

sf::Vector2f MassEngine::getVvector()
{
    return _speed;
}

float MassEngine::GetSpeed()
{
    return c_velocity;
}

float MassEngine::GetRotation()
{
    return c_angle;
}

void MassEngine::Incm_EngineSetting(int val)
{
    m_EngineSetting += val;
    m_EngineSetting = (m_EngineSetting > m_MaxEsetting) ? m_MaxEsetting : m_EngineSetting;
    timeEninge=timedelay;
}

void MassEngine::Decm_EngineSetting(int val)
{
    m_EngineSetting -= val;
    m_EngineSetting = (m_EngineSetting < m_MinEsetting) ? m_MinEsetting : m_EngineSetting;
    timeEninge=timedelay;
}

void MassEngine::SetRotation(int val)
{
    c_angle=val;
}

void MassEngine::Inc_SideEngineSetting(int val)
{
    s_Setting+=val;
    timeStrave=timedelay;
}

void MassEngine::Dec_SideEngineSetting(int val)
{
    s_Setting-=val;
    timeStrave=timedelay;
}
