module;

#include <filesystem>
#include "GraphicsApiPch.h"

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Graphics.Shader.ColorShader;

import cave.Graphics.Shader.Shader;
import cave.Core.Types.Float;
import cave.Core.Types.Vertex;

namespace cave
{
	export class ColorShader : public Shader
	{
	public:
		ColorShader() = delete;
		ColorShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool);
		ColorShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool);
		ColorShader(const ColorShader&) = delete;
		ColorShader(ColorShader&& other);
		ColorShader& operator=(const ColorShader&) = delete;
		ColorShader& operator=(ColorShader&& other);
		virtual ~ColorShader();

		void Render(ID3D11DeviceContext* context, uint32_t indexCount, uint32_t startIndex, const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix);
	protected:
		eResult setLayout(ID3D11Device* device, ID3DBlob* vsBlob, ID3DBlob* psBlob) override;
		eResult setSamplerState(ID3D11Device* device) override;
	};

	ColorShader::ColorShader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool)
		:Shader(vertexShaderFilePath, fragmentShaderFilePath, pool)
	{

	}

	ColorShader::ColorShader(const std::filesystem::path& shaderFilePath, MemoryPool& pool)
		:Shader(shaderFilePath, pool)
	{

	}

	ColorShader& ColorShader::operator=(ColorShader&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mShaderFilePath = std::move(other.mShaderFilePath);
			mVertexShaderFilePath = std::move(other.mVertexShaderFilePath);
			mFragmentShaderFilePath = std::move(other.mFragmentShaderFilePath);

			mVertexShader = other.mVertexShader;
			mPixelShader = other.mPixelShader;

			other.mVertexShader->Release();
			other.mPixelShader->Release();

			other.mVertexShader = nullptr;
			other.mPixelShader = nullptr;

			other.mPool = nullptr;
		}

		return *this;
	}
	ColorShader::~ColorShader()
	{
		Shader::Destroy();
	}

	void ColorShader::Render(ID3D11DeviceContext* context, uint32_t indexCount, uint32_t startIndex, const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix)
	{
		// 상수 버퍼의 내용을 쓸 수 있도록 잠급니다.
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		if (FAILED(context->Map(mBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
		{
			return;// return false;
		}

		// 상수 버퍼의 데이터에 대한 포인터를 가져옵니다.
		MatrixBufferType* dataPtr = reinterpret_cast<MatrixBufferType*>(mappedResource.pData);

		// 상수 버퍼에 행렬을 복사합니다.
		dataPtr->world = XMMatrixTranspose(worldMatrix);
		dataPtr->view = XMMatrixTranspose(viewMatrix);
		dataPtr->projection = XMMatrixTranspose(projectionMatrix);

		// 상수 버퍼의 잠금을 풉니다.
		context->Unmap(mBuffer, 0);

		// 정점 셰이더에서의 상수 버퍼의 위치를 설정합니다.
		uint32_t bufferNumber = 0;

		// 마지막으로 정점 셰이더의 상수 버퍼를 바뀐 값으로 바꿉니다.
		context->VSSetConstantBuffers(bufferNumber, 1, &mBuffer);


		context->IASetInputLayout(mInputLayout);

		context->VSSetShader(mVertexShader, nullptr, 0);
		context->PSSetShader(mPixelShader, nullptr, 0);

		//context->PSSetSamplers(0, 1, &mSamplerLinear);

		context->DrawIndexed(indexCount, startIndex, 0);
	}

	eResult ColorShader::setLayout(ID3D11Device* device, ID3DBlob* vsBlob, ID3DBlob* psBlob)
	{
		int32_t result;
		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{
				.SemanticName = "POSITION",
				.SemanticIndex = 0,
				.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				.InputSlot = 0,
				.AlignedByteOffset = 0,
				.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0
			},
			{
				.SemanticName = "COLOR",
				.SemanticIndex = 0,
				.Format = DXGI_FORMAT_R32G32B32_FLOAT,
				.InputSlot = 0,
				.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
				.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
				.InstanceDataStepRate = 0
			}
		};

		UINT numElements = ARRAYSIZE(layout);

		// Create the input layout
		result = device->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), &mInputLayout);

		if (FAILED(result))
		{
			return eResult::CAVE_FAIL;
		}


		return eResult::CAVE_OK;
	}
	eResult ColorShader::setSamplerState(ID3D11Device* device)
	{
		int32_t result;
		// Create the constant buffers
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(MatrixBufferType);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		result = device->CreateBuffer(&bufferDesc, nullptr, &mBuffer);

		if (FAILED(result))
		{
			return static_cast<eResult>(result);
		}

		// Create the sample state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		result = device->CreateSamplerState(&samplerDesc, &mSamplerLinear);

		if (FAILED(result))
		{
			return static_cast<eResult>(result);
		}

		return eResult::CAVE_OK;
	}
}