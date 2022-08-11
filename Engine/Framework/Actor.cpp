#include "Actor.h"
#include "Components/RendererComponents.h"

namespace Solas
{
	void Actor::Draw(Renderer& renderer)
	{
		for (auto& component : m_components) {
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent) {
				renderComponent->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component) {
		component->m_owner = this;

		m_components.push_back(std::move(component));
	}

	void Actor::Update() {
		for (auto& component : m_components) {
			component->Update();
		}
	}
}
