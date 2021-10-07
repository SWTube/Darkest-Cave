/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.HashSet;

//import cave.Core.Containers.Array;
import cave.Core.Containers.Hash;
import cave.Core.Containers.HashTable;
//import cave.Core.Containers.LinkedList;
//import cave.Core.Memory.Memory;

namespace cave
{
	export class HashSet final
	{
	public:
		HashSet(size_t elementSize);
		explicit HashSet(size_t elementSize, MemoryPool& pool);
		explicit HashSet(size_t elementSize, Hash& hash);
		explicit HashSet(size_t elementSize, Hash& hash, MemoryPool& pool);
		explicit HashSet(size_t elementSize, size_t bucketCount);
		explicit HashSet(size_t elementSize, size_t bucketCount, Hash& hash);
		explicit HashSet(size_t elementSize, size_t bucketCount, MemoryPool& pool);
		explicit HashSet(size_t elementSize, size_t bucketCount, Hash& hash, MemoryPool& pool);
		explicit HashSet(const HashSet& other);
		explicit HashSet(const HashSet& other, MemoryPool& pool);
		explicit HashSet(HashSet&& other);
		explicit HashSet(HashSet&& other, MemoryPool& pool);
		~HashSet() = default;

		constexpr MemoryPool& GetMemoryPool();
		constexpr const MemoryPool& GetMemoryPool() const;

		HashSet& operator=(const HashSet& other);
		HashSet& operator=(HashSet&& other);

		// iterators

		// capacity
		[[nodiscard]] constexpr bool IsEmpty() const;
		constexpr size_t GetSize() const;
		constexpr size_t GetMaxSize() const;

		// modifiers
		//constexpr void Clear();
		void Clear();
		bool Insert(void* key);
		bool Erase(const void* key);

		// lookup
		//constexpr void* At(const void* key);
		bool Contains(const void* key) const;

		// bucket interface
		constexpr size_t GetBucketCount() const;
		//constexpr size_t GetBucketSize(size_t index) const;
		size_t GetBucketSize(size_t index) const;

		// hash policy

		// observers
	protected:
		HashTable mHashTable;
	};

	// constructors
	HashSet::HashSet(size_t elementSize)
		: HashSet(elementSize, HashTable::DEFAULT_BUCKET_COUNT, gHash, gCoreMemoryPool)
	{
	}

	HashSet::HashSet(size_t elementSize, MemoryPool& pool)
		: HashSet(elementSize, HashTable::DEFAULT_BUCKET_COUNT, gHash, pool)
	{
	}

	HashSet::HashSet(size_t elementSize, Hash& hash)
		: HashSet(elementSize, HashTable::DEFAULT_BUCKET_COUNT, hash, gCoreMemoryPool)
	{
	}

	HashSet::HashSet(size_t elementSize, Hash& hash, MemoryPool& pool)
		: HashSet(elementSize, HashTable::DEFAULT_BUCKET_COUNT, hash, pool)
	{
	}

	HashSet::HashSet(size_t elementSize, size_t bucketCount)
		: HashSet(elementSize, bucketCount, gHash, gCoreMemoryPool)
	{
	}

	HashSet::HashSet(size_t elementSize, size_t bucketCount, Hash& hash)
		: HashSet(elementSize, bucketCount, hash, gCoreMemoryPool)
	{
	}

	HashSet::HashSet(size_t elementSize, size_t bucketCount, MemoryPool& pool)
		: HashSet(elementSize, bucketCount, gHash, pool)
	{
	}

	HashSet::HashSet(size_t elementSize, size_t bucketCount, Hash& hash, MemoryPool& pool)
		: mHashTable(elementSize, bucketCount, hash, pool)
	{
	}

	HashSet::HashSet(const HashSet& other)
		: mHashTable(other.mHashTable)
	{
	}

	HashSet::HashSet(const HashSet& other, MemoryPool& pool)
		: mHashTable(other.mHashTable, pool)
	{
	}

	HashSet::HashSet(HashSet&& other)
		: mHashTable(std::move(other.mHashTable))
	{
	}

	HashSet::HashSet(HashSet&& other, MemoryPool& pool)
		: mHashTable(std::move(other.mHashTable), pool)
	{
	}

	constexpr MemoryPool& HashSet::GetMemoryPool()
	{
		return mHashTable.GetMemoryPool();
	}

	constexpr const MemoryPool& HashSet::GetMemoryPool() const
	{
		return mHashTable.GetMemoryPool();
	}

	HashSet& HashSet::operator=(const HashSet& other)
	{
		if (this != &other)
		{
			mHashTable = other.mHashTable;
		}

		return *this;
	}

