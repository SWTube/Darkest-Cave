/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <string>
#include <unordered_set>

#include "Object/Obejct.h"

namespace cave
{	
	class GameObject;

	class Script : public Object
    {
    public:
        /** Default constructor for Actor. Called Private Initialize(). */
		Script() = delete;
		Script(const Script& other) = delete;
		Script(Script&& other) noexcept;

		virtual ~Script();
		Script& operator=(const Script& other) = delete;
		Script& operator=(Script&& other) noexcept;

		__forceinline const std::string& GetName() const
		{
			return mName;
		}

		virtual void Awake();

		virtual void FixedUpdate();
		virtual void LateUpdate();

		virtual void OnAnimatorIK();
		virtual void OnAnimatorMove();

		virtual void OnApplicationFocus();
		virtual void OnApplicationPause();
		virtual void OnApplicationQuit();

		virtual void OnAudioFilterRead();

		virtual void OnBecameInvisible();
		virtual void OnBecameVisible();

		virtual void OnCollisionEnter();
		virtual void OnCollisionExit();
		virtual void OnCollisionStay();
		virtual void OnControllerColliderHit();

		virtual void OnDestroy();

		virtual void OnDisable();

		virtual void OnDrawGizmos();
		virtual void OnDrawGizmosSelected();

		virtual void OnEnable();

		virtual void OnGUI();

		virtual void OnJointBreak();

		virtual void OnMouseDown();
		virtual void OnMouseDrag();
		virtual void OnMouseEnter();
		virtual void OnMouseExit();
		virtual void OnMouseOver();
		virtual void OnMouseUp();
		virtual void OnMouseUpAsButton();

		virtual void OnParticleCollision();
		virtual void OnParticleSystemStopped();
		virtual void OnParticleTrigger();
		virtual void OnParticleUpdateJobSheduled();

		virtual void OnPostRender();
		virtual void OnPreCull();
		virtual void OnPreRender();
		virtual void OnRenderImage();
		virtual void OnRenderObject();

		virtual void OnTransformChildrenChanged();
		virtual void OnTransformParentChanged();

		virtual void OnTriggerEnter();
		virtual void OnTriggerExit();
		virtual void OnTriggerStay();

		virtual void OnValidate();
		virtual void OnWillRenderObject();

		virtual void Reset();
		virtual void Start();
		virtual void Update();

    private:
		/*Global unique name.*/
		static std::unordered_set<std::string> mGUName;

		/*Script's name.*/
		std::string mName;
    };
}