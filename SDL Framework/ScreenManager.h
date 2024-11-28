#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"
#include "BackgroundStars.h"

class ScreenManager {
public:
	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:
	ScreenManager();
	~ScreenManager();

	enum Screens {Start, Play, HiScore};
	Screens mCurrentScreen;

	static ScreenManager* sInstance;

	BackgroundStars* mBackgroundStars;
	InputManager* mInput;

	//Screens
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;
};