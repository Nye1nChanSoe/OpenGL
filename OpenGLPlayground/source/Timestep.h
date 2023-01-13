#pragma once

/* Interval between each frame in seconds */
class Timestep
{
public:
	Timestep(float time)
		: m_Time(time)
	{}

	~Timestep() = default;

	inline float GetSeconds() const { return m_Time; }
	inline float GetMilliSeconds() const { return m_Time * 1000; }

	operator float()
	{
		return m_Time;
	}

private:
	float m_Time = 0.0f;
};