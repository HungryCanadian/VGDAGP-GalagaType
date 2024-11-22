#pragma once
#include "Graphics.h"
#include "AudioManager.h"
#include "PhysicsManager.h"
#include "StartScreen.h"


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

		//Screens
		StartScreen* mStartScreen;


		SDL_Event mEvents;

	};
}