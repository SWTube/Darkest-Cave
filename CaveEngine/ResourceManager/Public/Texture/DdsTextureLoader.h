/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreMinimal.h"

#include <algorithm>
#include <memory>

#ifdef __clang__
	#pragma clang diagnostic ignored "-Wcovered-switch-default"
	#pragma clang diagnostic ignored "-Wswitch-enum"
#endif

#ifdef __WIN32__
#pragma pack(pop)


namespace cave
{
	namespace DdsTextureLoader
	{
		//--------------------------------------------------------------------------------------
		// File: DDSTextureLoader.h
		//
		// Functions for loading a DDS texture and creating a Direct3D runtime resource for it
		//
		// Note these functions are useful as a light-weight runtime loader for DDS files. For
		// a full-featured DDS file reader, writer, and texture processing pipeline see
		// the 'Texconv' sample and the 'DirectXTex' library.
		//
		// Copyright (c) Microsoft Corporation.
		// Licensed under the MIT License (MIT).
		// Licensed under the MIT License.
		//
		// http://go.microsoft.com/fwlink/?LinkId=248926
		// http://go.microsoft.com/fwlink/?LinkId=248929
		//--------------------------------------------------------------------------------------

#ifndef DDS_ALPHA_MODE_DEFINED
    #define DDS_ALPHA_MODE_DEFINED
		enum DDS_ALPHA_MODE : uint32_t
		{
			DDS_ALPHA_MODE_UNKNOWN = 0,
			DDS_ALPHA_MODE_STRAIGHT = 1,
			DDS_ALPHA_MODE_PREMULTIPLIED = 2,
			DDS_ALPHA_MODE_OPAQUE = 3,
			DDS_ALPHA_MODE_CUSTOM = 4,
		};
#endif

		// Standard version
		_Use_decl_annotations_
		HRESULT CreateDDSTextureFromMemory(
			_In_ ID3D11Device* d3dDevice,
			_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
			_In_ size_t ddsDataSize,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_In_ size_t maxsize, 
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;

        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromFile(
			_In_ ID3D11Device* d3dDevice,
			_In_z_ const wchar_t* szFileName,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_In_ size_t maxsize = 0,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr) noexcept;

		// Standard version with optional auto-gen mipmap support
        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromMemory(
			_In_ ID3D11Device* d3dDevice,
			_In_opt_ ID3D11DeviceContext* d3dContext,
			_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
			_In_ size_t ddsDataSize,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_In_ size_t maxsize,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;

        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromFile(
			_In_ ID3D11Device* d3dDevice,
			_In_opt_ ID3D11DeviceContext* d3dContext,
			_In_z_ const wchar_t* szFileName,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_In_ size_t maxsize = 0,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode = nullptr) noexcept;

		// Extended version
        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromMemoryEx(
			_In_ ID3D11Device* d3dDevice,
			_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
			_In_ size_t ddsDataSize,
			_In_ size_t maxsize,
			_In_ D3D11_USAGE usage,
			_In_ unsigned int bindFlags,
			_In_ unsigned int cpuAccessFlags,
			_In_ unsigned int miscFlags,
			_In_ bool forceSRGB,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;

        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromFileEx(
			_In_ ID3D11Device* d3dDevice,
			_In_z_ const wchar_t* szFileName,
			_In_ size_t maxsize,
			_In_ D3D11_USAGE usage,
			_In_ unsigned int bindFlags,
			_In_ unsigned int cpuAccessFlags,
			_In_ unsigned int miscFlags,
			_In_ bool forceSRGB,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;

		// Extended version with optional auto-gen mipmap support
        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromMemoryEx(
			_In_ ID3D11Device* d3dDevice,
			_In_opt_ ID3D11DeviceContext* d3dContext,
			_In_reads_bytes_(ddsDataSize) const uint8_t* ddsData,
			_In_ size_t ddsDataSize,
			_In_ size_t maxsize,
			_In_ D3D11_USAGE usage,
			_In_ unsigned int bindFlags,
			_In_ unsigned int cpuAccessFlags,
			_In_ unsigned int miscFlags,
			_In_ bool forceSRGB,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;
		
        _Use_decl_annotations_
		HRESULT CreateDDSTextureFromFileEx(
			_In_ ID3D11Device* d3dDevice,
			_In_opt_ ID3D11DeviceContext* d3dContext,
			_In_z_ const wchar_t* szFileName,
			_In_ size_t maxsize,
			_In_ D3D11_USAGE usage,
			_In_ unsigned int bindFlags,
			_In_ unsigned int cpuAccessFlags,
			_In_ unsigned int miscFlags,
			_In_ bool forceSRGB,
			_Outptr_opt_ ID3D11Resource** texture,
			_Outptr_opt_ ID3D11ShaderResourceView** textureView,
			_Out_opt_ DDS_ALPHA_MODE* alphaMode) noexcept;
	}
}
#endif