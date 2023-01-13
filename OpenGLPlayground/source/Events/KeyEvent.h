#pragma once
#include "Event.h"

class KeyEvent : public Event
{
public:
	inline int GetKeyCode() const { return m_KeyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKey)

protected:
	KeyEvent(int keyCode)
		: m_KeyCode(keyCode)
	{}

	int m_KeyCode;
};

class KeyRepeatEvent : public KeyEvent
{
public:
	KeyRepeatEvent(int keycode, int repeatcount)
		: KeyEvent(keycode), m_RepeatCount(repeatcount)
	{}

	inline int GetKeyRepeatCount() const { return m_RepeatCount; }

	EVENT_CLASS_TYPE(EventType::KeyRepeatEvent)

		virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyRepeatEvent: " << m_KeyCode << ", " << m_RepeatCount;
		return ss.str();
	}

private:
	int m_RepeatCount;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int keyCode)
		: KeyEvent(keyCode)
	{}

	EVENT_CLASS_TYPE(EventType::KeyPressedEvent)

	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_KeyCode;
		return ss.str();
	}
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int keyCode)
		: KeyEvent(keyCode)
	{}

	EVENT_CLASS_TYPE(EventType::KeyReleasedEvent)

	virtual std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_KeyCode;
		return ss.str();
	}
}; 

// Event for text input
class KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(unsigned int codepoint)
		: KeyEvent(codepoint)
	{}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyTypedEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(EventType::KeyTypedEvent)
};
