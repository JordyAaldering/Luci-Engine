#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Core/Timestep.h"
#include "Luci/Events/Event.h"

namespace Luci {

	class Layer {
	public:
		Layer(const std::string& debugName = "Layer")
			: m_DebugName(debugName) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};

}
