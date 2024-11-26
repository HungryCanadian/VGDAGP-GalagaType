#pragma once
#include "Graphics.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "BoxCollider.h"
#include "StartScreen.h"
#include "BackgroundStars.h"



namespace SDLFramework {
	//Singleton
	class GameManager {
	public:
		static GameManager* Instance();
		static void Release();

		GameManager();
		~GameManager();

		void Update();
		void LateUpdate();

		void Render();

		void Run();


	private:
		const int FRAME_RATE = 60;
		//How we are creating this as a Singleton
		static GameManager* sInstance;
		//Loop Control
		bool mQuit;

		//Modules
		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;
		BackgroundStars* mBackgroundStars;



		//Example Variables
		AnimatedTexture* mTex;
		Texture* mRedShip;
		
		Texture* mFontTex;
		Texture* mBackground2;

		PhysicsEntity* mPhysone;
		PhysicsEntity* mPhystwo;

		//Screens
		StartScreen* mStartScreen;



		SDL_Event mEvents;

	};
}