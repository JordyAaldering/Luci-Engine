#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Renderer/Buffer.h"

#include <memory>

namespace Luci {

	class VertexArray {
	public:
		static Ref<VertexArray> Create();
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};

}