	HashSet& HashSet::operator=(HashSet&& other)
	{
		if (this != &other)
		{
			mHashTable = std::move(other.mHashTable);
		}

		return *this;
	}

	// iterators

	// capacity
	constexpr bool HashSet::IsEmpty() const
	{
		return mHashTable.IsEmpty();
	}

	constexpr size_t HashSet::GetSize() const
	{
		return mHashTable.GetSize();
	}

	constexpr size_t HashSet::GetMaxSize() const
	{
		return mHashTable.GetMaxSize();
	}

	// modifiers
	//constexpr void HashSet::Clear()
	void HashSet::Clear()
	{
		mHashTable.Clear();
	}

	bool HashSet::Insert(void* key)
	{
		return mHashTable.Insert(key, key);
	}

	bool HashSet::Erase(const void* key)
	{
		return mHashTable.Erase(key);
	}

	// lookup
	bool HashSet::Contains(const void* key) const
	{
		return mHashTable.Contains(key);
	}

	constexpr size_t HashSet::GetBucketCount() const
	{
		return mHashTable.GetBucketCount();
	}

	//constexpr size_t HashSet::GetBucketSize(size_t index) const
	size_t HashSet::GetBucketSize(size_t index) const
	{
		return mHashTable.GetBucketSize(index);
	}

//#ifdef CAVE_BUILD_DEBUG
//	#include "Debug/Log.h"
//
//	export namespace HashSetTest
//	{
//		// DECLARATIONS
//
//		void Main();
//		void Constructor();
//		void AssignmentOperator();
//		void Iterator();
//		void Capacity();
//		void Modifiers();
//		void Lookup();
//		void BucketInterface();
//
//		// DEFINITIONS
//		void Main()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "======HashSet Test======");
//			srand(time(nullptr));
//			Constructor();
//			AssignmentOperator();
//			Iterator();
//			Capacity();
//			Modifiers();
//			Lookup();
//			BucketInterface();
//			LOGD(eLogChannel::CORE_CONTAINER, "======HashSet Test Success======");
//		}
//
//		void Constructor()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Constructor Test====");
//			{
//				HashSet hashSet1(sizeof(int32_t));
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #1 Success");
//
//				MemoryPool temp(1024);
//				HashSet hashSet2(sizeof(int32_t), temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #2 Success");
//
//				Hash tHash(eHashId::NORMAL_REPRESENTATION);
//				HashSet hashSet3(sizeof(int32_t), tHash);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #3 Success");
//
//				HashSet hashSet4(sizeof(int32_t), tHash, temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #4 Success");
//
//				HashSet hashSet5(sizeof(int32_t), gPrimeNumberArray[20]);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #5 Success");
//
//				HashSet hashSet6(sizeof(int32_t), gPrimeNumberArray[30], tHash);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #6 Success");
//
//				HashSet hashSet7(sizeof(int32_t), gPrimeNumberArray[30], temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #7 Success");
//
//				HashSet hashSet8(sizeof(int32_t), gPrimeNumberArray[40], tHash, temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #8 Success");
//
//				HashSet hashSet9(hashSet1);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #9 Success");
//
//				HashSet hashSet10(hashSet1, temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #10 Success");
//
//				HashSet hashSet11(std::move(hashSet9));
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #11 Success");
//
//				HashSet hashSet12(std::move(hashSet11), temp);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #12 Success");
//			}
//		}
//
//		void AssignmentOperator()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Assignment Operator Test====");
//			{
//				HashSet copiedHashTable(sizeof(int32_t));
//				HashSet movedHashTable(sizeof(int32_t));
//				HashSet hashSet1(sizeof(int32_t));
//
//				copiedHashTable = hashSet1;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #1 Success");
//
//				MemoryPool temp(1024);
//				HashSet hashSet2(sizeof(int32_t), temp);
//				copiedHashTable = hashSet2;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #2 Success");
//
//				Hash tHash(eHashId::NORMAL_REPRESENTATION);
//				HashSet hashSet3(sizeof(int32_t), tHash);
//				copiedHashTable = hashSet3;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #3 Success");
//
//				HashSet hashSet4(sizeof(int32_t), tHash, temp);
//				copiedHashTable = hashSet4;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #4 Success");
//
//				HashSet hashSet5(sizeof(int32_t), gPrimeNumberArray[20]);
//				copiedHashTable = hashSet5;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #5 Success");
//
//				HashSet hashSet6(sizeof(int32_t), gPrimeNumberArray[30], tHash);
//				copiedHashTable = hashSet6;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #6 Success");
//
//				HashSet hashSet7(sizeof(int32_t), gPrimeNumberArray[30], temp);
//				copiedHashTable = hashSet7;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #7 Success");
//
//				HashSet hashSet8(sizeof(int32_t), gPrimeNumberArray[40], tHash, temp);
//				copiedHashTable = hashSet8;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #8 Success");
//
//				HashSet hashSet9(hashSet1);
//				copiedHashTable = hashSet9;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #9 Success");
//
//				HashSet hashSet10(hashSet1, temp);
//				copiedHashTable = hashSet10;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #10 Success");
//
//				HashSet hashSet11(std::move(hashSet9));
//				copiedHashTable = hashSet11;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #11 Success");
//
//				HashSet hashSet12(std::move(hashSet11), temp);
//				copiedHashTable = hashSet12;
//				movedHashTable = std::move(copiedHashTable);
//				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #12 Success");
//			}
//		}
//
//		void Iterator()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Iterator Test====");
//			{
//				LOGD(eLogChannel::CORE_CONTAINER, "\tIterator Success");
//			}
//		}
//
//		void Capacity()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Capacity Test====");
//			{
//				HashSet hashSet(sizeof(size_t));
//				assert(hashSet.IsEmpty());
//
//				size_t indices[256] = { 0, };
//
//				size_t index = 0;
//				for (size_t i = 0; i < 131072; ++i)
//				{
//					if (index == 0 || index < 256 && rand() % 5 != 0)
//					{
//						indices[index] = index;
//						//stack.Push(&numbers[index]);
//						hashSet.Insert(&indices[index]);
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
//						assert(!hashSet.IsEmpty());
//						++index;
//						assert(hashSet.GetSize() == index);
//					}
//					else
//					{
//						--index;
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
//						hashSet.Erase(&indices[index]);
//						indices[index] = 0;
//						assert(hashSet.GetSize() == index);
//					}
//				}
//
//				LOGD(eLogChannel::CORE_CONTAINER, "\tCapacity Success");
//			}
//		}
//
//		void Modifiers()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Modifiers Test====");
//			{
//				HashSet hashSet(sizeof(size_t));
//				assert(hashSet.IsEmpty());
//
//				size_t indices[256] = { 0, };
//
//				size_t index = 0;
//				for (size_t i = 0; i < 131072; ++i)
//				{
//					if (index == 0 || index < 256 && rand() % 5 != 0)
//					{
//						indices[index] = index;
//
//						//stack.Push(&numbers[index]);
//						hashSet.Insert(&indices[index]);
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
//						assert(!hashSet.IsEmpty());
//						++index;
//						assert(hashSet.GetSize() == index);
//					}
//					else
//					{
//						--index;
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
//						hashSet.Erase(&indices[index]);
//						indices[index] = 0;
//						assert(hashSet.GetSize() == index);
//					}
//				}
//				hashSet.Clear();
//				assert(hashSet.GetSize() == 0);
//				assert(hashSet.IsEmpty());
//
//				LOGD(eLogChannel::CORE_CONTAINER, "\tModifiers Success");
//			}
//		}
//
//		void Lookup()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====Lookup Test====");
//			{
//				HashSet hashSet(sizeof(size_t));
//				assert(hashSet.IsEmpty());
//
//				size_t indices[256] = { 0, };
//
//				size_t index = 0;
//				for (size_t i = 0; i < 131072; ++i)
//				{
//					if (index == 0 || index < 256 && rand() % 5 != 0)
//					{
//						indices[index] = index;
//
//						//stack.Push(&numbers[index]);
//						hashSet.Insert(&indices[index]);
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
//
//						assert(!hashSet.IsEmpty());
//						++index;
//						assert(hashSet.GetSize() == index);
//						assert(hashSet.Contains(&indices[index - 1]));
//					}
//					else
//					{
//						--index;
//						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
//						hashSet.Erase(&indices[index]);
//						indices[index] = 0;
//						assert(hashSet.GetSize() == index);
//					}
//				}
//				hashSet.Clear();
//				assert(hashSet.GetSize() == 0);
//				assert(hashSet.IsEmpty());
//
//				LOGD(eLogChannel::CORE_CONTAINER, "\tLookup Success");
//			}
//		}
//
//		void BucketInterface()
//		{
//			LOGD(eLogChannel::CORE_CONTAINER, "====BucketInterface Test====");
//			{
//
//				LOGD(eLogChannel::CORE_CONTAINER, "BucketInterface Success");
//			}
//		}
//	}
//#endif
}