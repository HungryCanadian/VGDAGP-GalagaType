#pragma once
#include "Graphics.h"
#include <map>
#include <sstream>
#include <SDL_mixer.h>

namespace SDLFramework {
	class AssetManager {
	public:
		static AssetManager* Instance();
		static void Release();

		SDL_Texture* getTexture(std::string filename, bool managed = true);
		SDL_Texture* getText(std::string text, std::string filename, int size, SDL_Color color, bool managed = true);

		Mix_Music* getMusic(std::string filename, bool managed = true);
		Mix_Chunk* getSFX(std::string filename, bool managed = true);

		void DestroyTexture(SDL_Texture* texture);
		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);


	private:
		AssetManager();
		~AssetManager();

		void UnloadTexture(SDL_Texture* texture);
		void UnloadMusic(Mix_Music* music);
		void UnloadSFX(Mix_Chunk* sfx);
		TTF_Font* getFont(std::string filename, int size);

		static AssetManager* sInstance;
				
				//Key			Value
		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, TTF_Font*> mFonts;
		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;

		std::map<Mix_Music*, unsigned> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned> mSFXRefCount;
		std::map<SDL_Texture*, unsigned> mTextureRefCount;
	};








}
