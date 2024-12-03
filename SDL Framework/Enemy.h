#pragma once
#include "AnimatedTexture.h"
#include "BezierPath.h"

class Enemy : public GameEntity {
public:
	enum States { FlyIn, InFormation, Diving, Dead };
	enum LevelStates { Running, Finished, GameOver };

	static void CreatePaths();
	Enemy(int path);
	virtual ~Enemy();

	States CurrentState();

	void Update();
	void Render();

protected:
	static std::vector<std::vector<Vector2>> sPaths;
	Timer* mTimer;
	Texture* mTexture;
	States mCurrentState;

	unsigned mCurrentPath;
	unsigned mCurrentWaypoint;

	const float EPSILON = 5.0f;
	float mSpeed;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState();
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDivingState();
	virtual void RenderDeadState();

	void RenderStates();
private:
	Enemy* mEnemy;
};