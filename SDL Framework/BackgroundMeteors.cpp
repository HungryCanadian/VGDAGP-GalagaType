#include "BackgroundMeteors.h"

BackgroundMeteors* BackgroundMeteors::sInstance = nullptr;

BackgroundMeteors* BackgroundMeteors::Instance() {
	if (sInstance == nullptr) {
		std::cerr << "before Creating BackgroundMeteors instance!" << std::endl;
		sInstance = new BackgroundMeteors();
		std::cerr << "after Creating BackgroundMeteors instance!" << std::endl;
	}
	return sInstance;
}

BackgroundMeteors::BackgroundMeteors() {
	for (int i = 0; i < LAYER_COUNT; i++) {
		mMeteorLayers[i] = new MeteorLayer(i + 1);
		std::cerr << "Attempting to add [" << i << "] as MeteorLayer!" << std::endl;
		if (mMeteorLayers[i] == nullptr) {
			std::cerr << "Error: mLayers[" << i << "] is nullptr!" << std::endl;
		}
		else {
			std::cerr << "Successfully added mMeteorLayers[" << i << "]!" << std::endl;
		}
	}
}


void BackgroundMeteors::Release() {
	std::cerr << "BackgroundMeteors Release called!" << std::endl;
	delete sInstance;
	sInstance = nullptr;
}

void BackgroundMeteors::Scroll(bool scroll) {
	Meteor::Scroll(scroll);
}

void BackgroundMeteors::Update() {
	if (mMeteorLayers != nullptr) {
		std::cerr << "mMeteorLayers address: " << mMeteorLayers << std::endl;
		for (auto layer : mMeteorLayers) {
			layer->Update();
		}
	}
	else {
		std::cerr << "Can't Update Meteor: mMeteorLayers is nullptr!\n";
	}
}

void BackgroundMeteors::Render() {
	if (mMeteorLayers != nullptr) {
		for (auto layer : mMeteorLayers) {
			layer->Render();
		}
		
	}
	else { std::cerr << "Can't Render Meteor\n"; }

}

BackgroundMeteors::~BackgroundMeteors() {
	std::cerr << "BackgroundMeteors destructor called!" << std::endl;
	for (int i = 0; i < LAYER_COUNT; i++) {
		delete mMeteorLayers[i];
		mMeteorLayers[i] = nullptr;
	}
}