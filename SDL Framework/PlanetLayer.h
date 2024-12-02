#pragma once
#include "Planet.h"

class PlanetLayer {
public:
	PlanetLayer(int layer);
	~PlanetLayer();

	void Update();
	void Render();

private:
	static const int PLANET_COUNT = 1;
	Planet* mPlanet[PLANET_COUNT];
};
