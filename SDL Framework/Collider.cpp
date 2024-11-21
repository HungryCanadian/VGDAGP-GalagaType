#include "Collider.h"

namespace SDLFramework {

	Collider::Collider(ColliderType type) : mType(type) {
		mDebugTexture = nullptr;
	}

	Collider::~Collider() {
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}

	void Collider::Render() {
		if (DEBUG_COLLIDERS == true) {
			mDebugTexture->Render();
		}
	}

	Collider::ColliderType Collider::getType() {
		return mType;
	}

	void Collider::SetDebugTexture(Texture* texture) {
		delete mDebugTexture;
		mDebugTexture = texture;
		mDebugTexture->Parent(this);
	}
}