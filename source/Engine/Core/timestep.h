#pragma once

class timestep {
public:
	timestep(float time = 0.0f)
		: m_Time(time) {

	}
	
	float getSeconds() const { return m_Time; }

	float getMilliseconds() const { return m_Time * 1000.0f; }

private:
	float m_Time;
};
