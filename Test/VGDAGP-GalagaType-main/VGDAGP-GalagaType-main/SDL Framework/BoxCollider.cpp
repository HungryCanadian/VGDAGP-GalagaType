#include "BoxCollider.h"

namespace SDLFramework {
	BoxCollider::BoxCollider(Vector2 size) : Collider(ColliderType::Box) {
		AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
		AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
		AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
		AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));

		if (DEBUG_COLLIDERS == true) {
			SetDebugTexture(new Texture("BoxCollider.png"));
			mDebugTexture->Scale(size);
		}
	}

	BoxCollider::~BoxCollider() {
		for (auto v : mVerts) {
			delete v;
			v = nullptr;
		}
	}

	Vector2 BoxCollider::GetFurthestPoint() {
		Vector2 localPos = getPosition(GameEntity::Local);

		int furthestIndex = 0;
		float dist = (localPos + mVerts[0]->getPosition(GameEntity::Local)).Magnitude();
		float otherDist = 0.0f;

		for (int i = 0; i < MAX_VERTS; i++) {
			otherDist = (localPos + mVerts[i]->getPosition(GameEntity::Local)).Magnitude(); // if this doesnt behave properly use MagnitudeSqr
			if (otherDist > dist) {
				furthestIndex = i;
				dist = otherDist;
			}
		}
		return localPos + mVerts[furthestIndex]->getPosition(GameEntity::Local);
	}

	Vector2 BoxCollider::getVertexPos(int index) {
		return mVerts[index]->getPosition();
	}

	void BoxCollider::AddVert(int index, Vector2 pos) {
		mVerts[index] = new GameEntity(pos);
		mVerts[index]->Parent(this);
	}
}