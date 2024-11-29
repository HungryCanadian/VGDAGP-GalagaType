#include "Meteor.h"

bool Meteor::sScroll = false;

void Meteor::Scroll(bool scroll) {
	sScroll = scroll;
}

Meteor::Meteor(int layer) : Texture("Meteors.png", 0, 0, 50, 50) {
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	int meteor = mRandom->RandomInt() % 4;

	mSourceRect.x = meteor * 4;

	Position(Vector2((float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),
		(float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));

	float inverseLayer = 1.0f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = 18.0f / layer;
	mFlickerTime = 0.0f;
	mFlickerSpeed = mRandom->RandomRange(0.95f, 1.0f);

	mVisible = true;

}

Meteor::~Meteor() {
	mTimer = nullptr;
	mRandom = nullptr;
}

void Meteor::ScrollMeteor() {
	Translate(Vec2_Up * mScrollSpeed);

	Vector2 pos = getPosition(Local);
	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = (float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
		Position(pos);
	}
}

void Meteor::Update() {
	std::cerr << "Updating Meteor! FlickerTime: " << mFlickerTime << ", FlickerSpeed: " << mFlickerSpeed << ", Visible: " << mVisible << std::endl;
	mFlickerTime += mTimer->DeltaTime();

	if (mFlickerTime >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTime = 0.0f;
	}
	if (sScroll == true) {
		ScrollMeteor();
	}
}

void Meteor::Render() {
	Texture::Render();
	
}