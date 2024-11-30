#include "Player.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT) || mInput->KeyDown(SDL_SCANCODE_D)) {
		Translate(Vec2_Right * mMoveSpeed * mTimer->DeltaTime(), World);
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT) || mInput->KeyDown(SDL_SCANCODE_A)) {
		Translate(Vec2_Left * mMoveSpeed * mTimer->DeltaTime(), World);
	}

	Vector2 pos = getPosition(Local);
	if (pos.x < mMoveBounds.x ) {
		pos.x = mMoveBounds.x;
	}
	else if (pos.x > mMoveBounds.y) {
		pos.x = mMoveBounds.y;
	}

	Position(pos);
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 1;

	mMoveSpeed = 100.0f;
	mMoveBounds = Vector2(0.0f, 800.0f);

	mShip = new Texture("player.png");
	mShip->Parent(this);
	mShip->Position(Vec2_Zero);
	mShip->Scale(Vector2(0.6f, 0.6f));

	mDeathAnimation = new AnimatedTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, AnimatedTexture::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(AnimatedTexture::Once);

	//PhysicsEntity Operations
	AddCollider(new BoxCollider(Vector2(16.0f, 47.0f)));
	AddCollider(new BoxCollider(Vector2(20.0f, 20.0f)), Vector2(18.0f, 5.0f));
	AddCollider(new BoxCollider(Vector2(20.0f, 20.0f)), Vector2(-18.0f, 5.0f));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);


}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mShip;
	mShip = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}
//TODO: Temporary Functionality. Hit() will be what Handles this.
void Player::WasHit() {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("PlayerExplosion.wav");
	
}

bool Player::IgnoreCollisions() {
	return !mVisible || mAnimating;
}

void Player::Hit(PhysicsEntity* other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mWasHit = true;
	//TODO: Add Audio to death
}

void Player::Update() {
	if (mAnimating == true) {
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (getActive()) {
			HandleMovement();
		}
	}
}

void Player::Render() {
	if (mVisible == true) {
		if (mAnimating == true) {
			mDeathAnimation->Render();
		}
		else {
			mShip->Render();

		}
		PhysicsEntity::Render();
	}
}