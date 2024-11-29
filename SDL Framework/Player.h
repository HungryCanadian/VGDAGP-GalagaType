#pragma once
#include "PhysicsEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "BoxCollider.h"

using namespace SDLFramework;

class Player : public PhysicsEntity {
public:
	Player();
	~Player();

	void Update() override;
	void Render() override;

	bool WasHit();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);


	//inherited from PhysicsEntity
	bool IgnoreCollisions() override;
	void Hit(PhysicsEntity* other) override;

private:
	bool mWasHit;

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	Texture* mShip;
	AnimatedTexture* mDeathAnimation;

	int mScore;
	int mLives;

	float mMoveSpeed;
	Vector2 mMoveBounds;

	void HandleMovement();
};