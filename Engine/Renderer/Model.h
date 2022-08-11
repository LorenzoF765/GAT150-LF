#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace Solas
{
	class Model
	{

	public:

		Model() = default;
		Model(const std::vector<Solas::Vector2>& points, const Solas::Color& color) : points_{ points }, color_{ color } {}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale = Vector2{1, 1});

		void Load(const std::string& filename);

		float GetRadius() { return radius_; }
		float CalculateRadius();

	private:

		Solas::Color color_;
		std::vector<Solas::Vector2> points_;
		float radius_ = 0;

	};
}
