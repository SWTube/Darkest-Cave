/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module TempObject;

import Point;

namespace cave
{
	export class TempObject final
	{
	public:
		constexpr explicit TempObject(const Point& position, uint32_t data);
		TempObject(const TempObject& other) = delete;
		TempObject(TempObject&& other) = delete;
		TempObject& operator=(const TempObject& other) = delete;
		TempObject& operator=(TempObject&& other) = delete;
		~TempObject() = default;

		constexpr const Point& GetPosition() const;
		constexpr uint32_t GetData() const;
	private:
		const Point mPosition;
		uint32_t mData;
	};

	constexpr TempObject::TempObject(const Point& position, uint32_t data)
		: mPosition(position)
		, mData(data)
	{
	}

	constexpr const Point& TempObject::GetPosition() const
	{
		return mPosition;
	}

	constexpr uint32_t TempObject::GetData() const
	{
		return mData;
	}
}