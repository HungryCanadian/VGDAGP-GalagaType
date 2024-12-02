#include "BackgroundPlanet.h"

BackgroundPlanets* BackgroundPlanets::sInstance = nullptr;

BackgroundPlanets* BackgroundPlanets::Instance() {
	if (sInstance == nullptr) {
		sInstance = new BackgroundPlanets();
	}
	return sInstance;
}

BackgroundPlanets::BackgroundPlanets() {
	for (int i = 0; i < LAYER_COUNT; i++) {
		mPlanetLayers[i] = new PlanetLayer(i + 1);
	}
}


void BackgroundPlanets::Release() {

	delete sInstance;
	sInstance = nullptr;
}

void BackgroundPlanets::Scroll(bool scroll) {
	Planet::Scroll(scroll);
}

void BackgroundPlanets::Update() {
		for (auto layer : mPlanetLayers) {
			layer->Update();
		}


}

void BackgroundPlanets::Render() {
		for (auto layer : mPlanetLayers) {
			layer->Render();
		}

}

BackgroundPlanets::~BackgroundPlanets() {
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mPlanetLayers[i];
		mPlanetLayers[i] = nullptr;
	}
}