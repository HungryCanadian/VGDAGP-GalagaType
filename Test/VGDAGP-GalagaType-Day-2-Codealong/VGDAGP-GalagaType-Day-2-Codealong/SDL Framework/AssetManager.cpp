#include "AssetManager.h"

namespace SDLFramework {
	AssetManager* AssetManager::sInstance = nullptr;

	AssetManager* AssetManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AssetManager();
		}

		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}



	SDL_Texture* AssetManager::getTexture(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mTextures[fullPath] == nullptr) {
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		}

		if (mTextures[fullPath] != nullptr && managed) {
			mTextureRefCount[mTextures[fullPath]] += 1;
		}

		return mTextures[fullPath];
	}

	SDL_Texture* AssetManager::getText(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		std::stringstream ss;

		ss << size << (int)color.r << (int)color.g << (int)color.b;
		std::string key = text + filename + ss.str();

		if (mTextures[key] == nullptr) {
			TTF_Font* font = getFont(filename, size);
			mTextures[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		}

		if (mTextures[key] != nullptr && managed) {
			mTextureRefCount[mTextures[key]] += 1;
		}

		return mTextures[key];

	}

	TTF_Font* AssetManager::getFont(std::string filename, int size) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + filename);

		std::stringstream ss;
		ss << size;
		std::string key = fullpath + ss.str();

		if (mFonts[key] == nullptr) {
			mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);

			if (mFonts[key] == nullptr) {
				std::cerr << "Unable to load Font: " << filename << "! TTF Error: " << TTF_GetError() << "\n";
			}
		}

		return mFonts[key];
	}

	Mix_Music* AssetManager::getMusic(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/Music/" + filename);

		if (mMusic[fullPath] == nullptr) {
			mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		}

		if (mMusic[fullPath] == nullptr) {
			std::cerr << "Unable to load Music: " << filename << "! Mixer Error: " << Mix_GetError() << "\n";
			return nullptr;
		} 
		else if (managed) {
			mMusicRefCount[mMusic[fullPath]] += 1;
		}

		return mMusic[fullPath];
	}

	Mix_Chunk* AssetManager::getSFX(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/SFX/" + filename);

		if (mSFX[fullPath] == nullptr) {
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());

		}

		if (mSFX[fullPath] == nullptr) {
			std::cerr << "Unable to load SFX: " << filename << "! Mix Error: " << Mix_GetError() << "\n";
			return nullptr;
		}
		else if (managed) {
			mSFXRefCount[mSFX[fullPath]] += 1;
		}

		return mSFX[fullPath];
	}

	void AssetManager::DestroyTexture(SDL_Texture* texture) {
		std::map<SDL_Texture*, unsigned>::iterator it = mTextureRefCount.find(texture);

		if (it != mTextureRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				//this means no more instances of the texture are being used
				UnloadTexture(it->first);
				mTextureRefCount.erase(it->first);
			}

		}
		else {
			//otherwise, something is still making a reference to this texture.
			UnloadTexture(texture);
		}
	}

	void AssetManager::DestroyMusic(Mix_Music* music) {
		std::map<Mix_Music*, unsigned>::iterator it = mMusicRefCount.find(music);

		if (it != mMusicRefCount.end()) {
			it->second -= 1;

			if (it->second == 0) {
				UnloadMusic(it->first);
				mMusicRefCount.erase(it->first);
			}
		}
		else {
			UnloadMusic(music);
		}
	}

	void AssetManager::UnloadMusic(Mix_Music* music) {
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Music*>::iterator it;

		for (it = mMusic.begin(); it != mMusic.end() && !found; it++) {
			if ((found = it->second == music)) {
				Mix_FreeMusic(it->second);
				key = it->first;
			}
		}

		if (found) {
			mMusic.erase(key);
		}
	}

	void AssetManager::DestroySFX(Mix_Chunk* sfx) {
		std::map<Mix_Chunk*, unsigned>::iterator it = mSFXRefCount.find(sfx);

		if (it != mSFXRefCount.end()) {
			it->second -= 1;

			if (it->second == 0) {
				UnloadSFX(it->first);
				mSFXRefCount.erase(it->first);
			}
		}
		else {
			UnloadSFX(sfx);
		}
	}

	void AssetManager::UnloadSFX(Mix_Chunk* sfx) {
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Chunk*>::iterator it;

		for (it = mSFX.begin(); it != mSFX.end() && !found; it++) {
			if ((found = it->second == sfx)) {
				Mix_FreeChunk(it->second);
				key = it->first;
			}
		}

		if (found) {
			mSFX.erase(key);
		}
	}

	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != nullptr) {
				SDL_DestroyTexture(tex.second);
			}

		}
		mTextures.clear();
	}

	void AssetManager::UnloadTexture(SDL_Texture* texture) {
		bool found = false;
		std::string key;
		std::map<std::string, SDL_Texture*>::iterator it;

		for (it = mTextures.begin(); it != mTextures.end() && !found; it++) {
			if ((found = it->second == texture)) {
				SDL_DestroyTexture(it->second);
				key = it->first;
			}
		}

		if (found) {
			mTextures.erase(key);
		}
	}


}