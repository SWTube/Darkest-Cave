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
#ifdef __WIN32__
		DirectX::XMVECTOR upVector;
		DirectX::XMVECTOR positionVector;
		DirectX::XMVECTOR lookAtVector;
#else
		glm::vec3 upVector = glm::vec3(0.0f);
		glm::vec3 positionVector = glm::vec3(0.0f);
		glm::vec3 lookAtVector = glm::vec3(0.0f);
#endif

		float yaw = 0.0f;
		float pitch = 0.0f;
		float roll = 0.0f;
#ifdef __WIN32__
		DirectX::XMMATRIX rotationMatrix;
#else
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
#endif	
		
		// 위쪽을 가리키는 벡터를 설정합니다.
		up.X = 0.0f;
		up.Y = 1.0f;
		up.Z = 0.0f;

#ifdef __WIN32__
		// XMVECTOR 구조체에 로드한다.
		upVector = XMLoadFloat3(&up);
#else
		upVector.x = up.X;
		upVector.y = up.Y;
		upVector.z = up.Z;
#endif

		// 3D월드에서 카메라의 위치를 ​​설정합니다.
		position = mPosition;

#ifdef __WIN32__
		// XMVECTOR 구조체에 로드한다.
		positionVector = XMLoadFloat3(&position);
#else
		positionVector.x = position.X;
		positionVector.y = position.Y;
		positionVector.z = position.Z;
#endif

		// 기본적으로 카메라가 찾고있는 위치를 설정합니다.
		lookAt.X = 0.0f;
		lookAt.Y = 0.0f;
		lookAt.Z = 1.0f;

#ifdef __WIN32__
		// XMVECTOR 구조체에 로드한다.
		lookAtVector = XMLoadFloat3(&lookAt);
#else
		lookAtVector.x = lookAt.X;
		lookAtVector.y = lookAt.Y;
		lookAtVector.z = lookAt.Z;
#endif
		// XMVECTOR 구조체에 로드한다.
		
		// yaw (Y 축), pitch (X 축) 및 roll (Z 축)의 회전값을 라디안 단위로 설정합니다.
		pitch = mRotation.X * 0.0174532925f;
		yaw = mRotation.Y * 0.0174532925f;
		roll = mRotation.Z * 0.0174532925f;

#ifdef __WIN32__
		//  yaw, pitch, roll 값을 통해 회전 행렬을 만듭니다.
		rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

		// lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록 합니다.
		lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
		upVector = XMVector3TransformCoord(upVector, rotationMatrix);

		// 회전 된 카메라 위치를 뷰어 위치로 변환합니다.
		lookAtVector = XMVectorAdd(positionVector, lookAtVector);

		// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
		mView = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
#else
		rotationMatrix = glm::rotate(rotationMatrix, roll, glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, pitch, glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, yaw, glm::vec3(0.0f, 0.0f, 1.0f));

		lookAtVector = glm::vec3(glm::vec4(lookAtVector, 1.0f) * rotationMatrix);
		upVector = glm::vec3(glm::vec4(upVector, 1.0f) * rotationMatrix);

		lookAtVector = positionVector + lookAtVector;

		mView = mView = glm::lookAtLH(positionVector, lookAtVector, upVector);
#endif
	}
} // namespace cave
