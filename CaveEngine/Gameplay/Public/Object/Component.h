#pragma once

#include "Math/Vector2.h"
#include "Object/Obejct.h"

namespace cave
{
	class Component : public Object
	{
	public:
		Component();

		virtual ~Component();

		void BroadcastMessage();
		void CompareTag();
		void GetComponent();
		void GetComponentInChildren();
		void GetComponentInParent();
		void GetComponents();
		void GetComponentsInChildren();
		void GetComponentsInParent();
		void SendMessage();
		void SendMessageUpwards();


	private:
		Object* mOwner;
		std::string tag;
		Vector2 mTransform;
	};

}