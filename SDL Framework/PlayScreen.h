#pragma once
#include "BackgroundStars.h"
#include "PlaySideBar.h"

using namespace SDLFramework;

class PlayScreen : public GameEntity {
public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;	

private:
	Timer* mTimer;
	AudioManager* mAudio;
	
	PlaySideBar* mSideBar;
	BackgroundStars* mStars;
};