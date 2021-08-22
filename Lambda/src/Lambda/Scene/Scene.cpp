#include "lmpch.h"
#include "Scene.h"

#include "Lambda/Scene/Components.h"
#include "Lambda/Scene/Entity.h"

#include "Lambda/Renderer/Renderer2D.h"

#include "glm/glm.hpp"


namespace Lambda
{
	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{
		
	}

	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for(auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}
