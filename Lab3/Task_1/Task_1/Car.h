#pragma once

enum class SDirectionMove 
{
	FORWARD,
	BACK,
	STAND
};

class CCar
{
public:
	bool IsTurnedOn();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);
	int GetGear();
	unsigned GetSpeed();
private:
	bool m_isOn = false;
	int m_gear = 0;
	unsigned m_currentSpeed = 0;
	SDirectionMove m_direction = SDirectionMove::STAND;
};

