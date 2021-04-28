/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Debug/Log.h"
#include "Shader/WindowsShader.h"

#ifdef __WIN32__
namespace cave
{
	WindowsShader::~WindowsShader()
	{
		delete[] mVertexShaderFilePath;
		delete[] mFragmentShaderFilePath;
	}

	eResult WindowsShader::Compile(ID3D11Device* device)
	{
		// 11. Compile Shaders ---------------------------------------------------------------------------------------------
		std::filesystem::path shaderPath = PROJECT_DIR;
		shaderPath += "/CaveEngine/Graphics/Shader/";
		shaderPath += mShaderFilePath;

		ID3DBlob* vsBlob = nullptr;
		eResult error = compileShaderFromFile(shaderPath.c_str(), "VS", "vs_4_0", &vsBlob);
		if (error != eResult::CAVE_OK)
		{
			LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			return error;
		}

		// Create the vertex shader
		int32_t result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &mVertexShader);
		if (FAILED(result))
		{
			vsBlob->Release();
			return eResult::CAVE_FAIL;
		}

		// Compile the pixel shader
		ID3DBlob* psBlob = nullptr;
		error = compileShaderFromFile(shaderPath.c_str(), "PS", "ps_4_0", &psBlob);
		if (error != eResult::CAVE_OK)
		{
			LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			return error;
		}

		// Create the pixel shader
		result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &mPixelShader);
		psBlob->Release();
		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}

		return eResult::CAVE_OK;
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