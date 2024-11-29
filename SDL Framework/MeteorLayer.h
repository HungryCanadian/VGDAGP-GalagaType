#pragma once
#include "Meteor.h"

class MeteorLayer {
public:
	MeteorLayer(int layer);
	~MeteorLayer();

	void Update();
	void Render();

private:
	static const int METEOR_COUNT = 3;
	Meteor* mMeteor[METEOR_COUNT];
};
