/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
	class CaveNode
	{
	public:
		CaveNode();
		virtual ~CaveNode();

		virtual void Renderer();
		virtual void Update(float eTime);
		
		void UpdateCameraPos();

		void AddObject(CaveNode* object);
		void RemoveObject(CaveNode* object, bool isRelease = true);
		bool HasObject(CaveNode* object);

		D2D_VECTOR_2F GetPosition() const;
		void SetPosition(const D2D_VECTOR_2F& position);
		void SetPosition(const float& x, const float& y);
		void SetPositionX(const float& x);
		void SetPositionY(const float& y);
		void AddPosition(const float& x, const float& y);
		void AddPositionX(const float& x);
		void AddPositionY(const float& y);
		D2D_VECTOR_2F GetGlobalPosition() const;
		D2D_VECTOR_2F GetScale() const;
		void SetScale(const float& scale);
		void SetScale(const D2D_VECTOR_2F& scale);
		void SetScale(const float& x, const float& y);
		void AddScale(const float& x, const float& y);
		void AddScale(const float& size);
		void AddScaleX(const float& x);
		void AddScaleY(const float& y);
		D2D_VECTOR_2F GetScalingCenter() const;
		void SetScalingCenter(const D2D_VECTOR_2F& scale);
		void SetScalingCenter(const float& x, const float& y);
		void AddScalingCenter(const float& x, const float& y);
		D2D_VECTOR_2F RotCenter() const;
		void SetRotationCenter(const D2D_VECTOR_2F& center);
		void SetRotationCenter(const float& x, const float& y);
		void AddRotationCenter(const float& x, const float& y);
		void AddRotationCenterX(const float& x);
		void AddRotationCenterY(const float& y);
		float GetRotationValue() const;
		float GetGlobalRotation() const;
		void SetRotationValue(float rotationValue);
		void AddRot(float rotationValue);
		float GetWidth() const;
		float GetScaleWidth() const;
		float GetHeight() const;
		float GetScaleHeight() const;
		CaveNode* Parent() const;
		bool IsErase() const;
		void SetErase(bool erase);
		HWND GetHWnd() const;
		void SetHwnd(HWND hwnd);
		D2D1_MATRIX_3X2_F GetTransformMatrix() const;

	protected:
		typedef std::vector<CaveNode*> NODE;
		NODE mNode;

		D2D1_MATRIX_3X2_F mObjecTransformMat;

		D2D_VECTOR_2F mObjectPosition;
		D2D_VECTOR_2F mObjectGlobalPosition;
		D2D_VECTOR_2F mObjectScale;
		D2D_VECTOR_2F mObjectScalingCenter;
		D2D_VECTOR_2F mObjectRotationCenter;
		float mObjectRotationValue;

		float mObjectWidth;
		float mObjectHeight;
		float mObjectScaleWidth;
		float mObjectScaleHeight;

		bool mbErase;

		CaveNode* mParentObject;
		std::vector<CaveNode*> mChildrenObjects;

		HWND mHWnd;

		void UpdateTransform();
		void UpdateScale();

	private:
		float mObjectLivingTime;
	};
#endif