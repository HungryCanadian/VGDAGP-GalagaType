#include "InputManager.h"


namespace SDLFramework {

    InputManager* InputManager::sInstance = nullptr;

    InputManager* InputManager::Instance() {
        if (sInstance == nullptr) {
            sInstance = new InputManager();
        }
        return sInstance;
    }

    void InputManager::Release() {
        delete sInstance;
        sInstance = nullptr;
    }

    bool InputManager::KeyDown(SDL_Scancode scancode) {
        return mKeyboardState[scancode] != 0;
    }

    bool InputManager::KeyPressed(SDL_Scancode scancode) {
        return !mPrevKeyboardState[scancode] && mKeyboardState[scancode];

    }

    bool InputManager::KeyReleased(SDL_Scancode scancode) {
        return mPrevKeyboardState[scancode] && !mKeyboardState[scancode];
    }

    bool InputManager::MouseButtonDown(MouseButton button) {
        Uint32 mask = 0;
        switch (button) {
        case LEFT: mask = SDL_BUTTON_LMASK; break;
        case RIGHT: mask = SDL_BUTTON_RMASK; break;
        case MIDDLE: mask = SDL_BUTTON_MMASK; break;
        case BACK: mask = SDL_BUTTON_X1MASK; break;
        case FORWARD: mask = SDL_BUTTON_X2MASK; break;
        }
        return (mMouseState & mask) != 0;
    }

    bool InputManager::MouseButtonPressed(MouseButton button) {
        Uint32 mask = 0;
        switch (button) {
        case LEFT: mask = SDL_BUTTON_LMASK; break;
        case RIGHT: mask = SDL_BUTTON_RMASK; break;
        case MIDDLE: mask = SDL_BUTTON_MMASK; break;
        case BACK: mask = SDL_BUTTON_X1MASK; break;
        case FORWARD: mask = SDL_BUTTON_X2MASK; break;
        }
        return !(mPrevMouseState & mask) && (mMouseState & mask);
    }

    bool InputManager::MouseButtonReleased(MouseButton button) {
        Uint32 mask = 0;
        switch (button) {
        case LEFT: mask = SDL_BUTTON_LMASK; break;
        case RIGHT: mask = SDL_BUTTON_RMASK; break;
        case MIDDLE: mask = SDL_BUTTON_MMASK; break;
        case BACK: mask = SDL_BUTTON_X1MASK; break;
        case FORWARD: mask = SDL_BUTTON_X2MASK; break;
        }
        return (mPrevMouseState & mask) && !(mMouseState & mask);
    }

    Vector2 InputManager::MousePosition() {
        return Vector2((float)mMouseXPos, (float)mMouseYPos);
    }

    void InputManager::Update() {
        mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);


        mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
    }

    void InputManager::UpdatePrevInput() {
        memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);

        mPrevMouseState = mMouseState;
    }

    InputManager::InputManager() {
        mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
        mPrevKeyboardState = new Uint8[mKeyLength];
        memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
    }

    InputManager::~InputManager() {
        delete[] mPrevKeyboardState;
        mPrevKeyboardState = nullptr;
    }

    void InputManager::HandleInput() {
        for (SDL_Scancode scancode : keysToCheck) {
            if (KeyPressed(scancode)) {
                std::cout << SDL_GetScancodeName(scancode) << " Key Pressed" << std::endl;
            }
            if (KeyReleased(scancode)) {
                std::cout << SDL_GetScancodeName(scancode) << " Key Released" << std::endl;
            }
        }
    }
}

