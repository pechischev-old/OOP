#include "Car.h"

using namespace std;

bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isOn) 
	{
		return false;
	}
	m_isOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	bool cannotTurnOff = !m_isOn || m_currentSpeed > 0 || m_gear != Gear::NEUTRAL;
	if (cannotTurnOff) 
	{
		return false;
	}
	m_isOn = false;
	return true;
}

bool const IsRangeOfSpeed(Gear gear, unsigned speed)
{
	switch (gear)
	{
	case Gear::REVERSE:
		return 0 <= speed && speed <= 20;
	case Gear::FIRST:
		return 0 <= speed && speed <= 30;
	case Gear::SECOND:
		return 20 <= speed && speed <= 50;
	case Gear::THIRD:
		return 30 <= speed && speed <= 60;
	case Gear::FOURTH:
		return 40 <= speed && speed <= 90;
	case Gear::FIFTH:
		return 50 <= speed && speed <= 150;
	default:
		return false;
	}
}

bool CCar::SetGear(Gear gear)
{                            
	bool canSwitch = false;
	if (m_isOn)
	{
		if (gear == Gear::REVERSE && IsRangeOfSpeed(gear, m_currentSpeed))
		{
			canSwitch = ((m_gear == Gear::NEUTRAL || m_gear == Gear::FIRST) && m_currentSpeed == 0);
		}
		else if (gear == Gear::FIRST && (m_gear == Gear::REVERSE || m_gear == Gear::NEUTRAL))
		{
			canSwitch = ((m_currentSpeed == 0 && m_gear == Gear::REVERSE) || (m_currentSpeed >= 0 && m_gear == Gear::NEUTRAL));
		}
		else if (gear >= Gear::FIRST && IsRangeOfSpeed(gear, m_currentSpeed))
		{
			canSwitch = true;
		}
	}
	if (gear == Gear::NEUTRAL && (m_gear == Gear::REVERSE || m_currentSpeed >= 0))
	{
		canSwitch = true;
	}

	if (canSwitch)
	{
		m_gear = gear;
		return true;
	}
	return false;
}

int CCar::GetGear() const
{
	return static_cast<int>(m_gear);
}

void CCar::UpdateDirection()
{
	if (m_currentSpeed != 0)
	{
		if (m_gear == Gear::REVERSE)
		{
			m_direction = Direction::BACK;
		}
		else if (m_gear != Gear::NEUTRAL)
		{
			m_direction = Direction::FORWARD;
		}
	}
	else
	{
		m_direction = Direction::STAND;
	}
}

unsigned CCar::GetSpeed() const
{
	return m_currentSpeed;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (0 <= speed && speed <= MAX_SPEED)
	{
		if (m_gear == Gear::NEUTRAL && (m_currentSpeed >= speed || speed == 0))
		{
			m_currentSpeed = speed;
			UpdateDirection();
			return true;
		}
		if (m_isOn && m_gear != Gear::NEUTRAL && IsRangeOfSpeed(m_gear, speed))
		{
			m_currentSpeed = speed;
			UpdateDirection();
			return true;
		}
	}
	return false;
}