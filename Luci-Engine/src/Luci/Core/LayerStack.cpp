#include "lucipch.h"

#include "Luci/Core/LayerStack.h"

namespace Luci {

	LayerStack::~LayerStack() {
		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		auto it = std::find(begin(), end(), layer);
		if (it != begin() + m_LayerInsertIndex) {
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		auto it = std::find(begin(), end(), overlay);
		if (it != end()) {
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}

}
