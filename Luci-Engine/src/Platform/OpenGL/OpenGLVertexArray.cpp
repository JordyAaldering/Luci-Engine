#include "lucipch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Luci {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Bool:	 return GL_BOOL;
			case ShaderDataType::Int:	 return GL_INT;
			case ShaderDataType::Int2:	 return GL_INT;
			case ShaderDataType::Int3:	 return GL_INT;
			case ShaderDataType::Int4:	 return GL_INT;
			case ShaderDataType::Float:	 return GL_FLOAT;
			case ShaderDataType::Float2: return GL_FLOAT;
			case ShaderDataType::Float3: return GL_FLOAT;
			case ShaderDataType::Float4: return GL_FLOAT;
			case ShaderDataType::Mat3:	 return GL_FLOAT;
			case ShaderDataType::Mat4:	 return GL_FLOAT;
		}

		LUCI_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		LUCI_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		LUCI_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		LUCI_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const {
		LUCI_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
		LUCI_PROFILE_FUNCTION();
		LUCI_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout.");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const BufferLayout& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
		LUCI_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}
