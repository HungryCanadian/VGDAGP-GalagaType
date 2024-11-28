#include "PhysicsEntity.h"
#include "PhysicsManager.h"
#include "PhysicsHelper.h"

namespace SDLFramework {

	void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos) {
		collider->Parent(this);
		collider->Position(localPos);
		mColliders.push_back(collider);

		if (mColliders.size() > 1 || mColliders[0]->getType() != Collider::ColliderType::Circle) {
			float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
			float dist = 0.0f;

			for (int i = 1; i < mColliders.size(); i++) {
				dist = mColliders[i]->GetFurthestPoint().Magnitude();

				if (dist > furthestDistance) {
					furthestDistance = dist;
				}
			}

			delete mBroadPhaseCollider;
			mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
			mBroadPhaseCollider->Parent(this);
			mBroadPhaseCollider->Position(Vec2_Zero);
		}
	}

	PhysicsEntity::PhysicsEntity() {
		mBroadPhaseCollider = nullptr;
		mId = 0;
	}

	PhysicsEntity::~PhysicsEntity() {
		for (auto colliders : mColliders) {
			delete colliders;
			colliders = nullptr;
		}
		mColliders.clear();

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;

		if (mId != 0) {
			PhysicsManager::Instance()->UnregisterEntity(mId);
		}
	}

	unsigned long PhysicsEntity::getId() {
		return mId;
	}

	bool PhysicsEntity::IgnoreCollisions() {
		return false;
	}

	void PhysicsEntity::Render() {
		for (auto colliders : mColliders) {
			colliders->Render();
		}

		if (mBroadPhaseCollider) {
			mBroadPhaseCollider->Render();
		}
	}

	bool PhysicsEntity::CheckCollision(PhysicsEntity* other) {
		if (IgnoreCollisions() || other->IgnoreCollisions()) {
			return false;
		}

		bool narrowPhaseCheck = false;

		if (mBroadPhaseCollider && other->mBroadPhaseCollider) {
			narrowPhaseCheck = ColliderVsColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
		}
		else {
			narrowPhaseCheck = true;
		}

		if (narrowPhaseCheck) {
			for (int i = 0; i < mColliders.size(); i++) {
				for (int j = 0; j < other->mColliders.size(); j++) {
					if (ColliderVsColliderCheck(mColliders[i], other->mColliders[j])) {
						//Collision!
						return true;
					}
				}
			}
		}
		return false;
	}

}