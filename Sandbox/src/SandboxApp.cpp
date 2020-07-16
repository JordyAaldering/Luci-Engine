#include <Luci.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Luci::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		m_VertexArray.reset(Luci::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Luci::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Luci::VertexBuffer::Create(vertices, 3 * 7));
		vertexBuffer->SetLayout({
			{ Luci::ShaderDataType::Float3, "a_Position" },
			{ Luci::ShaderDataType::Float4, "a_Color" },
			});
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Luci::IndexBuffer> indexBuffer;
		indexBuffer.reset(Luci::IndexBuffer::Create(indices, 3));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main() {
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 o_Color;

			in vec4 v_Color;

			void main() {
				o_Color = vec4(v_Color);
			}
		)";

		m_Shader.reset(new Luci::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Luci::Timestep timestep) override {
		if (Luci::Input::IsKeyPressed(LUCI_KEY_A)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_D)) {
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}
		if (Luci::Input::IsKeyPressed(LUCI_KEY_W)) {
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_S)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		}
		if (Luci::Input::IsKeyPressed(LUCI_KEY_Q)) {
			m_CameraRotation += m_CameraRotateSpeed * timestep;
		} else if (Luci::Input::IsKeyPressed(LUCI_KEY_E)) {
			m_CameraRotation -= m_CameraRotateSpeed * timestep;
		}

		Luci::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Luci::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Luci::Renderer::BeginScene(m_Camera);
		Luci::Renderer::Submit(m_Shader, m_VertexArray, glm::mat4(1.0f));
		Luci::Renderer::EndScene();
	}

private:
	std::shared_ptr<Luci::Shader> m_Shader;
	std::shared_ptr<Luci::VertexArray> m_VertexArray;

	Luci::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraRotation = 0.0f;

	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotateSpeed = 90.0f;
};

class Sandbox : public Luci::Application {
public:
	Sandbox() { PushLayer(new ExampleLayer()); }
	~Sandbox() = default;
};

Luci::Application* Luci::CreateApplication() {
	return new Sandbox();
}
