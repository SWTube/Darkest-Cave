/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <vector>
#include <string>

#include "Object/Obejct.h"

namespace cave
{
	class Component;
	class StateMachine;
	class Quaternion;
	class Vector3;
	
	class Actor : public Object
	{
	public:
		Actor();
		Actor(const Actor& other);
		Actor(Actor&& other) noexcept;

		virtual ~Actor();
		Actor& operator=(const Actor& other);
		Actor& operator=(Actor&& other);

		void Print();

		void AddComponent(Component& component);
		void RemoveComponent(Component& component);

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
		bool mbEnable;
		bool mbActive;

		bool mbRunInEditMode;
		bool mbGUILayoout;

		StateMachine* mStateMachine;

		Vector3* mPosition;
		Vector3* mScale;
		Quaternion* mRotation;

		std::string mName;
		unsigned int mTag;

		std::vector<Component*> mComponents;
	};
}