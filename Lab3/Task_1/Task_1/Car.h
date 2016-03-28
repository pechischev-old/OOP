#pragma once
#include <iostream>

static const int MAX_SPEED = 150;

enum class Direction 
{
	BACK = -1,
	STAND,
	FORWARD
};

enum class Gear
{
	reverse = -1,
	neutral,
	first,
	second,
	third,
	fourth,
	fifth
};

class CCar
{
public:
	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned speed);
	int GetGear() const;
	unsigned GetSpeed() const;
	int GetDirection() const;
private:
	bool IscorrespondsGearAndRangeOfSpeeds(int gear);
private:
	bool m_isOn = false;
	Gear m_gear = Gear::neutral;
	unsigned m_currentSpeed = 0;
	Direction m_direction = Direction::STAND;
};

