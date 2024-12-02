#pragma once
#include "Texture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class Planet : public Texture {
public:
	static void Scroll(bool scroll);

	Planet(int layer);
	~Planet();

	void Update() override;
	void Render() override;
private:
	Timer* mTimer;
	Random* mRandom;

	static bool sScroll;
	float mScrollSpeed;

	bool mVisible;
	float mFlickerTime;
	float mFlickerSpeed;

	void ScrollPlanet();
};
