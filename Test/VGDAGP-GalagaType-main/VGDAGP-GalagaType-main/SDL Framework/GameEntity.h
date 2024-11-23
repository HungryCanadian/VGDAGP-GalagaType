#pragma once
#include "MathHelper.h"

namespace SDLFramework {

	class GameEntity {
	public:
		enum Space { Local = 0, World};

		GameEntity(float x = 0.0f, float y = 0.0f);
		GameEntity(const Vector2& pos);
		~GameEntity();

		void Position(float x, float y);
		void Position(const Vector2& pos);
		Vector2 getPosition(Space space = World);

		void Rotation(float rot);
		float getRotation(Space space = World);

		void Scale(Vector2 scale);
		Vector2 getScale(Space space = World);

		void Active(bool active);
		bool getActive();

		void Parent(GameEntity* parent);
		GameEntity* getParent();

		void Translate(Vector2 vec, Space space = Local);
		void Rotate(float amount);

		virtual void Update() {};
		virtual void Render() {};

	private:
		Vector2 mPosition;
		float mRotation;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	};
}
