module;

#include <queue>

#include "CoreGlobals.h"
#include "CoreTypes.h"
#include "Assertion/Assert.h"

export module cave.Gameplay.Event.EventHandler;

import cave.Gameplay.Event.Event;

namespace cave
{
	export class EventHandler final
	{
	public:
		friend class Engine;

		EventHandler();
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;

		~EventHandler();
		EventHandler& operator=(const EventHandler&&) = delete;
		EventHandler& operator=(EventHandler&&) = delete;

		static bool IsValid();

		static void AddInputEvent(const Event* inputEvent);
		static void AddPhysicsEvent(const Event* physicsEvent);
		static void AddRendererEvent(const Event* rendererEvent);

		static std::priority_queue<const Event*>* GetInputEvents();
		static std::priority_queue<const Event*>* GetPhysicsEvents();
		static std::priority_queue<const Event*>* GetRendererEvents();

	private:
		static void setEventHandler(EventHandler* eventHandler);

	private:
		static EventHandler* mEventHandler;

		std::priority_queue<const Event*>* mCurrentInputEvents;
		std::priority_queue<const Event*>* mNextInputEvents;

		std::priority_queue<const Event*>* mCurrentPhysicsEvents;
		std::priority_queue<const Event*>* mNextPhysicsEvents;

		std::priority_queue<const Event*>* mCurrentRendererEvents;
		std::priority_queue<const Event*>* mNextRendererEvents;
	};

	EventHandler* EventHandler::mEventHandler = nullptr;

	EventHandler::EventHandler()
	{
		mCurrentInputEvents = new std::priority_queue<const Event*>();
		mNextInputEvents = new std::priority_queue<const Event*>();
		
		mCurrentPhysicsEvents = new std::priority_queue<const Event*>();
		mNextPhysicsEvents = new std::priority_queue<const Event*>();
		
		mCurrentRendererEvents = new std::priority_queue<const Event*>();
		mNextRendererEvents = new std::priority_queue<const Event*>();
	}

	EventHandler::~EventHandler()
	{
		if (mCurrentInputEvents != nullptr)
		{
			delete mCurrentInputEvents;
		}

		if (mNextInputEvents != nullptr)
		{
			delete mNextInputEvents;
		}

		if (mCurrentPhysicsEvents != nullptr)
		{
			delete mCurrentPhysicsEvents;
		}

		if (mNextPhysicsEvents != nullptr)
		{
			delete mNextPhysicsEvents;
		}

		if (mCurrentRendererEvents != nullptr)
		{
			delete mCurrentRendererEvents;
		}

		if (mNextRendererEvents != nullptr)
		{
			delete mNextRendererEvents;
		}
	}

	bool EventHandler::IsValid()
	{
		return mEventHandler == nullptr ? false : true;
	}

	void EventHandler::AddInputEvent(const Event* inputEvent)
	{
		assert(IsValid() && inputEvent != nullptr);
		mEventHandler->mCurrentInputEvents->push(inputEvent);
	}

	void EventHandler::AddPhysicsEvent(const Event* physicsEvent)
	{
		assert(IsValid() && physicsEvent != nullptr);
		mEventHandler->mCurrentPhysicsEvents->push(physicsEvent);
	}

	void EventHandler::AddRendererEvent(const Event* rendererEvent)
	{
		assert(IsValid() && rendererEvent != nullptr);
		mEventHandler->mCurrentRendererEvents->push(rendererEvent);
	}

	void EventHandler::setEventHandler(EventHandler* eventHandler)
	{
		mEventHandler = eventHandler;
	}

	std::priority_queue<const Event*>* EventHandler::GetInputEvents()
	{
		std::priority_queue<const Event*>* tmp = mEventHandler->mCurrentInputEvents;
		mEventHandler->mCurrentInputEvents = mEventHandler->mNextInputEvents;
		mEventHandler->mNextInputEvents = tmp;

		return mEventHandler->mNextInputEvents;
	}

	std::priority_queue<const Event*>* EventHandler::GetPhysicsEvents()
	{
		std::priority_queue<const Event*>* tmp = mEventHandler->mCurrentPhysicsEvents;
		mEventHandler->mCurrentPhysicsEvents = mEventHandler->mNextPhysicsEvents;
		mEventHandler->mNextPhysicsEvents = tmp;

		return mEventHandler->mNextInputEvents;
	}

	std::priority_queue<const Event*>* EventHandler::GetRendererEvents()
	{
		std::priority_queue<const Event*>* tmp = mEventHandler->mCurrentRendererEvents;
		mEventHandler->mCurrentRendererEvents = mEventHandler->mNextRendererEvents;
		mEventHandler->mNextRendererEvents = tmp;

		return mEventHandler->mNextRendererEvents;
	}
}