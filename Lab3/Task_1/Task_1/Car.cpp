#include "Car.h"

bool CCar::IsTurnedOn()
{
	return m_isOn;
}

bool CCar::TurnOnEngine()
{
	bool canTurnOff = m_currentSpeed == 0 && m_gear == 0;
	if (m_isOn && !canTurnOff) {
		return false;
	}
	m_isOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if (!m_isOn) {
		return false;
	}
	m_gear = 0;
	m_currentSpeed = 0;
	m_direction = SDirectionMove::STAND;
	m_isOn = false;
	return true;
}

bool CCar::SetGear(int gear) // TODO: переделать функцию
{
	if (m_isOn)
	{
		if (0 <= m_currentSpeed && m_currentSpeed <= 20 && gear == -1 && m_direction == SDirectionMove::STAND)
		{
			m_gear = gear;
			m_direction = SDirectionMove::BACK;
			return true;
		}
		else if (0 <= m_currentSpeed && m_currentSpeed <= 30 && gear == 1 && m_direction == SDirectionMove::BACK)
		{
			m_direction = SDirectionMove::FORWARD;
			m_gear = gear;
			return true;
		}
		else if (20 <= m_currentSpeed && m_currentSpeed <= 50)
		{
			m_direction = SDirectionMove::FORWARD;
			m_gear = gear;
			return true;
		}
		else if (30 <= m_currentSpeed && m_currentSpeed <= 60)
		{
			m_direction = SDirectionMove::FORWARD;
			m_gear = gear;
			return true;
		}
		else if (40 <= m_currentSpeed && m_currentSpeed <= 90)
		{
			m_direction = SDirectionMove::FORWARD;
			m_gear = gear;
			return true;
		}
		else if (50 <= m_currentSpeed && m_currentSpeed <= 150)
		{
			m_direction = SDirectionMove::FORWARD;
			m_gear = gear;
			return true;
		}
		else if (gear == 0 && m_direction == SDirectionMove::STAND)
		{
			m_direction = SDirectionMove::STAND;
			m_gear = gear;
			return true;
		}
	}
	return false;
}

int CCar::GetGear()
{
	return m_gear;
}

unsigned CCar::GetSpeed()
{
	return m_currentSpeed;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (m_isOn && m_gear != 0)
	{
		m_currentSpeed = speed;
		return true;
	}
	return false;
}