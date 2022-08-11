#include "Scene.h"
#include <algorithm>
#include <iostream>

namespace Solas
{
	void Scene::Update()
	{
		auto iter = actors_.begin();
		while (iter != actors_.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = actors_.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// Check Collision

		for (auto iter1 = actors_.begin(); iter1 != actors_.end(); iter1++)
		{
			for (auto iter2 = actors_.begin(); iter2 != actors_.end(); iter2++)
			{
				if (iter1 == iter2) continue;

				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();
				float distance = (*iter1)->transform_.position.Distance((*iter2)->transform_.position);

				if (distance > radius)
				{
					(*iter1)->OnCollision((*iter2).get());
					(*iter2)->OnCollision((*iter1).get());
				}
			}
		}
	}
	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : actors_)
		{
			actor->Draw(renderer);
		}
	}
	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		actors_.push_back(std::move(actor));
	}
}