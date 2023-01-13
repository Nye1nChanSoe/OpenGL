#pragma once

#include "Layer.h"
#include <vector>

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopOverlay(Layer* overlay);

	std::vector<Layer*>::iterator begin() { return m_LayerStack.begin(); }
	std::vector<Layer*>::iterator end() { return m_LayerStack.end(); }

private:
	unsigned int m_LayerStackIndex = 0;
	std::vector<Layer*> m_LayerStack;
};
