#include "Engine.h"
#include "Math/MathUtils.h"
#include <iostream>

int main()
{


	Solas::initializeMemory();

	Solas::setFilePath("../Assets");

	Solas::renderer_g.Initialize();
	Solas::inputSystem_g.Initialize();
	Solas::audioSystem_g.Initialize();

	Solas::audioSystem_g.AddAudio("lazer", "Audio/temp-lazer.wav");

	Solas::renderer_g.CreateWindow("Engine", 800, 600); // Creates the window with parameters
	Solas::renderer_g.SetClearColor(Solas::Color{ 0, 0, 0, 255 });

	std::shared_ptr<Solas::Texture> texture = std::make_shared<Solas::Texture>();
	texture->Create(Solas::renderer_g, "Sprites/WaddleDee.png");
	float angle = 0;

	Solas::Scene scene;
	std::unique_ptr<Solas::Actor> actor = std::make_unique<Solas::Actor>();
	//Player component
	std::unique_ptr<Solas::PlayerComponent> playerComponent = std::make_unique<Solas::PlayerComponent>();
	actor->AddComponent(std::move(playerComponent));
	//Sprite component
	std::unique_ptr<Solas::SpriteComponent> sprComponent = std::make_unique<Solas::SpriteComponent>();
	sprComponent->texture_ = texture;
	actor->AddComponent(std::move(sprComponent));
	//Audio component
	std::unique_ptr<Solas::AudioComponent> acomponent = std::make_unique<Solas::AudioComponent>();
	actor->AddComponent(std::move(acomponent));
	//Physics component
	std::unique_ptr<Solas::PhysicsComponent> phcomponent = std::make_unique<Solas::PhysicsComponent>();
	actor->AddComponent(std::move(phcomponent));

	scene.Add(move(actor));



	bool quit = false;
	while (!quit)
	{
		// Update
		Solas::timer_g.Tick();
		Solas::inputSystem_g.Update();
		Solas::audioSystem_g.Update();

		if (Solas::inputSystem_g.onKeyEsc(Solas::InputSystem::KeyState::Pressed)) {
			quit = true;
		}

		//angle += 1;

		scene.Update();

		// Render
		Solas::renderer_g.BeginFrame();

		Solas::renderer_g.Draw(texture, { 400, 300 }, angle, { 2.0f, 2.0f }, { 0.5f, 0.5f });

		Solas::renderer_g.EndFrame();
	}

	Solas::inputSystem_g.Shutdown();
	Solas::audioSystem_g.Shutdown();
	Solas::renderer_g.ShutDown();
}