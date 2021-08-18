/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Shapes/Quadrant.h"

// https://github.com/POCU/COMP3500CodeSamples/blob/master/07/src/academy/pocu/comp3500samples/w07/quadtree/Quadrant.java

namespace cave
{
	constexpr Quadrant::Quadrant(const BoundingRect& boundingRect)
		: mBoundingRect(boundingRect)
	{
		createChildren();
	}

	constexpr Quadrant::Quadrant(BoundingRect&& boundingRect)
		: mBoundingRect(std::move(boundingRect))
	{
		createChildren();
	}

	Quadrant::~Quadrant()
	{
		if (mTopLeft != nullptr)
		{
			mTopLeft->~Quadrant();
			mTopRight->~Quadrant();
			mBottomLeft->~Quadrant();
			mBottomRight->~Quadrant();

			gCoreMemoryPool.Deallocate(mTopLeft, sizeof(Quadrant));
			gCoreMemoryPool.Deallocate(mTopRight, sizeof(Quadrant));
			gCoreMemoryPool.Deallocate(mBottomLeft, sizeof(Quadrant));
			gCoreMemoryPool.Deallocate(mBottomRight, sizeof(Quadrant));

			mTopLeft = nullptr;
			mTopRight = nullptr;
			mBottomLeft = nullptr;
			mBottomRight = nullptr;
		}
	}

	bool Quadrant::Insert(const TempObject* tempObject)
	{
		const Point& position = tempObject->GetPosition();

		if (!mBoundingRect.Contains(position))
		{
			return false;
		}

		mGameObjects.push_back(tempObject);

		if (mTopLeft != nullptr)
		{
			mTopLeft->Insert(tempObject);
			mTopRight->Insert(tempObject);
			mBottomLeft->Insert(tempObject);
			mBottomRight->Insert(tempObject);
		}

		return true;
	}

	constexpr std::vector<const TempObject*> Quadrant::GetGameObjects(const BoundingRect& rect) const
	{
		if (!mBoundingRect.Contains(rect))
		{
			return std::vector<const TempObject*>();
		}

		if (mTopLeft == nullptr)
		{
			return mGameObjects;
		}

		if (mTopLeft->mBoundingRect.Contains(rect))
		{
			return mTopLeft->GetGameObjects(rect);
		}

		if (mTopRight->mBoundingRect.Contains(rect))
		{
			return mTopRight->GetGameObjects(rect);
		}

		if (mBottomLeft->mBoundingRect.Contains(rect))
		{
			return mBottomLeft->GetGameObjects(rect);
		}

		if (mBottomRight->mBoundingRect.Contains(rect))
		{
			return mBottomRight->GetGameObjects(rect);
		}

		return mGameObjects;
	}

	constexpr void Quadrant::createChildren()
	{
		float width = mBoundingRect.GetWidth();
		float height = mBoundingRect.GetHeight();

		if (width < 2.0f * static_cast<float>(MIN_QUAD_DIMENSION) || height < 2.0f * static_cast<float>(MIN_QUAD_DIMENSION))
		{
			return;
		}

		float x1 = mBoundingRect.GetTopLeft().GetX();
		float y1 = mBoundingRect.GetTopLeft().GetY();
		float x2 = mBoundingRect.GetBottomRight().GetX();
		float y2 = mBoundingRect.GetBottomRight().GetY();

		float midX = (x1 + x2) / 2.0f;
		float midY = (y1 + y2) / 2.0f;

		Point p1(x1, y1);
		Point p2(midX, midY);
		
		mTopLeft = new(reinterpret_cast<Quadrant*>(gCoreMemoryPool.Allocate(sizeof(Quadrant)))) Quadrant(BoundingRect(p1, p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY()));

		p1 = Point(midX, y1);
		p2 = Point(x2, midY);

		mTopRight = new(reinterpret_cast<Quadrant*>(gCoreMemoryPool.Allocate(sizeof(Quadrant)))) Quadrant(BoundingRect(p1, p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY()));

		p1 = Point(x1, midY);
		p2 = Point(midX, y2);

		mBottomLeft = new(reinterpret_cast<Quadrant*>(gCoreMemoryPool.Allocate(sizeof(Quadrant)))) Quadrant(BoundingRect(p1, p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY()));

		p1 = Point(midX, midY);
		p2 = Point(x2, y2);

		mBottomRight = new(reinterpret_cast<Quadrant*>(gCoreMemoryPool.Allocate(sizeof(Quadrant)))) Quadrant(BoundingRect(p1, p2.GetX() - p1.GetX(), p2.GetY() - p1.GetY()));
	}

#ifdef CAVE_BUILD_DEBUG
	namespace QuadrantTest
	{
		void Main()
		{
			const Point p1(1.0f, 4.0f);
			const TempObject tempObject1(p1, 1);

			const Point p2(7.0f, 9.0f);
			const TempObject tempObject2(p2, 2);

			const Point p3(5.0f, 5.0f);
			const TempObject tempObject3(p3, 3);

			const Point p4(3.0f, 4.0f);
			const TempObject tempObject4(p4, 4);

			const Point p5(2.0f, 7.0f);
			const TempObject tempObject5(p5, 5);

			const Point p6(9.0f, 3.0f);
			const TempObject tempObject6(p6, 6);

			Quadrant root(BoundingRect(Point(0.0f, 0.0f), 10.0f, 10.0f));

			root.Insert(&tempObject1);
			root.Insert(&tempObject2);
			root.Insert(&tempObject3);
			root.Insert(&tempObject4);
			root.Insert(&tempObject5);
			root.Insert(&tempObject6);

			std::vector<const TempObject*> tempObjects = root.GetGameObjects(BoundingRect(Point(0.0f, 1.0f), 4.0f, 3.0f));
			//ArrayList<GameObject> tempObjects = root.getGameObjects(rect);

			Print(tempObjects);

			tempObjects = root.GetGameObjects(BoundingRect(Point(5.0f, 8.0f), 1.0f, 1.0f));

			Print(tempObjects);

			tempObjects = root.GetGameObjects(BoundingRect(Point(6.0f, 3.0f), 3.0f, 1.0f));

			Print(tempObjects);
		}

		void Print(const std::vector<const TempObject*> tempObjects)
		{
			LOGD(cave::eLogChannel::CORE_CONTAINER, "--------------------");
			
			for (size_t i = 0; i < tempObjects.size(); ++i) {
				const TempObject* obj = tempObjects[i];
				LOGDF(cave::eLogChannel::CORE_CONTAINER, "%u. [%u] (%f, %f)",
					i + 1,
					obj->GetData(),
					obj->GetPosition().GetX(),
					obj->GetPosition().GetY());
			}
			LOGDF(cave::eLogChannel::CORE_CONTAINER, "Count: %u", tempObjects.size());

			LOGD(cave::eLogChannel::CORE_CONTAINER, "--------------------");
		}
	}
#endif
}