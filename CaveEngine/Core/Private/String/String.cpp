/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "String/String.h"

namespace cave
{
	template <size_t N>
	FORCEINLINE constexpr size_t GetSufficientCapacity(size_t length)
	{
		assert(length <= SIZE_MAX - 1ul - N);

		return (length + 1ul + N - 1ul) - ((length + 1ul + N - 1ul) % N);
	}
	// Constructor

	/**
	 *
  	 * @brief (1) Default constructor.
	 * @details Constructs empty string (zero size and zero capacity). Memory pool is obtained from the Core Memory Pool.
	 * 			@n@n
	 * 			Complexity: constant
	 *
	 */
	String::String() noexcept(noexcept(gCoreMemoryPool))
		: String(ALIGNED_BYTE, '\0', *mPool)
	{
	}

	/**
	 *
  	 * @brief (1) Default constructor.
	 * @details Constructs empty string (zero size and zero capacity). Memory pool is obtained from the Core Memory Pool.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	String::String(MemoryPool& pool) noexcept
		: String(ALIGNED_BYTE, '\0', pool)
	{
	}

	/**
	 *
  	 * @brief (2) Constructs the string with count copies of character ch.
	 * @details Complexity: linear in count
	 * @param count size of the resulting string
	 * @param ch value to initialize the string with
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	String::String(size_t count, char ch, MemoryPool& pool)
		: mPool(&pool)
		, mLength(count)
		, mCapacity(GetSufficientCapacity<ALIGNED_BYTE>(mLength))
		, mString(static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char))))
	{
		memset(mString, ch, mLength);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}

	/**
	 *
  	 * @brief (3) Constructs the string with a substring [pos, pos+count) of other.
	 * @details If count == NPOS, if count is not specified, or if the requested substring lasts past the end of the string,
	 * 			the resulting substring is [pos, other.GetLength()).
	 * 			@n@n
	 * 			Complexity: linear in count
	 * @param other another string to use as source to intialize the string with
	 * @param pos position of the first character to include
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	String::String(const String& other, size_t pos, MemoryPool& pool)
		: String(other, pos, NPOS, pool)
	{
	}

	/**
	 *
  	 * @brief (3) Constructs the string with a substring [pos, pos+count) of other.
	 * @details If count == NPOS, if count is not specified, or if the requested substring lasts past the end of the string,
	 * 			the resulting substring is [pos, other.GetLength()).
	 * 			@n@n
	 * 			Complexity: linear in count
	 * @param other another string to use as source to intialize the string with
	 * @param pos position of the first character to include
	 * @param count size of the resulting string
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	String::String(const String& other, size_t pos, size_t count, MemoryPool& pool)
		: mPool(&pool)
		, mLength(other.mLength)
		, mCapacity(other.mCapacity)
		, mString(static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char))))
	{
		if (count == NPOS || other.mLength < count)
		{
			count = other.mLength;	
		}

		// Copy s to mString
		strncpy(mString, &other.mString[pos], count);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}
	
	/**
	 *
  	 * @brief (4) Constructs the string with the first count characters of character string pointed to by s.
	 * @details s can contain null characters.
	 * 			The length of the string is count.
	 * 			The behavior is undefined if [s, s + count) is not a valid range.
	 * 			@n@n
	 * 			Complexity: linear in count
	 * @param s	pointer to an array of characters to use as source to initialize the string with 
	 * @param count size of the resulting string
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	constexpr String::String(const char* s, size_t count, MemoryPool& pool)
		: mPool(&pool)
	{
		assert(s != nullptr);

		mLength = count;
		mCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mLength);
		mString = static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char)));

		if (count == NPOS || strlen(s) < count)
		{
			count = strlen(s);
		}

		// Copy s to mString
		strncpy(mString, s, count);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}

	/**
	 *
  	 * @brief (5) Constructs the string with the contents initialized with a copy of the null-terminated character string pointed to by s.
	 * @details The length of the string is determined by the first null character.
	 * 			The behavior is undefined if [s, s + strlen(s)) is not a valid range (for example, if s is a null pointer).
	 * 			@n@n
	 * 			Complexity: linear in length of s
	 * @param s	pointer to an array of characters to use as source to initialize the string with 
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	constexpr String::String(const char* s, MemoryPool& pool)
		: mPool(&pool)
	{
		assert (s != nullptr);

		// Allocate Memory
		mLength = strlen(s);
		mCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mLength);
		mString = static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char)));

		// Copy s to mString
		strncpy(mString, s, mLength);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}

	/**
	 *
  	 * @brief (6) Constructs the string with the contents of the range [first, last).
	 * @details Complexity: linear in distance between first and last
	 * @param first	range to copy the characters from
	 * @param last range to copy the characters from
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	constexpr String::String(const char* first, const char* last, MemoryPool& pool)
		: mPool(&pool)
	{
		assert(first != nullptr && last != nullptr);

		// Allocate Memory
		const char* temp = first;
		for (; temp != last; ++temp, ++mLength)
		{
		}

		mCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mLength);
		mString = static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char)));

		memcpy(mString, first, mLength);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}

	/**
	 *
  	 * @brief (7) Copy constructor.
	 * @details Constructs the string with a copy of the contents of other.
	 * 			@n@n
	 * 			Complexity: linear in size of other
	 * @param other	another string to use as source to initialize the string with
	 *
	 */
	constexpr String::String(const String& other)
		: String(other, *other.mPool)
	{
	}

