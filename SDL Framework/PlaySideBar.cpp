#include "PlaySideBar.h"


PlaySideBar::PlaySideBar() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("Panel.png");
	mBackground->Parent(this);
	mBackground->Scale(Vector2(0.65f, 1.05f));
	mBackground->Position(10.0f, 400.0f);
	//High Score
	mHighLabel = new Texture("HIGHSCORE", "Stargazer.ttf", 32, { 150,0,0 });
	mHighLabel->Parent(this);
	mHighLabel->Position(15.0f, 10.0f);

	mScoreLabel = new Texture("Score", "Stargazer.ttf", 32, { 150,0,0 });
	mScoreLabel->Parent(this);
	mScoreLabel->Position(50.0f, 150.0f);

	mHighScorePanel = new Texture("Button.png");
	mHighScorePanel->Parent(this);
	mHighScorePanel->Position(10.0f, 32.0f);
	mHighScorePanel->Scale(Vector2(2.0f, 2.0f));

	mHighScoreBoard = new Scoreboard();
	mHighScoreBoard->Parent(this);
	mHighScoreBoard->Position(90.0f, 45.0f);

	//One up
	mOneUpLabel = new Texture("1UP", "emulogic.ttf", 18, { 150,0,0 });
	mOneUpLabel->Parent(this);
	mOneUpLabel->Position(-45.0f, 145.0f);

	mBlinkTimer = 0.0f;
	mBlinkInterval = 0.5f;
	mOneUpLabelVisible = true; //TODO: Set to False when submitting

	mPlayerOneScore = new Scoreboard();
	mPlayerOneScore->Parent(this);
	mPlayerOneScore->Position(90.0f, 192.0f);
	
	mPlayerScorePanel = new Texture("PanelEmpty.png");
	mPlayerScorePanel->Parent(this);
	mPlayerScorePanel->Position(15.0f, 192.0f);
	mPlayerScorePanel->Scale(Vector2(2.4f, 1.45f));



	//Ships Lives (displaying the ships in connection with player lives)
	mLivesPanel = new Texture("PanelRed.png");
	mLivesPanel->Parent(this);
	mLivesPanel->Position(15.0f, 420.0f);
	mLivesPanel->Scale(Vector2(2.45f, 2.0f));
	mLivesLabel = new Texture("Lives", "Stargazer.ttf", 32, { 150,0,0 });
	mLivesLabel->Parent(this);
	mLivesLabel->Position(-15.0f, 370.0f);
	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Position(-65.0f, 420.0f);

	for (int i = 0; i < MAX_SHIP_TEXTURES; i++) {
		mShipTextures[i] = new Texture("Life.png", 0, 0, 35, 27);
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Position(40.0f * (i % 10), 25.0f * (i / 5));

	}

	mTotalShipsLabel = new Scoreboard();
	mTotalShipsLabel->Parent(mShips);
	mTotalShipsLabel->Position(140.0f, 80.0f);

	//Level Flags
	mFlags = new GameEntity();
	mFlags->Parent(this);
	mFlags->Position(-50.0f, 600.0f);

	mFlagTimer = 0.0f;
	mFlagInterval = 0.25f;

}

PlaySideBar::~PlaySideBar() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mBackground;
	mBackground = nullptr;

	delete mHighLabel;
	mHighLabel = nullptr;

	delete mScoreLabel;
	mScoreLabel = nullptr;
	
	delete mLivesLabel;
	mLivesLabel = nullptr;

	delete mHighScoreBoard;
	mHighScoreBoard = nullptr;

	delete mOneUpLabel;
	mOneUpLabel = nullptr;

	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;

	delete mShips;
	mShips = nullptr;

	delete mTotalShipsLabel;
	mTotalShipsLabel = nullptr;

	for (auto texture : mShipTextures) {
		delete texture;
		texture = nullptr;
	}

	delete mFlags;
	mFlags = nullptr;

	ClearFlags();

}

void PlaySideBar::ClearFlags() {
	for (int i = 0; i < mFlagTextures.size(); i++) {
		delete mFlagTextures[i];
		mFlagTextures[i] = nullptr;
	}

	mFlagTextures.clear();
}

void PlaySideBar::AddNextFlag() {
	if (mRemainingLevels >= 50) {
		AddFlag("LevelFlags.png", 62, 50);
	}
	else if (mRemainingLevels >= 30) {
		AddFlag("LevelFlags.png", 62, 30);
	}
	else if (mRemainingLevels >= 20) {
		AddFlag("LevelFlags.png", 62, 20);
	}
	else if (mRemainingLevels >= 10) {
		AddFlag("LevelFlags.png", 54, 10);
	}
	else if (mRemainingLevels >= 5) {
		AddFlag("LevelFlags.png", 30, 5);
	}
	else {
		AddFlag("LevelFlags.png", 30, 1);
	}
}

void PlaySideBar::AddFlag(std::string filename, float width, int value) {
	int index = (int)mFlagTextures.size();

	if (index > 0) {
		mFlagXOffset += width * 0.5f;
	}

	if (mFlagXOffset > 140) {
		mFlagYOffset += 66;
		mFlagXOffset = 0;
	}

	mRemainingLevels -= value;
	//The x position of the flag we want to cut from the texture
	int x = 0;

	switch (value) {
	case 50:
		x = 228;
		break;
	case 30:
		x = 168;
		break;
	case 20:
		x = 108;
		break;
	case 10:
		x = 56;
		break;
	case 5:
		x = 28;
		break;

	}

	mFlagTextures.push_back(new Texture(filename, x, 0, width - 2, 64));
	mFlagTextures[index]->Parent(mFlags);
	mFlagTextures[index]->Position(mFlagXOffset, mFlagYOffset);
	mFlagXOffset += width * 0.5f;

	mAudio->PlaySFX("FlagSound.wav", 0, -1);
}

void PlaySideBar::SetShips(int ships) {
	mTotalShips = ships;

	if (ships > MAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Score(ships);
	}
}

void PlaySideBar::SetHighScore(int score) {
	mHighScoreBoard->Score(score);
}

void PlaySideBar::SetPlayerScore(int score) {
	mPlayerOneScore->Score(score);
}

void PlaySideBar::SetLevel(int level) {
	ClearFlags();

	mRemainingLevels = level;
	mFlagXOffset = 0.0f;
}

void PlaySideBar::Update() { 
	mBlinkTimer += mTimer->DeltaTime();

	if (mBlinkTimer >= mBlinkInterval) {
		mOneUpLabelVisible = !mOneUpLabelVisible;
		mBlinkTimer = 0.0f;
	}

	if (mRemainingLevels > 0) {
		mFlagTimer += mTimer->DeltaTime();

		if (mFlagTimer >= mFlagInterval) {
			AddNextFlag();
			mFlagTimer = 0.0f;
		}
	}
}

void PlaySideBar::Render() {
	mBackground->Render();
	mHighScorePanel->Render();
	mLivesPanel->Render();
	mLivesLabel->Render();
	mPlayerScorePanel->Render();

	mHighLabel->Render();
	mScoreLabel->Render();
	mHighScoreBoard->Render();

	if (mOneUpLabelVisible == true) {
		mOneUpLabel->Render();
	}
	mPlayerOneScore->Render();

	for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; i++) {
		mShipTextures[i]->Render();
	}

	if (mTotalShips > MAX_SHIP_TEXTURES) {
		mTotalShipsLabel->Render();
	}

	for (auto flag : mFlagTextures) {
		flag->Render();
	}
}