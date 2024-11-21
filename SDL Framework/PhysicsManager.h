#pragma once
#include <bitset>
#include "PhysicsEntity.h"

namespace SDLFramework {
	class PhysicsManager {
	public:
		enum class CollisionLayers { //Any NEW layers need to be placed BEFORE MaxLayers
			Friendly,
			FriendlyProjectile,
			Hostile,
			HostileProjectile,
			MaxLayers
		};

		enum class CollisionFlags {
			None = 0x00,
			Friendly = 0x01,
			FriendlyProjectile = 0x02,
			Hostile = 0x04,
			HostileProjectile = 0x08
		};

		static PhysicsManager* Instance();
		static void Release();

		unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
		void UnregisterEntity(unsigned long id);

		void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

		void Update();
		
	private:
		static PhysicsManager* sInstance;
		PhysicsManager();
		~PhysicsManager();
		std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
		std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

		unsigned long mLastID;
	};

	inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int> (b));
	}

	inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int> (b));
	}
}
