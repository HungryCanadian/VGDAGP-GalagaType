#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Bullet::IgnoreCollisions() {
	return !getActive();
}

Bullet::Bullet(bool friendly) {
	mTimer = Timer::Instance();

	if (friendly == true) {
		mTexture = new Texture("laserGreen.png");
	}
	else if (friendly == false) {
		mTexture = new Texture("laserRed.png");
	}
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mSpeed = 500.0f;

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaledDimensions()));

	if (friendly == true) {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::FriendlyProjectile);
	}
	else {
		mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::HostileProjectile);
	}
 }

Bullet::~Bullet() {
	delete mTexture;
	mTexture = nullptr;

	mTimer = nullptr;
}

void Bullet::Fire(Vector2 pos) {
	Position(pos);
	Active(true);
}

void Bullet::Reload() {
	Active(false);
}

void Bullet::Hit(PhysicsEntity* other) {
	Reload();
}

void Bullet::Update() {
	if (getActive()) {
		Translate(Vec2_Down * mSpeed * mTimer->DeltaTime());

		Vector2 pos = getPosition();
		if (pos.y < -OFFSCREEN_BUFFER) {
			Reload();
		}
	}
}

void Bullet::Render() {
	if (getActive()) {
		mTexture->Render();
		PhysicsEntity::Render();
	}
}

