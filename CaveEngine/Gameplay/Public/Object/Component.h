#pragma once

#include "Object/Obejct.h"

namespace cave
{
	class Actor;

	class Component : public Object
	{
	public:
		Component();
		/** only use for test.*/
		Component(const Component& other);
		Component(Component&& other) noexcept;

		virtual ~Component();
		Component& operator=(const Component& other);
		Component& operator=(Component&& other) noexcept;

		void SetTarget(Actor& target);
		Actor& GetTarget() const;

	private:
		Actor* mTarget;
	};

}