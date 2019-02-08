#ifndef MASSENGINE_H
#define MASSENGINE_H
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class MassEngine
{
    public:
        MassEngine(float mass, float Power, float Rudder, float radius = 100);
        MassEngine();
        ~MassEngine();

        virtual void Update(sf::Time dt);

    //    MassEngine(const MassEngine& other);
        MassEngine& operator=(const MassEngine& other);
        float Getm_Mass() { return m_Mass; };
        void Setm_Mass(float val) { m_Mass = val; };
        int Getm_EngineSetting() { return m_EngineSetting; };
        void Setm_EngineSetting(int val) { m_EngineSetting = val; };
        void Incm_EngineSetting(int val=1);
        void Decm_EngineSetting(int val=1);
        float Getm_EnginePower() { return m_EnginePower; };
        void Setm_EnginePower(float val) { m_EnginePower = val; };
        void Set_SideEngineSetting(int val){s_Setting=val;};
        void Inc_SideEngineSetting(int val=1);
        void Dec_SideEngineSetting(int val=1);
        int GetSideEngineSetting(){return s_Setting;};
        void SetMaxSpeed(float v){max_velocity=v;};

        void Setm_SideEnginePower(float val) { S_EnginePower = val; }; // to the right is positive
        float Getm_Radius() { return m_Radius; };
        void Setm_Radius(float val) { m_Radius = val; };
        float GetRudder() { return m_Rudder; };
        void SetRudder(float val) { m_Rudder = val; };
        int GetRudderSetting() { return m_RudderSetting; };
        void SetRudderSetting(int val) ;
        void IncRudderSetting(int val=1) ;
        void DecRudderSetting(int val=1) ;
        float GetSpeed();
        void SetSpeed(float val){c_velocity=val;};
        float GetRotation();
        void SetRotation(int val);
        void SetMaxEsetting(int val) {m_MaxEsetting = val;};
        void SetMinEsetting(int val) {m_MinEsetting = val;};
        void SetMaxRsetting(int val) {m_maxRsetting = val;};
        sf::Vector2f getVvector();
        void Output();
        void setdelay(sf::Time delay);

    protected:
    private:
        float m_Mass;
        float m_Radius;         //large radius for high inertia when turning
        int m_EngineSetting=0;
        float m_EnginePower;
        float S_EnginePower=10;
        float s_power=0;
        int s_Setting=0;
        int Max_s_Setting=5;
        float c_strave=0;
        float max_strave=10;
        float m_Rudder;
        int m_RudderSetting=0;
        int c_Ruddersetting=0;
        int m_MaxEsetting=4;    // full forward
        int m_MinEsetting=-2;   // full reverse
        int m_maxRsetting=4;    // full rudder (symmetric)
        float c_power=0;          // current power setting
        float c_Amoment=0;        // current angular moment
        float c_velocity=0;       // current velocity
        float c_angledt=0;        // angular velocity
        float max_angle=180;      // max angular velocity
        float c_angle=0;          // current angle
        float max_velocity=20;
        float min_velocity=-10;
        sf::Vector2f _speed;
        sf::Time timedelay=sf::seconds(5);
        sf::Time timeRudder=sf::Time::Zero;
        sf::Time timeEninge=sf::Time::Zero;
        sf::Time timeStrave=sf::Time::Zero;
};

#endif // MASSENGINE_H
