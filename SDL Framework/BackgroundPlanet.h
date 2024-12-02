#pragma once
#include "PlanetLayer.h"

class BackgroundPlanets {
public:
	static BackgroundPlanets* Instance();
	static void Release();

	void Scroll(bool scroll);

	void Update();
	void Render();

private:
	static BackgroundPlanets* sInstance;
	static const int LAYER_COUNT = 1;
	PlanetLayer* mPlanetLayers[LAYER_COUNT];

	BackgroundPlanets();
	~BackgroundPlanets();
};
