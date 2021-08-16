/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

export module Pair;

namespace cave
{
	export class Pair final
	{
	public:
		constexpr Pair(void* first, void* second);
		constexpr Pair(const Pair& other);
		constexpr Pair(Pair&& other);
		constexpr ~Pair() = default;
		constexpr Pair& operator=(const Pair& other);
		constexpr Pair& operator=(Pair&& other);

		void* GetFirst();
		const void* GetFirst() const;
		void* GetSecond();
		const void* GetSecond() const;

		void SetFirst(void* first);
		void SetSecond(void* second);
	private:
		void* mFirst;
		void* mSecond;
	};

	constexpr Pair::Pair(void* first, void* second)
		: mFirst(first)
		, mSecond(second)
	{
	}

	constexpr Pair::Pair(const Pair& other)
		: mFirst(other.mFirst)
		, mSecond(other.mSecond)
	{
	}

	constexpr Pair::Pair(Pair&& other)
		: mFirst(other.mFirst)
		, mSecond(other.mSecond)
	{
		other.mFirst = nullptr;
		other.mSecond = nullptr;
	}

	constexpr Pair& Pair::operator=(const Pair& other)
	{
		if (this != &other)
		{
			mFirst = other.mFirst;
			mSecond = other.mSecond;
		}

		return *this;
	}

	constexpr Pair& Pair::operator=(Pair&& other)
	{
		if (this != &other)
		{
			mFirst = other.mFirst;
			mSecond = other.mSecond;

			other.mFirst = nullptr;
			other.mSecond = nullptr;
		}

		return *this;
	}

	void* Pair::GetFirst()
	{
		return mFirst;
	}

	const void* Pair::GetFirst() const
	{
		return mFirst;
	}

	void* Pair::GetSecond()
	{
		return mSecond;
	}

	const void* Pair::GetSecond() const
	{
		return mSecond;
	}

	void Pair::SetFirst(void* first)
	{
		mFirst = first;
	}

	void Pair::SetSecond(void* second)
	{
		mSecond = second;
	}
}