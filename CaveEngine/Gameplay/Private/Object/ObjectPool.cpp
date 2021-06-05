/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include <cassert>

#include "Object/Obejct.h"
#include "Object/ObjectPool.h"
#include "Tmp/Log.h"

namespace cave
{
	size_t ObjectPool::mObjectArrayMaxSize = 0;
	size_t ObjectPool::mObjectArrayIndex = 0;
	Object* ObjectPool::mObjectArray = nullptr;

	ObjectPool::ObjectPool()
	{	
		Log("ObjectPool::ObjectPool()");

		mObjectArrayMaxSize = 100;
		mObjectArray = (Object*)malloc(sizeof(Object) * mObjectArrayMaxSize);

		assert(mObjectArray != nullptr);

		for (size_t i = 0; i < mObjectArrayMaxSize; ++i)
		{
			mObjectArray[i].Initialize();
			mObjectArray[i].SetInternalIndex(i);
			mObjectArray[i].SetOwner(mObjectArray[i]);
		}
	}

	ObjectPool::~ObjectPool()
	{
		Log("ObjectPool::~ObjectPool()");

		free(mObjectArray);
	}

	Object* ObjectPool::Allocate()
	{
		Object* ptr = &mObjectArray[mObjectArrayIndex];
		++mObjectArrayIndex;
		return ptr;
	}

	void ObjectPool::Deallocate(Object* object)
	{
		assert(object != nullptr);

		if (mObjectArrayIndex > 0)
		{
			--mObjectArrayIndex;
		}
		Swap(mObjectArray[object->GetInternalIndex()], mObjectArray[mObjectArrayIndex]);
		mObjectArray[mObjectArrayIndex].Initialize();
	}
}