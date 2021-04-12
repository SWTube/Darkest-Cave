/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "Core/Public/Core.h"
#include "Gameplay/Public/Object/ActorState.h"
#include "Gameplay/Public/Tick/TimeManager.h"

namespace cave
{
    class Actor : public IPhysics
    {
    public:
        /** Default constructor for Actor. Called Private Initialize(). */
        Actor();

        /********************
         *      Actor       *
         ********************/

        Actor* GetOwner() const;

        Pawn* GetInstigator() const;

        void SetFolderPath(const char* newFolderPath);
        const char* GetFolderPath() const;

        void AddTag(const char* tag);
        void RemoveTag(const char* tag);
        bool SearchTag(const char* tag);

        /********************
         *      Physics     *
         ********************/

        void SetCanCollision(bool newCanCollision);
        bool IsCanCollision() const;

        /** Override IPhysics::OnCollsion(). */
        void OnCollision() override;

        /******************
         *      Time      *
         ******************/

        void SetRenderTime(uint64_t& newRenderTime);
        uint64_t GetRenderTime() const;

        void SetLifeState(ActorStateType::Life newLifeState);

        uint64_t GetCreationTime() const;

        /********************
         *      Camera      *
         ********************/

        void SetVisible(bool visible);

        bool IsVisible() const;

        bool IsCameraViewTarget() const;

    protected:
        void SetOwner(Actor* newOwner);

        void SetInstigator(class Pawn* newInstigator);

        void SetCreationTime(uint64_t primary);

        void SetLifeSpan(uint64_t lifeSpan);

        void SetLifeState(ActorStateType::Life lifeState = ActorStateType::Life::Forever);

    private:
        /** Initialized all Actor's members. */
        void initialize();

    protected:
        /******************
         *      Time      *
         ******************/

        class TimeManager* mActorTime;

        uint64_t mCreationTime;

        uint64_t mLastRenderTime;
        
        /** Set once. */
        uint64_t mLifeSpan;

        ActorStateType::Life mLifeState;

        /********************
         *      Camera      *
         ********************/

        bool mbCameraViewTarget;

        bool mbVisible;

        /********************
         *     Transform    *
         ********************/

        Vector2 mPivotOffset;

        bool mbLockLocation;

        /********************
         *      Input       *
         ********************/

        bool mbBlockInput;

        int32_t mInputPriority;

        class Component* mInputComponent;

        /********************
         *      Physics     *
         ********************/

        bool mbCanCollision;


        /********************
         *    Actor State   *
         ********************/

        ActorStateType::Play mPlayState;

        bool mbIsBeingDestroyed;

        bool mbHasFinishedSpawning;

        bool mbInitailized;

        bool mbCanBeInCluster;


        std::vector<Actor*> mChildren;

        class Guid* mGuid;

        class SeneComponent* mRootCompoent;

        std::vector<class Animation*> mControllingAnimation;

    private:
        /********************
         *       Actor      *
         ********************/

        Actor* mOwner;

        class Pawn* mInstigator;

        const char* mFolderPath;

        std::vector<const char*> mTags;

        class Guid* mGuid;
    };
}

struct Vector2
{
    float posX;
    float posY;
};

class IPhysics
{
public:
    virtual ~IPhysics() = 0;

    virtual void OnCollision() = 0;
};