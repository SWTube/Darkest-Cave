module;

#include "CoreTypes.h"
#include "Assertion/Assert.h"
#include "Object/GameObject.h"

export module cave.Gameplay.Event.Event;

namespace cave
{
	class Event
	{
	public:
		Event() = delete;
		Event(uint16_t message, GameObject* target);
		Event(const Event& other);
		Event(Event&& other) noexcept;

		~Event();
		Event& operator=(const Event& other);
		Event& operator=(Event&& other) noexcept;

		uint16_t GetMessage() const;
		GameObject* GetTarget() const;
		bool IsValid() const;

	private:
		uint16_t mMessage;
		GameObject* mTarget;
	};

	Event::Event(uint16_t message, GameObject* target)
		: mMessage(message)
		, mTarget(target)
	{
		assert(IsValid());
	}

	Event::Event(const Event& other)
		: mMessage(other.mMessage)
		, mTarget(other.mTarget)
	{
		assert(IsValid());
	}

	Event::Event(Event&& other) noexcept
		: mMessage(other.mMessage)
		, mTarget(other.mTarget)
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

		return *this;
	}

	Event& Event::operator=(Event&& other) noexcept
	{
		assert(IsValid());

		mMessage = other.mMessage;
		mTarget = other.mTarget;
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
}