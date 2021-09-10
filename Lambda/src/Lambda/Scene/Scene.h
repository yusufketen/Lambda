#pragma once

#include "entt.hpp"

#include "Lambda/Core/Timestep.h"
#include <vector>

namespace Lambda
{
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);
		void DeleteAllClickedObjects();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		friend class Entity;
		friend class SceneHierarchyPanel;
	public:
		entt::registry m_Registry;
		int renderOrder = 0;
	};


	
}


