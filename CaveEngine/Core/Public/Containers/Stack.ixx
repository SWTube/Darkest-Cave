/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Debug/Log.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.Stack;

import cave.Core.Memory.Memory;


namespace cave
{
	/**
	 *
	 * @brief Stack is a LIFO data structure.
	 * @details The cave::Stack class is a container adapter that gives the programmer the functionality of a stack - specifically,
	 * 			a LIFO (last-in, first-out) data structure.@n
	 * 			The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.
	 * @author Alegruz
	 * @date 2021-08-16
	 * @version 0.0.2
	 *
	 */
	export class Stack final
	{
		// Non-member functions
		friend constexpr bool operator==(const Stack& lhs, const Stack& rhs);
		friend constexpr bool operator!=(const Stack& lhs, const Stack& rhs);
	public:
		Stack();
		Stack(MemoryPool& pool);
		Stack(const Stack& other);
		Stack(const Stack& other, MemoryPool& pool);
		Stack(Stack&& other);
		Stack(Stack&& other, MemoryPool& pool);
		~Stack();
		Stack& operator=(const Stack& other);
		Stack& operator=(Stack&& other);

		// Element Access
		void* GetTop();
		const void* GetTop() const;

		// Capacity
		[[nodiscard]] bool IsEmpty() const;
		size_t GetSize() const;

		// Modifiers
		void Push(void* value);
		void Pop();

		// Constants
		static constexpr size_t INITIAL_CAPACITY = 8ul;
		static constexpr size_t ALIGNED_BYTE = 16ul;
	private:
		MemoryPool* mPool = nullptr;
		size_t mSize = 0u;
		size_t mCapacity = INITIAL_CAPACITY;
		void** mData = nullptr;
	};

	export class ConstantStack final
	{
		// Non-member functions
		friend constexpr bool operator==(const ConstantStack& lhs, const ConstantStack& rhs);
		friend constexpr bool operator!=(const ConstantStack& lhs, const ConstantStack& rhs);
	public:
		ConstantStack();
		ConstantStack(MemoryPool& pool);
		ConstantStack(const ConstantStack& other);
		ConstantStack(const ConstantStack& other, MemoryPool& pool);
		ConstantStack(ConstantStack&& other);
		ConstantStack(ConstantStack&& other, MemoryPool& pool);
		~ConstantStack();
		ConstantStack& operator=(const ConstantStack& other);
		ConstantStack& operator=(ConstantStack&& other);

		// Element Access
		const void* GetTop() const;

		// Capacity
		[[nodiscard]] bool IsEmpty() const;
		size_t GetSize() const;

		// Modifiers
		void Push(const void* value);
		void Pop();

		// Constants
		static constexpr size_t INITIAL_CAPACITY = 8ul;
		static constexpr size_t ALIGNED_BYTE = 16ul;
	private:
		MemoryPool* mPool = nullptr;
		size_t mSize = 0u;
		size_t mCapacity = INITIAL_CAPACITY;
		const void** mData = nullptr;
	};

	/**
	 *
	 * @brief (1) Constructs the stack
	 * @details Default constructor. Value-initializes the container.
	 * 			@n@n
	 * 			Complexity: constant
	 *
	 */
	Stack::Stack()
		: Stack(gCoreMemoryPool)
	{
	}

