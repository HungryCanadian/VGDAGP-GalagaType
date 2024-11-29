#include "BackgroundMeteors.h"

BackgroundMeteors* BackgroundMeteors::sInstance = nullptr;

BackgroundMeteors* BackgroundMeteors::Instance() {
	if (sInstance == nullptr) {
		sInstance = new BackgroundMeteors();
	}
	return sInstance;
}

BackgroundMeteors::BackgroundMeteors() {
	for (int i = 0; i < LAYER_COUNT; i++) {
		mMeteorLayers[i] = new MeteorLayer(i + 1);
		if (mMeteorLayers[i] == nullptr) {
			std::cerr << "Error: mLayers[" << i << "] is nullptr!" << std::endl;
		}
	}
}

void BackgroundMeteors::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void BackgroundMeteors::Scroll(bool scroll) {
	Meteor::Scroll(scroll);
}

void BackgroundMeteors::Update() {
	if (mMeteorLayers != nullptr) {
		for (auto layer : mMeteorLayers) {
			layer->Update();
		}
		
	}
	else {
		std::cerr << "Can't Update Meteor's\n";
	}
}

void BackgroundMeteors::Render() {
	if (mMeteorLayers != nullptr) {
		for (auto layer : mMeteorLayers) {
			layer->Render();
		}
		
	}
	else { std::cerr << "Can't Render Meteor's\n"; }

}

BackgroundMeteors::~BackgroundMeteors() {
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mMeteorLayers[i];
		mMeteorLayers[i] = nullptr;
	}
}