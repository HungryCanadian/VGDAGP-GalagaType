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
	mMeteors->Scroll(true);
	mPlanets->Scroll(false);
	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
	//mAudio->PlayMusic("GameStart.wav", 0);

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
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

bool PlayScreen::GameOver() {
	//This is essentially an if statement as a return on a single line
	//If mLevelStarts == false, return false. Otherwise we return true or false if the state == gameover
	return !mLevelStarted ? false : (mLevel->State() == Level::GameOver);
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
			//the level has started or is in session.
			mLevel->Update();

			if (mLevel->State() == Level::Finished) {
				mLevelStarted = false;
			}
		}

		if (mCurrentStage > 0) {
			mSideBar->Update();
		}
		mPlayer->Update();
	}
	else {
		if (!Mix_PlayingMusic()) {
			mGameStarted = true;
			
		}
	}
	
	
}

void PlayScreen::Render() { 
	mSideBar->Render();
	if (!mGameStarted) {
		mStartLabel->Render();
	}

	if (mGameStarted) {
		if (mLevelStarted) {
			mLevel->Render();
		}
		mPlayer->Render();
	}
}