	/**
	 *
	 * @brief (2) Constructs the stack
	 * @details Constructs the underlying container using pool as allocator.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 *
	 */
	Stack::Stack(MemoryPool& pool)
		: mPool(&pool)
		, mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * mCapacity)))
	{
	}

	/**
	 *
	 * @brief (3) Constructs the stack
	 * @details Copy constructor. The adaptor is copy-constructed with the contents of other.mData.
	 * 			@n@n
	 * 			Complexity: linear in size of other.mData
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */
	
	Stack::Stack(const Stack& other)
		: Stack(other, *other.mPool)
	{
	}

	/**
	 *
	 * @brief (4) Constructs the stack
	 * @details Constructs the adaptor with the contents of other.mData and using pool as allocator.
	 * 			@n@n
	 * 			Complexity: linear in size of other.mData
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */
	
	Stack::Stack(const Stack& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * mCapacity)))
	{
		Memory::Memcpy(mData, other.mData, sizeof(void*) * mSize);
	}

	/**
	 *
	 * @brief (5) Constructs the stack
	 * @details Move constructor. The adaptor is constructed with std::move(other.mData)
	 * 			@n@n
	 * 			Complexity: constant
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */
	
	Stack::Stack(Stack&& other)
		: Stack(std::move(other), *other.mPool)
	{
	}

	/**
	 *
	 * @brief (6) Constructs the stack
	 * @details Constructs the adaptor with the contents of other using move semantics while utilizing pool as allocator.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */
	
	Stack::Stack(Stack&& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * mCapacity)))
	{
		Memory::Memcpy(mData, other.mData, sizeof(void*) * mSize);
		other.mPool->Deallocate(other.mData, sizeof(void*) * other.mCapacity);
		other.mPool = nullptr;
		other.mSize = 0ul;
		other.mCapacity = 0ul;
		other.mData = nullptr;
	}

	/**
	 *
	 * @brief Destructs the stack.
	 * @details The destructors of the elements are called and the used storage is deallocated. @n
	 * 			Note, that if the elements are pointers, the pointed-to objects are not destroyed.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */
	
	Stack::~Stack()
	{
		for (size_t i = 0; i < mSize; ++i)
		{
			mData[i] = nullptr;
		}

		mPool->Deallocate(mData, sizeof(void*) * mCapacity);
		mSize = 0ul;
		mCapacity = 0ul;
		mPool = nullptr;
	}

	/**
	 *
	 * @brief (1) Assigns values to the container adaptor
	 * @details Replaces the contents of the container adaptor with those of other. @n
	 * 			Copy assignment operator. Replaces the contents with a copy of the contents of other. Effectively calls mData = other.mData;
	 * 			@n@n
	 * 			Complexity: equivalent to that of `operator=` of the underlying container
	 * @param other another container adaptor to be used as source
	 * @return *this
	 *
	 */
	
	Stack& Stack::operator=(const Stack& other)
	{
		if (this != &other)
		{
			if (mCapacity < other.mSize)
			{
				size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(other.mSize);
				void** newArray = reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * newCapacity));
				mPool->Deallocate(mData, sizeof(void*) * mCapacity);
				mData = newArray;
				mCapacity = newCapacity;
			}

			Memory::Memcpy(mData, other.mData, sizeof(void*) * other.mSize);
			mSize = other.mSize;
		}

		return *this;
	}

	/**
	 *
	 * @brief (2) Assigns values to the container adaptor
	 * @details Replaces the contents of the container adaptor with those of other. @n
	 * 			Move assignment operator. Replaces the contents with those of other using move semantics. Effectively calls mData = std::move(other.mData);
	 * 			@n@n
	 * 			Complexity: equivalent to that of `operator=` of the underlying container
	 * @param other another container adaptor to be used as source
	 * @return *this
	 *
	 */
	
	Stack& Stack::operator=(Stack&& other)
	{
		if (this != &other)
		{
			mPool->Deallocate(mData, sizeof(void*) * mCapacity);

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = other.mData;

			other.mSize = 0ul;
			other.mCapacity = 0ul;
			other.mData = nullptr;
		}

		return *this;
	}

	/**
	 *
	 * @brief (1) Accesses the top element
	 * @details Returns reference to the top element in the stack. @n
	 * 			This is the most recently pushed element. @n
	 * 			This element will be removed on a call to Pop().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the last element
	 *
	 */
	
	void* Stack::GetTop()
	{
		void* top = mData[mSize - 1ul];

		return top;
	}

	/**
	 *
	 * @brief (2) Accesses the top element
	 * @details Returns reference to the top element in the stack. @n
	 * 			This is the most recently pushed element. @n
	 * 			This element will be removed on a call to Pop().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the last element
	 *
	 */
	
	const void* Stack::GetTop() const
	{
		return mData[mSize - 1ul];
	}

	/**
	 *
	 * @brief Checks whether the underlying container is empty
	 * @details Checks if the underlying container has no elements, i.e. whether c.IsEmpty().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return `true` if the underlying container is empty, `false` otherwise
	 *
	 */
	
	[[nodiscard]] bool Stack::IsEmpty() const
	{
		return mSize == 0ul;
	}

	/**
	 *
	 * @brief Returns the number of elements
	 * @details Returns the number of elements in the underlying container, that is, c.GetSize().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return The number of elements in the container.
	 *
	 */
	
	size_t Stack::GetSize() const
	{
		return mSize;
	}

	/**
	 *
	 * @brief Inserts element at the top
	 * @details Pushes the given element value to the top of the stack. @n
	 * 			Effectively calls c.PushBack(value)
	 * 			@n@n
	 * 			Complexity: Equal to the complexity of Container::PushBack
	 * @param value the value of the element to push
	 *
	 */
	
	void Stack::Push(void* value)
	{
		if (mSize >= mCapacity)
		{
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mSize + 1);
#endif
			void** newArray = reinterpret_cast<void**>(mPool->Allocate(sizeof(void*) * newCapacity));
			Memory::Memcpy(newArray, mData, sizeof(void*) * mSize);
			mPool->Deallocate(mData, sizeof(void*) * mCapacity);
			mData = newArray;
			mCapacity = newCapacity;
		}

		mData[mSize++] = value;
	}

	/**
	 *
	 * @brief Removes the top element
	 * @details Removes the top element from the stack. @n
	 * 			Effectively calls c.PopBack()
	 * 			@n@n
	 * 			Complexity: Equal to the complexity of Container::PopBack
	 *
	 */
	
	void Stack::Pop()
	{
		if (mSize > 0ul)
		{
			mData[mSize - 1] = nullptr;
			--mSize;
		}
	}

	/**
	 *
	 * @brief (1) Compares the values in the stack
	 * @details Compares the contents of the underlying containers of two container adaptors. @n
	 * 			The comparison is done by applying the corresponding operator to the underlying containers.
	 * 			@n@n
	 * 			Complexity: Linear in the size of the container
	 * @param lhs container adaptors whose contents to compare
	 * @param rhs container adaptors whose contents to compare
	 * @return `true` if the corresponding comparison yields `true`, `false` otherwise
	 *
	 */
	
	constexpr bool operator==(const Stack& lhs, const Stack& rhs)
	{
		if (lhs.mSize != rhs.mSize)
		{
			return false;
		}

		int result = Memory::Memcmp(lhs.mData, rhs.mData, sizeof(void*) * lhs.mSize);
		void* start0 = &lhs.mData[0];
		void* end0 = &lhs.mData[lhs.mSize - 1];

		void* start1 = &rhs.mData[0];
		void* end1 = &rhs.mData[lhs.mSize - 1];

		return result == 0;
	}

	/**
	 *
	 * @brief (2) Compares the values in the stack
	 * @details Compares the contents of the underlying containers of two container adaptors. @n
	 * 			The comparison is done by applying the corresponding operator to the underlying containers.
	 * 			@n@n
	 * 			Complexity: Linear in the size of the container
	 * @param lhs container adaptors whose contents to compare
	 * @param rhs container adaptors whose contents to compare
	 * @return `true` if the corresponding comparison yields `true`, `false` otherwise
	 *
	 */
	
	constexpr bool operator!=(const Stack& lhs, const Stack& rhs)
	{
		if (lhs.mSize != rhs.mSize)
		{
			return true;
		}

		return Memory::Memcmp(lhs.mData, rhs.mData, sizeof(void*) * lhs.mSize) != 0;
	}

	/**
	 *
	 * @brief (1) Constructs the stack
	 * @details Default constructor. Value-initializes the container.
	 * 			@n@n
	 * 			Complexity: constant
	 *
	 */
	ConstantStack::ConstantStack()
		: ConstantStack(gCoreMemoryPool)
	{
	}

	/**
	 *
	 * @brief (2) Constructs the stack
	 * @details Constructs the underlying container using pool as allocator.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 *
	 */
	ConstantStack::ConstantStack(MemoryPool& pool)
		: mPool(&pool)
		, mData(reinterpret_cast<const void**>(mPool->Allocate(sizeof(const void*) * mCapacity)))
	{
	}

	/**
	 *
	 * @brief (3) Constructs the stack
	 * @details Copy constructor. The adaptor is copy-constructed with the contents of other.mData.
	 * 			@n@n
	 * 			Complexity: linear in size of other.mData
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */

	ConstantStack::ConstantStack(const ConstantStack& other)
		: ConstantStack(other, *other.mPool)
	{
	}

	/**
	 *
	 * @brief (4) Constructs the stack
	 * @details Constructs the adaptor with the contents of other.mData and using pool as allocator.
	 * 			@n@n
	 * 			Complexity: linear in size of other.mData
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */

	ConstantStack::ConstantStack(const ConstantStack& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(reinterpret_cast<const void**>(mPool->Allocate(sizeof(const void*)* mCapacity)))
	{
		Memory::Memcpy(mData, other.mData, sizeof(void*) * mSize);
	}

	/**
	 *
	 * @brief (5) Constructs the stack
	 * @details Move constructor. The adaptor is constructed with std::move(other.mData)
	 * 			@n@n
	 * 			Complexity: constant
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */

	ConstantStack::ConstantStack(ConstantStack&& other)
		: ConstantStack(std::move(other), *other.mPool)
	{
	}

	/**
	 *
	 * @brief (6) Constructs the stack
	 * @details Constructs the adaptor with the contents of other using move semantics while utilizing pool as allocator.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */

	ConstantStack::ConstantStack(ConstantStack&& other, MemoryPool& pool)
		: mPool(&pool)
		, mSize(other.mSize)
		, mCapacity(other.mCapacity)
		, mData(reinterpret_cast<const void**>(mPool->Allocate(sizeof(const void*)* mCapacity)))
	{
		Memory::Memcpy(mData, other.mData, sizeof(const void*) * mSize);
		other.mPool->Deallocate(other.mData, sizeof(const void*) * other.mCapacity);
		other.mPool = nullptr;
		other.mSize = 0ul;
		other.mCapacity = 0ul;
		other.mData = nullptr;
	}

	/**
	 *
	 * @brief Destructs the stack.
	 * @details The destructors of the elements are called and the used storage is deallocated. @n
	 * 			Note, that if the elements are pointers, the pointed-to objects are not destroyed.
	 * 			@n@n
	 * 			Complexity: constant
	 * @param pool memory pool to use for all memory allocations of the underlying container
	 * @param other another container adaptor to be used as source to initialize the underlying container
	 *
	 */

	ConstantStack::~ConstantStack()
	{
		for (size_t i = 0; i < mSize; ++i)
		{
			mData[i] = nullptr;
		}

		mPool->Deallocate(mData, sizeof(const void*) * mCapacity);
		mSize = 0ul;
		mCapacity = 0ul;
		mPool = nullptr;
	}

	/**
	 *
	 * @brief (1) Assigns values to the container adaptor
	 * @details Replaces the contents of the container adaptor with those of other. @n
	 * 			Copy assignment operator. Replaces the contents with a copy of the contents of other. Effectively calls mData = other.mData;
	 * 			@n@n
	 * 			Complexity: equivalent to that of `operator=` of the underlying container
	 * @param other another container adaptor to be used as source
	 * @return *this
	 *
	 */

	ConstantStack& ConstantStack::operator=(const ConstantStack& other)
	{
		if (this != &other)
		{
			if (mCapacity < other.mSize)
			{
				size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(other.mSize);
				const void** newArray = reinterpret_cast<const void**>(mPool->Allocate(sizeof(const void*) * newCapacity));
				mPool->Deallocate(mData, sizeof(const void*) * mCapacity);
				mData = newArray;
				mCapacity = newCapacity;
			}

			Memory::Memcpy(mData, other.mData, sizeof(const void*) * other.mSize);
			mSize = other.mSize;
		}

		return *this;
	}

	/**
	 *
	 * @brief (2) Assigns values to the container adaptor
	 * @details Replaces the contents of the container adaptor with those of other. @n
	 * 			Move assignment operator. Replaces the contents with those of other using move semantics. Effectively calls mData = std::move(other.mData);
	 * 			@n@n
	 * 			Complexity: equivalent to that of `operator=` of the underlying container
	 * @param other another container adaptor to be used as source
	 * @return *this
	 *
	 */

	ConstantStack& ConstantStack::operator=(ConstantStack&& other)
	{
		if (this != &other)
		{
			mPool->Deallocate(mData, sizeof(const void*) * mCapacity);

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = other.mData;

			other.mSize = 0ul;
			other.mCapacity = 0ul;
			other.mData = nullptr;
		}

		return *this;
	}

	/**
	 *
	 * @brief Accesses the top element
	 * @details Returns reference to the top element in the stack. @n
	 * 			This is the most recently pushed element. @n
	 * 			This element will be removed on a call to Pop().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return Reference to the last element
	 *
	 */

	const void* ConstantStack::GetTop() const
	{
		return mData[mSize - 1ul];
	}

	/**
	 *
	 * @brief Checks whether the underlying container is empty
	 * @details Checks if the underlying container has no elements, i.e. whether c.IsEmpty().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return `true` if the underlying container is empty, `false` otherwise
	 *
	 */

	[[nodiscard]] bool ConstantStack::IsEmpty() const
	{
		return mSize == 0ul;
	}

	/**
	 *
	 * @brief Returns the number of elements
	 * @details Returns the number of elements in the underlying container, that is, c.GetSize().
	 * 			@n@n
	 * 			Complexity: constant
	 * @return The number of elements in the container.
	 *
	 */

	size_t ConstantStack::GetSize() const
	{
		return mSize;
	}

	/**
	 *
	 * @brief Inserts element at the top
	 * @details Pushes the given element value to the top of the stack. @n
	 * 			Effectively calls c.PushBack(value)
	 * 			@n@n
	 * 			Complexity: Equal to the complexity of Container::PushBack
	 * @param value the value of the element to push
	 *
	 */

	void ConstantStack::Push(const void* value)
	{
		if (mSize >= mCapacity)
		{
#if CAPACITY_INCREASE_MODE == CAPACITY_INCREASE_MODE_DOUBLE
			size_t newCapacity = mCapacity * 2;
#else
			size_t newCapacity = GetSufficientCapacity<ALIGNED_BYTE>(mSize + 1);
#endif
			const void** newArray = reinterpret_cast<const void**>(mPool->Allocate(sizeof(const void*) * newCapacity));
			Memory::Memcpy(newArray, mData, sizeof(const void*) * mSize);
			mPool->Deallocate(mData, sizeof(void*) * mCapacity);
			mData = newArray;
			mCapacity = newCapacity;
		}

		mData[mSize++] = value;
	}

	/**
	 *
	 * @brief Removes the top element
	 * @details Removes the top element from the stack. @n
	 * 			Effectively calls c.PopBack()
	 * 			@n@n
	 * 			Complexity: Equal to the complexity of Container::PopBack
	 *
	 */

	void ConstantStack::Pop()
	{
		if (mSize > 0ul)
		{
			mData[mSize - 1] = nullptr;
			--mSize;
		}
	}

	/**
	 *
	 * @brief (1) Compares the values in the stack
	 * @details Compares the contents of the underlying containers of two container adaptors. @n
	 * 			The comparison is done by applying the corresponding operator to the underlying containers.
	 * 			@n@n
	 * 			Complexity: Linear in the size of the container
	 * @param lhs container adaptors whose contents to compare
	 * @param rhs container adaptors whose contents to compare
	 * @return `true` if the corresponding comparison yields `true`, `false` otherwise
	 *
	 */

	constexpr bool operator==(const ConstantStack& lhs, const ConstantStack& rhs)
	{
		if (lhs.mSize != rhs.mSize)
		{
			return false;
		}

		int result = Memory::Memcmp(lhs.mData, rhs.mData, sizeof(const void*) * lhs.mSize);
		void* start0 = &lhs.mData[0];
		void* end0 = &lhs.mData[lhs.mSize - 1];

		void* start1 = &rhs.mData[0];
		void* end1 = &rhs.mData[lhs.mSize - 1];

		return result == 0;
	}

	/**
	 *
	 * @brief (2) Compares the values in the stack
	 * @details Compares the contents of the underlying containers of two container adaptors. @n
	 * 			The comparison is done by applying the corresponding operator to the underlying containers.
	 * 			@n@n
	 * 			Complexity: Linear in the size of the container
	 * @param lhs container adaptors whose contents to compare
	 * @param rhs container adaptors whose contents to compare
	 * @return `true` if the corresponding comparison yields `true`, `false` otherwise
	 *
	 */

	constexpr bool operator!=(const ConstantStack& lhs, const ConstantStack& rhs)
	{
		if (lhs.mSize != rhs.mSize)
		{
			return true;
		}

		return Memory::Memcmp(lhs.mData, rhs.mData, sizeof(const void*) * lhs.mSize) != 0;
	}

#ifdef CAVE_BUILD_DEBUG
	#include <time.h>

	export namespace StackTest
	{
		// DECLARATIONS
		
		void Main();
		
		void Constructor();
		void AssignmentOperator();
		void GetTop();
		void IsEmpty();
		void GetSize();
		void Push();
		void Pop();
		void ComparisonOperator();

		// DEFINITIONS
		void Main()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "======Stack Test======");
			srand(time(nullptr));
;			Constructor();
			AssignmentOperator();
			GetTop();
			IsEmpty();
			GetSize();
			Push();
			Pop();
			ComparisonOperator();
			LOGD(eLogChannel::CORE_CONTAINER, "======Stack Test Success======");
		}

		void Constructor()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Constructor Test====");
			{
				Stack stack0;

				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #1 Success");

				MemoryPool tempPool(1024);
				Stack stack1(tempPool);

				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #2 Success");

				Stack stack2(stack0);
				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #3 Success");

				Stack stack3(stack0, tempPool);
				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #4 Success");

				Stack stack4(std::move(stack3));
				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #3 Success");

				Stack stack5(std::move(stack2), tempPool);
				LOGD(eLogChannel::CORE_CONTAINER, "Constructor #4 Success");
			}
		}

		void AssignmentOperator()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Assignment Operator Test====");
			{
				Stack stack;

				Stack stack0;
				stack0 = stack;

				Stack stack1;
				stack1 = std::move(stack0);
				LOGD(eLogChannel::CORE_CONTAINER, "Assignment Operator Success");
			}
		}
		
		void GetTop()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====GetTop Test====");
			{
				Stack stack;
				stack.Push(nullptr);

				assert(stack.GetTop() == nullptr);
				stack.Pop();
				int* numbers[128] = { nullptr, };
				for (size_t i = 0; i < 128; ++i)
				{
					numbers[i] = reinterpret_cast<int*>(gCoreMemoryPool.Allocate(sizeof(int)));
					*numbers[i] = i;
					stack.Push(numbers[i]);
					assert(stack.GetTop() == numbers[i]);
					assert(*reinterpret_cast<int*>(stack.GetTop()) == *numbers[i]);
				}

				for (size_t i = 0; i < 128; ++i)
				{
					stack.Pop();
				}

				for (size_t i = 0; i < 128; ++i)
				{
					gCoreMemoryPool.Deallocate(numbers[i], sizeof(int));
				}

				LOGD(eLogChannel::CORE_CONTAINER, "GetTop Success");
			}
		}
		
		void IsEmpty()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====IsEmpty Test====");
			{
				Stack stack;
				assert(stack.IsEmpty());
				stack.Push(nullptr);

				assert(!stack.IsEmpty());
				stack.Pop();
				assert(stack.IsEmpty());

				int* numbers[128] = { nullptr, };
				for (size_t i = 0; i < 128; ++i)
				{
					numbers[i] = reinterpret_cast<int*>(gCoreMemoryPool.Allocate(sizeof(int)));
					*numbers[i] = i;
					stack.Push(numbers[i]);
					assert(!stack.IsEmpty());
				}

				for (size_t i = 0; i < 128; ++i)
				{
					stack.Pop();
					if (i == 127)
					{
						assert(stack.IsEmpty());
					}
					else
					{
						assert(!stack.IsEmpty());
					}
				}
				assert(stack.IsEmpty());

				for (size_t i = 0; i < 128; ++i)
				{
					gCoreMemoryPool.Deallocate(numbers[i], sizeof(int));
				}

				LOGD(eLogChannel::CORE_CONTAINER, "IsEmpty Success");
			}
		}
		
		void GetSize()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====GetSize Test====");
			{
				Stack stack;
				assert(stack.GetSize() == 0);
				stack.Push(nullptr);

				assert(stack.GetSize() == 1);
				stack.Pop();
				assert(stack.GetSize() == 0);

				int* numbers[128] = { nullptr, };
				for (size_t i = 0; i < 128; ++i)
				{
					numbers[i] = reinterpret_cast<int*>(gCoreMemoryPool.Allocate(sizeof(int)));
					*numbers[i] = i;
					stack.Push(numbers[i]);
					assert(stack.GetSize() == i + 1);
				}

				for (size_t i = 0; i < 128; ++i)
				{
					stack.Pop();
					assert(stack.GetSize() == 127 - i);
				}
				assert(stack.GetSize() == 0);

				for (size_t i = 0; i < 128; ++i)
				{
					gCoreMemoryPool.Deallocate(numbers[i], sizeof(int));
				}

				LOGD(eLogChannel::CORE_CONTAINER, "GetSize Success");
			}
		}

		void Push()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Push Test====");
			{
				Stack stack;

				int numbers[256] = { 0, };

				size_t index = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					if (index == 0 || index < 256 && rand() % 5 != 0)
					{
						numbers[index] = rand();
						stack.Push(&numbers[index]);
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
						assert(!stack.IsEmpty());
						++index;
						assert(stack.GetSize() == index);
					}
					else
					{
						--index;
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
						void* top = stack.GetTop();
						int* numberTop = &numbers[index];
						assert(top == numberTop);
						numbers[index] = 0;
						stack.Pop();
					}
				}

				LOGD(eLogChannel::CORE_CONTAINER, "Push Success");
			}
		}
		
		void Pop()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Pop Test====");
			{
				Stack stack;

				int numbers[256] = { 0, };

				size_t index = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					if (index == 0 || index < 256 && rand() % 5 != 0)
					{
						numbers[index] = rand();
						stack.Push(&numbers[index]);
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
						assert(!stack.IsEmpty());
						++index;
						assert(stack.GetSize() == index);
					}
					else
					{
						--index;
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
						void* top = stack.GetTop();
						int* numberTop = &numbers[index];
						assert(top == numberTop);
						numbers[index] = 0;
						stack.Pop();
					}
				}

				LOGD(eLogChannel::CORE_CONTAINER, "Pop Success");
			}
		}
		
		void ComparisonOperator()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====ComparisonOperator Test====");
			{
				int numbers0[256] = { 0, };
				int numbers1[256] = { 0, };

				size_t index0 = 0;
				size_t index1 = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					Stack stack0;
					Stack stack1;

					int randomFlag = rand() % 3;
					if (randomFlag == 0)
					{
						size_t randomSize = static_cast<size_t>(rand() % 255) + 1;
						for (size_t i = 0; i < randomSize; ++i)
						{
							numbers0[i] = rand();
							stack0.Push(&numbers0[i]);
							stack1.Push(&numbers0[i]);
							assert(stack0 == stack1);
						}

						assert(stack0 == stack1);

						for (size_t i = 0; i < randomSize; ++i)
						{
							numbers0[i] = 0;
							stack0.Pop();
							stack1.Pop();
							assert(stack0 == stack1);
						}
					}
					else if (randomFlag == 1)
					{
						size_t randomSize = static_cast<size_t>(rand() % 255) + 1;
						for (size_t i = 0; i < randomSize - 1; ++i)
						{
							numbers0[i] = rand();
							numbers1[i] = rand();
							stack0.Push(&numbers0[i]);
							stack1.Push(&numbers1[i]);
						}

						numbers0[randomSize - 1] = 0;
						numbers1[randomSize - 1] = -1;
						stack0.Push(&numbers0[randomSize - 1]);
						stack1.Push(&numbers1[randomSize - 1]);

						assert(stack0 != stack1);

						for (size_t i = 0; i < randomSize; ++i)
						{
							numbers0[i] = 0;
							numbers1[i] = 0;
							stack0.Pop();
							stack1.Pop();
						}
					}
					else
					{
						size_t randomSize0 = static_cast<size_t>(rand() % 255) + 1;
						for (size_t i = 0; i < randomSize0; ++i)
						{
							numbers0[i] = rand();
							stack0.Push(&numbers0[i]);
						}

						size_t randomSize1 = static_cast<size_t>(rand() % 255 - randomSize0) + randomSize0;
						for (size_t i = 0; i < randomSize1; ++i)
						{
							numbers1[i] = rand();
							stack1.Push(&numbers1[i]);
						}

						assert(stack0 != stack1);

						for (size_t i = 0; i < randomSize0; ++i)
						{
							numbers0[i] = 0;
							stack0.Pop();
						}

						for (size_t i = 0; i < randomSize1; ++i)
						{
							numbers1[i] = 0;
							stack1.Pop();
						}
					}
				}

				LOGD(eLogChannel::CORE_CONTAINER, "ComparisonOperator Success");
			}
		}
	}
#endif
} // namespace cave
