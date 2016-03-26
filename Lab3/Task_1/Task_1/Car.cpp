#include "Car.h"

using namespace std;

bool CCar::IsTurnedOn() const
{
	return m_isOn;
}

bool CCar::TurnOnEngine()
{
	bool canTurnOff = m_currentSpeed == 0 && m_gear == Gear::neutral;
	if (m_isOn && !canTurnOff) {
		return false;
	}
	m_isOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isOn && m_gear != Gear::neutral && m_direction != Direction::STAND) {
		return false;
	}

	m_isOn = false;
	return true;
}

bool CCar::SetGear(int gear) // TODO: переключение на нейтралку как осуществляется?
{                            // TODO: упростить метод
	bool canSwitch = false;
	if (m_isOn)
	{
		if (static_cast<Gear>(gear) == Gear::reverse && m_currentSpeed >= 0 && m_currentSpeed <= 20)
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
		else if (static_cast<Gear>(gear) == Gear::first && m_currentSpeed >= 0 && m_currentSpeed <= 30)
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
		}
		else if (static_cast<Gear>(gear) == Gear::second)
		{
			if (20 <= m_currentSpeed && m_currentSpeed <= 50)
			{
				m_direction = Direction::FORWARD; // move back
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::third)
		{
			if (30 <= m_currentSpeed && m_currentSpeed <= 60)
			{
				m_direction = Direction::FORWARD; // move back
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::fourth)
		{
			if (40 <= m_currentSpeed && m_currentSpeed <= 90)
			{
				m_direction = Direction::FORWARD; // move back
				canSwitch = true;
			}
		}
		else if (static_cast<Gear>(gear) == Gear::fifth)
		{
			if (50 <= m_currentSpeed && m_currentSpeed <= 150)
			{
				m_direction = Direction::FORWARD; // move back
				canSwitch = true;
			}
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
	if (speed == 0 && m_gear == Gear::neutral)
	{
		return true;
	}
	if (m_isOn && m_gear != Gear::neutral)
	{
		m_currentSpeed = speed;
		return true;
	}
	return false;
}