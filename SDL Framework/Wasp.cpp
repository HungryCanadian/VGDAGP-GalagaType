#include "Wasp.h"

std::vector<std::vector<Vector2>> Wasp::sDivePaths;

void Wasp::CreateDivePaths() {
	int currentPath = 0;
	BezierPath* path = new BezierPath();

	path->AddCurve({
		Vector2(Vec2_Zero),
		Vector2(0.0f, -45.0f),
		Vector2(-60.0f, -45.0f),
		Vector2(-60.0f, 0.0f)
		}, 15);
	path->AddCurve({
		Vector2(-60.0f, 0.0f),
		Vector2(-60.0f, 80.0f),
		Vector2(0.0f, 150.0f),
		Vector2(100.0f, 150.0f)
		}, 15);
	path->AddCurve({
		Vector2(100.0f, 150.0f),
		Vector2(250.0f, 150.0f),
		Vector2(350.0f, 200.0f),
		Vector2(350.0f, 350.0f)
		}, 15);
	path->AddCurve({
		Vector2(350.0f, 350.0f),
		Vector2(350.0f, 575.0f),
		Vector2(100.0f, 575.0f),
		Vector2(100.0f, 350.0f)
		}, 15);

	sDivePaths.push_back(std::vector<Vector2>());
	path->Sample(&sDivePaths[currentPath]);

	delete path;
	currentPath++;

    path = new BezierPath();

    path->AddCurve({
        Vector2(0.0f, 0.0f),
        Vector2(0.0f, -45.0f),
        Vector2(60.0f, -45.0f),
        Vector2(60.f, 0.0f) }, 15);
    path->AddCurve({
        Vector2(60.0f, 0.0f),
        Vector2(60.0f, 80.0f),
        Vector2(0.0f, 150.0f),
        Vector2(-100.0f, 150.0f) }, 15);
    path->AddCurve({
        Vector2(-100.0f, 150.0f),
        Vector2(-250.0f, 150.0f),
        Vector2(-350.0f, 200.0f),
        Vector2(-350.0f, 350.0f) }, 15);
    path->AddCurve({
        Vector2(-350.0f, 350.0f),
        Vector2(-350.0f, 575.0f),
        Vector2(-100.0f, 575.0f),
        Vector2(-100.0f, 350.0f) }, 15);

    sDivePaths.push_back(std::vector<Vector2>());
    path->Sample(&sDivePaths[currentPath]);
    delete path;

}

void Wasp::FlyInComplete() {
	if (mDiver == true) {
		mCurrentState = Dead;
	}
	else {
		JoinFormation();
	}
}

Vector2 Wasp::LocalFormationPosition() {
	Vector2 retVal;

	int dir = mIndex % 2 == 0 ? -1 : 1;

	retVal.x = (sFormation->GridSize().x + sFormation->GridSize().x * 2 * (mIndex / 4)) * (float)dir;
	retVal.y = sFormation->GridSize().y * 2 + sFormation->GridSize().y * ((mIndex % 4) / 2);

	return retVal;
}

void Wasp::HandleDiveState() {
	int currentPath = mIndex % 2;

	if (mCurrentWaypoint < sDivePaths[currentPath].size()) {
		//Follow Dive path
		Vector2 waypointPos = mDiveStartPosition + sDivePaths[currentPath][mCurrentWaypoint];
		Vector2 dist = waypointPos - getPosition();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if ((waypointPos - getPosition()).MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			mCurrentWaypoint++;
		}
	}
	else {
		//Return to formation
		Vector2 dist = WorldFormationPosition() - getPosition();

		Translate(dist.Normalized() * mSpeed * mTimer->DeltaTime(), World);
		Rotation(atan2(dist.y, dist.x) * RAD_TO_DEG + 90.0f);

		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25) {
			JoinFormation();
		}
	}
}

void Wasp::HandleDeadState() { }

void Wasp::RenderDeadState() { }

void Wasp::RenderDiveState() {
	mTexture->Render();

	//Debug Render of dive path
	int currentPath = mIndex % 2;

	for (int i = 0; i < sDivePaths[currentPath].size() - 1;) {
		Graphics::Instance()->DrawLine(
			mDiveStartPosition.x + sDivePaths[currentPath][i].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i].y,
			mDiveStartPosition.x + sDivePaths[currentPath][i + 1].x,
			mDiveStartPosition.y + sDivePaths[currentPath][i + 1].y
		);
	}

	//Debug Render of the return to formation path.
	Vector2 finalPos = WorldFormationPosition();
	Vector2 pathEndPos = mDiveStartPosition + sDivePaths[currentPath][sDivePaths[currentPath].size() - 1];

	Graphics::Instance()->DrawLine(
		pathEndPos.x,
		pathEndPos.y,
		finalPos.x,
		finalPos.y
		);
}

Wasp::Wasp(int path, int index, bool challenge, bool diver) : Enemy(path, index, challenge), mDiver(diver) {
	mTexture = new Texture("Animatedenemies.png", 0, 40, 52, 40);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);
	
	mType = Enemy::Wasp;
}

Wasp::~Wasp() {

}