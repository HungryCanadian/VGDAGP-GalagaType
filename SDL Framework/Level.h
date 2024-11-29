#pragma once
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "BackgroundMeteors.h"
#include "Scoreboard.h"
#include "Player.h"

using namespace SDLFramework;

class Level : public GameEntity {
public:
	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();

	void Update();
	void Render();

	enum LevelStates {Running,Finished,GameOver};

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mBackgroundStars;
	BackgroundMeteors* mBackgroundMeteors;

	int mStage;
	bool mStageStarted;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	float mLabelTimer;

	void StartStage();

	Player* mPlayer;
};
