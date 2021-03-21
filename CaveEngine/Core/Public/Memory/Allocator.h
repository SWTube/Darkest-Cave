/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#include <memory>

#include "DataTypes.h"

namespace caveengine
{
	template<typename T>
	struct Allocator
	{
	public:
		constexpr Allocator() noexcept
			: mAllocator()
		{
		}

		constexpr Allocator(const Allocator& other) noexcept
			: mAllocator(other.mAllocator)
		{
		}

		template<typename U>
		constexpr Allocator(const Allocator<U>& other) noexcept
			: mAllocator(other.mAllocator)
		{
		}

		constexpr ~Allocator()
		{
		}

		[[nodiscard]] constexpr T* Allocate(size_t n)
		{
			// Allocates n * sizeof(T) bytes of uninitialized storage by calling ::operator new(std::size_t) or ::operator new(std::size_t, std::align_val_t) (since C++17), but it is unspecified when and how this function is called. The pointer hint may be used to provide locality of reference: the allocator, if supported by the implementation, will attempt to allocate the new memory block as close as possible to hint.

			// Then, this function creates an array of type T[n] in the storage and starts its lifetime, but does not start lifetime of any of its elements.

			// Use of this function is ill-formed if T is an incomplete type.

			// In order to use this function in a constant expression, the allocated storage must be deallocated within the evaluation of the same expression.
			// 	(since C++20)
			// Parameters
			// n 	- 	the number of objects to allocate storage for
			// hint 	- 	pointer to a nearby memory location
			// Return value

			// Pointer to the first element of an array of n objects of type T whose elements have not been constructed yet.
			// Exceptions

			// Throws std::bad_array_new_length if std::numeric_limits<std::size_t>::max() / sizeof(T) < n.
			// 	(since C++11)

			// Throws std::bad_alloc if allocation fails.

			mAllocator.allocate(n);
		}

		constexpr void Deallocate(T* ptr, size_t n)
		{
			// Deallocates the storage referenced by the pointer p, which must be a pointer obtained by an earlier call to allocate().

			// The argument n must be equal to the first argument of the call to allocate() that originally produced p; otherwise, the behavior is undefined.

			// Calls ::operator delete(void*) or ::operator delete(void*, std::align_val_t) (since C++17), but it is unspecified when and how it is called.

			// In evaluation of a constant expression, this function must deallocate storage allocated within the evaluation of the same expression.
			// 	(since C++20)
			// Parameters
			// p 	- 	pointer obtained from allocate()
			// n 	- 	number of objects earlier passed to allocate()
			mAllocator.deallocate(ptr, n);
		}

	private:
		std::allocator<T> mAllocator;
		T mValueType;
		size_t mSizeType;
		ptrdiff_t mDifferenceType;
	};
} // namespace caveengine