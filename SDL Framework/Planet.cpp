#include "Planet.h"

bool Planet::sScroll = false;

void Planet::Scroll(bool scroll) {
	sScroll = scroll;
}

Planet::Planet(int layer) : Texture("Planets.png", 0, 0, 315, 314) {
	mTimer = Timer::Instance();
	mRandom = Random::Instance();

	int planet = mRandom->RandomInt() % 2;

	mSourceRect.x = planet * 2;

	Position(Vector2((float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH),
		(float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));

	float inverseLayer = 1.0f / layer;
	Scale(Vec2_One * inverseLayer);

	mScrollSpeed = 0.25f / layer;

	mVisible = true;

}

Planet::~Planet() {
	mTimer = nullptr;
	mRandom = nullptr;
}

void Planet::ScrollPlanet() {
	Translate(Vec2_Up * mScrollSpeed);

	Vector2 pos = getPosition(Local);
	if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
		pos.y = 0.0f;
		pos.x = (float)(mRandom->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
		Position(pos);
	}
}

void Planet::Update() {
	if (sScroll == true) {
		ScrollPlanet();
	}
}

void Planet::Render() {
	Texture::Render();

}