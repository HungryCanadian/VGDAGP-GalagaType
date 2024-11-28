#pragma once
#include "Level.h"

using namespace SDLFramework;

class PlayScreen : public GameEntity {
public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	void StartNextLevel();

	void Update() override;
	void Render() override;	

private:
	Timer* mTimer;
	AudioManager* mAudio;
	
	PlaySideBar* mSideBar;
	BackgroundStars* mStars;

	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;
};