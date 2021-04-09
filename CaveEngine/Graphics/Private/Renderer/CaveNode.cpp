/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#include "Renderer/CaveNode.h"
#include "Renderer/CaveApplication.h"

CaveNode::CaveNode() :
	mObjectWidth(0.0f)
	, mObjectHeight(0.0f)
	, mObjectScaleWidth(0.0f)
	, mObjectScaleHeight(0.0f)
	, mObjectLivingTime(0.0f)
	, mParentObject(nullptr)
{
	SetPosition(0.0f, 0.0f);
	SetScale(0.0f, 0.0f);
	SetScalingCenter(0.0f, 0.0f);
	SetRotationCenter(0.0f, 0.0f);
	SetRotationValue(0.0f);

	mObjectGlobalPosition.x = 0.0f;
	mObjectGlobalPosition.y = 0.0f;

	SetHwnd(GetForegroundWindow());
}

CaveNode::~CaveNode()
{
	for (std::vector<CaveNode*>::iterator iter = mChildrenObjects.begin(); iter != mChildrenObjects.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	mNode.clear();
}


void CaveNode::Renderer()
{

}
void CaveNode::Update(float eTime)
{
	mObjectLivingTime += eTime;
	for (NODE::iterator iter = mNode.begin(); iter != mNode.end(); ++iter)
	{
		(*iter)->Update(eTime);
		if ((*iter)->IsErase())
		{
			SAFE_DELETE(*iter);
			iter = mNode.erase(iter);
			if (iter == mNode.end())
			{
				break;
			}
		}
	}

}
void CaveNode::UpdateTransform()
{

}
void CaveNode::UpdateScale()
{

}
void CaveNode::UpdateCameraPos()
{

}
void CaveNode::AddObject(CaveNode* object)
{

}
void CaveNode::RemoveObject(CaveNode* object, bool isRelease)
{

}
bool CaveNode::HasObject(CaveNode* object)
{
	return true;
}
D2D_VECTOR_2F CaveNode::GetPosition() const
{
	return mObjectPosition;
}

void CaveNode::SetPosition(const D2D_VECTOR_2F& position)
{
	mObjectPosition = position;
	UpdateTransform();
}
void CaveNode::SetPosition(const float& x, const float& y)
{
	mObjectPosition.x = x;
	mObjectPosition.y = y;
	UpdateTransform();
}
void CaveNode::SetPositionX(const float& x)
{
	mObjectPosition.x = x;
	UpdateTransform();
}
void CaveNode::SetPositionY(const float& y)
{
	mObjectPosition.y = y;
	UpdateTransform();
}
void CaveNode::AddPosition(const float& x, const float& y)
{
	mObjectPosition.x += x;
	mObjectPosition.y += y;
	UpdateTransform();
}
void CaveNode::AddPositionX(const float& x)
{
	mObjectPosition.x += x;
	UpdateTransform();
}
void CaveNode::AddPositionY(const float& y)
{
	mObjectPosition.y += y;
	UpdateTransform();
}
D2D_VECTOR_2F CaveNode::GetGlobalPosition() const
{
	return mObjectGlobalPosition;
}
D2D_VECTOR_2F CaveNode::GetScale() const
{
	return mObjectScale;
}
void CaveNode::SetScale(const float& scale)
{
	SetScale(scale, scale);
}
void CaveNode::SetScale(const D2D_VECTOR_2F& scale)
{
	SetScale(scale.x, scale.y);
}
void CaveNode::SetScale(const float& x, const float& y)
{
	mObjectScale.x = x;
	mObjectScale.y = y;
	UpdateScale();
}
void CaveNode::AddScale(const float& x, const float& y)
{
	mObjectScale.x += x;
	mObjectScale.y += y;
	UpdateScale();
}
void CaveNode::AddScale(const float& size)
{
	AddScale(size, size);
}
void CaveNode::AddScaleX(const float& x)
{
	mObjectScale.x += x;
	UpdateScale();
}
void CaveNode::AddScaleY(const float& y)
{
	mObjectScale.y += y;
	UpdateScale();
}
D2D_VECTOR_2F CaveNode::GetScalingCenter() const
{
	return mObjectScalingCenter;
}
void CaveNode::SetScalingCenter(const D2D_VECTOR_2F& scale)
{
	mObjectScalingCenter = scale;
}
void CaveNode::SetScalingCenter(const float& x, const float& y)
{
	mObjectScalingCenter.x = x;
	mObjectScalingCenter.y = y;
}
void CaveNode::AddScalingCenter(const float& x, const float& y)
{
	mObjectScalingCenter.x += x;
	mObjectScalingCenter.y += y;
}
D2D_VECTOR_2F CaveNode::RotCenter() const
{
	return mObjectRotationCenter;
}
void CaveNode::SetRotationCenter(const D2D_VECTOR_2F& center)
{
	mObjectRotationCenter = center;
}
void CaveNode::SetRotationCenter(const float& x, const float& y)
{
	mObjectRotationCenter.x = x;
	mObjectRotationCenter.y = y;
}
void CaveNode::AddRotationCenter(const float& x, const float& y)
{
	mObjectRotationCenter.x += x;
	mObjectRotationCenter.y += y;
}
void CaveNode::AddRotationCenterX(const float& x)
{
	mObjectRotationCenter.x += x;
}
void CaveNode::AddRotationCenterY(const float& y)
{
	mObjectRotationCenter.y += y;
}
float CaveNode::GetRotationValue() const {
	return mObjectRotationValue;
}

float CaveNode::GetGlobalRotation() const {
	return 0.0f;
}

void CaveNode::SetRotationValue(float rotationValue) {
	mObjectRotationValue = rotationValue;
}
void CaveNode::AddRot(float rotationValue) {
	mObjectRotationValue += rotationValue;
}
float CaveNode::GetWidth() const {
	return mObjectWidth;
}
float CaveNode::GetScaleWidth() const {
	return mObjectScaleWidth;
}
float CaveNode::GetHeight() const {
	return mObjectHeight;
}
float CaveNode::GetScaleHeight() const {
	return mObjectScaleHeight;
}
CaveNode* CaveNode::Parent() const {
	return mParentObject;
}
bool CaveNode::IsErase() const
{
	return mbErase;
}
void CaveNode::SetErase(bool erase)
{
	mbErase = erase;
}
HWND CaveNode::GetHWnd() const {
	return mHWnd;
}
void CaveNode::SetHwnd(HWND hwnd) {
	mHWnd = hwnd;
}
D2D1_MATRIX_3X2_F CaveNode::GetTransformMatrix() const {
	return mObjecTransformMat;
}