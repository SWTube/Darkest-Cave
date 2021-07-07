/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#ifdef __WIN32__
#include "GraphicsApiPch.h"

#include "CoreTypes.h"
#include "Sprite/GenericSprite.h"

namespace cave
{
	class WindowsSprite : public GenericSprite
	{
	public:
		WindowsSprite() = delete;
		WindowsSprite(Texture* texture, MemoryPool& pool);
		WindowsSprite(const Texture& texture, MemoryPool& pool);
		WindowsSprite(Texture&& texture, MemoryPool& pool);
		WindowsSprite(const WindowsSprite& object);
		WindowsSprite(WindowsSprite&& object);
		WindowsSprite& operator=(const WindowsSprite& object);
		WindowsSprite& operator=(WindowsSprite&& object);
		virtual ~WindowsSprite();

		void Destroy() override;
		void Update() override;
		void Render() override;

		void SetMultiSprite(int frameCount, int framesPerSecond);

	private:
		eResult initializeBuffers(ID3D11Device* device, ID3D11DeviceContext* context) override;
		ID3D11Device* mDevice = nullptr;
		ID3D11DeviceContext* mContext = nullptr;
		ID3D11Buffer* mVertexBuffer = nullptr;
		ID3D11Buffer* mIndexBuffer = nullptr;
		ID3D11InputLayout* mVertexLayout = nullptr;
		ID3D11ShaderResourceView* mTextureRv = nullptr;
		

		////스프라이트 시트, 애니메이션 재생 관련 변수.
		//bool mbIsMultiSprite = false;
		//int mFrame = 0;
		//int mFrameCount = 0;
		//float mTimePerFrame = 0;
		//float mTotalElapsed = 0;
		//float mDividedTexture = 1;

		//float tempElapsed = 0; // (임시)업데이트 간 간격

	};

	typedef WindowsSprite Sprite;
} // namespace cave
#endif