#include "PlanetLayer.h"	

PlanetLayer::PlanetLayer(int layer) {
	for (int i = 0; i < PLANET_COUNT; i++) {
		mPlanet[i] = new Planet(layer);
	}
}

PlanetLayer::~PlanetLayer() {
	for (auto planet : mPlanet) {
		delete planet;
		planet = nullptr;
	}
}

void PlanetLayer::Update() {
	for (auto planet : mPlanet) {
		planet->Update();
	}
}

void PlanetLayer::Render() {
	for (auto planet : mPlanet) {
		planet->Render();
	}
}