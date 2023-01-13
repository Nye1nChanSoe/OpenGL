#pragma once
#include "Event.h"

class WindowClosedEvent : public Event
{
public:
	WindowClosedEvent() {}

	EVENT_CLASS_TYPE(EventType::WindowClosedEvent)
	EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowResizedEvent : public Event
{
public:
	WindowResizedEvent(int width, int height)
		: m_Width(width), m_Height(height)
	{}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::WindowResizedEvent)
	EVENT_CLASS_CATEGORY(EventCategoryWindow)

private:
	int m_Width, m_Height;
};
