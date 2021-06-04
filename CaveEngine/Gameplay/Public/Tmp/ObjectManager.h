#pragma once

#include <vector>

#include "Object/Obejct.h"

constexpr size_t DEFAULT_SIZE = 1;

namespace cave
{
	class ObjectManager final
	{
	public:
		friend class Game;

		~ObjectManager();

		static void Print();

		static ObjectManager& Instance();
		static void Destroy();

		static Object* Allocate();
		static void Deallocate(unsigned int internalIndex);

	private:
		ObjectManager() = delete;
		ObjectManager(const ObjectManager& other) = delete;
		ObjectManager(ObjectManager&& other) = delete;

		Object& operator=(const ObjectManager& other) = delete;
		Object& operator=(ObjectManager&& other) = delete;

		static void Initialize();
		static void Free(void* target);
	
	private:
		static ObjectManager* mObjectManager;
		static Object* mObjectArray;
		static size_t mMaxSize;
		static size_t mObjectID;
	};
}