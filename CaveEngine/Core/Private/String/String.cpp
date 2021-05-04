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
		: String(gCoreMemoryPool)
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
		: mPool(&pool)
		, mLength(0ul)
		, mCapacity(ALIGNED_BYTE)
		, mString(static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char))))
	{
		memset(mString, '\0', mCapacity);
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
		, mLength(count)
		, mCapacity(other.mCapacity)
		, mString(static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char))))
	{
		assert(other.mString != nullptr);
		
		if (count == NPOS || other.mLength < count)
		{
			count = other.mLength;
		}
		mLength = count;

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
	{
		assert(other.mPool != nullptr && other.mString != nullptr);
		String(other, *other.mPool);
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
		assert(other.mString != nullptr);
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
	constexpr String::String(String&& other) noexcept
	{
		assert(other.mPool != nullptr && other.mString != nullptr);
		String(std::move(other), *other.mPool);
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
	constexpr String::String(String&& other, MemoryPool& pool)
		: mPool(&pool)
		, mLength(other.mLength)
		, mCapacity(other.mCapacity)
		, mString(other.mString)
	{
		assert(other.mString != nullptr);

		other.mPool = nullptr;
		other.mLength = 0ul;
		other.mCapacity = 0ul;
		other.mString = nullptr;

		other.~String();
	}

	/**
	 *
  	 * @brief destroys the string, deallocating internal storage if used
	 *
	 */
	String::~String()
	{
		if (mString != nullptr)
		{
			mPool->Deallocate(mString, mCapacity * sizeof(char));
		}
	}

	/**
	 *
  	 * @brief (1) Assigns values to the string 
	 * @details Replaces the contents with a copy of <code>str</code>. If *this and str are the same object, this function has no effect.
	 * 			@n@n
	 * 			Complexity: linear in size of <code>str</code>
	 * @param str string to be used as source to initialize the string with
	 * @return *this
	 *
	 */
	String& String::operator=(const String& str)
	{
		if (this != &str)
		{
			assert(mString != str.mString && str.mString != nullptr);

			if (mCapacity < str.mLength + 1)
			{
				mPool->Deallocate(mString, mCapacity * sizeof(char));

				mCapacity = GetSufficientCapacity<ALIGNED_BYTE>(str.mLength);

				mString = static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char)));
			}

			mLength = str.mLength;
			memset(mString, '\0', mLength);
			strncpy(mString, str.mString, mLength);
		}

		return *this;
	}

	/**
	 *
  	 * @brief (2) Assigns values to the string 
	 * @details Replaces the contents with those of str using move semantics. 
	 * 			str is in a valid but unspecified state afterwards. 
	 * 			Unlike other container move assignments, references, pointers, and iterators to str may be invalidated.
	 * 			@n@n
	 * 			Complexity: linear in size of <code>this</code>
	 * @param str string to be used as source to initialize the string with
	 * @return *this
	 *
	 */
	String& String::operator=(String&& str)
	{
		if (this != &str)
		{
			assert(mString != str.mString && str.mString != nullptr);

			if (mString != nullptr)
			{
				mPool->Deallocate(mString, mCapacity * sizeof(char));
			}

			mLength = str.mLength;
			mCapacity = str.mCapacity;
			mString = str.mString;

			str.mPool = nullptr;
			str.mLength = 0ul;
			str.mCapacity = 0ul;
			str.mString = nullptr;

			str.~String();
		}

		return *this;
	}

	/**
	 *
  	 * @brief (3) Assigns values to the string 
	 * @details Replaces the contents with those of null-terminated character string pointed to by s.
	 * 			@n@n
	 * 			Complexity: linear in size of <code>s</code>
	 * @param s pointer to a null-terminated character string to use as source to initialize the string with
	 * @return *this
	 *
	 */
	String& String::operator=(const char* s)
	{
		assert(s != nullptr);

		if (s != mString)
		{
			size_t sLength = strlen(s);

			if (mCapacity < sLength + 1)
			{
				mPool->Deallocate(mString, mCapacity * sizeof(char));

				mCapacity = GetSufficientCapacity<ALIGNED_BYTE>(sLength);

				mString = static_cast<char*>(mPool->Allocate(mCapacity * sizeof(char)));
			}

			memset(mString, '\0', mLength);

			mLength = sLength;
			strncpy(mString, s, mLength);
		}

		return *this;
	}

	/**
	 *
  	 * @brief (4) Assigns values to the string 
	 * @details Replaces the contents with character ch.
	 * 			@n@n
	 * 			Complexity: linear in size of <code>str</code>
	 * @param ch value to initialize characters to the string with
	 * @return *this
	 *
	 */
	String& String::operator=(char ch)
	{
		assert (ch != '\0');
		
		mLength = 2ul;
		memset(&mString[1], '\0', mCapacity);
		mString[0] = ch;

		return *this;
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
  	 * @brief Reserves storage
	 * @details Informs a cave::String object of a planned change in size, so that it can manage the storage allocation appropriately.@n
	 * 			If newCapacity is greater than the current GetCapacity(), new storage is allocated, and GetCapacity() is made equal or greater than newCapacity.@n
	 * 			If newCapacity is less than or equal to the current GetCapacity(), there is no effect.@n
	 * 			 If a capacity change takes place, all iterators and references, including the past-the-end iterator, are invalidated. 
	 * 			@n@n
	 * 			Complexity: at most linear in the GetSize() of the string
	 * @param newCapacity new capacity of the string
	 *
	 */
	constexpr void String::SetCapacity(size_t newCapacity)
	{
		++newCapacity;
		if (newCapacity > mCapacity)
		{
			char* newString = reinterpret_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
			strncpy(newString, mString, mLength);
			memset(&newString[mLength], '\0', newCapacity - mLength);
			
			mPool->Deallocate(mString, mCapacity * sizeof(char));
			mCapacity = newCapacity;
			mString = newString;
		}
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
		return mCapacity - 1ul;
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
		memset(mString, '\0', mLength);
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
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i > index; --i)
		{
			mString[i - 1 + count] = mString[i - 1];
		}

		mLength = mLength + count;

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
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i > index; --i)
		{
			mString[i - 1 + count] = mString[i - 1];
		}
		mLength = mLength + count;

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
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i > index; --i)
		{
			mString[i - 1 + str.mLength] = mString[i - 1];
		}

		mLength = mLength + str.mLength;

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
			mCapacity = newCapacity;
		}

		for (size_t i = mLength + 1; i > index; --i)
		{
			mString[i - 1 + str.mLength] = mString[i - 1];
		}

		mLength = mLength + count;

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

		for (; mString[index] != '\0'; ++index)
		{
			mString[index] = mString[index + count];
		}

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

	/**
	 *
  	 * @brief (1) Appends characters to the end
	 * @details Appends string str
	 * 			@n@n
	 * 			Complexity: linear in str.GetLength()
	 * @param str string to append
	 * @return *this
	 *
	 */
	String& String::operator+=(const String& str)
	{
		Append(str.mString);

		return *this;
	}

	/**
	 *
  	 * @brief (2) Appends characters to the end
	 * @details Appends character ch
	 * 			@n@n
	 * 			Complexity: constant
	 * @param ch character value to append
	 * @return *this
	 *
	 */
	String& String::operator+=(char ch)
	{
		Append(1ul, ch);

		return *this;
	}

	/**
	 *
  	 * @brief (3) Appends characters to the end
	 * @details Appends the null-terminated character string pointed to by s. 
	 * 			@n@n
	 * 			Complexity: linear in size of s
	 * @param s pointer to a null-terminated character string to append 
	 * @return *this
	 *
	 */
	String& String::operator+=(const char* s)
	{
		Append(s);

		return *this;
	}

	/**
	 *
  	 * @brief (1) Checks if the string starts with the given prefix
	 * @details Checks if the string begins with the given prefix, a string str.
	 * @param str a string
	 * @return true if the string begins with the provided prefix, false otherwise. 
	 *
	 */
	constexpr bool String::StartsWith(const String& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < str.mLength; ++i)
		{
			if (mString[i] != str.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (1) Checks if the string starts with the given prefix
	 * @details Checks if the string begins with the given prefix, a string str.
	 * @param str a string
	 * @return true if the string begins with the provided prefix, false otherwise. 
	 *
	 */
	constexpr bool String::StartsWith(const String&& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < str.mLength; ++i)
		{
			if (mString[i] != str.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (2) Checks if the string starts with the given prefix
	 * @details Checks if the string begins with the given prefix, a single character c.
	 * @param c a single character
	 * @return true if the string begins with the provided prefix, false otherwise. 
	 *
	 */
	constexpr bool String::StartsWith(char c) const noexcept
	{
		if (mLength <= 0ul)
		{
			return false;
		}

		return mString[0] == c;
	}

	/**
	 *
  	 * @brief (3) Checks if the string starts with the given prefix
	 * @details Checks if the string begins with the given prefix, a null-terminated character string s.
	 * @param s a null-terminated character string
	 * @return true if the string begins with the provided prefix, false otherwise. 
	 *
	 */
	constexpr bool String::StartsWith(const char* s) const
	{
		size_t sLength = strlen(s);
		if (mLength < sLength)
		{
			return false;
		}

		for (size_t i = 0; i < sLength; ++i)
		{
			if (mString[i] != s[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (1) Checks if the string ends with the given suffix 
	 * @details Checks if the string ends with the given suffix, a string str.
	 * @param str a string
	 * @return true if the string ends with the provided suffix, false otherwise.
	 *
	 */
	constexpr bool String::EndsWith(const String& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < str.mLength; ++i)
		{
			if (mString[i + mLength - str.mLength] != str.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (1) Checks if the string ends with the given suffix 
	 * @details Checks if the string ends with the given suffix, a string str.
	 * @param str a string
	 * @return true if the string ends with the provided suffix, false otherwise.
	 *
	 */
	constexpr bool String::EndsWith(const String&& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < str.mLength; ++i)
		{
			if (mString[i + mLength - str.mLength] != str.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (2) Checks if the string starts with the given prefix
	 * @details Checks if the string ends with the given suffix, a single character c.
	 * @param c a single character
	 * @return true if the string ends with the provided suffix, false otherwise.
	 *
	 */
	constexpr bool String::EndsWith(char c) const noexcept
	{
		if (mLength <= 0ul)
		{
			return false;
		}

		return mString[mLength - 1] == c;
	}

	/**
	 *
  	 * @brief (3) Checks if the string starts with the given prefix
	 * @details Checks if the string ends with the given suffix, a null-terminated character string s.
	 * @param s a null-terminated character string
	 * @return true if the string ends with the provided suffix, false otherwise.
	 *
	 */
	constexpr bool String::EndsWith(const char* s) const
	{
		size_t sLength = strlen(s);
		if (mLength < sLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < sLength; ++i)
		{
			if (mString[i + mLength - sLength] != s[i])
			{
				return false;
			}
		}

		return true;
	}

	/**
	 *
  	 * @brief (1) Checks if the string contains the given substring or character
	 * @details Checks if the string contains the given substring, a string str.
	 * @param str a string
	 * @return true if the string contains the provided substring, false otherwise.
	 *
	 */
	constexpr bool String::Contains(const String& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < mLength; ++i)
		{
			if (mString[i] == str.mString[0])
			{
				if (mLength - i < str.mLength)
				{
					return false;
				}

				size_t strIndex = 1ul;
				for (; strIndex < str.mLength; ++strIndex)
				{
					if (mString[strIndex + i] != str.mString[strIndex])
					{
						break;
					}
				}

				if (strIndex == str.mLength)
				{
					return true;
				}
			}
		}

		return false;
	}

	/**
	 *
  	 * @brief (1) Checks if the string contains the given substring or character
	 * @details Checks if the string contains the given substring, a string str.
	 * @param str a string
	 * @return true if the string contains the provided substring, false otherwise.
	 *
	 */
	constexpr bool String::Contains(const String&& str) const noexcept
	{
		if (mLength < str.mLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < mLength; ++i)
		{
			if (mString[i] == str.mString[0])
			{
				if (mLength - i < str.mLength)
				{
					return false;
				}

				size_t strIndex = 1ul;
				for (; strIndex < str.mLength; ++strIndex)
				{
					if (mString[strIndex + i] != str.mString[strIndex])
					{
						break;
					}
				}

				if (strIndex == str.mLength)
				{
					return true;
				}
			}
		}

		return false;
	}

	/**
	 *
  	 * @brief (2) Checks if the string contains the given substring or character
	 * @details Checks if the string contains the given substring, a string str.
	 * @param c a single character
	 * @return true if the string contains the provided substring, false otherwise.
	 *
	 */
	constexpr bool String::Contains(char c) const noexcept
	{
		if (mLength < 1ul)
		{
			return false;
		}

		for (size_t i = 0ul; i < mLength; ++i)
		{
			if (mString[i] == c)
			{
				return true;
			}
		}

		return false;
	}

	/**
	 *
  	 * @brief (3) Checks if the string contains the given substring or character
	 * @details Checks if the string contains the given substring, a string str.
	 * @param s a null-terminated character string 
	 * @return true if the string contains the provided substring, false otherwise.
	 *
	 */
	constexpr bool String::Contains(const char* s) const
	{
		size_t sLength = strlen(s);
		if (mLength < sLength)
		{
			return false;
		}

		for (size_t i = 0ul; i < mLength; ++i)
		{
			if (mString[i] == s[0])
			{
				if (mLength - i < sLength)
				{
					return false;
				}

				size_t strIndex = 1ul;
				for (; strIndex < sLength; ++strIndex)
				{
					if (mString[strIndex + i] != s[strIndex])
					{
						break;
					}
				}

				if (strIndex == sLength)
				{
					return true;
				}
			}
		}

		return false;
	}

	/**
	 *
  	 * @brief (1) Replaces specified portion of a string
	 * @details Replaces the part of the string indicated by [pos, pos + count) with a new string, 
	 * 			string str.
	 * @param pos start of the substring that is going to be replaced
	 * @param count length of the substring that is going to be replaced
	 * @param str string to use for replacement
	 * @return *this
	 *
	 */
	constexpr String& String::Replace(size_t pos, size_t count, const String& str)
	{
		return Replace(pos, count, str, 0ul, str.mLength);
	}

	/**
	 *
  	 * @brief (2) Replaces specified portion of a string
	 * @details Replaces the part of the string indicated by [pos, pos + count) with a new string, 
	 * 			substring [pos2, pos2 + count2) of str, except if count2 == NPOS or 
	 * 			if would extend past str.GetLength(), [pos2, str.GetLength()) is used..
	 * @param pos start of the substring that is going to be replaced
	 * @param count length of the substring that is going to be replaced
	 * @param str string to use for replacement
	 * @param pos2 start of the substring to replace with
	 * @param count2 number of characters to replace with
	 * @return *this
	 *
	 */
	constexpr String& String::Replace(size_t pos, size_t count, const String& str, size_t pos2, size_t count2)
	{
		assert(pos <= mLength && pos2 <= str.mLength);

		if (count2 > str.mLength || count2 == NPOS)
		{
			count2 = str.mLength;
		}

		if (count < count2)
		{
			for (size_t i = mLength + 1; i > pos + count; --i)
			{
				mString[i - 1 + count2 - count] = mString[i - 1];
			}
		}
		else
		{
			for (size_t i = pos + count; i < mLength + 1; ++i)
			{
				mString[i - count + count2] = mString[i];
			}
		}

		strncpy(&mString[pos], &str.mString[pos2], count2);
		if (pos + count >= mLength)
		{
			count = mLength - pos;
		}

		if (pos2 + count2 >= str.mLength)
		{
			count2 = str.mLength - pos2;
		}
		
		mLength = mLength + count2 - count;
		mString[mLength] = '\0';

		return *this;
	}

	/**
	 *
  	 * @brief (3) Replaces specified portion of a string
	 * @details Replaces the part of the string indicated by [pos, pos + count) with a new string, 
	 * 			characters in the range [cstr, cstr + count2);.
	 * @param pos start of the substring that is going to be replaced
	 * @param count length of the substring that is going to be replaced
	 * @param count2 number of characters to replace with
	 * @param cStr pointer to the character string to use for replacement
	 * @return *this
	 *
	 */
	constexpr String& String::Replace(size_t pos, size_t count, const char* cStr, size_t count2)
	{
		assert(cStr != nullptr && pos <= mLength);

		size_t sLength = strlen(cStr);

		if (count2 > sLength)
		{
			count2 = sLength;
		}

		if (count < count2)
		{
			for (size_t i = mLength + 1; i > pos + count; --i)
			{
				mString[i - 1 + count2 - count] = mString[i - 1];
			}
		}
		else
		{
			for (size_t i = pos + count; i < mLength + 1; ++i)
			{
				mString[i - count + count2] = mString[i];
			}
		}

		strncpy(&mString[pos], cStr, count2);
		if (pos + count >= mLength)
		{
			count = mLength - pos;
		}
		
		mLength = mLength + count2 - count;
		mString[mLength] = '\0';

		return *this;
	}
	
	/**
	 *
  	 * @brief (4) Replaces specified portion of a string
	 * @details Replaces the part of the string indicated by [pos, pos + count) with a new string, 
	 * 			characters in the range [cStr, cStr + strlen(cStr));.
	 * @param pos start of the substring that is going to be replaced
	 * @param count length of the substring that is going to be replaced
	 * @param cStr pointer to the character string to use for replacement
	 * @return *this
	 *
	 */
	constexpr String& String::Replace(size_t pos, size_t count, const char* cStr)
	{
		assert(cStr != nullptr);

		return Replace(pos, count, cStr, strlen(cStr));
	}

	/**
	 *
  	 * @brief (5) Replaces specified portion of a string
	 * @details Replaces the part of the string indicated by [pos, pos + count) with a new string, 
	 * 			count2 copies of character ch;.
	 * @param pos start of the substring that is going to be replaced
	 * @param count length of the substring that is going to be replaced
	 * @param count2 number of characters to replace with
	 * @param ch character value to use for replacement 
	 * @return *this
	 *
	 */
	constexpr String& String::Replace(size_t pos, size_t count, size_t count2, char ch)
	{
		assert(pos <= mLength);

		if (count < count2)
		{
			for (size_t i = mLength + 1; i > pos + count; --i)
			{
				mString[i - 1 + count2 - count] = mString[i - 1];
			}
		}
		else
		{
			for (size_t i = pos + count; i < mLength + 1; ++i)
			{
				mString[i - count + count2] = mString[i];
			}
		}

		memset(&mString[pos], ch, count2);
		if (pos + count >= mLength)
		{
			count = mLength - pos;
		}
		
		mLength = mLength + count2 - count;
		mString[mLength] = '\0';

		return *this;
	}

	/**
	 *
  	 * @brief Returns a substring
	 * @details Returns a substring [pos, pos+count). 
	 * 			If the requested substring extends past the end of the string, 
	 * 			or if count == NPOS, the returned substring is [pos, GetLength()). 
	 * @param pos position of the first character to include
	 * @param count length of the substring
	 * @return String containing the substring [pos, pos+count).
	 *
	 */
	String String::GetSubstring(size_t pos, size_t count) const
	{
		assert(pos <= mLength);

		if (count == NPOS || pos + count >= mLength)
		{
			count = mLength - pos;
		}

		return String(*this, pos, count, *mPool);
	}

	/**
	 *
  	 * @brief Changes the number of characters stored
	 * @details Resizes the string to contain count characters.
	 * 			If the current size is less than count, additional characters are appended.
	 * 			If the current size is greater than count, the string is reduced to its first count elements.
	 * 			Initializes new characters to '\0'., the second version initializes new characters to ch. 
	 * @param count new size of the string
	 * @param ch character to initialize the new characters with
	 *
	 */
	constexpr void String::Resize(size_t count)
	{
		Resize(count, '\0');
	}

	/**
	 *
  	 * @brief Changes the number of characters stored
	 * @details Resizes the string to contain count characters.
	 * 			If the current size is less than count, additional characters are appended.
	 * 			If the current size is greater than count, the string is reduced to its first count elements.
	 * 			Initializes new characters to ch. 
	 * @param count new size of the string
	 * @param ch character to initialize the new characters with
	 *
	 */
	constexpr void String::Resize(size_t count, char ch)
	{
		size_t newLength = count;
		if (newLength < mLength)
		{
			memset(&mString[newLength], ch, mLength - newLength);
		}
		else
		{
			if (newLength + 1 > mCapacity)
			{
				size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(newLength);
				char* newString = reinterpret_cast<char*>(mPool->Allocate(newCapacity * sizeof(char)));
				strncpy(newString, mString, mLength);
				memset(&newString[mLength], '\0', newCapacity - mLength);
				mPool->Deallocate(mString, mCapacity * sizeof(char));
				mString = newString;
				mCapacity = newCapacity;
			}

			memset(&mString[mLength], ch, newLength - mLength);
		}

		mLength = newLength;
		mString[mLength] = '\0';
	}

	/**
	 *
  	 * @brief (1) Find characters in the string
	 * @details Finds the first substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position preceding pos.
	 * @param str string to search for
	 * @param pos position at which to start the search
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 *
	 */
	constexpr size_t String::GetIndexOf(const String& str, size_t pos) const noexcept
	{
		return GetIndexOf(str.mString, pos);
	}

	/**
	 *
  	 * @brief (2) Find characters in the string
	 * @details Finds the first substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position preceding pos.
	 * @param pos position at which to start the search
	 * @param count length of substring to search for
	 * @param s pointer to a character string to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 *
	 */
	constexpr size_t String::GetIndexOf(const char* s, size_t pos, size_t count) const
	{
		if (s == nullptr)
		{
			return NPOS;
		}

		char* temp = &mString[pos];
		size_t index = pos;
		const char* checkS = nullptr;

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
				return NPOS;
			}

			// Check whether s and rest of characters of mString resembles
			for (; *temp != '\0' && *temp == *checkS; ++temp, ++checkS)
			{
			}

			// Success. Resembles
			if (*checkS == '\0')
			{
				return index;
			}

			++index;
		}
	}

	/**
	 *
  	 * @brief (3) Find characters in the string
	 * @details Finds the first substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position preceding pos.
	 * @param pos position at which to start the search
	 * @param s pointer to a character string to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 *
	 */
	constexpr size_t String::GetIndexOf(const char* s, size_t pos) const
	{
		assert(s != nullptr);

		return GetIndexOf(s, pos, strlen(s));
	}

	/**
	 *
  	 * @brief (4) Find characters in the string
	 * @details Finds the first substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position preceding pos.
	 * @param pos position at which to start the search
	 * @param ch character to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 *
	 */
	constexpr size_t String::GetIndexOf(char ch, size_t pos) const
	{
		for (size_t i = 0ul; i < mLength; ++i)
		{
			if (mString[i] == ch)
			{
				return i;
			}
		}

		return NPOS;
	}

	/**
	 *
  	 * @brief (1) Find the last occurrence of a substring
	 * @details Finds the last substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position following pos. 
	 * 			If NPOS or any value not smaller than GetLength() - 1 is passed as pos, whole string will be searched.@n 
	 * 			Finds the last substring equal to str.
	 * @param str string to search for
	 * @param pos position at which to begin searching
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 * 			Note that this is an offset from the start of the string, not the end.@n
	 * 			If searching for an empty string (str.size(), count, or strlen(s) is zero) returns pos (the empty string is found immediately) 
	 * 			unless pos > GetLength() (including the case where pos == NPOS), in which case returns GetLength().@n
	 * 			Otherwise, if GetLength() is zero, NPOS is always returned. 
	 *
	 */
	constexpr size_t String::GetLastIndexOf(const String& str, size_t pos) const noexcept
	{
		return GetLastIndexOf(str.mString, pos, str.mLength);
	}

	/**
	 *
  	 * @brief (2) Find the last occurrence of a substring
	 * @details Finds the last substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position following pos. 
	 * 			If NPOS or any value not smaller than GetLength() - 1 is passed as pos, whole string will be searched.@n
	 * 			Finds the last substring equal to the range [s, s+count). This range can include null characters.  
	 * @param pos position at which to begin searching
	 * @param count length of substring to search for
	 * @param s pointer to a character string to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 * 			Note that this is an offset from the start of the string, not the end.@n
	 * 			If searching for an empty string (str.size(), count, or strlen(s) is zero) returns pos (the empty string is found immediately) 
	 * 			unless pos > GetLength() (including the case where pos == NPOS), in which case returns GetLength().@n
	 * 			Otherwise, if GetLength() is zero, NPOS is always returned. 
	 *
	 */
	constexpr size_t String::GetLastIndexOf(const char* s, size_t pos, size_t count) const
	{
		if (s == nullptr)
		{
			return NPOS;
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
			return NPOS;
		}

		if (pos == NPOS || pos >= mLength  - 1)
		{
			pos = mLength - 1;
		}

		char* temp = mString + pos;
		size_t index = pos;
		const char* checkS = s;
		char* firstCharacter = nullptr;

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
				return NPOS;
			}

			firstCharacter = temp;
			// Check whether s and rest of characters of mString resembles
			for (; *firstCharacter != '\0' && *firstCharacter == *checkS; ++firstCharacter, ++checkS)
			{
			}

			// Success. Resembles
			if (*checkS == '\0')
			{
				return index;
			}

			--temp;
			--index;
		}
	}

	/**
	 *
  	 * @brief (3) Find the last occurrence of a substring
	 * @details Finds the last substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position following pos. 
	 * 			If NPOS or any value not smaller than GetLength() - 1 is passed as pos, whole string will be searched.@n 
	 * 			Finds the last substring equal to the character string pointed to by s. 
	 * 			The length of the string is determined by the first null character using strlen(s).
	 * @param pos position at which to begin searching
	 * @param s pointer to a character string to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 * 			Note that this is an offset from the start of the string, not the end.@n
	 * 			If searching for an empty string (str.size(), count, or strlen(s) is zero) returns pos (the empty string is found immediately) 
	 * 			unless pos > GetLength() (including the case where pos == NPOS), in which case returns GetLength().@n
	 * 			Otherwise, if GetLength() is zero, NPOS is always returned. 
	 *
	 */
	constexpr size_t String::GetLastIndexOf(const char* s, size_t pos) const
	{
		assert(s != nullptr);

		return GetLastIndexOf(s, pos, strlen(s));
	}

	/**
	 *
  	 * @brief (4) Find the last occurrence of a substring
	 * @details Finds the last substring equal to the given character sequence. 
	 * 			Search begins at pos, i.e. the found substring must not begin in a position following pos. 
	 * 			If NPOS or any value not smaller than GetLength() - 1 is passed as pos, whole string will be searched.@n 
	 * 			Finds the last character equal to ch.
	 * @param pos position at which to begin searching
	 * @param ch character to search for
	 * @return Position of the first character of the found substring or npos if no such substring is found. 
	 * 			Note that this is an offset from the start of the string, not the end.@n
	 * 			If searching for an empty string (str.size(), count, or strlen(s) is zero) returns pos (the empty string is found immediately) 
	 * 			unless pos > GetLength() (including the case where pos == NPOS), in which case returns GetLength().@n
	 * 			Otherwise, if GetLength() is zero, NPOS is always returned. 
	 *
	 */
	constexpr size_t String::GetLastIndexOf(char ch, size_t pos) const
	{
		for (size_t i = mLength; i > 0; --i)
		{
			if (mString[i - 1] == ch)
			{
				return i - 1;
			}
		}

		return NPOS;
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

	String String::operator+(const String& rhs) const
	{
		String s(mString);

		// Append other to s
		s.Append(rhs.mString);

		return String(s.mString);
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

	std::ostream& operator<<(std::ostream& os, const String& str)
	{
		os << str.mString;

		return os;
	}

#ifdef CAVE_BUILD_DEBUG
	namespace StringTest
	{
		void Test()
		{
			Constructor();
			AssignmentOperator();
			SubscriptOperator();
			GetFront();
			GetBack();
			GetCString();
			IsEmpty();
			GetSize();
			SetCapacity();
			GetCapacity();
			Shrink();
			Clear();
			InsertAt();
			RemoveAt();
			Append();
			AdditionCompoundAssignmentOperator();
			StartsWith();
			EndsWith();
			Contains();
			Replace();
			GetSubstring();
			Resize();
			GetIndexOf();
			GetLastIndexOf();
		}

		void Constructor()
		{
			{
				String s;
				assert(s.IsEmpty() && (s.GetLength() == 0));
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String() TEST SUCCESS");
			}

			{
				String s(4, '=');
				assert(strncmp(s.GetCString(), "====", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(size_t count, char ch) TEST SUCCESS");
			}

			{
				String const other("Exemplary");
				String s(other, 0, other.GetLength() - 1);
				LOGDF(eLogChannel::CORE_STRING, std::cout, "other: %s, s: %s", other.GetCString(), s.GetCString());
				assert(strncmp(s.GetCString(), "Exemplar", s.GetLength()) == 0);
			}

			{
				String const other("Mutatis Mutandis");
				String s(other, 8);
				assert(strncmp(s.GetCString(), "Mutandis", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(const String& other, size_t pos) TEST SUCCESS");
			}

			{
				String s("C-style string", 7);
				assert(strncmp(s.GetCString(), "C-style", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(char const* s, size_t count) TEST SUCCESS");
			}

			{
				String s("C-style\0string");
				assert(strncmp(s.GetCString(), "C-style", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(char const* s) TEST SUCCESS");
			}

			{
				char mutable_c_str[] = "another C-style string";
				String s(mutable_c_str + 8, mutable_c_str + strlen(mutable_c_str) - 1);
				assert(strncmp(s.GetCString(), "C-style string", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(const char* first, const char* last) TEST SUCCESS");
			}

			{
				String const other("Exemplar");
				String s(other);
				assert(strncmp(s.GetCString(), "Exemplar", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(const String& other) TEST SUCCESS");
			}

			{
				// 
				String s(String("C++ by ") + String("example"));
				assert(strncmp(s.GetCString(), "C++ by example", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(String&& str) TEST SUCCESS");
			}

			{
				// overload resolution selects String(InputIt first, InputIt last) [with InputIt = int]
				// which behaves as if String(size_t count, char ch) is called
				String s(3, std::toupper('a'));
				assert(strncmp(s.GetCString(), "AAA", s.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String::String(size_t count, char ch) TEST SUCCESS");
			}
		}

		void AssignmentOperator()
		{
			String str1;
			String str2 { "alpha" };
		
			str1 = str2;
			assert(strncmp(str1.GetCString(), "alpha", str1.GetLength()) == 0);
			assert(strncmp(str2.GetCString(), "alpha", str1.GetLength()) == 0);
			assert(strncmp(str1.GetCString(), str2.GetCString(), str1.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator=(const String&) TEST SUCCESS");

			str1 = std::move(str2);
			assert(strncmp(str1.GetCString(), "alpha", str1.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator=(String&&) TEST SUCCESS");
		
			str1 = "beta";
			assert(strncmp(str1.GetCString(), "beta", str1.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator=(const char*) TEST SUCCESS");
		
			str1 = '!'; 
			assert(strncmp(str1.GetCString(), "!", str1.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator=(char) TEST SUCCESS");
		}

		void SubscriptOperator()
		{
			String const e("Exemplar");
			for (size_t i = e.GetLength() - 1, j = 0; i != 0; i /= 2, ++j)
			{
				assert(e[i] == "rmx"[j]);
			}
		
			const char* c = &e[0];
			assert(strncmp(c, e.GetCString(), e.GetLength()) == 0);
		
			// Change the last character of s into a 'y'
			String s("Exemplar ");
			s[s.GetLength() - 1] = 'y'; // equivalent to s.GetBack() = 'y';
			assert(strncmp(s.GetCString(), "Exemplary", s.GetLength()) == 0);

			LOGD(eLogChannel::CORE_STRING, std::cout, "String::operator[](size_t pos) TEST SUCCESS");
		}

		void GetFront()
		{
			{
				String s("Exemplary");
				char& f = s.GetFront();
				f = 'e';
				assert(strncmp(s.GetCString(), "exemplary", s.GetLength()) == 0);
			}
			
			{
				String const c("Exemplary");
				char const& f = c.GetFront();
				assert(strncmp(&f, "Exemplary", strlen(&f)) == 0);
			}

			LOGD(eLogChannel::CORE_STRING, std::cout, "char& String::GetFront() TEST SUCCESS");
		}

		void GetBack()
		{
			{
				String s("Exemplary");
				char& back = s.GetBack();
				back = 's';
				assert(strncmp(s.GetCString(), "Exemplars", s.GetLength()) == 0);
			}
			
			{
				String const c("Exemplary");
				char const& back = c.GetBack();
				assert(back == 'y');
			}

			LOGD(eLogChannel::CORE_STRING, std::cout, "char& String::GetBack() TEST SUCCESS");
		}

		void GetCString()
		{
			String const s("Emplary");
			assert(s.GetLength() == strlen(s.GetCString()));
			assert(0 == *(s.GetCString() + s.GetLength()));

			LOGD(eLogChannel::CORE_STRING, std::cout, "const char* String::GetCString() TEST SUCCESS");
		}

		void IsEmpty()
		{
			String s;
			assert(s.IsEmpty());
			assert(strncmp(s.GetCString(), "", 1ul) == 0);
		
			s = "Exemplar";
			assert(!s.IsEmpty());
			assert(strncmp(s.GetCString(), "Exemplar", s.GetLength()) == 0);
		
			s = "";
			assert(s.IsEmpty());
			assert(strncmp(s.GetCString(), "", 1ul) == 0);

			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::IsEmpty() TEST SUCCESS");
		}

		void GetSize()
		{
			String s("Exemplar");
			assert(8ul == s.GetLength());

			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetSize() TEST SUCCESS");
		}

		void SetCapacity()
		{
			String s;
			size_t newCapacity = 100ul;
			assert(newCapacity > s.GetCapacity());

			s.SetCapacity(newCapacity);
			assert(newCapacity <= s.GetCapacity());

			LOGD(eLogChannel::CORE_STRING, std::cout, "void String::SetCapacity() TEST SUCCESS");
		}
		
		void GetCapacity()
		{
			String s{"Exemplar"};
			assert(s.GetCapacity() == 15ul);
		
			s += " is an example string.";
			assert(s.GetCapacity() == 31ul);

			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetCapacity() TEST SUCCESS");
		}
	
		void Shrink()
		{
			String s;
			assert(s.GetCapacity() == String::ALIGNED_BYTE - 1ul);
			assert(s.GetLength() == 0ul);

			for (int i = 0; i < 42; i++)
			{
				s.Append(" 42 ");
			}

			assert(s.GetCapacity() == 255ul);
			assert(s.GetLength() == 168ul);
			
			s.Clear();
			assert(s.GetCapacity() == 255ul);
			assert(s.GetLength() == 0ul);

			s.Shrink();
			assert(s.GetCapacity() == String::ALIGNED_BYTE - 1ul);
			assert(s.GetLength() == 0ul);

			LOGD(eLogChannel::CORE_STRING, std::cout, "void String::Shrink() TEST SUCCESS");
		}

		void Clear()
		{
			String s{ "Exemplar" };
			size_t const capacity = s.GetCapacity();
		
			s.Clear();
			assert(s.GetCapacity() == capacity);
			assert(s.IsEmpty());
			assert(s.GetLength() == 0);

			LOGD(eLogChannel::CORE_STRING, std::cout, "void String::Clear() TEST SUCCESS");
		}
	
		void InsertAt()
		{
			String s = "xmplr";
 
			s.InsertAt(0, 1, 'E');
			assert(strncmp("Exmplr", s.GetCString(), s.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::InsertAt(size_t index, size_t count, char ch) TEST SUCCESS");
		
			s.InsertAt(2, "e");
			assert(strncmp("Exemplr", s.GetCString(), s.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::InsertAt(size_t index, const char* s) TEST SUCCESS");
		
			String a = "a";
			s.InsertAt(6, a);
			assert(strncmp("Exemplar", s.GetCString(), s.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::InsertAt(size_t index, String const& str) TEST SUCCESS");
		
			String exampleStr = " is an example string.";
			s.InsertAt(8, exampleStr, 0, 14);
			assert(strncmp("Exemplar is an example", s.GetCString(), s.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::InsertAt(size_t index, String const& str, size_t indexStr, size_t count) TEST SUCCESS");
		}

		void RemoveAt()
		{
			String s = "This is an example";
			assert(strncmp(s.GetCString(), "This is an example", s.GetLength()) == 0);

			s.RemoveAt(0, 5); // Erase "This "
			assert(strncmp(s.GetCString(), "is an example", s.GetLength()) == 0);

			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::RemoveAt(size_t index = 0, size_t count) TEST SUCCESS");
		}

		void Append()
		{
			String str = "string";
			const char* cPtr = "C-string";
			const char cArr[] = "Two and one";
		
			String output;
		
			// 1) Append a char 3 times. 
			// Notice, this is the only overload accepting chars.
			output.Append(3, '*');
			assert(strncmp(output.GetCString(), "***", output.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Append(size_t count, char ch) TEST SUCCESS");
		
			//  2) Append a whole string
			output.Append(str);
			assert(strncmp(output.GetCString(), "***string", output.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Append(const String& str) TEST SUCCESS");
		
			// 3) Append part of a string (last 3 letters, in this case)
			output.Append(str, 3, 3);
			assert(strncmp(output.GetCString(), "***stringing", output.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Append(const String& str, size_t pos, size_t count) TEST SUCCESS");
		
			// 4) Append part of a C-string
			output.Append(1, ' ');
			assert(strncmp(output.GetCString(), "***stringing ", output.GetLength()) == 0);
			output.Append(cArr, 4);
			assert(strncmp(output.GetCString(), "***stringing Two ", output.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Append(const char* s, size_t count) TEST SUCCESS");
		
			// 5) Append a whole C-string
			output.Append(cPtr);
			assert(strncmp(output.GetCString(), "***stringing Two C-string", output.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Append(const char* s, size_t count) TEST SUCCESS");
		}

		void AdditionCompoundAssignmentOperator()
		{
			String str;
			str.SetCapacity(50); //reserves sufficient storage space to avoid memory reallocation
			assert(strncmp(str.GetCString(), "", 1ul) == 0);
			
			str += "This";
			assert(strncmp(str.GetCString(), "This", str.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator+=(const char* s) TEST SUCCESS");
			
			str += String(" is ");
			assert(strncmp(str.GetCString(), "This is ", str.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator+=(const String& str) TEST SUCCESS");
			
			str += 'a';
			assert(strncmp(str.GetCString(), "This is a", str.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::operator+=(char ch) TEST SUCCESS");
		}

		void StartsWith()
		{
			String helloWorld = String("hello world");
 
			assert(helloWorld.StartsWith(String("hello")));
			assert(!helloWorld.StartsWith(String("goodbye")));
			assert(helloWorld.StartsWith('h'));
			assert(!helloWorld.StartsWith('x'));

			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::StartsWith TEST SUCCESS");
		}

		void EndsWith()
		{
			String helloWorld = String("hello world");
 
			assert(helloWorld.EndsWith(String("world")));
			assert(!helloWorld.EndsWith(String("goodbye")));
			assert(helloWorld.EndsWith('d'));
			assert(!helloWorld.EndsWith('x'));

			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::EndsWith TEST SUCCESS");
		}

		void Contains()
		{
			String helloWorld = String("hello world");
 
			assert(helloWorld.Contains(String("hello")));
			assert(!helloWorld.Contains(String("goodbye")));
			assert(helloWorld.Contains('w'));
			assert(!helloWorld.Contains('x'));

			LOGD(eLogChannel::CORE_STRING, std::cout, "bool String::Contains TEST SUCCESS");
		}

		void Replace()
		{
			{
				String str = "hello world";

				str.Replace(0, 1, String("bey"));
				assert(str.GetLength() == strlen("beyello world"));
				assert(strncmp(str.GetCString(), "beyello world", str.GetLength()) == 0);

				str.Replace(str.GetLength(), 1, String("boy"));
				assert(str.GetLength() == strlen("beyello worldboy"));
				assert(strncmp(str.GetCString(), "beyello worldboy", str.GetLength()) == 0);

				str.Replace(2, 2, String(""));
				assert(str.GetLength() == strlen("bello worldboy"));
				assert(strncmp(str.GetCString(), "bello worldboy", str.GetLength()) == 0);	
				LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::Replace(size_t pos, size_t count, const String& str) TEST SUCCESS");
			}

			{
				String str = "hello world";

				str.Replace(0, 1, String("bey"), 1, 1);
				assert(str.GetLength() == strlen("eello world"));
				assert(strncmp(str.GetCString(), "eello world", str.GetLength()) == 0);

				str.Replace(str.GetLength(), 1, String("boy"), 3, 1);
				assert(str.GetLength() == strlen("eello world"));
				assert(strncmp(str.GetCString(), "eello world", str.GetLength()) == 0);

				str.Replace(0, 5, String("good morning, hello"), 14, 5);
				assert(str.GetLength() == strlen("hello world"));
				assert(strncmp(str.GetCString(), "hello world", str.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::Replace(size_t pos, size_t count, const String& str, size_t pos2, size_t count2 = NPOS) TEST SUCCESS");
			}

			{
				String str = "hello world";

				str.Replace(0, 1, "bey", 2);
				assert(str.GetLength() == strlen("beello world"));
				assert(strncmp(str.GetCString(), "beello world", str.GetLength()) == 0);

				str.Replace(str.GetLength(), 1, "boy", 1);
				assert(str.GetLength() == strlen("beello worldb"));
				assert(strncmp(str.GetCString(), "beello worldb", str.GetLength()) == 0);

				str.Replace(2, 2, "blyat", 0);
				assert(str.GetLength() == strlen("belo worldb"));
				assert(strncmp(str.GetCString(), "belo worldb", str.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::Replace(size_t pos, size_t count, const char* cStr, size_t count2) TEST SUCCESS");
			}

			{
				String str = "hello world";

				str.Replace(0, 1, "bey");
				assert(str.GetLength() == strlen("beyello world"));
				assert(strncmp(str.GetCString(), "beyello world", str.GetLength()) == 0);

				str.Replace(str.GetLength(), 1, "boy");
				assert(str.GetLength() == strlen("beyello worldboy"));
				assert(strncmp(str.GetCString(), "beyello worldboy", str.GetLength()) == 0);

				str.Replace(2, 2, "");
				assert(str.GetLength() == strlen("bello worldboy"));
				assert(strncmp(str.GetCString(), "bello worldboy", str.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::Replace(size_t pos, size_t count, const char* cStr) TEST SUCCESS");
			}

			{
				String str = "hello world";

				str.Replace(0, 1, 3, 'h');
				assert(str.GetLength() == strlen("hhhello world"));
				assert(strncmp(str.GetCString(), "hhhello world", str.GetLength()) == 0);

				str.Replace(str.GetLength(), 2, 4, 'd');
				assert(str.GetLength() == strlen("hhhello worlddddd"));
				assert(strncmp(str.GetCString(), "hhhello worlddddd", str.GetLength()) == 0);
				LOGD(eLogChannel::CORE_STRING, std::cout, "String& String::Replace(size_t pos, size_t count, size_t count2, char ch) TEST SUCCESS");
			}
		}

		void GetSubstring()
		{
			String a = "0123456789abcdefghij";
 
			// count is npos, returns [pos, GetLength())
			String sub1 = a.GetSubstring(10);
			assert(sub1.GetLength() == strlen("abcdefghij"));
			assert(strncmp(sub1.GetCString(), "abcdefghij", sub1.GetLength()) == 0);
		
			// both pos and pos+count are within bounds, returns [pos, pos+count)
			String sub2 = a.GetSubstring(5, 3);
			assert(sub2.GetLength() == strlen("567"));
			assert(strncmp(sub2.GetCString(), "567", sub2.GetLength()) == 0);
		
			// pos is within bounds, pos+count is not, returns [pos, size()) 
			String sub4 = a.GetSubstring(a.GetLength() - 3, 50);
			// this is effectively equivalent to
			// std::string sub4 = a.substr(17, 3);
			// since a.size() == 20, pos == a.size()-3 == 17, and a.size()-pos == 3
		
			assert(sub4.GetLength() == strlen("hij"));
			assert(strncmp(sub4.GetCString(), "hij", sub4.GetLength()) == 0);
		
			LOGD(eLogChannel::CORE_STRING, std::cout, "String String::GetSubstring(size_t pos, size_t count) TEST SUCCESS");
		}

		void Resize()
		{
			const size_t desired_length = 8ul;
			String longString("Where is the end?");
			String shortString("Ha");

			// Shorten
			longString.Resize(desired_length);
			assert(longString.GetLength() == strlen("Where is"));
			assert(strncmp(longString.GetCString(), "Where is", longString.GetLength()) == 0);
			
			// Lengthen
			shortString.Resize(desired_length, 'a');
			assert(shortString.GetLength() == strlen("Haaaaaaa"));
			assert(strncmp(shortString.GetCString(), "Haaaaaaa", shortString.GetLength()) == 0);

			LOGD(eLogChannel::CORE_STRING, std::cout, "void String::Resize(size_t count, char ch) TEST SUCCESS");
		}
	
		void GetIndexOf()
		{
			int32_t n = 0ul;
			String const s = "This is a string";
		
			// search from beginning of string
			n = s.GetIndexOf("is");
			assert(n != String::NPOS);
			String sub1 = s.GetSubstring(n);
			assert(sub1.GetLength() == strlen("is is a string"));
			assert(strncmp(sub1.GetCString(), "is is a string", sub1.GetLength()) == 0);
		
			// search from position 5
			n = s.GetIndexOf("is", 5);
			assert(n != String::NPOS);
			String sub2 = s.GetSubstring(n);
			assert(sub2.GetLength() == strlen("is a string"));
			assert(strncmp(sub2.GetCString(), "is a string", sub2.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetIndexOf(const char* s, size_t pos) TEST SUCCESS");
		
			// find a single character
			n = s.GetIndexOf('a');
			assert(n != String::NPOS);
			String sub3 = s.GetSubstring(n);
			assert(sub3.GetLength() == strlen("a string"));
			assert(strncmp(sub3.GetCString(), "a string", sub3.GetLength()) == 0);
		
			// find a single character
			n = s.GetIndexOf('q');
			assert(n == String::NPOS);
			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetIndexOf(char ch, size_t pos) TEST SUCCESS");
		}

		void GetLastIndexOf()
		{
			size_t n = 0ul;
			String const s = "This is a string";
		
			// search backwards from end of string
			n = s.GetLastIndexOf("is");
			assert(n != String::NPOS && n == 5);
			String sub1 = s.GetSubstring(n);
			assert(sub1.GetLength() == strlen("is a string"));
			assert(strncmp(sub1.GetCString(), "is a string", sub1.GetLength()) == 0);

			// search backwards from position 4
			n = s.GetLastIndexOf("is", 4);
			assert(n != String::NPOS && n == 2);
			String sub2 = s.GetSubstring(n);
			assert(sub2.GetLength() == strlen("is is a string"));
			assert(strncmp(sub2.GetCString(), "is is a string", sub2.GetLength()) == 0);
			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetIndexOf(const char* s, size_t pos) TEST SUCCESS");
			
			// find a single character
			n = s.GetLastIndexOf('s');
			assert(n != String::NPOS && n == 10);
			String sub3 = s.GetSubstring(n);
			assert(sub3.GetLength() == strlen("string"));
			assert(strncmp(sub3.GetCString(), "string", sub3.GetLength()) == 0);

			// find a single character
			n = s.GetLastIndexOf('q');
			assert(n == String::NPOS);

			LOGD(eLogChannel::CORE_STRING, std::cout, "size_t String::GetIndexOf(char ch, size_t pos) TEST SUCCESS");
		}
	}
#endif
} // namespace cave