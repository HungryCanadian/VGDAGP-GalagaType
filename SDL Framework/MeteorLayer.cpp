#include "MeteorLayer.h"	

MeteorLayer::MeteorLayer(int layer) {
	for (int i = 0; i < METEOR_COUNT; i++) {
		mMeteor[i] = new Meteor(layer);
		std::cerr << "Created Meteor for layer " << layer << ", Meteor " << i << ": " << mMeteor[i] << std::endl;
		if (mMeteor[i] == nullptr) {
			std::cerr << "Error: Failed to allocate memory for Meteor!" << std::endl;
		}
	}
}

MeteorLayer::~MeteorLayer() {
	for (auto meteor : mMeteor) {
		delete meteor;
		meteor = nullptr;
	}
}

void MeteorLayer::Update() {
	std::cerr << "Updating MeteorLayer!" << std::endl;
	for (auto meteor : mMeteor) {
		std::cerr << "Updating Meteor: " << meteor << std::endl;
		meteor->Update();
	}
}

void MeteorLayer::Render() {
	for (auto meteor : mMeteor) {
		meteor->Render();
	}
}