#pragma once
#pragma warning(push)
#pragma warning(disable: 26812)		// prefer enum class warning

#include "Core.h"

#include <string>
#include <functional>
#include <sstream>

enum class EventType
{
	KeyPressedEvent, KeyReleasedEvent, KeyRepeatEvent, KeyTypedEvent,
	MouseButtonPressed, MouseButtonReleased, MouseMovedEvent, MouseScrolledEvent,
	WindowResizedEvent, WindowClosedEvent
};

enum EventCategory
{
	NONE = 0,
	EventCategoryInput		 = BIT(0),
	EventCategoryKey		 = BIT(1),
	EventCategoryMouse		 = BIT(2),
	EventCategoryMouseButton = BIT(3),
	EventCategoryWindow		 = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return type; }\
							virtual EventType GetEventType() const override { return GetStaticType(); }\
							virtual const char* GetName() const override { return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

class Event
{
	friend class EventDispatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetEventCategoryFlags() const = 0;

	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category) const
	{
		return category & GetEventCategoryFlags();
	}

	bool m_Handled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;

public:
	EventDispatcher(Event& event)
		:m_Event(event)
	{}

	template<typename T>
	bool Dispatch(EventFn<T> funcObject)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled = funcObject((T&)m_Event);	// calling the functor and return true or false
			return true;
		}
		return false;
	}

private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& stream, const Event& event)
{
	return stream << event.ToString();
}

#pragma warning(pop)
