#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;

void Enemy::CreatePaths() {
	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();
	path->AddCurve({ Vector2(500.0f,10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 310.0f), Vector2(500.0f, 300.0f) }, 1);

	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

void Enemy::HandleFlyInState() {
	if ((sPaths[mCurrentPath][mCurrentWaypoint] - getPosition()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
		mCurrentWaypoint++;
	}
	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - getPosition();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
	}
	else {
		mCurrentState = InFormation;
	}
}

void Enemy::HandleFormationState() {}

void Enemy::HandleDiveState() {}

void Enemy::HandleDeadState() {}

void Enemy::HandleStates() {
	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case InFormation:
		HandleFormationState();
		break;
	case Diving:
		HandleDiveState();
		break;
	case Dead:
		HandleDeadState();
		break;

	}
}

void Enemy::RenderFlyInState() {
	mTexture->Render();
}

void Enemy::RenderFormationState() {
	mTexture->Render();
}

void Enemy::RenderDivingState() {}

void Enemy::RenderDeadState() {}

void Enemy::RenderStates() {
	switch (mCurrentState) {
	case FlyIn:
		RenderFlyInState();
		break;
	case InFormation:
		RenderFormationState();
		break;
	case Diving:
		RenderDivingState();
		break;
	case Dead:
		RenderDeadState();
		break;

	}
}

Enemy::Enemy(int path) : mCurrentPath(path) {
	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWaypoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mTexture = new Texture("AnimatedEnemies.png", 0, 0, 52, 40);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	mSpeed = 100.0f;
}

Enemy::~Enemy() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

void Enemy::Update() {
	if (getActive()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (getActive()) {
		mTexture->Render();
	}
}

