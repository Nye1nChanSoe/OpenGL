#pragma once
#include "Event.h"

class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float xpos, float ypos)
		: m_xpos(xpos), m_ypos(ypos)
	{}

	inline float GetXPos() const { return m_xpos; }
	inline float GetYPos() const { return m_ypos; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << m_xpos << ", " << m_ypos;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	EVENT_CLASS_TYPE(EventType::MouseMovedEvent)

private:
	float m_xpos, m_ypos;
};


class MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(float xoffset, float yoffset)
		: m_xoffset(xoffset), m_yoffset(yoffset)
	{}

	inline float GetXOffset() const { return m_xoffset; }
	inline float GetYOffset() const { return m_yoffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << m_xoffset << ", " << m_yoffset;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	EVENT_CLASS_TYPE(EventType::MouseScrolledEvent)

private:
	float m_xoffset, m_yoffset;
};


class MouseButtonEvent : public Event
{
public:
	inline int GetMouseButton() const { return m_Button; }

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

protected:
	MouseButtonEvent(int button)
		: m_Button(button)
	{}

	int m_Button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button)
		: MouseButtonEvent(button)
	{}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button)
		: MouseButtonEvent(button)
	{}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << m_Button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::MouseButtonPressed)
};