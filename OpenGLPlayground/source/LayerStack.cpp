#include "LayerStack.h"

LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
	for (auto* layer : m_LayerStack)
		delete layer;
}

void LayerStack::PushLayer(Layer* layer)
{
	m_LayerStack.emplace(m_LayerStack.begin() + m_LayerStackIndex, layer);
	m_LayerStackIndex++;
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), layer);
	if (it != m_LayerStack.end())
	{
		m_LayerStack.erase(it);
		m_LayerStackIndex--;
	}
}

void LayerStack::PushOverlay(Layer* overlay)
{
	m_LayerStack.emplace_back(overlay);
}

void LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_LayerStack.begin(), m_LayerStack.end(), overlay);
	if (it != m_LayerStack.end())
	{
		m_LayerStack.erase(it);
	}
}
