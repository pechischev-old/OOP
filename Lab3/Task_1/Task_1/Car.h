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
	REVERSE = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

class CCar
{
public:
	bool IsTurnedOn() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(Gear gear);
	bool SetSpeed(unsigned speed);
	int GetGear() const;
	unsigned GetSpeed() const;
	Direction GetDirection() const;
private:
	void UpdateDirection();
private:
	bool m_isOn = false;
	Gear m_gear = Gear::NEUTRAL;
	unsigned m_currentSpeed = 0;
	Direction m_direction = Direction::STAND;
};

static bool const IsRangeOfSpeed(Gear gear, unsigned speed);
