#include "Enemy.h"

std::vector<std::vector<Vector2>> Enemy::sPaths;
Player* Enemy::sPlayer = nullptr;
Formation* Enemy::sFormation = nullptr;

void Enemy::CreatePaths() {
	int screenMidPoint = (int)(Graphics::Instance()->SCREEN_WIDTH * 0.4f);

	int currentPath = 0;
	BezierPath* path = new BezierPath();
	//path->AddCurve({ Vector2(500.0f,10.0f), Vector2(500.0f, 0.0f), Vector2(500.0f, 310.0f), Vector2(500.0f, 300.0f) }, 1);
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, -10.0f),
		Vector2(screenMidPoint + 50.0f, -20.0f),
		Vector2(screenMidPoint + 50.0f, 30.0f),
		Vector2(screenMidPoint + 50.0f, 20.0f) },
		1);
	path->AddCurve({
		Vector2(screenMidPoint + 50.0f, 20.0f),
		Vector2(screenMidPoint + 50.0f, 100.0f),
		Vector2(75.0f, 325.0f),
		Vector2(75.0f, 425.0f) }, 25);
	path->AddCurve({
		Vector2(75.0f, 425.0f),
		Vector2(75.0f, 650.0f),
		Vector2(350.0f, 650.0f),
		Vector2(350.0f, 425.0f)
		}, 25);
	sPaths.push_back(std::vector<Vector2>());
	path->Sample(&sPaths[currentPath]);
	delete path;
}

void Enemy::SetFormation(Formation* formation) {
	sFormation = formation;
}

Vector2 Enemy::WorldFormationPosition() {
	return sFormation->getPosition() + LocalFormationPosition();
}

void Enemy::FlyInComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;
	}
	else {
		JoinFormation();
	}
}

void Enemy::JoinFormation() {
	Position(WorldFormationPosition());
	Rotation(0);
	Parent(sFormation);
	mCurrentState = InFormation;
}

void Enemy::PathComplete() {
	if (mChallengeStage) {
		mCurrentState = Dead;
	}
}

Enemy::Types Enemy::Type() {
	return mType;
}

int Enemy::Index() {
	return mIndex;
}

void Enemy::HandleFlyInState() {
	if (mCurrentWaypoint < sPaths[mCurrentPath].size()) {
		Vector2 dist = sPaths[mCurrentPath][mCurrentWaypoint] - getPosition();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f); //This was Rotate instead of Rotation (if beyblade mode still exists this wasnt it)

		if ((sPaths[mCurrentPath][mCurrentWaypoint] - getPosition()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			mCurrentWaypoint++;
		}

		if (mCurrentWaypoint >= sPaths[mCurrentPath].size()) {
			//we have reached the end of our flyin path.
			PathComplete();
		}
	}
	else {
		Vector2 dist = WorldFormationPosition() - getPosition();
		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			FlyInComplete();
		}
	}
}

void Enemy::HandleInFormationState() {
	Position(LocalFormationPosition());
}


void Enemy::HandleStates() {
	switch (mCurrentState) {
	case FlyIn:
		HandleFlyInState();
		break;
	case InFormation:
		HandleInFormationState();
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

	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(
			sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}
}

void Enemy::RenderInFormationState() {
	mTexture->Render();

	for (int i = 0; i < sPaths[mCurrentPath].size() - 1; i++) {
		Graphics::Instance()->DrawLine(
			sPaths[mCurrentPath][i].x,
			sPaths[mCurrentPath][i].y,
			sPaths[mCurrentPath][i + 1].x,
			sPaths[mCurrentPath][i + 1].y
		);
	}
}

void Enemy::RenderStates() {
	switch (mCurrentState) {
	case FlyIn:
		RenderFlyInState();
		break;
	case InFormation:
		RenderInFormationState();
		break;
	case Diving:
		RenderDiveState();
		break;
	case Dead:
		RenderDeadState();
		break;

	}
}

Enemy::Enemy(int path, int index, bool challenge) : mCurrentPath(path), mIndex(index), mChallengeStage(challenge) {
	mTimer = Timer::Instance();

	mCurrentState = FlyIn;

	mCurrentWaypoint = 1;
	Position(sPaths[mCurrentPath][0]);

	mTexture = nullptr;

	mSpeed = 450.0f;
}

Enemy::~Enemy() {
	mTimer = nullptr;

	delete mTexture;
	mTexture = nullptr;
}

Enemy::States Enemy::CurrentState() {
	return mCurrentState;
}

void Enemy::Dive(int type) {
	Parent(nullptr);
	mCurrentState = Diving;
	mDiveStartPosition = getPosition();
	mCurrentWaypoint = 1;
}

void Enemy::Update() {
	if (getActive()) {
		HandleStates();
	}
}

void Enemy::Render() {
	if (getActive()) {
		RenderStates();
	}
}

