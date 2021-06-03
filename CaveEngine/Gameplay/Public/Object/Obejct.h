#pragma once

#include <string>
#include <vector>

#include "Math/Vector2.h"

namespace cave
{
	class Type;
	class Transform;
	class Vector3;
	class Quaternion;

	class Object
	{
	public:
		friend class ObjectManager;

		Object();
		Object(const Object& other);
		Object(Object&& other) noexcept;
		
		virtual ~Object();
		Object& operator=(const Object& other);
		Object& operator=(Object&& other) noexcept;

		static void Destroy(Object& target, float timeDelay = 0.f);
		static void DestroyImmediate(Object& target);
		static void DontDestroyOnLoad(Object& target);

		static Object& FindObjectOfType(Type& type);
		static Object& FindObjectsOfType(Type& type, bool includeInactive = false);

		static Object& Instantiate(Object& original);
		static Object& Instantiate(Object& original, Transform& parent);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation, Transform& parent);

		unsigned int GetInstanceID();
		const char* ToString();

		unsigned int GetInternalIndex() const;

		bool CompareTag(const char* tag);

		__forceinline bool IsNull() const;

		void Print();

	private:
		void Initialize();

		void SetInternalIndex(unsigned int internalIndex);
		
		void SetInstanceID(unsigned int id);

	private:
		Object* mOwner;

		const char* mName;
		const char* mTag;

		Vector2 mTransform;

		unsigned char mHideFlags;
		unsigned int mInternalIndex;
		unsigned int mInstanceID;

		bool mbNull;
		bool mbIsUsed;
	};

	void Swap(Object& left, Object& right);
}