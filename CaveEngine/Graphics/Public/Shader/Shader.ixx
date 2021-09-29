module;

#include <filesystem>

#include "GraphicsApiPch.h"

#include "CoreGlobals.h"
//#include "CoreTypes.h"
#include "Memory/MemoryPool.h"

export module cave.Graphics.Shader.Shader;
import cave.Core.Types.Float;
import cave.Core.Types.Vertex;
import Sprite;

namespace cave
{
	export class Shader 
	{

	public:
		struct MatrixBufferType
		{
			DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
			DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
			DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
		};

	public:
		Shader() = delete;
		Shader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool);
		Shader(const std::filesystem::path& shaderFilePath, MemoryPool& pool);
		Shader(const Shader&) = delete;
		Shader(Shader&& other);
		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&& other);
		virtual ~Shader();
		constexpr MemoryPool* GetMemoryPool() const;

		eResult Compile(ID3D11Device* device);
		void Render(ID3D11DeviceContext* context, uint32_t indexCount, uint32_t startIndex, const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture);

		void Destroy();

	protected:
		virtual eResult setLayout(ID3D11Device* device, ID3DBlob* vsBlob, ID3DBlob* psBlob);
		virtual eResult setSamplerState(ID3D11Device* device);
		eResult compileShaderFromFile(const wchar_t* fileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** blobOut);
		
		MemoryPool* mPool = nullptr;
		std::filesystem::path mShaderFilePath = PROJECT_DIR;
		std::filesystem::path mVertexShaderFilePath = PROJECT_DIR;
		std::filesystem::path mFragmentShaderFilePath = PROJECT_DIR;
		
		ID3D11Buffer* mBuffer = nullptr;
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11PixelShader* mPixelShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
		ID3D11SamplerState* mSamplerLinear = nullptr;

	};

	Shader::Shader(const std::filesystem::path& vertexShaderFilePath, const std::filesystem::path& fragmentShaderFilePath, MemoryPool& pool)
		: mPool(&pool)
	{
		mVertexShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mFragmentShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mVertexShaderFilePath /= vertexShaderFilePath;
		mFragmentShaderFilePath /= fragmentShaderFilePath;
	}

	Shader::Shader(const std::filesystem::path& shaderFilePath, MemoryPool& pool)
		: mPool(&pool)
	{
		mShaderFilePath /= "CaveEngine\\Graphics\\Shader";
		mShaderFilePath /= shaderFilePath;
		mVertexShaderFilePath = mShaderFilePath;
		mFragmentShaderFilePath = mShaderFilePath;
	}

	Shader::Shader(Shader&& other)
		: mPool(other.mPool)
		, mShaderFilePath(std::move(other.mShaderFilePath))
		, mVertexShaderFilePath(std::move(other.mVertexShaderFilePath))
		, mFragmentShaderFilePath(std::move(other.mFragmentShaderFilePath))
		, mVertexShader(other.mVertexShader)
		, mPixelShader(other.mPixelShader)
	{
		other.mPool = nullptr;
	}

	Shader::~Shader()
	{
		Destroy();
	}

	constexpr MemoryPool* Shader::GetMemoryPool() const
	{
		return mPool;
	}

	Shader& Shader::operator=(Shader&& other)
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
	void Shader::Destroy()
	{

		if (mSamplerLinear != nullptr)
		{
			mSamplerLinear->Release();
			mSamplerLinear = nullptr;
		}

		if (mInputLayout != nullptr)
		{
			mInputLayout->Release();
			mInputLayout = nullptr;
		}

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

		mPool = nullptr;
		mShaderFilePath.clear();
		mVertexShaderFilePath.clear();
		mFragmentShaderFilePath.clear();

	}

	eResult Shader::Compile(ID3D11Device* device)
	{
		// 11. Compile Shaders ---------------------------------------------------------------------------------------------
		ID3DBlob* vsBlob = nullptr;
		eResult error = compileShaderFromFile(mVertexShaderFilePath.c_str(), "VS", "vs_4_0", &vsBlob);
		if (error != eResult::CAVE_OK)
		{
			//LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			vsBlob->Release();
			vsBlob = nullptr;
			return error;
		}

		// Create the vertex shader
		int32_t result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &mVertexShader);
		if (FAILED(result))
		{
			vsBlob->Release();
			vsBlob = nullptr;
			return eResult::CAVE_FAIL;
		}

		// Compile the pixel shader
		ID3DBlob* psBlob = nullptr;
		error = compileShaderFromFile(mFragmentShaderFilePath.c_str(), "PS", "ps_4_0", &psBlob);
		if (error != eResult::CAVE_OK)
		{
			//LOGE(eLogChannel::GRAPHICS, "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.");
			vsBlob->Release();
			psBlob->Release();

			vsBlob = nullptr;
			psBlob = nullptr;
			return error;
		}

		// Create the pixel shader
		result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &mPixelShader);
		if (FAILED(result))
		{
			vsBlob->Release();
			psBlob->Release();

			vsBlob = nullptr;
			psBlob = nullptr;
			return eResult::CAVE_FAIL;
		}
		
		error = setLayout(device, vsBlob, psBlob);

		vsBlob->Release();
		psBlob->Release();

		vsBlob = nullptr;
		psBlob = nullptr;

		if (error != eResult::CAVE_OK)
		{
			return eResult::CAVE_FAIL;
		}

		return setSamplerState(device);
	}

	eResult Shader::setLayout(ID3D11Device* device, ID3DBlob* vsBlob,ID3DBlob* psBlob)
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
				.SemanticName = "TEXCOORD",
				.SemanticIndex = 0,
				.Format = DXGI_FORMAT_R32G32_FLOAT,
				.InputSlot = 0,
				.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
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

	eResult Shader::setSamplerState(ID3D11Device* device)
	{
		int32_t result;
		// Create the constant buffers
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.ByteWidth = sizeof(MatrixBufferType);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		//bufferDesc.CPUAccessFlags = 0;
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
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

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

	void Shader::Render(ID3D11DeviceContext* context, uint32_t indexCount,uint32_t startIndex , const DirectX::XMMATRIX& worldMatrix, const DirectX::XMMATRIX& viewMatrix, const DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture)
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

		//텍스쳐 세팅.
		context->PSSetShaderResources(0, 1, &texture);

		context->IASetInputLayout(mInputLayout);

		context->VSSetShader(mVertexShader, nullptr, 0);
		context->PSSetShader(mPixelShader, nullptr, 0);

		context->PSSetSamplers(0, 1, &mSamplerLinear);

		context->DrawIndexed(indexCount, startIndex, 0);
	}

	//--------------------------------------------------------------------------------------
	// Helper for compiling shaders with D3DCompile
	//
	// With VS 11, we could load up prebuilt .cso files instead...
	//--------------------------------------------------------------------------------------
	eResult Shader::compileShaderFromFile(const wchar_t* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		// szFileName ���� �̸�
		// szEntryPoint �� ������ � �Լ� �������ҰŴ�
		// szShaderModel ���̴� ��
		HRESULT hResult = S_OK;

		// ������ �ɼ�
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef CAVE_BUILD_DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		// �̰� ���� ������. ���̴� ������� �� ���� ��. �����ϸ� �ϱ� ������ ���� �������� �������� ����� ����

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* pErrorBlob = nullptr;

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