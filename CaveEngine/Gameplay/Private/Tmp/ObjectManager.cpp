#include <cassert>
#include <iostream>

#include "Tmp/ObjectManager.h"
#include "Tmp/Log.h"

namespace cave
{
	Object* ObjectManager::mObjectArray = nullptr;
	size_t ObjectManager::mMaxSize = 0;
	ObjectManager* ObjectManager::mObjectManager = nullptr;
	size_t ObjectManager::mObjectID = 100000;

	ObjectManager::ObjectManager()
	{
		Log("ObjectManager::ObjectManager()");
	}

	ObjectManager::~ObjectManager()
	{
		Log("ObjectManager::~ObjectManager()");
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

	Object* ObjectManager::Allocate()
	{
		Log("ObjectManager::Allocate()");

		Object* ptr = &mObjectArray[0];
		for (size_t i = 1; i < mMaxSize; ++i)
		{
			if (!(mObjectArray[i].IsUsed()))
			{
				mObjectArray[i].SetInstanceID(mObjectID);
				mObjectArray[i].SetUsed(true);
				++mObjectID;
				std::cout << mObjectID << std::endl;
				ptr = &mObjectArray[i];

				return ptr;
			}
		}
		return ptr;
	}

	void ObjectManager::Deallocate(unsigned int internalIndex)
	{
		Log("ObjectManager::Deallocate(unsigned int)");

		if (internalIndex == 0)
		{
			return;
		}

		mObjectArray[internalIndex].Initialize();
	}

	void ObjectManager::Free(void* target)
	{
		if (target != nullptr)
		{
			free(target);
		}
	}

	void ObjectManager::Initialize()
	{
		Log("ObjectManager::Initialize()");

		mMaxSize = 100;
		mObjectArray = (Object*)malloc(sizeof(Object) * mMaxSize);
		
		assert(mObjectArray != nullptr);

		for (size_t i = 0; i < mMaxSize; ++i)
		{
			mObjectArray[i].Initialize();
			mObjectArray[i].SetInternalIndex(i);
		}
		mObjectArray[0].SetNull(true);
	}
}