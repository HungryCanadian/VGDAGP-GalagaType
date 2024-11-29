#pragma once
#include "Texture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class Meteor : public Texture {
public:
	static void Scroll(bool scroll);

	Meteor(int layer);
	~Meteor();

	void Update() override;
	void Render() override;
private:
	Timer* mTimer;
	Random* mRandom;

	static bool sScroll;
	float mScrollSpeed;

	bool mVisible;

	void ScrollMeteor();
};
