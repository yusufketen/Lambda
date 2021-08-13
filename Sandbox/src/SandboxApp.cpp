#include <Lambda.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Lambda::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(Lambda::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		Lambda::Ref<Lambda::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lambda::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lambda::BufferLayout layout = {
			{Lambda::ShaderDataType::Float3, "a_Position" },
			{Lambda::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Lambda::Ref<Lambda::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lambda::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lambda::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Lambda::Ref<Lambda::VertexBuffer> squareVB;
		squareVB.reset(Lambda::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Lambda::ShaderDataType::Float3, "a_Position" },
			{Lambda::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Lambda::Ref<Lambda::IndexBuffer> squareIB;
		squareIB.reset(Lambda::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
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


		m_Shader.reset(Lambda::Shader::Create(vertexSrc, fragmentSrc));

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


		m_FlatColorShader.reset(Lambda::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));

		std::string textureShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in  vec3 a_Position;
			layout(location = 1) in  vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out  vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";


		m_TextureShader.reset(Lambda::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = Lambda::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Lambda::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Lambda::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Lambda::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
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

		std::dynamic_pointer_cast<Lambda::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Lambda::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for(int y = 0; y < 20; y++)
		{
			for(int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Lambda::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		m_Texture->Bind();
		Lambda::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_LogoTexture->Bind();
		Lambda::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
	Lambda::Ref<Lambda::Shader> m_Shader;
	Lambda::Ref<Lambda::VertexArray> m_VertexArray;

	Lambda::Ref<Lambda::Shader> m_FlatColorShader, m_TextureShader;
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
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Lambda::Application* Lambda::CreateApplication()
{
	return new Sandbox();
}