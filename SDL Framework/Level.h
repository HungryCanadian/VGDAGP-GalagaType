#pragma once
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "BackgroundMeteors.h"
#include "BackgroundPlanet.h"
#include "Player.h"
#include "Butterfly.h"
#include "Wasp.h"
#include "Boss.h"
#include "tinyxml2.h"

using namespace SDLFramework;
using namespace tinyxml2;

class Level : public GameEntity {
public:
	enum LevelStates { Running, Finished, GameOver };

	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	LevelStates State();

	void Update();
	void Render();

	

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mBackgroundStars;
	BackgroundMeteors* mBackgroundMeteors;
	BackgroundPlanets* mBackgroundPlanets;

	Player* mPlayer;
	Formation* mFormation;

	static const int MAX_BUTTERFLIES = 16;
	static const int MAX_WASPS = 20;
	static const int MAX_BOSSES = 4;
	
	int mButterflyCount;
	int mWaspCount;
	int mBossCount;
	
	Butterfly* mFormationButterflies[MAX_BUTTERFLIES];
	Wasp* mFormationWasps[MAX_WASPS];
	Boss* mFormationBosses[MAX_BOSSES];

	std::vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	float mSpawnDelay;
	float mSpawnTimer;

	bool mSpawningFinished;

	int mStage;
	bool mChallengeStage;
	bool mStageStarted;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();

	void StartStage();

	bool EnemyFlyingIn();
	
	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();
};
