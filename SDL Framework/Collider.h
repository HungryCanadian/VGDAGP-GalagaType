#pragma once
#include "Texture.h"

namespace SDLFramework {

	//Abstract class - will not be made an Object
	class Collider : public GameEntity {
	public:
		enum class ColliderType {Box, Circle}; // box = narrow collision, circle = broad collision

		Collider(ColliderType type);
		virtual ~Collider();

		virtual void Render();

		virtual Vector2 GetFurthestPoint() = 0;

		ColliderType getType();

	protected:
		ColliderType mType;

		static const bool DEBUG_COLLIDERS = false;
		Texture* mDebugTexture;

		void SetDebugTexture(Texture* texture);
	};

}