#include "MeteorLayer.h"	

MeteorLayer::MeteorLayer(int layer) {
	for (int i = 0; i < METEOR_COUNT; i++) {
		mMeteor[i] = new Meteor(layer);
	}
}

MeteorLayer::~MeteorLayer() {
	for (auto meteor : mMeteor) {
		delete meteor;
		meteor = nullptr;
	}
}

void MeteorLayer::Update() {
	for (auto meteor : mMeteor) {
		meteor->Update();
	}
}

void MeteorLayer::Render() {
	for (auto meteor : mMeteor) {
		meteor->Render();
	}
}