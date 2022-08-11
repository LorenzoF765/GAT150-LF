#pragma once
#include "../Math/Transform.h"

namespace Solas
{
	class GameObject
	{
	public:

		GameObject() = default;
		

		virtual void Update() = 0;

		 // Removed GetTransform(), was never used. Maple said to so yeah

	private:

	protected:

		

	};
}