module;

#include "CoreTypes.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"

export module cave.Gameplay.Event.Event;

namespace cave
{
	export class Event final
	{
	public:
		Event() = delete;
		Event(uint16_t message, GameObject* target);
		Event(uint16_t message, GameObject* target, uint8_t priority);
		Event(const Event& other);
		Event(Event&& other) noexcept;

		~Event();
		Event& operator=(const Event& other);
		Event& operator=(Event&& other) noexcept;

		friend bool operator==(const Event& lhs, const Event& rhs);
		friend bool operator!=(const Event& lhs, const Event& rhs);
		friend bool operator<(const Event& lhs, const Event& rhs);
		friend bool operator>(const Event& lhs, const Event& rhs);

		uint16_t GetMessage() const;
		GameObject* GetTarget() const;
		bool IsValid() const;

	private:
		uint8_t mPriority;
		uint16_t mMessage;
		GameObject* mTarget;
	};

	Event::Event(uint16_t message, GameObject* target)
		: mMessage(message)
		, mTarget(target)
		, mPriority(0)
	{
		assert(IsValid());
	}

	Event::Event(uint16_t message, GameObject* target, uint8_t priority)
		: mMessage(message)
		, mTarget(target)
		, mPriority(priority)
	{

	}

	Event::Event(const Event& other)
		: mMessage(other.mMessage)
		, mTarget(other.mTarget)
		, mPriority(other.mPriority)
	{
		assert(IsValid());
	}

	Event::Event(Event&& other) noexcept
		: mMessage(other.mMessage)
		, mTarget(other.mTarget)
		, mPriority(other.mPriority)
	{
		assert(IsValid());
		other.mTarget = nullptr;
	}

	Event::~Event()
	{

	}

	Event& Event::operator=(const Event& other)
	{
		assert(IsValid());
		
		mMessage = other.mMessage;
		mTarget = other.mTarget;
		mPriority = other.mPriority;

		return *this;
	}

	Event& Event::operator=(Event&& other) noexcept
	{
		assert(IsValid());

		mMessage = other.mMessage;
		mTarget = other.mTarget;
		mPriority = other.mPriority;
		other.mTarget = nullptr;

		return *this;
	}

	uint16_t Event::GetMessage() const
	{
		assert(IsValid());
		return mMessage;
	}

	GameObject* Event::GetTarget() const
	{
		assert(IsValid());
		return mTarget;
	}

	bool Event::IsValid() const
	{
		return mTarget != nullptr ? true : false;
	}

	bool operator==(const Event& lhs, const Event& rhs)
	{
		return lhs.mPriority == rhs.mPriority;
	}

	bool operator!=(const Event& lhs, const Event& rhs)
	{
		return lhs.mPriority != rhs.mPriority;
	}

	bool operator<(const Event& lhs, const Event& rhs)
	{
		return lhs.mPriority < rhs.mPriority;
	}

	bool operator>(const Event& lhs, const Event& rhs)
	{
		return lhs.mPriority > rhs.mPriority;
	}
}