	/**
	 *
  	 * @brief (7) Copy constructor.
	 * @details Constructs the string with a copy of the contents of other.
	 * 			@n@n
	 * 			Complexity: linear in size of other
	 * @param other	another string to use as source to initialize the string with
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	constexpr String::String(const String& other, MemoryPool& pool)
		: mPool(&pool)
		, mLength(other.mLength)
		, mCapacity(other.mCapacity)
	{
		mString = static_cast<char*>(mPool->Allocate((mCapacity) * sizeof(char)));
		strncpy(mString, other.mString, mLength);
		memset(&mString[mLength], '\0', mCapacity - mLength);
	}

	/**
	 *
  	 * @brief (8) Move constructor.
	 * @details Constructs the string with the contents of other using move semantics.
	 * 			other is left in valid, but unspecified state.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param other	another string to use as source to initialize the string with
	 *
	 */
	constexpr String::String(const String&& other) noexcept
		: String(std::move(other), *other.mPool)
	{
	}

	/**
	 *
  	 * @brief (8) Move constructor.
	 * @details Constructs the string with the contents of other using move semantics.
	 * 			other is left in valid, but unspecified state.
	 * 			@n@n
	 * 			Complexity: constant. If <code>pool</pool> is given and <code>pool != other.pool</code>, then linear
	 * @param other	another string to use as source to initialize the string with
	 * @param pool memory pool to use for all memory allocations of this string
	 *
	 */
	constexpr String::String(const String&& other, MemoryPool& pool)
		: mPool(&pool)
		, mLength(other.mLength)
		, mCapacity(other.mCapacity)
		, mString(other.mString)
	{
	}

	/**
	 *
  	 * @brief destroys the string, deallocating internal storage if used
	 *
	 */
	String::~String()
	{
		mPool->Deallocate(mString, mCapacity * sizeof(char));
	}

	/**
	 *
  	 * @brief Returns the associated memory pool 
	 * @details Returns the memory pool associated with the string. 
	 * 			@n@n
	 * 			Complexity: constant
	 * @return The associated memory pool
	 *
	 */
	constexpr const MemoryPool& String::GetMemoryPool() const
	{
		return *mPool;
	}


	// Element Access

	/**
	 *
  	 * @brief Accesses the specified character
	 * @details Returns a reference to the character at specified location pos.
	 * 			No bounds checking is performed. If pos > size(), the behavior is undefined.@n
	 * 			If pos == mLength, a reference to the last character (the null character) is returned.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pos position of the character to return
	 * @return Reference to the requested character.
	 *
	 */
	constexpr char& String::operator[](size_t pos)
	{
		if (pos >= mLength)
		{
			pos = mLength;
		}

		return mString[pos];
	}

	/**
	 *
  	 * @brief Accesses the specified character
	 * @details Returns a reference to the character at specified location pos.
	 * 			No bounds checking is performed. If pos > size(), the behavior is undefined.@n
	 * 			If pos == mLength, a reference to the last character (the null character) is returned.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pos position of the character to return
	 * @return Reference to the requested character.
	 *
	 */
	constexpr const char& String::operator[](size_t pos) const
	{
		if (pos >= mLength)
		{
			pos = mLength;
		}

		return mString[pos];
	}

