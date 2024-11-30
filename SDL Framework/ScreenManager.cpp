#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}

	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mBackgroundStars = BackgroundStars::Instance();
	mInput = InputManager::Instance();
	//Screens
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {
	mInput = nullptr;

	BackgroundStars::Release();
	mBackgroundStars = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mPlayScreen;
	mPlayScreen = nullptr;
}

void ScreenManager::Update() {
	mBackgroundStars->Update();
	mBackgroundMeteors->Update();

	switch (mCurrentScreen) {
	case ScreenManager::Start:
		mBackgroundStars->Scroll(false);
		mBackgroundMeteors->Scroll(false);
		mStartScreen->Update();

		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
			//we want to switch from start screen to the play screen
			//Find a way to determine which choice the player is choosing to determine if 'hiscore is selected' (startscreen variable = mSelectedMode; write a getter to grab the selected mode)
			mCurrentScreen = Play;
			mStartScreen->ResetAnimation();
			mPlayScreen->StartNewGame();


		}
		break;

	case ScreenManager::Play:
		mPlayScreen->Update();

		if (mPlayScreen->GameOver()) {
			mCurrentScreen = Start;
		}

		break;
	case ScreenManager::HiScore:
		break;
	default:
		std::cerr << "Unknown Screen Found! please supply a valid Screen!\n";
		break;
	}
}

void ScreenManager::Render() {
	mBackgroundStars->Render();
	mBackgroundMeteors->Render();

	switch (mCurrentScreen) {
	case ScreenManager::Start:
		mStartScreen->Render();
		break;
	case ScreenManager::Play:
		mPlayScreen->Render();
		break;
	case ScreenManager::HiScore:
		break;
	}
}