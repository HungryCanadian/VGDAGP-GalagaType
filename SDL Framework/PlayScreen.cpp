#include "PlayScreen.h"


PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mStars = BackgroundStars::Instance();
	mMeteors = BackgroundMeteors::Instance();

	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);

	mStartLabel = new Texture("Start", "emulogic.ttf", 32, { 150,0,0 });
	mStartLabel->Parent(this);
	mStartLabel->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);

	mLevel = nullptr;
	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = nullptr;

}

PlayScreen::~PlayScreen() {
	mTimer = nullptr;
	mAudio = nullptr;

	mStars = nullptr;
	mMeteors = nullptr;
	

	delete mSideBar;
	mSideBar = nullptr;

	delete mStartLabel;
	mStartLabel = nullptr;

	delete mLevel;
	mLevel = nullptr;

	delete mPlayer;
	mPlayer = nullptr;
}

void PlayScreen::StartNewGame() {
	mSideBar->SetHighScore(3080);
	mStars->Scroll(false);
	mMeteors->Scroll(false);
	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
	mAudio->PlayMusic("GameStart.wav", 0);

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f);
	mPlayer->Active(false);

	mSideBar->SetPlayerScore(mPlayer->Score());
	mSideBar->SetShips(mPlayer->Lives());
	mSideBar->SetLevel(0);


}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);
}

void PlayScreen::Update() { 
	if (mGameStarted) {
		if (!mLevelStarted) {
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay) {
				StartNextLevel();
			}
		}
		else {
			mLevel->Update();
		}
		if (mCurrentStage > 0) {
			mSideBar->Update();
		}
	}
	else {
		if (!Mix_PlayingMusic()) {
			mGameStarted = true;
			
		}
	}
	mPlayer->Update();
	
}

void PlayScreen::Render() { 
	mSideBar->Render();
	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted && mLevelStarted) {
		mLevel->Render();
	}
	mPlayer->Render();
}