	/**
	 *
  	 * @brief Accesses the first character 
	 * @details Returns reference to the first character in the string.
	 * 			Assertion fail occurs if <code>IsEmpty() == true<code>
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the first character, equivalent to <code>operator[](0)</code>.
	 *
	 */
	constexpr char& String::GetFront()
	{
		assert(mString != nullptr);

		return mString[0];
	}

	/**
	 *
  	 * @brief Accesses the first character 
	 * @details Returns reference to the first character in the string.
	 * 			Assertion fail occurs if <code>IsEmpty() == true<code>
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the first character, equivalent to <code>operator[](0)</code>.
	 *
	 */
	constexpr const char& String::GetFront() const
	{
		assert(mString != nullptr);

		return mString[0];
	}

	/**
	 *
  	 * @brief Accesses the last character 
	 * @details Returns reference to the last character in the string.
	 * 			Assertion fail occurs if <code>IsEmpty() == true<code>
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the last character, equivalent to <code>operator[](GetLength() - 1)</code>.
	 *
	 */
	constexpr char& String::GetBack()
	{
		assert(mString != nullptr);

		return mString[mLength - 1];
	}

	/**
	 *
  	 * @brief Accesses the last character 
	 * @details Returns reference to the last character in the string.
	 * 			Assertion fail occurs if <code>IsEmpty() == true<code>
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the last character, equivalent to <code>operator[](GetLength() - 1)</code>.
	 *
	 */
	constexpr const char& String::GetBack() const
	{
		assert(mString != nullptr);

		return mString[mLength - 1];
	}

	/**
	 *
  	 * @brief Returns a non-modifiable standard C character array version of the string
	 * @details Returns a pointer to a null-terminated character array with data equivalent to those stored in the string.@n
	 * 			The pointer is such that the range [GetCString(); GetCString() + GetLength()] is valid and the values in it correspond to the values stored in the string 
	 * 			with an additional null character after the last position.
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Pointer to the underlying character storage.@n
	 * 			<code>GetCString() + i == std::addressof(operator[](i))</code> for every <code>i</code> in <code>[0, GetLength()]</code>.
	 *
	 */
	const char* String::GetCString() const
	{
		return mString;
	}

	/**
	 *
  	 * @brief Checks whether the string is empty 
	 * @details Checks if the string has no characters.
	 * 			@n@n
	 * 			Complexity: constant
	 * @return <code>true</code> if the string is empty, <code>false</code> otherwise 
	 *
	 */
	[[nodiscard]] constexpr bool String::IsEmpty() const noexcept
	{
		return mLength == 0ul;
	}

	/**
	 *
  	 * @brief Returns the number of characters 
	 * @details Returns the number of <code>char</code> elements in the string
	 * 			@n@n
	 * 			Complexity: constant
	 * @return The number of <code>char</code> elements in the string. 
	 *
	 */
	constexpr size_t String::GetLength() const noexcept
	{
		return mLength;
	}

	/**
	 *
  	 * @brief Returns the number of characters that can be held in currently allocated storage 
	 * @details Returns the number of characters that the string has currently allocated space for.
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Capacity of the currently allocated storage, i.e. the storage available for storing elements.
	 *
	 */
	constexpr size_t String::GetCapacity() const noexcept
	{
		return mCapacity;
	}

