#pragma once
#include "Collider.h"
#include <vector>

namespace SDLFramework {
	//base class for any object we want to have colliders
	class PhysicsEntity : public GameEntity {
	public:
		PhysicsEntity();
		virtual ~PhysicsEntity();

		unsigned long getId();

		bool CheckCollision(PhysicsEntity* other);

		virtual void Hit(PhysicsEntity* other) {};

		virtual void Render() override;


	protected:
		

		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;
		
		virtual bool IgnoreCollisions();


		void AddCollider(Collider* collider, Vector2 localPos = Vec2_Zero);
		unsigned long mId;
	};

}