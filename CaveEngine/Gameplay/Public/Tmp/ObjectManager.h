#pragma once

#include <vector>

#include "Object/Obejct.h"

namespace cave
{
	class ObjectManager
	{
	public:
		~ObjectManager();

		static ObjectManager& Instance();

		static Object& Allocate();
		static void Deallocate(unsigned int internalIndex);

		static std::vector<Object>& GetObjectArray();

	private:
		ObjectManager();
	
	private:
		static ObjectManager* mObjectManager;
		static std::vector<Object> mObjectArray;
		static size_t mSize;
	};
}