#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {
public:
	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;

private:
	Timer* mTimer;
	InputManager* mInputManager;

	//Background Entities
	Texture* mBackground;

	//Top Bar Entities
	//Empty game Object/Entity
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;

	//Logo Entities
	GameEntity* mLogoSpace;
	Texture* mLogo;
	Texture* mLogo2;
	AnimatedTexture* mAnimatedLogo;

	//Play Mode
	GameEntity* mPlayModes;
	Texture* mOnePlayer;
	Texture* mTwoPlayer;
	Texture* mCursor;
	//TODO: Texture* mHiScoreList; Make a screen to display previous high scores and a three Char name to show who it belongs to

	//Bottom Bar
	GameEntity* mBottomBar;
	Texture* mNamco;
	Texture* mDates;
	Texture* mRights;

};