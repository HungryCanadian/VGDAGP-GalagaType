#include "StartScreen.h"

StartScreen::StartScreen() {
	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	//Screen Animation Variables
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = Vec2_Zero;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;



	//Top Bar
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 40.0f);
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 0,0,200 });
	mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200,0,0 });

	//Background Entities
	mAudioManager->PlayMusic("5. Dread March .mp3", -1);
	mBackground = new Texture("4.png");
	mBackground->Position(Graphics::SCREEN_HEIGHT * 0.5f, Graphics::SCREEN_WIDTH * 0.5f);

	//Top Bar Entities
	mTopBar->Parent(this);
	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);

	mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
	mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.3f, 0.0f);
	mHiScore->Position(-30.0f, 0.0f);

	mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
	mOnePlayer = new Texture("1 Player", "emulogic.ttf", 32, { 230, 230, 230 });
	mTwoPlayer = new Texture("2 Player", "emulogic.ttf", 32, { 230, 230, 230 });
	mCursor = new Texture("Anchor.png");

	//Logo Texture
	mLogoSpace = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.20f);
	//mLogo = new Texture("Caspiran", "ToThePoint.ttf", 152, { 0,0,200 });;
	//mLogo2 = new Texture("Galaga", "ToThePoint.ttf", 152, { 0,0,200 });;
	mAnimatedLogo = new AnimatedTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.4f, AnimatedTexture::Vertical);

	mLogoSpace->Parent(this);
	//mLogo->Parent(mLogoSpace);
	//mLogo2->Parent(mLogoSpace);
	mAnimatedLogo->Parent(mLogoSpace);

	//mLogo->Position(Vec2_Zero);
	//mLogo2->Position(0.0f, 125.0f);
	mAnimatedLogo->Position(0.0f, 65.0f);

	//Play Bar Entities
	mPlayModes->Parent(this);
	mOnePlayer->Parent(mPlayModes);
	mTwoPlayer->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	mOnePlayer->Position(0.0f, -35.0f);
	mTwoPlayer->Position(0.0f, 35.0f);
	mCursor->Position(-175.0f, -35.0f);

	mCursorStartPos = mCursor->getPosition(Local);
	mCursorOffSet = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities
	mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
	mNamco = new Texture("estate games", "namco__.ttf", 26, { 0,0,200 });
	mDates = new Texture("2024 Estate Games", "emulogic.ttf", 26, { 230,230,230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230,230,230 });



	mBottomBar->Parent(this);
	mNamco->Parent(mBottomBar);
	mDates->Parent(mBottomBar);
	mRights->Parent(mBottomBar);

	mNamco->Position(Vec2_Zero);
	mDates->Position(0.0f, 90.0f);
	mRights->Position(0.0f, 170.0f);


	Position(mAnimationStartPos);



}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;

	if (mSelectedMode < 0) {
		mSelectedMode = 1;
	}
	else if (mSelectedMode > 1) {
		mSelectedMode = 0;
	}

	mCursor->Position(mCursorStartPos + mCursorOffSet * (float)mSelectedMode);

}

void StartScreen::Update() {
	if (mAnimationDone == false) {
		mAnimationTimer += mTimer->DeltaTime();
		Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));


		if (mAnimationTimer >= mAnimationTotalTime) {
			mAnimationDone = true;
		}

		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN) ||
			mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
			mAnimationTimer = mAnimationTotalTime;
		}
	}
	else {
		mAnimatedLogo->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_DOWN)) {
			ChangeSelectedMode(1);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_UP)) {
			ChangeSelectedMode(-1);
		}
	}
}

void StartScreen::Render() {
	//Background Entities
	mBackground->Render();

	//Top Bar Entities
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	//Play bar Entities
	mOnePlayer->Render();
	mTwoPlayer->Render();
	mCursor->Render();
	//Bottom Bar Entities
	mNamco->Render();
	mDates->Render();
	mRights->Render();
	//Logo Entities
	//mLogo->Render();
	//mLogo2->Render();
	mAnimatedLogo->Render();
}

StartScreen::~StartScreen() {
	//Background Entities
	delete mBackground;
	mBackground = nullptr;


	//This is our TopBar Entities
	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHiScore;
	mHiScore = nullptr;

	//Play Bar Entities
	delete mPlayModes;
	mPlayModes = nullptr;
	delete mOnePlayer;
	mOnePlayer = nullptr;
	delete mTwoPlayer;
	mTwoPlayer = nullptr;
	delete mCursor;
	mCursor = nullptr;

	//Bottom Bar Entities
	delete mBottomBar;
	mBottomBar = nullptr;
	delete mNamco;
	mBottomBar = nullptr;
	delete mDates;
	mBottomBar = nullptr;
	delete mRights;
	mBottomBar = nullptr;

	//Logo Entities
	//delete mLogo;
	//mLogo = nullptr;
	//delete mLogo2;
	//mLogo2 = nullptr;
	delete mLogoSpace;
	mLogoSpace = nullptr;
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;


	mTimer = nullptr;
	mInputManager = nullptr;
	mAudioManager = nullptr;
}
