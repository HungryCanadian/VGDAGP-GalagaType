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
		mInputManager->HandleInput();
		mTex->Update();
		mRedShip->Update();

		if (mInputManager->KeyDown(SDL_SCANCODE_W)) {
			mPhysone->Translate(Vector2(0.0f, -40.0f) * mTimer->DeltaTime(), GameEntity::Local);			
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_S)) {
			mPhysone->Translate(Vector2(0.0f, 40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_A)) {
			mPhysone->Translate(Vector2(-40.0f, 0.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_D)) {
			mPhysone->Translate(Vector2(40.0f, 0.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_Q)) {
			mPhysone->Rotation(mPhysone->getRotation(GameEntity::Local) + -180.0f * mTimer->DeltaTime());
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_E)) {
			mPhysone->Rotation(mPhysone->getRotation(GameEntity::Local) + 180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_Z)) {
			mPhysone->Scale(mPhysone->getScale() + Vector2(0.1f, 0.1f));
		}
		else if (mInputManager->KeyDown(SDL_SCANCODE_C)) {
			mPhysone->Scale(mPhysone->getScale() - Vector2(0.1f, 0.1f));
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_I)) {
			mPhystwo->Translate(Vector2(0.0f, -40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_K)) {
			mPhystwo->Translate(Vector2(0.0f, 40.0f) * mTimer->DeltaTime(), GameEntity::Local);
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_J)) {
			mPhystwo->Rotation(mPhystwo->getRotation(GameEntity::Local) + -180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_L)) {
			mPhystwo->Rotation(mPhystwo->getRotation(GameEntity::Local) + 180.0f * mTimer->DeltaTime());
		}
		if (mInputManager->KeyDown(SDL_SCANCODE_ESCAPE)) {
			mQuit = true;
		}
		if (mInputManager->MouseButtonPressed(InputManager::LEFT)) {
			std::cout << "Left Mouse Button Pressed" << "\n";
			mAudioManager->PlaySFX("coin_credit.wav", 0, -1);
		}
		if (mInputManager->MouseButtonReleased(InputManager::LEFT)) {
			std::cout << "Left Mouse Button Released" << "\n";
		}
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->UpdatePrevInput();
		
	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();

		mBackground2->Render();
		mTex->Render();
		mRedShip->Render();
		mFontTex->Render();
		
		//mPhysone->Render();
		//mPhystwo->Render();
		
//		mGreenGalaga->Render();
//		mPurpleGalaga->Render();

		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		mTimer = Timer::Instance();
		mGraphics = Graphics::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mAssetManager = AssetManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();

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

		

		mTex = new AnimatedTexture("SpriteSheet.png", 204, 45, 40, 38, 4, 0.5f, AnimatedTexture::Horizontal);
		mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
		mTex->Scale(Vector2(2.3f, 2.3f));

		mRedShip = new Texture("player.png");
		mRedShip->Position(Vector2(Graphics::SCREEN_WIDTH * 0.35f, Graphics::SCREEN_HEIGHT * 0.49f));
		mRedShip->Scale(Vector2(0.5f, 0.5f));

		mFontTex = new Texture("Caspiran Galaga", "ToThePoint.ttf", 100, { 0, 0, 225 });
		mFontTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.05f));

		mBackground2 = new Texture("background.jpg");
		mBackground2->Position(Vector2(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.5f));
		mBackground2->Scale(Vector2(1.3f, 1.3f));
		
		mAudioManager->PlayMusic("BeachAmbience.mp3", -1);

		mPhysone = new PhysicsEntity();
		mPhysone->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.5f));
		mPhysone->AddCollider(new BoxCollider(Vector2(20.0f, 20.0f)));
		mPhysone->mId = mPhysicsManager->RegisterEntity(mPhysone, PhysicsManager::CollisionLayers::Friendly);

		

		mPhystwo = new PhysicsEntity();
		mPhystwo->Position(Vector2(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f));
		mPhystwo->AddCollider(new BoxCollider(Vector2(20.0f, 20.0f)));
		mPhystwo->mId = mPhysicsManager->RegisterEntity(mPhystwo, PhysicsManager::CollisionLayers::Hostile);



		//mAudioManager->PlayMusic("TavernAmbience.mp3", -1);
		//mGreenGalaga = new Texture("SpriteSheet.png", 182, 100, 20, 20);
		//mGreenGalaga->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.49f));
		//mGreenGalaga->Scale(Vector2(2.0f, 2.0f));

		//mPurpleGalaga = new Texture("SpriteSheet.png", 182, 125, 20, 20);
		//mPurpleGalaga->Position(Vector2(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.49f));
		//mPurpleGalaga->Scale(Vector2(2.0f, 2.0f));
		

	}

	GameManager::~GameManager() {
		//Release Variables
		delete mTex;
		mTex = nullptr;

		delete mRedShip;
		mRedShip = nullptr;

		delete mFontTex;
		mFontTex = nullptr;

		delete mBackground2;
		mBackground2 = nullptr;

		delete mPhysone;
		mPhysone = nullptr;

		delete mPhystwo;
		mPhystwo = nullptr;



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


		//Quit SDL
		SDL_Quit();
	}


}