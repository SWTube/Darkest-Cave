/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Debug/Log.h"
#include "Shader/WindowsShader.h"

#ifdef __WIN32__
namespace cave
{
	WindowsShader::WindowsShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool)
		: GenericShader(shaderFilePath, pool)
	{
	}

	WindowsShader::WindowsShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool)
		: GenericShader(vertexShaderFilePath, fragmentShaderFilePath, pool)
	{
	}

	WindowsShader::WindowsShader(WindowsShader&& other)
		: GenericShader(std::move(other))
		, mVertexShader(other.mVertexShader)
		, mPixelShader(other.mPixelShader)
		, mVsBlob(other.mVsBlob)
		, mPsBlob(other.mPsBlob)
	{
	}

	WindowsShader& WindowsShader::operator=(WindowsShader&& other)
	{
		if (this != &other)
		{
			GenericShader::operator=(std::move(other));
			mVertexShader = other.mVertexShader;
			mPixelShader = other.mPixelShader;
			mVsBlob = other.mVsBlob;
			mPsBlob = other.mPsBlob;

			other.mVertexShader->Release();
			other.mPixelShader->Release();
			other.mVsBlob->Release();
			other.mPsBlob->Release();
			
			other.mVertexShader = nullptr;
			other.mPixelShader = nullptr;
			other.mVsBlob = nullptr;
			other.mPsBlob = nullptr;
		}

		return *this;
	}

	WindowsShader::~WindowsShader()
	{
		mVertexShaderFilePath.clear();
		mFragmentShaderFilePath.clear();

		if (mVertexShader != nullptr)
		{
			mVertexShader->Release();
			mVertexShader = nullptr;
		}

		if (mPixelShader != nullptr)
		{
			mPixelShader->Release();
			mPixelShader = nullptr;
		}

		if (mVsBlob != nullptr)
		{
			mVsBlob->Release();
		}

		if (mPsBlob != nullptr)
		{
			mPsBlob->Release();
			mPsBlob = nullptr;
		}
	}

	eResult WindowsShader::Compile(ID3D11Device* device)
	{
		// 11. Compile Shaders ---------------------------------------------------------------------------------------------
		std::filesystem::path shaderPath = PROJECT_DIR;
		shaderPath += "/CaveEngine/Graphics/Shader/";
		shaderPath += mShaderFilePath;

		mVsBlob = nullptr;
		eResult error = compileShaderFromFile(shaderPath.c_str(), "VS", "vs_4_0", &mVsBlob);
		if (error != eResult::CAVE_OK)
		{
			LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			return error;
		}

		// Create the vertex shader
		int32_t result = device->CreateVertexShader(mVsBlob->GetBufferPointer(), mVsBlob->GetBufferSize(), nullptr, &mVertexShader);
		if (FAILED(result))
		{
			mVsBlob->Release();
			return eResult::CAVE_FAIL;
		}

		// Compile the pixel shader
		mPsBlob = nullptr;
		error = compileShaderFromFile(shaderPath.c_str(), "PS", "ps_4_0", &mPsBlob);
		if (error != eResult::CAVE_OK)
		{
			LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			return error;
		}

		// Create the pixel shader
		result = device->CreatePixelShader(mPsBlob->GetBufferPointer(), mPsBlob->GetBufferSize(), nullptr, &mPixelShader);
		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		return eResult::CAVE_OK;
	}

	void WindowsShader::Render(ID3D11DeviceContext* context)
	{
		context->VSSetShader(mVertexShader, nullptr, 0);
		context->PSSetShader(mPixelShader, nullptr, 0);
	}

	ID3DBlob* const WindowsShader::GetVertexShaderBlob()
	{
		return mVsBlob;
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	eResult WindowsShader::compileShaderFromFile(const wchar_t* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		// szFileName ���� �̸�
		// szEntryPoint �� ������ � �Լ� �������ҰŴ�
		// szShaderModel ���̴� ��
		HRESULT hResult = S_OK;

		// ������ �ɼ�
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		// �̰� ���� ������. ���̴� ������� �� ���� ��. �����ϸ� �ϱ� ������ ���� �������� �������� ����� ����

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		// ID3DBlob �ؽ�Ʈ ������ ���𰡸� ������ ��. ���̴� ������ �� ���� �ֳ�...?
		// �̸� ���̴� ������ �صΰ� ��Ÿ�ӿ� ���̴� ���̳ʸ��� �ٷ� Blob�� �������� ������ ���� ����� �� ����
		// ��κ��� ��� ���̴��� �ɼǿ� ���� ������ �ٸ��� �ؾ��� ���� ����
		// �̷� �� ifdef�� ������ ��ÿ� �־��༭ �ٸ��� ���� ����
		ID3DBlob* pErrorBlob = nullptr;

		// GLUTó�� D3DX��� ���� ���̺귯���� ����. 12���� �����
		// MS�� ��� ���� 11���� D3DX ���� ����
		// d3dx���� prod �������� ���־� 12 ������ �� ����
		// ���� �ι�° �Ű������� PDefines�ε� ���⿡ ifdef�� �ش��ϴ� �� �� �־���� �� ����
		// ���̴� ������ ���Ƶ� ������ �� def�� ���� �ٸ� ���̳ʸ� �� ����
		// �Ź� ������ �ٽ��ϸ� �������ϱ� ���̴� ĳ�� ���
		// �� ������ �� ���̴� ������ ���� ������, ���� ���̴� ĳ�ö� ���ؼ�, 
		// ������ / ���빰 �ٲ������ �������ؼ� ���̳ʸ��� ĳ�� �ʿ� ����
		// ���̴� ĳ�� ���̳ʸ��κ��� ���̴� ����
		// ���� ���� ������ �׳� ĳ�ÿ��� �ٷ� �о ����
		hResult = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hResult))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return eResult::CAVE_FAIL;
		}
		if (pErrorBlob)
		{
			pErrorBlob->Release();
		}

		return eResult::CAVE_OK;
	}
}
#endif