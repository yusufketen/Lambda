#include <Lambda.h>
#include <Lambda/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

namespace Lambda
{

	class ExampleLayer : public Lambda::Layer
	{
	public:
		ExampleLayer()
			: Layer("Example"), m_CameraController(1280.0f / 720.0f)
		{
			m_VertexArray = Lambda::VertexArray::Create();

			float vertices[3 * 7] = {
				-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
				 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
				 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
			};

			Lambda::Ref<Lambda::VertexBuffer> vertexBuffer = Lambda::VertexBuffer::Create(vertices, sizeof(vertices));
			Lambda::BufferLayout layout = {
				{Lambda::ShaderDataType::Float3, "a_Position" },
				{Lambda::ShaderDataType::Float4, "a_Color" }
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			uint32_t indices[3] = { 0, 1, 2 };
			Lambda::Ref<Lambda::IndexBuffer> indexBuffer = Lambda::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_SquareVA = Lambda::VertexArray::Create();

			float squareVertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			Lambda::Ref<Lambda::VertexBuffer> squareVB = Lambda::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
			squareVB->SetLayout({
				{Lambda::ShaderDataType::Float3, "a_Position" },
				{Lambda::ShaderDataType::Float2, "a_TexCoord" },
				});
			m_SquareVA->AddVertexBuffer(squareVB);

			uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
			Lambda::Ref<Lambda::IndexBuffer> squareIB = Lambda::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
			m_SquareVA->SetIndexBuffer(squareIB);

			std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in  vec3 a_Position;
			layout(location = 1) in  vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

			std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out  vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";


			m_Shader = Lambda::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

			std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in  vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

			std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out  vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";


			m_FlatColorShader = Lambda::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);


			auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

			m_Texture = Lambda::Texture2D::Create("assets/textures/Checkerboard.png");
			m_LogoTexture = Lambda::Texture2D::Create("assets/textures/ChernoLogo.png");

			textureShader->Bind();
			textureShader->SetInt("u_Texture", 0);
		}

		void OnUpdate(Lambda::Timestep ts) override
		{
			//LM_TRACE("Timestep: {0}ms", ts.GetMilliseconds());

			// Update
			m_CameraController.OnUpdate(ts);

			// Render
			Lambda::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			Lambda::RenderCommand::Clear();

			Lambda::Renderer::BeginScene(m_CameraController.GetCamera());

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			m_FlatColorShader->Bind();
			m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Lambda::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				}
			}

			auto textureShader = m_ShaderLibrary.Get("Texture");

			m_Texture->Bind();
			Lambda::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			m_LogoTexture->Bind();
			Lambda::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			// Triangle
			//Lambda::Renderer::Submit(m_Shader, m_VertexArray);

			Lambda::Renderer::EndScene();
		}

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Settings");

			ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

			ImGui::End();
		}

		void OnEvent(Lambda::Event& e) override
		{
			m_CameraController.OnEvent(e);
		}

	private:
		Lambda::ShaderLibrary m_ShaderLibrary;
		Lambda::Ref<Lambda::Shader> m_Shader;
		Lambda::Ref<Lambda::VertexArray> m_VertexArray;

		Lambda::Ref<Lambda::Shader> m_FlatColorShader;
		Lambda::Ref<Lambda::VertexArray> m_SquareVA;

		Lambda::Ref<Lambda::Texture2D> m_Texture, m_LogoTexture;

		Lambda::OrthographicCameraController m_CameraController;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	};

	class Sandbox : public Lambda::Application
	{
	public:
		Sandbox()
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new Sandbox2D());
		}

		~Sandbox()
		{

		}
	};

	Lambda::Application* Lambda::CreateApplication()
	{
		return new Sandbox();
	}

}
