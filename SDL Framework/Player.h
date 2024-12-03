#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BoxCollider.h"
#include "Bullet.h"

using namespace SDLFramework;

class Player : public PhysicsEntity {
public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

	void WasHit();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);


	//inherited from PhysicsEntity
	bool IgnoreCollisions() override;
	void Hit(PhysicsEntity* other) override;

private:
	static const int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS];
	bool mWasHit;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	Texture* mIdleShip;
	Texture* mLeftShip;
	Texture* mRightShip;
	Texture* mCurrentShip;
	AnimatedTexture* mDeathAnimation;

	int mScore;
	int mLives;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
	void HandleFiring();
};