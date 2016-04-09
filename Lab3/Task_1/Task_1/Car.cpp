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
	bool cannotTurnOff = !m_isOn || m_currentSpeed > 0 || m_gear != Gear::neutral;
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
	case Gear::reverse:
		return 0 <= speed && speed <= 20;
	case Gear::first:
		return 0 <= speed && speed <= 30;
	case Gear::second:
		return 20 <= speed && speed <= 50;
	case Gear::third:
		return 30 <= speed && speed <= 60;
	case Gear::fourth:
		return 40 <= speed && speed <= 90;
	case Gear::fifth:
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
		if (gear == Gear::reverse && IsRangeOfSpeed(gear, m_currentSpeed))
		{
			canSwitch = ((m_gear == Gear::neutral || m_gear == Gear::first) && m_currentSpeed == 0);
		}
		else if (gear == Gear::first && (m_gear == Gear::reverse || m_gear == Gear::neutral))
		{
			canSwitch = ((m_currentSpeed == 0 && m_gear == Gear::reverse) || (m_currentSpeed >= 0 && m_gear == Gear::neutral));
		}
		else if (gear >= Gear::first && IsRangeOfSpeed(gear, m_currentSpeed))
		{
			canSwitch = true;
		}
	}
	if (gear == Gear::neutral && (m_gear == Gear::reverse || m_currentSpeed >= 0))
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

void CCar::SetDirection()
{
	if (m_currentSpeed != 0)
	{
		if (m_gear == Gear::reverse)
		{
			m_direction = Direction::BACK;
		}
		else if (m_gear != Gear::neutral)
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

int CCar::GetDirection() const
{
	return static_cast<int>(m_direction);
}

bool CCar::SetSpeed(unsigned speed)
{
	if (0 <= speed && speed <= MAX_SPEED)
	{
		if (m_gear == Gear::neutral && (m_currentSpeed >= speed || speed == 0))
		{
			m_currentSpeed = speed;
			SetDirection();
			return true;
		}
		if (m_isOn && m_gear != Gear::neutral && IsRangeOfSpeed(m_gear, speed))
		{
			m_currentSpeed = speed;
			SetDirection();
			return true;
		}
	}
	return false;
}