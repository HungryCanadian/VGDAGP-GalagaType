#include "GameManager.h"

namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void GameManager::Run() {
		while (!mQuit) {
			mTimer->Update();
			while (SDL_PollEvent(&mEvents) != 0) {
				if (mEvents.type == SDL_QUIT) {
					mQuit = true;
				}
			}

			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();
			}
		}
	}


	void GameManager::Update() {
		mInputManager->Update();
		mScreenManager->Update();

	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();
		
	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		
		mBackground2->Render();
		mScreenManager->Render();
		
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		mTimer = Timer::Instance();
		mGraphics = Graphics::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mAssetManager = AssetManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();
		mScreenManager = ScreenManager::Instance();


		//Create the Physics Layers
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, 
			PhysicsManager::CollisionFlags::Hostile | 
			PhysicsManager::CollisionFlags::HostileProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile, 
			PhysicsManager::CollisionFlags::Friendly | 
			PhysicsManager::CollisionFlags::FriendlyProjectile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile, 
			PhysicsManager::CollisionFlags::Hostile);

		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile, 
			PhysicsManager::CollisionFlags::Friendly);



		if (!Graphics::Initialized) {
			mQuit = true;
		}


		


		mBackground2 = new Texture("background.png");
		mBackground2->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
		mBackground2->Scale(Vector2(1.1f, 0.6f));
		




	}

	GameManager::~GameManager() {
		//Release Variables
		delete mBackground2;
		mBackground2 = nullptr;

		//Release Modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		ScreenManager::Release();
		mScreenManager = nullptr;


		//Quit SDL
		SDL_Quit();
	}


}