	/**
	 *
  	 * @brief Reduces memory usage by freeing unused memory
	 * @details Requests the removal of unused capacity.@n
	 * 			It is a non-binding request to reduce GetCapacity() to GetSize(). It depends on the implementation if the request is fulfilled.@n
	 * 			If (and only if) reallocation takes place, all pointers, references, and iterators are invalidated.
	 * 			@n@n
	 * 			Complexity: linear in the size of the string
	 *
	 */
	constexpr void String::Shrink()
	{
		size_t fitCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mLength);
		if (mCapacity != fitCapacity)
		{
			char* newString = static_cast<char*>(mPool->Allocate(fitCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', fitCapacity - mLength);
			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mCapacity = fitCapacity;
			mString = newString;
		}
	}

	/**
	 *
  	 * @brief Clears the contents 
	 * @details Removes all characters from the string.@n
	 * 			All pointers, references, and iterators are invalidated. 
	 * 			@n@n
	 * 			Complexity: Linear in the size of the string, although existing implementations operate in constant time.
	 * @note Current implementation do not change capacity. This means that they do not release the allocated memory
	 *
	 */
	constexpr void String::Clear() noexcept
	{
		mLength = 0ul;
	}

	/**
	 *
  	 * @brief (1) Inserts characters 
	 * @details Inserts count copies of character ch at the position index
	 * @param index position at which the content will be inserted
	 * @param ch character to insert
	 * @param count number of characters to insert
	 * @return true if insertion succeeds, false otherwise.
	 *
	 */
	constexpr bool String::InsertAt(size_t index, size_t count, char ch)
	{
		if (index > mLength)
		{
			return false;
		}

		if (index + count + 1 >= mCapacity)
		{
			size_t newLength = mLength + count;
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
#endif
			char* newString = static_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', newCapacity - mLength);

			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mString = newString;
			mLength = newLength;
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i >= index; --i)
		{
			mString[i + count] = mString[i];
		}

		memset(&mString[index], ch, count);

		return true;
	}

	/**
	 *
  	 * @brief (2) Inserts characters 
	 * @details Inserts null-terminated character string pointed to by s at the position index. 
	 * 			The length of the string is determined by the first null character using strlen(s).
	 * @param index position at which the content will be inserted
	 * @param s pointer to the character string to insert
	 * @return true if insertion succeeds, false otherwise.
	 *
	 */
	constexpr bool String::InsertAt(size_t index, const char* s)
	{
		if (s == nullptr)
		{
			return false;
		}

		return InsertAt(index, s, strlen(s));
	}

	/**
	 *
  	 * @brief (3) Inserts characters 
	 * @details Inserts the characters in the range [s, s+count) at the position index. 
	 * 			The range can contain null characters.
	 * @param index position at which the content will be inserted
	 * @param count number of characters to insert
	 * @param s pointer to the character string to insert
	 * @return true if insertion succeeds, false otherwise.
	 *
	 */
	constexpr bool String::InsertAt(size_t index, const char* s, size_t count)
	{
		if (index > mLength || s == nullptr)
		{
			return false;
		}

		if (index + count + 1 >= mCapacity)
		{
			size_t newLength = mLength + count;
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
#endif
			char* newString = static_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', newCapacity - mLength);

			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mString = newString;
			mLength = newLength;
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i >= index; --i)
		{
			mString[i + count] = mString[i];
		}

		strncpy(&mString[index], s, count);

		return true;
	}

	/**
	 *
  	 * @brief (4) Inserts characters 
	 * @details Inserts string str at the position index
	 * @param index position at which the content will be inserted
	 * @param str string to insert
	 * @return true if insertion succeeds, false otherwise.
	 *
	 */
	constexpr bool String::InsertAt(size_t index, const String& str)
	{
		if (index > mLength)
		{
			return false;
		}

		if (index + str.mLength + 1 >= mCapacity)
		{
			size_t newLength = mLength + str.mLength;
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
#endif
			char* newString = static_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', mCapacity - mLength);

			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mString = newString;
			mLength = newLength;
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i >= index; --i)
		{
			mString[i + str.mLength] = mString[i];
		}

		strncpy(&mString[index], str.mString, str.mLength);

		return true;
	}

	/**
	 *
  	 * @brief (5) Inserts characters 
	 * @details Inserts a string, obtained by str.GetSubstring(indexStr, count) at the position index
	 * @param index position at which the content will be inserted
	 * @param count number of characters to insert
	 * @param str string to insert
	 * @param indexStr position of the first character in the string str to insert
	 * @return true if insertion succeeds, false otherwise.
	 *
	 */
	constexpr bool String::InsertAt(size_t index, const String& str, size_t indexStr, size_t count)
	{
		if (index > mLength || indexStr > str.mLength)
		{
			return false;
		}

		if (index + str.mLength + 1 >= mCapacity)
		{
			size_t newLength = mLength + str.mLength;
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
#endif
			char* newString = static_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', mCapacity - mLength);

			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mString = newString;
			mLength = newLength;
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i >= index; --i)
		{
			mString[i + str.mLength] = mString[i];
		}

		strncpy(&mString[index], &str.mString[indexStr], count);

		return true;
	}

	/**
	 *
  	 * @brief Removes characters
	 * @details Removes min(count, GetLength() - index) characters starting at index.
	 * @param index first character to remove
	 * @param count number of characters to remove
	 * @return true if removal succeeds, false otherwise.
	 *
	 */
	constexpr bool String::RemoveAt(size_t index, size_t count)
	{
		if (index + count > mLength)
		{
			return false;
		}

		// // Reallocate memory
		// char* newString = static_cast<char*>(mPool->Allocate((mLength + 1) * sizeof(char)));
		// strncpy(newString, mString, mLength);

		// Moves characters forward to delete a character
		// for (; newString[index] != '\0'; ++index)
		// {
		// 	newString[index] = newString[index + 1];
		// }
		for (; mString[index] != '\0'; ++index)
		{
			mString[index] = mString[index + count];
		}

		// // Reallocate memory
		// mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
		// --mLength;
		// mString = static_cast<char*>(mPool->Allocate((mLength + 1) * sizeof(char)));
		// strncpy(mString, newString, mLength);
		// mPool->Deallocate(mString, ((mLength + 1) + 1) * sizeof(char));
		return true;
	}

	/**
	 *
  	 * @brief Appends a character to the end
	 * @details Appends the given character ch to the end of the string.
	 * 			@n@n
	 * 			Complexity: amortized constant
	 * @param ch the character to append
	 *
	 */
	constexpr void String::PushBack(char ch)
	{
		if (ch == '\0')
		{
			return;
		}

		if (mLength + 1 >= mCapacity)
		{
			// Reallocate memory
			size_t newLength = mLength + 1;
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
#endif
			char* newString = static_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));

			// Copy s to mString
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', newCapacity - newLength);
			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mString = newString;
			mLength = newLength;
			mCapacity = newCapacity;
		}

