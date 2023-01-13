#pragma once

#include <string>
#include "Events/Event.h"
#include "Timestep.h"

class Layer
{
public:
	Layer(const std::string& name = "Layer")
		: m_Name(name)
	{}

	virtual ~Layer() {}

	virtual inline void OnAttach() {}
	virtual inline void OnDetach() {}
	virtual inline void OnUpdate(Timestep time) {}
	virtual inline void OnEvent(Event& e){}

private:
	std::string m_Name;
};
