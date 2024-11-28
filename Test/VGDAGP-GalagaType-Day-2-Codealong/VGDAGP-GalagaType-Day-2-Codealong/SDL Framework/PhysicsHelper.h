#pragma once
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "MathHelper.h"


namespace SDLFramework {
	//circle vs circle
	inline bool CircleVsCircleCollision(CircleCollider* circle1, CircleCollider* circle2) {
		return (circle1->getPosition() - circle2->getPosition()).Magnitude() < (circle1->getRadius() + circle2->getRadius());

	}
	//circle vs box
	inline bool BoxVsCircleCollision(BoxCollider* box, CircleCollider* circle) {
		Vector2 circlePos = circle->getPosition();
		float radius = circle->getRadius();

		Vector2 quad[4];
		quad[0] = box->getVertexPos(0);
		quad[1] = box->getVertexPos(1);
		quad[2] = box->getVertexPos(2);
		quad[3] = box->getVertexPos(3);

		//Vertex Collision Check
		for (int i = 0; i < 4; i++) {
			if ((quad[i] - circlePos).Magnitude() < radius) {
				//We have an edge of our sqaure inside our circle collider
				std::cout << "BoxVsCircleCollision: Vertex collision detected" << std::endl;
				return true;
			}
		}

		if (PointToLineDistance(box->getVertexPos(0), box->getVertexPos(1), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(0), box->getVertexPos(2), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(2), box->getVertexPos(3), circlePos) < radius ||
			PointToLineDistance(box->getVertexPos(3), box->getVertexPos(1), circlePos) < radius) {
			std::cout << "BoxVsCircleCollision: Edge collision detected" << std::endl;
			return true;
		}
		
		if (PointinPolygon(quad, 4, circlePos)) {
			std::cout << "BoxVsCircleCollision: Circle inside box" << std::endl;
			return true; // Circle is INSIDE our box collider. - collision
		}
		return false;
	}
	//box vs box
	inline bool BoxVsBoxCollision(BoxCollider* box1, BoxCollider* box2) {
		Vector2 projAxes[4];
		projAxes[0] = (box1->getVertexPos(0) - box1->getVertexPos(1)).Normalized();
		projAxes[1] = (box1->getVertexPos(0) - box1->getVertexPos(2)).Normalized();
		projAxes[2] = (box2->getVertexPos(0) - box2->getVertexPos(1)).Normalized();
		projAxes[3] = (box2->getVertexPos(0) - box2->getVertexPos(2)).Normalized();

		float box1Min = 0.0f;
		float box1Max = 0.0f;
		float box2Min = 0.0f;
		float box2Max = 0.0f;
		float proj1 = 0.0f;
		float proj2 = 0.0f;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				proj1 = Dot(box1->getVertexPos(j), projAxes[i]);
				proj2 = Dot(box2->getVertexPos(j), projAxes[i]);

				if (j == 0) {
					box1Min = box1Max = proj1;
				}
				else {
					if (proj1 < box1Min) {
						box1Min = proj1;
					}
					if (proj1 > box1Max) {
						box1Max = proj1;
					}

					if (proj2 < box2Min) {
						box2Min = proj2;
					}
					if (proj2 > box2Max) {
						box2Max = proj2;
					}
				}
			}

			//At this point, we have our two box projections
			float halfDist1 = (box1Max - box1Min) * 0.5f;
			float midPoint1 = box1Min + halfDist1;

			float halfDist2 = (box2Max - box2Min) * 0.5f;
			float midPoint2 = box2Min + halfDist2;

			if (abs(midPoint1 - midPoint2) > (halfDist1 + halfDist2)) {
				return false;
			}
		}

		//Implicitly returns true
	}

	inline bool ColliderVsColliderCheck(Collider* c1, Collider* c2) { //c1 = Collider 1, c2 = Collider 2
		if (c1->getType() == Collider::ColliderType::Circle && c2->getType() == Collider::ColliderType::Circle)
			return CircleVsCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Circle)
			return BoxVsCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
		else if (c2->getType() == Collider::ColliderType::Box && c1->getType() == Collider::ColliderType::Circle)
			return BoxVsCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
		else if (c1->getType() == Collider::ColliderType::Box && c2->getType() == Collider::ColliderType::Box)
			return BoxVsBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
		else
			return false;
	}

}