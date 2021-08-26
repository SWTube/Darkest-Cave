/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Renderer/Camera.h"

namespace cave
{
	void Camera::Render()
	{
		Float3 up;
		Float3 position;
		Float3 lookAt;

		DirectX::XMVECTOR upVector;
		DirectX::XMVECTOR positionVector;
		DirectX::XMVECTOR lookAtVector;

		float yaw = 0.0f;
		float pitch = 0.0f;
		float roll = 0.0f;

		DirectX::XMMATRIX rotationMatrix;

		// 위쪽을 가리키는 벡터를 설정합니다.
		up.X = 0.0f;
		up.Y = 1.0f;
		up.Z = 0.0f;

		// XMVECTOR 구조체에 로드한다.
		DirectX::XMFLOAT3 dUp = DirectX::XMFLOAT3(up.X, up.Y, up.Z);
		upVector = DirectX::XMLoadFloat3(&dUp);

		// 3D월드에서 카메라의 위치를 ​​설정합니다.
		position = mPosition;

		// XMVECTOR 구조체에 로드한다.
		DirectX::XMFLOAT3 dPosition = DirectX::XMFLOAT3(position.X, position.Y, position.Z);
		positionVector = DirectX::XMLoadFloat3(&dPosition);

		// 기본적으로 카메라가 찾고있는 위치를 설정합니다.
		lookAt.X = 0.0f;
		lookAt.Y = 0.0f;
		lookAt.Z = 1.0f;

		// XMVECTOR 구조체에 로드한다.
		DirectX::XMFLOAT3 dLookAt = DirectX::XMFLOAT3(lookAt.X, lookAt.Y, lookAt.Z);
		lookAtVector = DirectX::XMLoadFloat3(&dLookAt);

		// XMVECTOR 구조체에 로드한다.
		
		// yaw (Y 축), pitch (X 축) 및 roll (Z 축)의 회전값을 라디안 단위로 설정합니다.
		pitch = mRotation.X * 0.0174532925f;
		yaw = mRotation.Y * 0.0174532925f;
		roll = mRotation.Z * 0.0174532925f;

		//  yaw, pitch, roll 값을 통해 회전 행렬을 만듭니다.
		rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

		// lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록 합니다.
		lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
		upVector = XMVector3TransformCoord(upVector, rotationMatrix);

		// 회전 된 카메라 위치를 뷰어 위치로 변환합니다.
		lookAtVector = DirectX::XMVectorAdd(positionVector, lookAtVector);

		// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
		mView = DirectX::XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	}
} // namespace cave
