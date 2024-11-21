#pragma once
#include "Collider.h"

namespace SDLFramework {
	class BoxCollider : public Collider {
		//Corners of a box collder are known as its vertices (verts)
	public:
		BoxCollider(Vector2 size);
		~BoxCollider();

		Vector2 GetFurthestPoint() override;
		Vector2 getVertexPos(int index);

	private:
		static const int MAX_VERTS = 4;

		GameEntity* mVerts[MAX_VERTS];

		void AddVert(int index, Vector2 pos);
	};

}