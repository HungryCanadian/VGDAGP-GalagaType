#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

namespace SDLFramework {
	class Texture : public GameEntity {
	public:
		//This one makes a texture from a whole image.
		Texture(std::string filename, bool managed = false);
		//This one makes a texture from a 'piece' of an image.
		Texture(std::string filename, int x, int y, int width, int height, bool managed = false);
		//This one makes a Text appear instead of an image.
		Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = false);
		~Texture();

		Vector2 ScaledDimensions();

		void SetSourceRect(SDL_Rect* sourceRect);

		void Render() override;

	protected:
		SDL_Texture* mTexture;
		Graphics* mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped;
		SDL_Rect mSourceRect;
		SDL_Rect mDestinationRect;
	};
}