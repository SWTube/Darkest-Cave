#include <cassert>

#include "Object/Obejct.h"
#include "Tmp/ObjectManager.h"
#include "Tmp/Log.h"

namespace cave
{
	Object::Object()
	{
		Log("Object::Object()");

		Initialize();
	}

	Object::Object(const Object& other)
	{
		Log("Object::Object(const Object&)");
	}

	Object::Object(Object&& other) noexcept
	{
		Log("Object::Object(Object&&)");

		mOwner = other.mOwner;

		mHideFlags = other.mHideFlags;
		mName = std::move(other.mName);
		mTag = std::move(other.mTag);
		mTransform = std::move(other.mTransform);
		mInstanceID = other.mInstanceID;

		other.mOwner = nullptr;

		other.mHideFlags = 0x00000000;
		other.mInstanceID = 0;
	}

	Object::~Object()
	{
		Log("Object::~Object()");
	}

	Object& Object::operator=(const Object& other)
	{
		Log("Object::operator=(const Object&)");

		return *this;
	}

	Object& Object::operator=(Object&& other) noexcept
	{
		Log("Object::operator=(Object&&)");
		
		mOwner = other.mOwner;

		mHideFlags = other.mHideFlags;
		mName = std::move(other.mName);
		mTag = std::move(other.mTag);
		mTransform = std::move(other.mTransform);
		mInstanceID = other.mInstanceID;

		other.mOwner = nullptr;

		other.mHideFlags = 0x00000000;
		other.mInstanceID = 0;

		return *this;
	}


	void Object::Destroy(Object& target, float timeDelay)
	{
		Log("Object::Destroy(Object&, float)");

		if (timeDelay == 0.f)
		{
			ObjectManager::Deallocate(target.GetInternalIndex());
		}
	}

	void Object::DestroyImmediate(Object& target)
	{
		Log("Object::DestroyImmediate(Object&)");

		ObjectManager::Deallocate(target.GetInternalIndex());
	}

	void Object::DontDestroyOnLoad(Object& target)
	{
		Log("Object::DontDestroyOnLoad");
	}

	Object& Object::FindObjectOfType(Type& type)
	{
		Log("Object::FindObjectOfType(Type&)");

		std::vector<Object>& vec = ObjectManager::GetObjectArray();
		auto iter = vec.begin();
		for (auto end = vec.end(); iter != end; ++iter)
		{
			
		}
		return *iter;
	}

	std::vector<Object>& Object::FindObjectsOfType(Type& type, bool includeInactive)
	{
		Log("Object::FindObjectsOfType(Type&, bool)");

		std::vector<Object>& vec = ObjectManager::GetObjectArray();
		std::vector<Object> result;
		for (auto& e : vec)
		{
			result.push_back(Instantiate(e));
		}
		return result;
	}

	Object& Object::Instantiate(Object& original)
	{
		Log("Object::Instantiate(Object&)");

		Object& tmp = ObjectManager::Allocate();
		tmp.mName = original.mName;
		tmp.mHideFlags = original.mHideFlags;

		return tmp;
	}

	Object& Object::Instantiate(Object& original, Transform& parent)
	{
		Log("Object::Instantiate(Object&, Transform&)");

		Object& tmp = ObjectManager::Allocate();
		tmp.mName = original.mName;
		tmp.mHideFlags = original.mHideFlags;

		return tmp;
	}

	Object& Object::Instantiate(Object& original, Vector3& position, Quaternion& rotation)
	{
		Log("Object::Instantiate(Object&, Vector3&, Quaternion&)");

		Object& tmp = ObjectManager::Allocate();
		tmp.mName = original.mName;
		tmp.mHideFlags = original.mHideFlags;

		return tmp;
	}

	Object& Object::Instantiate(Object& original, Vector3& position, Quaternion& rotation, Transform& parent)
	{
		Log("Object::Instantiate(Object&, Vector3&, Quaternion&, Transform&)");

		Object& tmp = ObjectManager::Allocate();
		tmp.mName = original.mName;
		tmp.mHideFlags = original.mHideFlags;

		return tmp;
	}

	void Object::Initialize()
	{
		Log("Object::Initialize()");

		mOwner = this;
		mHideFlags = 0x00000000;
		mInternalIndex = -1;
		mName = "";
		mTag = "";

		mTransform = { .x = 0.f, .y = 0.f};

		mInstanceID = 0;
	}

	void Object::SetInternalIndex(int internalIndex)
	{
		Log("Object::SetInternalIndex(int)");

		mInternalIndex = internalIndex;
	}

	unsigned int Object::GetInternalIndex() const
	{
		Log("Object::GetInternalIndex()");

		return mInternalIndex;
	}

	int Object::GetInstanceID()
	{
		Log("Object::GetInstanceID()");

		return mInstanceID;
	}

	const char* Object::ToString()
	{
		Log("Object::ToString()");

		return mName.c_str();
	}

	bool Object::CompareTag(std::string& tag)
	{
		return mTag.compare(tag.c_str());
	}

	void Swap(Object& left, Object& right)
	{
		Log("cave::Swap(Object&, Object&)");

		Object tmp = std::move(left);
		left = std::move(right);
		right = std::move(tmp);
	}
}