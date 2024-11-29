#include "Star.h"

bool Star::sScroll = false;

void Star::Scroll(bool scroll) {
	sScroll = scroll;
}

Star::Star(int layer) : Texture("Stars.png", 0,0,50,50) {
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	int starColor = mRandom->RandomInt() % 4;

	mSourceRect.x = starColor * 3;

	Position(Vector2((float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),
		(float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));

	mFlickerTime = 0.0f;
	mFlickerSpeed = mRandom->RandomRange(0.55f, 1.0f);
	
	float inverseLayer = 1.0f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = 8.0f / layer;

}

Star::~Star() {
	mTimer = nullptr;
	mRandom = nullptr;
}

void Star::ScrollStar() {
	Translate(Vec2_Up * mScrollSpeed);

	Vector2 pos = getPosition(Local);
	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = (float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
		Position(pos);
	}
}

void Star::Update() {
	mFlickerTime += mTimer->DeltaTime();

	if (mFlickerTime >= mFlickerSpeed) {
		mVisible = !mVisible;
		mFlickerTime =  0.0f;
	}

	if (sScroll == true) {
		ScrollStar();
	}
}

void Star::Render() {
	if (mVisible == true) {
		Texture::Render();
	}
}