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
		tag.order = renderOrder++;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdate(Timestep ts)
	{

		const Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			
			Renderer2D::BeginScene(*mainCamera, cameraTransform);
			
			//auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>, entt::exclude<ClickComponent>);
			
			

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent, TagComponent>);

			group.sort<TagComponent>([](const auto &a, const auto &b)
			{
				return a.order < b.order;
			});

			for (auto entity : group)
			{	
				auto&[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);	
			}
			

			/*auto clickedGroup = m_Registry.group<ClickComponent>(entt::get<TransformComponent, SpriteRendererComponent>);
			
			clickedGroup.sort([](const entt::entity a, const entt::entity b) {
				return (int)a > (int)b;
			});

			for (auto clickedEntity : clickedGroup)
			{	
				auto&[transform, sprite] = clickedGroup.get<TransformComponent, SpriteRendererComponent>(clickedEntity);
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)clickedEntity);
			}*/

			/*if (group.size() == 0 && clickedGroup.size() != 0)
			{
				m_Registry.clear<ClickComponent>();
			}*/
			Renderer2D::EndScene();

		}


	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non fixed aspect ration cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
	}

	template <typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	/*template<>
	void Scene::OnComponentAdded<ClickComponent>(Entity entity, ClickComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdded<SelectComponent>(Entity entity, SelectComponent& component)
	{

	}*/
	/*
	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{

	}
	*/

	void Scene::DeleteAllClickedObjects()
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent, TagComponent>);

		//group.sort<TagComponent>([](const auto &a, const auto &b)
		//{
		//	return (int)a < (int)b;
		//});

		for (auto entity : group)
		{
			m_Registry.get<TagComponent>(entity).order = (int)entity;
			
		}
		//m_Registry.clear<ClickComponent>();
	}
}
