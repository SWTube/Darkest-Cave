#pragma once

#include <string>

namespace cave
{
	class Type;
	class Transform;
	class Vector3;
	class Quaternion;

	class Object
	{
	public:
		Object();
		Object(const Object& other) = delete;
		Object(Object&& other);
		
		virtual ~Object();
		Object& operator=(const Object& other) = delete;
		Object& operator=(Object&& other);

		static void Destroy(Object& target, float timeDelay = 0.f);
		static void DestroyImmediate(Object& target);
		static void DontDestroyOnLoad(Object& target);

		static Object& FindObjectOfType(Type& type);
		static Object* FindObjectsOfType(Type& type, bool includeInactive = false);

		static Object& Instantiate(Object& original);
		static Object& Instantiate(Object& original, Transform& parent);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation);
		static Object& Instantiate(Object& original, Vector3& position, Quaternion& rotation, Transform parent);

		int GetInstanceID();
		std::string& ToString();

	private:
		std::string mName;
		unsigned char mHideFlags;
	};
}