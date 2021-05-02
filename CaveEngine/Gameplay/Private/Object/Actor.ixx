#include <cassert>
#include <map>

export module Actor;

import Component;
import Timer;

namespace cave
{
	export class Actor
	{
	public:
		Actor()
		{
			mTimer = new Timer();
			mComponents = new std::map<Component::eType, Component*>();
		}

		~Actor()
		{
			delete mTimer;
			for (auto iter : *mComponents)
			{
				delete iter.second;
			}
			delete mComponents;
		}

		Timer* GetTimer() const noexcept
		{
			return mTimer;
		}

		void AddComponent(Component* component)
		{
			assert(component != nullptr);
			mComponents->insert({ component->GetType(), component });
		}

		Component* GetComponentByType(Component::eType type) const noexcept
		{
			auto iter = mComponents->find(type);
			if (iter == mComponents->end())
			{
				return nullptr;
			}
			return (*iter).second;
		}

	private:
		Timer* mTimer;

		std::map<Component::eType, Component*>* mComponents;
	};
}