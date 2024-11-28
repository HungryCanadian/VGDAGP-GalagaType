#pragma once
#include <random>
#include <chrono>

namespace SDLFramework {
	class Random {
	public:
		static Random* Instance();
		static void Release();

		unsigned RandomInt();
		float RandomFloat();
		int RandomRange(int low, int high);
		float RandomRange(float low, float high);


	private:
		Random();
		~Random();

		static Random* sInstance;

		std::mt19937 mGenerator;

	};
}