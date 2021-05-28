#include "Tmp/ObjectManager.h"

namespace cave
{
	ObjectManager* ObjectManager::mObjectManager = nullptr;
	std::vector<Object> ObjectManager::mObjectArray(100);
	size_t ObjectManager::mSize = 1;

	ObjectManager::ObjectManager()
	{
		
	}

	ObjectManager::~ObjectManager()
	{
		
	}

	ObjectManager& ObjectManager::Instance()
	{
		if (mObjectManager == nullptr)
		{
			mObjectManager = new ObjectManager();
		}

		return *mObjectManager;
	}

	Object& ObjectManager::Allocate()
	{
		size_t index = mSize;
		mObjectArray[index].SetInternalIndex(index);
		++mSize;

		return *(mObjectArray[index].mOwner);
	}

	void ObjectManager::Deallocate(unsigned int internalIndex)
	{
		if (mSize > 0)
		{
			--mSize;
		}
		unsigned int tmp = mObjectArray[internalIndex].mInternalIndex;
		mObjectArray[internalIndex].mInternalIndex = mObjectArray[mSize].mInternalIndex;
		mObjectArray[mSize].mInternalIndex = tmp;
		Swap(mObjectArray[internalIndex], mObjectArray[mSize]);
		mObjectArray[mSize].Initialize();
	}

	std::vector<Object>& ObjectManager::GetObjectArray()
	{
		return mObjectArray;
	}

}