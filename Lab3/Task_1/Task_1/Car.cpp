#include "Car.h"

using namespace std;

bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

bool CCar::TurnOnEngine()
{
	if (m_isOn) {
		return false;
	}
	m_isOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	bool cannotTurnOff = m_currentSpeed > 0 && m_gear != Gear::neutral;
	if (m_isOn && cannotTurnOff) 
	{
		return false;
	}
	m_isOn = false;
	return true;
}

bool CCar::IscorrespondsGearAndRangeOfSpeeds(int gear)
{
	switch (static_cast<Gear>(gear))
	{
	case Gear::reverse:
		return 0 <= m_currentSpeed && m_currentSpeed <= 20;
	case Gear::first:
		return 0 <= m_currentSpeed && m_currentSpeed <= 30;
	case Gear::second:
		return 20 <= m_currentSpeed && m_currentSpeed <= 50;
	case Gear::third:
		return 30 <= m_currentSpeed && m_currentSpeed <= 60;
	case Gear::fourth:
		return 40 <= m_currentSpeed && m_currentSpeed <= 90;
	case Gear::fifth:
		return 50 <= m_currentSpeed && m_currentSpeed <= 150;
	default:
		return false;
	}
}

bool CCar::SetGear(int gear) // TODO: переключение на нейтралку как осуществляется?
{                            // TODO: упростить метод
	bool canSwitch = false;
	if (m_isOn)
	{
		if (static_cast<Gear>(gear) == Gear::reverse && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			if (m_gear == Gear::neutral)
			{
				m_direction = Direction::BACK; // move back
				canSwitch = true;
			}
			else if (m_gear == Gear::first && m_currentSpeed == 0)
			{
				m_direction = Direction::BACK; // move back
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::neutral)
		{
			if (m_gear == Gear::reverse || m_currentSpeed >= 0)
			{
				m_direction = Direction::STAND; //car standed
				SetSpeed(0);
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::first && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			if (m_gear == Gear::reverse && m_currentSpeed == 0)
			{
				m_direction = Direction::FORWARD; // move forward
				canSwitch = true;
			}
			else if (m_gear == Gear::neutral && m_direction == Direction::STAND)
			{
				m_direction = Direction::FORWARD; // move forward
				canSwitch = true;
			}
			else
			{
				m_direction = Direction::FORWARD; // move forward
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::second && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			m_direction = Direction::FORWARD; // move forward
			canSwitch = true;
		}
		else if (static_cast<Gear>(gear) == Gear::third && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			m_direction = Direction::FORWARD; // move forward
			canSwitch = true;
		}
		else if (static_cast<Gear>(gear) == Gear::fourth && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			m_direction = Direction::FORWARD; // move forward
			canSwitch = true;
		}
		else if (static_cast<Gear>(gear) == Gear::fifth && IscorrespondsGearAndRangeOfSpeeds(gear))
		{
			m_direction = Direction::FORWARD; // move forward
			canSwitch = true;
		}
	}
	else if (static_cast<Gear>(gear) == Gear::neutral)
	{
		m_direction = Direction::STAND; //car standed
		canSwitch = true;
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
			return true;
		}
		if (m_isOn && m_gear != Gear::neutral)
		{
			m_currentSpeed = speed;
			return true;
		}
	}
	return false;
}