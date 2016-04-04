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

bool CCar::IsCorrespondsGearAndRangeOfSpeeds(int gear, unsigned speed)
{
	switch (static_cast<Gear>(gear))
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

bool CCar::SetGear(int gear) 
{                            
	bool canSwitch = false;
	if (m_isOn)
	{
		if (static_cast<Gear>(gear) == Gear::reverse && IsCorrespondsGearAndRangeOfSpeeds(gear, m_currentSpeed))
		{
			if (m_gear == Gear::neutral)
			{
				canSwitch = true;
			}
			else if (m_gear == Gear::first && m_currentSpeed == 0)
			{
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::first && (m_gear == Gear::reverse || m_gear == Gear::neutral))
		{
			if (m_currentSpeed == 0)
			{
				canSwitch = true;
			}
			else if (m_direction == Direction::STAND)
			{
				canSwitch = true;
			}
		}
		else if (IsCorrespondsGearAndRangeOfSpeeds(gear, m_currentSpeed))
		{
			canSwitch = true;
		}
	}
	if (static_cast<Gear>(gear) == Gear::neutral)
	{
		if (m_gear == Gear::reverse || m_currentSpeed >= 0)
		{
			canSwitch = true;
		}
	}

	if (canSwitch)
	{
		m_gear = static_cast<Gear>(gear);
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
		if (speed == 0 && m_gear == Gear::neutral)
		{
			m_direction = Direction::STAND;
			return true;
		}
		if (m_isOn && m_gear != Gear::neutral && IsCorrespondsGearAndRangeOfSpeeds(static_cast<int>(m_gear), speed))
		{
			m_currentSpeed = speed;
			SetDirection();
			return true;
		}
	}
	return false;
}