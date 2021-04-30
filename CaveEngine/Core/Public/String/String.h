/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include <iostream>

#include "CoreTypes.h"
#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"
#include "Utils/Crt.h"

namespace cave
{
	/**
	 *
  	 * @brief String stores and manipulates sequences of <code>char</code> objects, 
	 * 			which are non-array objects of 
	 * 			[trivial](https://en.cppreference.com/w/cpp/named_req/TrivialType)
	 * 			[standard-layout](https://en.cppreference.com/w/cpp/named_req/StandardLayoutType) type.
	 * @details The class is dependent on the character type and the nature of operations on that type. 
	 * 			@n@n
	 * 			The elements of a <code>String</code> are stored contiguously, that is, for as <code>String s</code>, 
	 * 			<code>&*(s.GetCString() + n) == &*s.GetString() + n</code> for any <code>n</code> in [0, <code>s.GetLength()</code>], 
	 * 			or equivalently, a pointer to <code>s[0]</code> can be passed to functions that expect a pointer to the first element of a null-terminated
	 * 			char[] array.
	 * @author Alegruz
	 * @date 2021-04-30
	 * @version 0.0.1
	 * @todo check if cave::String satisfies the requirements of 
	 * 			<a href="https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer">AllocatorAwareContainer</a>, 
	 * 			<a href="https://en.cppreference.com/w/cpp/named_req/SequenceContainer">SequenceContainer</a> and 
	 * 			<a href="https://en.cppreference.com/w/cpp/named_req/ContiguousContainer">ContiguousContainer</a>
	 *
	 */
	class String final
	{
		// Non-member functions
			// input / output
		friend std::ostream& operator<<(std::ostream& os, const String& str);
	public:
		String() noexcept(noexcept(gCoreMemoryPool));
		explicit String(MemoryPool& pool) noexcept;
		String(size_t count, char ch, MemoryPool& pool = gCoreMemoryPool);
		String(const String& other, size_t pos, MemoryPool& pool = gCoreMemoryPool);
		String(const String& other, size_t pos, size_t count, MemoryPool& pool = gCoreMemoryPool);
		constexpr String(const char* s, size_t count, MemoryPool& pool = gCoreMemoryPool);
		constexpr String(const char* s, MemoryPool& pool = gCoreMemoryPool);
		constexpr String(const char* first, const char* last, MemoryPool& pool = gCoreMemoryPool);
		constexpr String(const String& other);
		constexpr String(const String& other, MemoryPool& pool);
		constexpr String(const String&& other) noexcept;
		constexpr String(const String&& other, MemoryPool& pool);
		virtual ~String();
		String& operator=(const char* s);
		String& operator=(const String& str);
		constexpr const MemoryPool& GetMemoryPool() const;

		// Element access
		constexpr char& operator[](size_t pos);
		constexpr const char& operator[](size_t pos) const;
		constexpr char& GetFront();
		constexpr const char& GetFront() const;
		constexpr char& GetBack();
		constexpr const char& GetBack() const;
		const char* GetCString() const;

		// Capacity
		[[nodiscard]] constexpr bool IsEmpty() const noexcept;
		constexpr size_t GetLength() const noexcept;
		constexpr size_t GetCapacity() const noexcept;
		constexpr void Shrink();

		// Operations
		constexpr void Clear() noexcept;
		constexpr bool InsertAt(size_t index, size_t count, char ch);
		constexpr bool InsertAt(size_t index, const char* s);
		constexpr bool InsertAt(size_t index, const char* s, size_t count);
		constexpr bool InsertAt(size_t index, const String& str);
		constexpr bool InsertAt(size_t index, const String& str, size_t indexStr, size_t count = NPOS);
		constexpr bool RemoveAt(size_t index = 0, size_t count = NPOS);
		constexpr void PushBack(char ch);
		constexpr void PopBack();
		constexpr void Append(size_t count, char ch);
		constexpr void Append(const String& str);
		constexpr void Append(const String& str, size_t pos, size_t count = NPOS);
		constexpr void Append(const char* s, size_t count);
		constexpr void Append(const char* s);
		String& operator+=(const String& str);
		String& operator+=(const char* s);
		String operator+(const String& rhs) const;
		bool operator==(const String& rhs) const;		

		// Search
		int32_t IndexOf(const char* s);
		int32_t LastIndexOf(const char* s);
		void Interleave(const char* s);

		// Constants
		static constexpr size_t NPOS = -1;

	private:
		static constexpr size_t ALIGNED_BYTE = 8ul;
		MemoryPool* mPool = &gCoreMemoryPool;
		size_t mLength = 0ul;
		size_t mCapacity = 0ul;
		char* mString = nullptr;
	};
} // namespace cave