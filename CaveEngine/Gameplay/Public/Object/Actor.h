/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Core.h"

namespace cave
{
	class Actor
	{
	public:
		/** Default constructor for Actor. Called Private Initialize(). */
		Actor();

		/********************
		 *		Actor 		*
		 ********************/

		void SetOwner(Actor* newOwner);
		Actor* GetOwner() const;

		void SetInstigator(class Pawn* newInstigator);
		Pawn* GetInstigator() const;

		void SetFolderPath(const char* newFolderPath);
		const char* GetFolderPath() const;

	protected:
		void SetLifeSpan(uint64_t primaryLifeSpan);

	private:
		/** Initialized all Actor's member. */
		void Initialize();

	public:
		/********************
		 *		Time		*
		 ********************/

		uint64_t mPrimaryTick;

		uint64_t mCreationTime;

		uint64_t mLifeSpan;

		uint64_t mLastRenderTime;

		bool mbTickFunctionsRegisterd;

		/********************
		 *		Camera		*
		 ********************/

		bool mbViewTarget;

		bool mbHidden;

		/********************
		 *	   Transform	*
		 ********************/

		struct Vector* mPivotOffset;

		bool mbLockLocation;

		/********************
		 *		Input		*
		 ********************/

		bool mbBlockInput;

		int32_t mInputPriority;

		class Component* mInputComponent;

		bool mbCollideWhenPlacing;

		std::vector<const char*> mTags;

		bool mbCanBeInCluster;

		class Guid* mGuid;

		std::vector<Actor*> mChildren;

		class SeneComponent* mRootCompoent;

		std::vector<class Animation*> mControllingAnimation;

		bool mbHasFinishedSpawning;

		bool mbActorInitailized;

		bool mbActorBeginningPlayFromLevelStreaming;

		bool mbHasDeferredComponentRegistration;

		/********************
		 *		Physics		*
		 ********************/

		bool mbActorEnableCollision;

		bool mbActorIsBeingDestroyed;

		bool mbActorWantsDestroyDuringBeginPlay;

		/********************
		 *	  Actor State	*
		 ********************/

		enum class eActorPlayState : uint8_t
		{
			None,
			Start,
			Begin,
			End,
		};

		eActorPlayState mActorPlayState;

		/**
		 * Called when another actor begins to overlap this actor, for example a player walking into a trigger.
		 * For events when objects have a blocking collision, for example a player hitting a wall, see 'Hit' events.
		 * @note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
		 */
		
		//	FActorBeginOverlapSignature OnActorBeginOverlap;

		/**
		 * Called when another actor stops overlapping this actor.
		 * @note Components on both this and the other Actor must have bGenerateOverlapEvents set to true to generate overlap events.
		 */
		
		//	FActorEndOverlapSignature OnActorEndOverlap;

		/** Called when the mouse cursor is moved over this actor if mouse over events are enabled in the player controller. */
		
		//	FActorBeginCursorOverSignature OnBeginCursorOver;

		/** Called when the mouse cursor is moved off this actor if mouse over events are enabled in the player controller. */
		
		//	FActorEndCursorOverSignature OnEndCursorOver;

		/** Called when the left mouse button is clicked while the mouse is over this actor and click events are enabled in the player controller. */
		
		//	FActorOnClickedSignature OnClicked;

		/** Called when the left mouse button is released while the mouse is over this actor and click events are enabled in the player controller. */
		
		//	FActorOnReleasedSignature OnReleased;

		/** Called when a touch input is received over this actor when touch events are enabled in the player controller. */
		
		//	FActorOnInputTouchBeginSignature OnInputTouchBegin;

		/** Called when a touch input is received over this component when touch events are enabled in the player controller. */
	
		//	FActorOnInputTouchEndSignature OnInputTouchEnd;

		/** Called when a finger is moved over this actor when touch over events are enabled in the player controller. */
		
		//	FActorBeginTouchOverSignature OnInputTouchEnter;

		/** Called when a finger is moved off this actor when touch over events are enabled in the player controller. */
		
		//	FActorEndTouchOverSignature OnInputTouchLeave;

		/**
		 *	Called when this Actor hits (or is hit by) something solid. This could happen due to things like Character movement, using Set Location with 'sweep' enabled, or physics simulation.
		 *	For events when objects overlap (e.g. walking into a trigger) see the 'Overlap' event.
		 *	@note For collisions during physics simulation to generate hit events, 'Simulation Generates Hit Events' must be enabled.
		 */
		
		//	FActorHitSignature OnActorHit;

	protected:
		/********************
		 *		Time		*
		 ********************/

		uint64_t mPrimaryTick;

		uint64_t mCreationTime;

		uint64_t mLifeSpan;

		uint64_t mLastRenderTime;

		bool mbTickFunctionsRegisterd;

		/********************
		 *		Camera		*
		 ********************/

		bool mbViewTarget;

		bool mbHidden;

		/********************
		 *	   Transform	*
		 ********************/

		struct Vector* mPivotOffset;

		bool mbLockLocation;

		/********************
		 *		Input		*
		 ********************/

		bool mbBlockInput;

		int32_t mInputPriority;

		class Component* mInputComponent;

		bool mbCollideWhenPlacing;

		std::vector<const char*> mTags;

		bool mbCanBeInCluster;

		class Guid* mGuid;

		std::vector<Actor*> mChildren;

		class SeneComponent* mRootCompoent;

		std::vector<class Animation*> mControllingAnimation;

		bool mbHasFinishedSpawning;

		bool mbActorInitailized;

		bool mbActorBeginningPlayFromLevelStreaming;

		bool mbHasDeferredComponentRegistration;

		/********************
		 *		Physics		*
		 ********************/

		bool mbActorEnableCollision;

		bool mbActorIsBeingDestroyed;

		bool mbActorWantsDestroyDuringBeginPlay;

		/********************
		 *	  Actor State	*
		 ********************/

		enum class eActorPlayState : uint8_t
		{
			None,
			Start,
			Begin,
			End,
		};

		eActorPlayState mActorPlayState;

	private:
		/********************
		 *		Actor 		*
		 ********************/

		Actor* mOwner;

		class Pawn* mInstigator;

		const char* mFolderPath;
	};
}