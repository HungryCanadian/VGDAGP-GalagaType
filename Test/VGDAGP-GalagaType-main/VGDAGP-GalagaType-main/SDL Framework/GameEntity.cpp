#include "GameEntity.h"

namespace SDLFramework {

	GameEntity::GameEntity(float x, float y)
		: mPosition(x, y), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {

	}

	GameEntity::GameEntity(const Vector2& pos) 
		: mPosition(pos), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {

	}

	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPosition = Vector2(x, y);
	}

	void GameEntity::Position(const Vector2& pos) {
		mPosition = pos;
	}

	Vector2 GameEntity::getPosition(Space space) {
		if (space == Local || mParent == nullptr) {
			return mPosition;
		}

		Vector2 parentScale = mParent->getScale(World);
		Vector2 rotPosition = RotateVector(mPosition, mParent->getRotation(Local));

		return mParent->getPosition(World) + Vector2(rotPosition.x * parentScale.x, rotPosition.y * parentScale.y);
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;

		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}

		while (mRotation, 0.0f) {
			mRotation += 360.0f;
		}
	}

	float GameEntity::getRotation(Space space) {
		if (space == Local || mParent == nullptr) {
			return mRotation;
		}

		return mParent->getRotation(World) + mRotation;

	}

	void GameEntity::Scale(Vector2 scale) {
		mScale = scale;
	}

	Vector2 GameEntity::getScale(Space space) {
		if (space == Local || mParent == nullptr) {
			return mScale;
		}

		Vector2 scale = mParent->getScale(World);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}

	bool GameEntity::getActive() {
		return mActive;
	}

	void GameEntity::Parent(GameEntity* parent) {
		if (parent == nullptr) {
			mPosition = getPosition(World);
			mRotation = getRotation(World);
			mScale = getScale(World);
		}
		else {
			if (mParent != nullptr) {
				//if we are already a child of something
				Parent(nullptr);
			}

			//at this point, we have an object we want to attach to AND
			//we have unattached from our previous object.

			Vector2 parentScale = parent->getScale(World);

			mPosition = RotateVector(getPosition(World) - parent->getPosition(World), -parent->getRotation(World));
			mPosition.x /= parentScale.x;
			mPosition.y /= parentScale.y;

			mRotation -= parent->getRotation(World);
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);

		}

		mParent = parent;
	}

	GameEntity* GameEntity::getParent() {
		return mParent;
	}

	void GameEntity::Translate(Vector2 vec, Space space) {
		if (space == World) {
			mPosition += vec;
		}
		else {
			mPosition += RotateVector(vec, getRotation());
		}
	}

	void GameEntity::Rotate(float amount) {
		mRotation += amount;
	}
}