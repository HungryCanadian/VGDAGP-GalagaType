#pragma once
#include "PhysicsEntity.h"
#include "Timer.h"

using namespace SDLFramework;

class Bullet : public PhysicsEntity {
public:
	Bullet(bool friendly);
	~Bullet();

	void Update() override;
	void Render() override;

	void Hit(PhysicsEntity* other) override;

	void Fire(Vector2 pos);
	void Reload();

private:
	static const int OFFSCREEN_BUFFER = 10;
	Timer* mTimer;
	Texture* mTexture;
	float mSpeed;

	bool IgnoreCollisions() override;

};
