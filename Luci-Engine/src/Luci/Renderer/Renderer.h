#pragma once

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Luci {
	
	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};

}