#include <cassert>
#include <iostream>

#include "Tmp/ObjectManager.h"
#include "Tmp/Log.h"

namespace cave
{
	Object** ObjectManager::mObjectArray = nullptr;
	size_t ObjectManager::mMaxSize = 0;
	ObjectManager* ObjectManager::mObjectManager = nullptr;
	size_t ObjectManager::mObjectID = 100000;

	ObjectManager::ObjectManager()
	{
		Log("ObjectManager::ObjectManager()");
		//Initialize();
	}

	ObjectManager::~ObjectManager()
	{
		Log("ObjectManager::~ObjectManager()");

		//free(mObjectArray);
	}

	void ObjectManager::Print()
	{
		Log("ObjectManager::Print()");

#ifdef _DEBUG
		std::cout << "mObjectManager: " << &mObjectManager << std::endl;
		std::cout << "mObjectArray: " << mObjectArray << std::endl;
		std::cout << "mMaxSize: " << mMaxSize << std::endl;
#endif // _DEBUG

	}

	ObjectManager& ObjectManager::Instance()
	{
		Log("ObjectManager::Instance()");

		if (mObjectManager == nullptr)
		{
			mObjectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
		}

		return *mObjectManager;
	}

	void ObjectManager::Destroy()
	{
		Free(mObjectArray);
		Free(mObjectManager);
	}

	void ObjectManager::Allocate(const Object& object)
	{
		
	}

	void ObjectManager::Deallocate(unsigned int internalIndex)
	{

	}

	void ObjectManager::Free(void* target)
	{
		if (target != nullptr)
		{
			free(target);
		}
	}

	Object* ObjectManager::GetObjectArray()
	{
		assert(mObjectArray != nullptr);

		return mObjectArray;
	}

	void ObjectManager::Explosion()
	{
		Log("ObjectManager::Explosion()");

		if (mObjectArray != nullptr)
		{
			free(mObjectArray);
		}
	}

	void ObjectManager::Initialize()
	{
		Log("ObjectManager::Initialize()");

		mMaxSize = 100;
		mObjectArray = (Object**)malloc(sizeof(Object*) * mMaxSize);
		
		assert(mObjectArray != nullptr);

		for (size_t i = 0; i < mMaxSize; ++i)
		{
			mObjectArray[i] = nullptr;
		}
	}
}