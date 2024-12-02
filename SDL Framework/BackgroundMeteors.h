#pragma once
#include "MeteorLayer.h"

class BackgroundMeteors {
public:
	static BackgroundMeteors* Instance();
	static void Release();

	void Scroll(bool scroll);

	void Update();
	void Render();

private:
	static BackgroundMeteors* sInstance;
	static const int LAYER_COUNT = 1;
	MeteorLayer* mMeteorLayers[LAYER_COUNT];

	BackgroundMeteors();
	~BackgroundMeteors();
};