		mString[mLength] = ch;
		++mLength;
	}

	/**
	 *
  	 * @brief Removes the last character
	 * @details Removes the last character from the string.
	 * 			@n@n
	 * 			Complexity: constant
	 *
	 */
	constexpr void String::PopBack()
	{
		if (mLength > 0ul)
		{
			--mLength;
		}
	}


	/**
	 *
  	 * @brief (1) Appends characters to the end
	 * @details Appends count copies of character ch
	 * 			@n@n
	 * 			Complexity: constant
	 * @param count number of characters to append
	 * @param ch character value to append
	 *
	 */
	constexpr void String::Append(size_t count, char ch)
	{
		InsertAt(mLength, count, ch);
	}

	/**
	 *
  	 * @brief (2) Appends characters to the end
	 * @details Appends string str
	 * 			@n@n
	 * 			Complexity: constant
	 * @param str string to append
	 *
	 */
	constexpr void String::Append(const String& str)
	{
		InsertAt(mLength, str);
	}

	/**
	 *
  	 * @brief (3) Appends characters to the end
	 * @details Appends a substring [pos, pos+count) of str. 
	 * 			If the requested substring lasts past the end of the string, or if count == NPOS, the appended substring is [pos, GetLength()). 
	 * 			@n@n
	 * 			Complexity: constant
	 * @param count number of characters to append
	 * @param pos the index of the first character to append
	 * @param str string to append
	 *
	 */
	constexpr void String::Append(const String& str, size_t pos, size_t count)
	{
		InsertAt(mLength, str, pos, count);
	}

	/**
	 *
  	 * @brief (4) Appends characters to the end
	 * @details Appends characters in the range <code>[s, s + count)</code>. 
	 * 			This range can contain null characters.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param count number of characters to append
	 * @param s pointer to the character string to append
	 *
	 */
	constexpr void String::Append(const char* s, size_t count)
	{
		InsertAt(mLength, s, count);
	}

	/**
	 *
  	 * @brief (5) Appends characters to the end
	 * @details Appends the null-terminated character string pointed to by s. 
	 * 			The length of the string is determined by the first null character using <code>strlen(s)</code>. 
	 * 			@n@n
	 * 			Complexity: constant
	 * @param s pointer to the character string to append
	 *
	 */
	constexpr void String::Append(const char* s)
	{
		InsertAt(mLength, s);
	}

	String String::operator+(const String& rhs) const
	{
		String s(mString);

		// Append other to s
		s.Append(rhs.mString);

		return String(s.mString);
	}

	int32_t String::IndexOf(const char* s)
	{
		if (s == nullptr)
		{
			return -1;
		}

		if (*s == '\0')
		{
			return 0;
		}

		char* temp = mString;
		unsigned int index = 0;
		const char* checkS;

		while (true)
		{
			checkS = s;
			// Find first index of mString that either is NULL or is same to first character of s
			for (; *temp != '\0' && *temp != *checkS; ++temp, ++index)
			{
			}

			// Fail. No identical first letter character
			if (*temp == '\0')
			{
				return -1;
			}

			// Check whether s and rest of characters of mString resembles
			for (; *temp != '\0' && *temp == *checkS; ++temp, ++checkS)
			{
			}

			// Success. Resembles
			if (*checkS == '\0')
			{
				return static_cast<int32_t>(index);
			}

			++index;
		}
	}

	int32_t String::LastIndexOf(const char* s)
	{
		if (s == nullptr)
		{
			return -1;
		}
		
		if (*s == '\0')
		{
			if (mLength > 0)
			{
				return mLength;
			}

			return 0;
		}

		if (*mString == '\0')
		{
			return -1;
		}

		char* temp = mString + mLength - 1;
		unsigned int index = mLength - 1;
		const char* checkS = s;
		char* firstCharacter;

		while (true)
		{
			checkS = s;
			// Find last index of mString that either is first character or is same to first character of s
			for (; temp != (mString - 1) && *temp != *checkS; --temp, --index)
			{
			}

			// Fail. No identical character
			if (temp == (mString - 1))
			{
				return -1;
			}

			firstCharacter = temp;
			// Check whether s and rest of characters of mString resembles
			for (; *firstCharacter != '\0' && *firstCharacter == *checkS; ++firstCharacter, ++checkS)
			{
			}

			// Success. Resembles
			if (*checkS == '\0')
			{
				return static_cast<int32_t>(index);
			}

			--temp;
			--index;
		}
	}

	void String::Interleave(const char* s)
	{
		if (s == nullptr || *s == '\0')
		{
			return;
		}

		// Reallocate memory
		size_t sLength = strlen(s);
		char* newString = static_cast<char*>(mPool->Allocate((mLength + sLength + 1) * sizeof(char)));
		strncpy(newString, mString, mLength + sLength);

		char* newTemp = newString;
		char* temp = mString;
		constexpr bool MSTRING = true;
		constexpr bool S = false;
		bool turn = MSTRING;

		for (; *temp != '\0' || *s != '\0'; ++newTemp)
		{
			if (*temp == '\0' && *s != '\0')
			{
				turn = S;
			}
			else if (*s == '\0' && *temp != '\0')
			{
				turn = MSTRING;
			}

			if (turn == MSTRING)
			{
				*newTemp = *temp;
				++temp;
				turn = S;
			}
			else if (turn == S)
			{
				*newTemp = *s;
				++s;
				turn = MSTRING;
			}
		}
		++*newTemp = '\0';

		// Reassign mString
		mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
		mLength += sLength;
		mString = static_cast<char*>(mPool->Allocate((mLength + 1) * sizeof(char)));
		strncpy(mString, newString, mLength);
		mPool->Deallocate(newString, (mLength + 1) * sizeof(char));
	}

	bool String::operator==(const String& str) const
	{
		if (mLength != str.mLength)
		{
			return false;
		}

		char* temp = mString;
		const char* comp = str.mString;
		if (comp != nullptr)
		{
			for (; *temp == *comp && *temp != '\0' && *comp != '\0'; ++temp, ++comp)
			{
			}

			if (*temp == '\0' && *comp == '\0')
			{
				return true;
			}
		}
		return false;
	}

	String& String::operator=(const String& str)
	{
		if (str.mString != mString)
		{
			if (mLength > 0)
			{
				if (mString != nullptr)
				{
					mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
				}
			}

			if (str.mLength > 0)
			{
				if (mString != nullptr)
				{
					mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
				}
				mLength = str.mLength;
				mString = static_cast<char*>(mPool->Allocate((mLength + 1) * sizeof(char)));
				strncpy(mString, str.mString, mLength);
			}
		}

		return *this;
	}

	String& String::operator=(const char* s)
	{
		if (s != mString)
		{
			if (mLength > 0)
			{
				if (mString != nullptr)
				{
					mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
				}
			}

			size_t sLength = strlen(s);

			if (sLength > 0)
			{
				if (mString != nullptr)
				{
					mPool->Deallocate(mString, (mLength + 1) * sizeof(char));
				}
				mLength = sLength;
				mString = static_cast<char*>(mPool->Allocate((mLength + 1) * sizeof(char)));
				strncpy(mString, s, mLength);
			}
		}

		return *this;
	}

	String& String::operator+=(const String& str)
	{
		Append(str.mString);

		return *this;
	}

	String& String::operator+=(const char* s)
	{
		Append(s);

		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		os << str.mString;

		return os;
	}
} // namespace cave