#include "lmpch.h"

#include "Lambda/Renderer/Renderer2D.h"

#include "Lambda/Renderer/VertexArray.h"
#include "Lambda/Renderer/Shader.h"
#include "Lambda/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Lambda
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;

		// Editor-only

		int EntityID;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		static const uint32_t MaxCubes = 1000;
		static const uint32_t MaxCubeVertices = MaxCubes * 8;
		static const uint32_t MaxCubeIndices = MaxCubes * 36;

		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;

		Ref<VertexArray> CubeVertexArray;
		Ref<VertexBuffer> CubeVertexBuffer;

		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		uint32_t CubeIndexCount = 0;
		QuadVertex* CubeVertexBufferBase = nullptr;
		QuadVertex* CubeVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];
		glm::vec4 CubeVertexPositions[8];

		Renderer2D::Statistics Stats;
	};

	static Renderer2DData s_Data;
	static glm::vec2 s_TexCoords[4]{ {0.0f,0.0f}, {1.0f, 0.0f},{1.0f, 1.0f}, {0.0f, 1.0f} };

	void Renderer2D::Init()
	{
		LM_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();
		s_Data.CubeVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"		},
			{ ShaderDataType::Float4,	"a_Color"			},
			{ ShaderDataType::Float2,	"a_TexCoord"		},
			{ ShaderDataType::Float,	"a_TexIndex"		},
			{ ShaderDataType::Float,	"a_TilingFactor"	},
			{ ShaderDataType::Int,		"a_EntityID"	}
		});

		s_Data.CubeVertexBuffer = VertexBuffer::Create(s_Data.MaxCubeVertices * sizeof(QuadVertex));
		s_Data.CubeVertexBuffer->SetLayout({
			{ ShaderDataType::Float3,	"a_Position"		},
			{ ShaderDataType::Float4,	"a_Color"			},
			{ ShaderDataType::Float2,	"a_TexCoord"		},
			{ ShaderDataType::Float,	"a_TexIndex"		},
			{ ShaderDataType::Float,	"a_TilingFactor"	},
			{ ShaderDataType::Int,		"a_EntityID"	}
		});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
		s_Data.CubeVertexArray->AddVertexBuffer(s_Data.CubeVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.CubeVertexBufferBase = new QuadVertex[s_Data.MaxCubeVertices];

		auto* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for(uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
		{
			// 0 1 2 2 3 0
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		auto* cubeIndices = new uint32_t[s_Data.MaxCubeIndices];
		uint32_t cubeOffset = 0;
		for (uint32_t i = 0; i < s_Data.MaxCubeIndices; i += 36)
		{
			// Front
			cubeIndices[i + 0] = cubeOffset + 0;
			cubeIndices[i + 1] = cubeOffset + 1;
			cubeIndices[i + 2] = cubeOffset + 2;
			cubeIndices[i + 3] = cubeOffset + 2;
			cubeIndices[i + 4] = cubeOffset + 3;
			cubeIndices[i + 5] = cubeOffset + 0;
			// Right
			cubeIndices[i + 6] = cubeOffset + 1;
			cubeIndices[i + 7] = cubeOffset + 5;
			cubeIndices[i + 8] = cubeOffset + 6;
			cubeIndices[i + 9] = cubeOffset + 6;
			cubeIndices[i + 10] = cubeOffset + 2;
			cubeIndices[i + 11] = cubeOffset + 1;
			// Back
			cubeIndices[i + 12] = cubeOffset + 7;
			cubeIndices[i + 13] = cubeOffset + 6;
			cubeIndices[i + 14] = cubeOffset + 5;
			cubeIndices[i + 15] = cubeOffset + 5;
			cubeIndices[i + 16] = cubeOffset + 4;
			cubeIndices[i + 17] = cubeOffset + 7;
			// Left
			cubeIndices[i + 18] = cubeOffset + 4;
			cubeIndices[i + 19] = cubeOffset + 0;
			cubeIndices[i + 20] = cubeOffset + 3;
			cubeIndices[i + 21] = cubeOffset + 3;
			cubeIndices[i + 22] = cubeOffset + 7;
			cubeIndices[i + 23] = cubeOffset + 4;
			// Bottom
			cubeIndices[i + 24] = cubeOffset + 4;
			cubeIndices[i + 25] = cubeOffset + 5;
			cubeIndices[i + 26] = cubeOffset + 1;
			cubeIndices[i + 27] = cubeOffset + 1;
			cubeIndices[i + 28] = cubeOffset + 0;
			cubeIndices[i + 29] = cubeOffset + 4;
			// Top
			cubeIndices[i + 30] = cubeOffset + 3;
			cubeIndices[i + 31] = cubeOffset + 2;
			cubeIndices[i + 32] = cubeOffset + 6;
			cubeIndices[i + 33] = cubeOffset + 6;
			cubeIndices[i + 34] = cubeOffset + 7;
			cubeIndices[i + 35] = cubeOffset + 3;
		}


		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;


		Ref<IndexBuffer> cubeIB = IndexBuffer::Create(cubeIndices, s_Data.MaxCubeIndices);
		s_Data.CubeVertexArray->SetIndexBuffer(cubeIB);
		delete[] cubeIndices;

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

		// Set all texture slots to 0
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;

		s_Data.QuadVertexPositions[0] = { -0.5f,-0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[1] = {  0.5f,-0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[2] = {  0.5f, 0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };


		s_Data.CubeVertexPositions[0] = { -0.5f,-0.5f, 0.5f, 1.0f };
		s_Data.CubeVertexPositions[1] = {  0.5f,-0.5f, 0.5f, 1.0f };
		s_Data.CubeVertexPositions[2] = {  0.5f, 0.5f, 0.5f, 1.0f };
		s_Data.CubeVertexPositions[3] = { -0.5f, 0.5f, 0.5f, 1.0f };
		s_Data.CubeVertexPositions[4] = { -0.5f,-0.5f,-0.5f, 1.0f };
		s_Data.CubeVertexPositions[5] = { 0.5f,-0.5f,-0.5f, 1.0f };
		s_Data.CubeVertexPositions[6] = { 0.5f, 0.5f,-0.5f, 1.0f };
		s_Data.CubeVertexPositions[7] = { -0.5f, 0.5f,-0.5f, 1.0f };
	}

	void Renderer2D::Shutdown()
	{
		LM_PROFILE_FUNCTION();

		delete[] s_Data.QuadVertexBufferBase;
		delete[] s_Data.CubeVertexBufferBase;
	}

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		LM_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", viewProj);

		StartBatch();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		LM_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		StartBatch();
	}

	void Renderer2D::EndScene()
	{
		LM_PROFILE_FUNCTION();
		
		Flush();
	}

	void Renderer2D::StartBatch()
	{
		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.CubeIndexCount = 0;
		s_Data.CubeVertexBufferPtr = s_Data.CubeVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	void Renderer2D::Flush()
	{
		if (s_Data.QuadIndexCount == 0)
			return;

		if (s_Data.CubeIndexCount == 0)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		uint32_t cubeDataSize = (uint32_t)((uint8_t*)s_Data.CubeVertexBufferPtr - (uint8_t*)s_Data.CubeVertexBufferBase);
		s_Data.CubeVertexBuffer->SetData(s_Data.CubeVertexBufferBase, cubeDataSize);

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
		s_Data.Stats.DrawCalls++;

		RenderCommand::DrawIndexed(s_Data.CubeVertexArray, s_Data.CubeIndexCount);
		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::NextBatch()
	{
		Flush();
		StartBatch();
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID)
	{
		LM_PROFILE_FUNCTION();

		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		const float texIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		for (int i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = s_TexCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawCube(const glm::mat4& transform, const glm::vec4& color, int entityID)
	{
		LM_PROFILE_FUNCTION();

		if (s_Data.CubeIndexCount >= Renderer2DData::MaxCubeIndices)
			NextBatch();

		const float texIndex = 0.0f; // White Texture
		const float tilingFactor = 1.0f;

		/*for (int i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = s_TexCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = texIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;*/

		for (int i = 0; i < 8; i++)
		{
			s_Data.CubeVertexBufferPtr->Position = transform * s_Data.CubeVertexPositions[i];
			s_Data.CubeVertexBufferPtr->Color = color;
			s_Data.CubeVertexBufferPtr->TexCoord = s_TexCoords[i%4];
			s_Data.CubeVertexBufferPtr->TexIndex = texIndex;
			s_Data.CubeVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.CubeVertexBufferPtr->EntityID = entityID;
			s_Data.CubeVertexBufferPtr++;
		}

		s_Data.CubeIndexCount += 36;

		s_Data.Stats.CubeCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D> texture, float tilingFactor,
		const glm::vec4& tintColor, int entityID)
	{
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			NextBatch();

		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i] == *texture.get())
			{
				textureIndex = static_cast<float>(i);
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (int i = 0; i < 4; i++)
		{
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
			s_Data.QuadVertexBufferPtr->Color = tintColor;
			s_Data.QuadVertexBufferPtr->TexCoord = s_TexCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			s_Data.QuadVertexBufferPtr->EntityID = entityID;
			s_Data.QuadVertexBufferPtr++;
		}
		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2 position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec2& size, const glm::vec4& color)
	{
		LM_PROFILE_FUNCTION();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawCube(const glm::vec3 position, const glm::vec3& size, const glm::vec4& color)
	{
		LM_PROFILE_FUNCTION();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z });

		DrawCube(transform, color);
	}


	void Renderer2D::DrawQuad(const glm::vec2 position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3 position, const glm::vec2& size, const Ref<Texture2D> texture, float tilingFactor, const glm::vec4& tintColor)
	{
		LM_PROFILE_FUNCTION();

		const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
	                                 const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const glm::vec4& color)
	{
		LM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);

	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
		const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		LM_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID)
	{
		DrawQuad(transform, src.Color, entityID);
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

}

