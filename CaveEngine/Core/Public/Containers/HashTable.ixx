/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include <list>
#include <vector>

#include "CoreGlobals.h"
#include "Memory/MemoryPool.h"

export module cave.Core.Containers.HashTable;

import cave.Core.Containers.Array;
import cave.Core.Containers.Hash;
import cave.Core.Containers.LinkedList;
import cave.Core.Memory.Memory;
import cave.Core.Containers.Pair;

namespace cave
{
	/// gPrimeNumberArray
	///
	/// This is an array of prime numbers. This is the same set of prime
	/// numbers suggested by the C++ standard proposal. These are numbers
	/// which are separated by 8% per entry.
	/// 
	/// To consider: Allow the user to specify their own prime number array.
	///
	constexpr const uint32_t gPrimeNumberArray[] =
	{
		2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
		37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u, 79u,
		83u, 89u, 97u, 103u, 109u, 113u, 127u, 137u, 139u, 149u,
		157u, 167u, 179u, 193u, 199u, 211u, 227u, 241u, 257u,
		277u, 293u, 313u, 337u, 359u, 383u, 409u, 439u, 467u,
		503u, 541u, 577u, 619u, 661u, 709u, 761u, 823u, 887u,
		953u, 1031u, 1109u, 1193u, 1289u, 1381u, 1493u, 1613u,
		1741u, 1879u, 2029u, 2179u, 2357u, 2549u, 2753u, 2971u,
		3209u, 3469u, 3739u, 4027u, 4349u, 4703u, 5087u, 5503u,
		5953u, 6427u, 6949u, 7517u, 8123u, 8783u, 9497u, 10273u,
		11113u, 12011u, 12983u, 14033u, 15173u, 16411u, 17749u,
		19183u, 20753u, 22447u, 24281u, 26267u, 28411u, 30727u,
		33223u, 35933u, 38873u, 42043u, 45481u, 49201u, 53201u,
		57557u, 62233u, 67307u, 72817u, 78779u, 85229u, 92203u,
		99733u, 107897u, 116731u, 126271u, 136607u, 147793u,
		159871u, 172933u, 187091u, 202409u, 218971u, 236897u,
		256279u, 277261u, 299951u, 324503u, 351061u, 379787u,
		410857u, 444487u, 480881u, 520241u, 562841u, 608903u,
		658753u, 712697u, 771049u, 834181u, 902483u, 976369u,
		1056323u, 1142821u, 1236397u, 1337629u, 1447153u, 1565659u,
		1693859u, 1832561u, 1982627u, 2144977u, 2320627u, 2510653u,
		2716249u, 2938679u, 3179303u, 3439651u, 3721303u, 4026031u,
		4355707u, 4712381u, 5098259u, 5515729u, 5967347u, 6456007u,
		6984629u, 7556579u, 8175383u, 8844859u, 9569143u, 10352717u,
		11200489u, 12117689u, 13109983u, 14183539u, 15345007u,
		16601593u, 17961079u, 19431899u, 21023161u, 22744717u,
		24607243u, 26622317u, 28802401u, 31160981u, 33712729u,
		36473443u, 39460231u, 42691603u, 46187573u, 49969847u,
		54061849u, 58488943u, 63278561u, 68460391u, 74066549u,
		80131819u, 86693767u, 93793069u, 101473717u, 109783337u,
		118773397u, 128499677u, 139022417u, 150406843u, 162723577u,
		176048909u, 190465427u, 206062531u, 222936881u, 241193053u,
		260944219u, 282312799u, 305431229u, 330442829u, 357502601u,
		386778277u, 418451333u, 452718089u, 489790921u, 529899637u,
		573292817u, 620239453u, 671030513u, 725980837u, 785430967u,
		849749479u, 919334987u, 994618837u, 1076067617u, 1164186217u,
		1259520799u, 1362662261u, 1474249943u, 1594975441u,
		1725587117u, 1866894511u, 2019773507u, 2185171673u,
		2364114217u, 2557710269u, 2767159799u, 2993761039u,
		3238918481u, 3504151727u, 3791104843u, 4101556399u,
		4294967291u,
		4294967291u // Sentinel so we don't have to test result of lower_bound
	};

	/// gPrimeCount
	///
	/// The number of prime numbers in gPrimeNumberArray.
	///
	constexpr const size_t gPrimeCount = (sizeof(gPrimeNumberArray) / sizeof(gPrimeNumberArray[0]) - 1);

	export class HashTable final
	{
	public:
		HashTable(size_t elementSize);
		explicit HashTable(size_t elementSize, MemoryPool& pool);
		explicit HashTable(size_t elementSize, Hash& hash);
		explicit HashTable(size_t elementSize, Hash& hash, MemoryPool& pool);
		explicit HashTable(size_t elementSize, size_t bucketCount);
		explicit HashTable(size_t elementSize, size_t bucketCount, Hash& hash);
		explicit HashTable(size_t elementSize, size_t bucketCount, MemoryPool& pool);
		explicit HashTable(size_t elementSize, size_t bucketCount, Hash& hash, MemoryPool& pool);
		explicit HashTable(const HashTable& other);
		explicit HashTable(const HashTable& other, MemoryPool& pool);
		explicit HashTable(HashTable&& other);
		explicit HashTable(HashTable&& other, MemoryPool& pool);
		~HashTable() = default;

		constexpr MemoryPool& GetMemoryPool();
		constexpr const MemoryPool& GetMemoryPool() const;

		HashTable& operator=(const HashTable& other);
		HashTable& operator=(HashTable&& other);

		// iterators

		// capacity
		constexpr bool IsEmpty() const;
		constexpr size_t GetSize() const;
		constexpr size_t GetMaxSize() const;

		// modifiers
		//constexpr void Clear();
		void Clear();
		bool Insert(void* key, void* value);
		bool Insert(const Pair& pair);
		bool Insert(Pair&& pair);
		bool Erase(const void* key);

		// lookup
		//constexpr void* At(const void* key);
		void* At(const void* key);
		//constexpr const void* At(const void* key) const;
		const void* At(const void* key) const;
		//constexpr void* operator[](void* key);
		void* operator[](void* key);
		void* Find(const void* key);
		const void* Find(const void* key) const;
		constexpr bool Contains(const void* key) const;

		// bucket interface
		constexpr size_t GetBucketCount() const;
		//constexpr size_t GetBucketSize(size_t index) const;
		size_t GetBucketSize(size_t index) const;

		// hash policy

		// observers

		static constexpr size_t DEFAULT_BUCKET_COUNT = gPrimeNumberArray[10];
	protected:
		MemoryPool* mPool;
		size_t mElementSize = 0u;
		size_t mBucketCount = DEFAULT_BUCKET_COUNT;
		size_t mElementCount = 0u;
		//Array<LinkedList<Pair>> mData;
		std::vector<std::list<Pair>> mData;
		Hash* mHash;
	};

	// constructors
	HashTable::HashTable(size_t elementSize)
		: HashTable(elementSize, DEFAULT_BUCKET_COUNT, gHash, gCoreMemoryPool)
	{
	}

	HashTable::HashTable(size_t elementSize, MemoryPool& pool)
		: HashTable(elementSize, DEFAULT_BUCKET_COUNT, gHash, pool)
	{
	}

	HashTable::HashTable(size_t elementSize, Hash& hash)
		: HashTable(elementSize, DEFAULT_BUCKET_COUNT, hash, gCoreMemoryPool)
	{
	}

	HashTable::HashTable(size_t elementSize, Hash& hash, MemoryPool& pool)
		: HashTable(elementSize, DEFAULT_BUCKET_COUNT, hash, pool)
	{
	}

	HashTable::HashTable(size_t elementSize, size_t bucketCount)
		: HashTable(elementSize, bucketCount, gHash, gCoreMemoryPool)
	{
	}


	HashTable::HashTable(size_t elementSize, size_t bucketCount, Hash& hash)
		: HashTable(elementSize, bucketCount, hash, gCoreMemoryPool)
	{
	}

	HashTable::HashTable(size_t elementSize, size_t bucketCount, MemoryPool& pool)
		: HashTable(elementSize, bucketCount, gHash, pool)
	{
	}

	HashTable::HashTable(size_t elementSize, size_t bucketCount, Hash& hash, MemoryPool& pool)
		: mPool(&pool)
		, mElementSize(elementSize)
		, mBucketCount(bucketCount)
		, mElementCount(0u)
		//, mData(bucketCount, pool)
		, mData(mBucketCount)
		, mHash(&hash)
	{
	}

	HashTable::HashTable(const HashTable& other)
		: mPool(other.mPool)
		, mElementSize(other.mElementSize)
		, mBucketCount(other.mBucketCount)
		, mElementCount(other.mElementCount)
		, mData(other.mData)
	{
	}

	HashTable::HashTable(const HashTable& other, MemoryPool& pool)
		: mPool(&pool)
		, mElementSize(other.mElementSize)
		, mBucketCount(other.mBucketCount)
		, mElementCount(other.mElementCount)
		, mData(other.mData)
	{
	}

	HashTable::HashTable(HashTable&& other)
		: mPool(other.mPool)
		, mElementSize(other.mElementSize)
		, mBucketCount(other.mBucketCount)
		, mElementCount(other.mElementCount)
		, mData(std::move(other.mData))
	{
		other.mPool = nullptr;
		//other.mData.~Array();
		other.mData.clear();
	}

	HashTable::HashTable(HashTable&& other, MemoryPool& pool)
		: mPool(&pool)
		, mElementSize(other.mElementSize)
		, mBucketCount(other.mBucketCount)
		, mElementCount(other.mElementCount)
		, mData(std::move(other.mData))
	{
		other.mPool = nullptr;
		//other.mData.~Array();
		other.mData.clear();
	}

	constexpr MemoryPool& HashTable::GetMemoryPool()
	{
		return *mPool;
	}

	constexpr const MemoryPool& HashTable::GetMemoryPool() const
	{
		return *mPool;
	}

	HashTable& HashTable::operator=(const HashTable& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mElementSize = other.mElementSize;
			mBucketCount = other.mBucketCount;
			mElementCount = other.mElementCount;
			mData = other.mData;
		}

		return *this;
	}

	HashTable& HashTable::operator=(HashTable&& other)
	{
		if (this != &other)
		{
			mPool = other.mPool;
			mElementSize = other.mElementSize;
			mBucketCount = other.mBucketCount;
			mElementCount = other.mElementCount;
			mData = other.mData;

			other.mPool = nullptr;
			//other.mData.~Array();
			other.mData.clear();
		}

		return *this;
	}

	// iterators

	// capacity
	constexpr bool HashTable::IsEmpty() const
	{
		return mElementCount == 0;
	}

	constexpr size_t HashTable::GetSize() const
	{
		return mElementCount;
	}

	constexpr size_t HashTable::GetMaxSize() const
	{
		return mPool->GetFreeMemorySize() / mElementSize;
	}

	// modifiers
	//constexpr void HashTable::Clear()
	void HashTable::Clear()
	{
		//while (!mData[mData.GetSize() - 1].IsEmpty())
		while (!mData[mData.size() - 1].empty())
		{
			//mData[mData.GetSize() - 1].DeleteBack();
			mData[mData.size() - 1].pop_back();
		}
		mElementCount = 0;
	}

	bool HashTable::Insert(void* key, void* value)
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (Pair& pair : mData[index])
		{
			if (Memory::Memcmp(key, pair.GetFirst(), mElementSize) == 0)
			{
				pair.SetSecond(value);
				++mElementCount;
				return true;
			}
		}

		Pair item(key, value);

		//mData[index].InsertBack(item);
		mData[index].push_back(item);
		++mElementCount;
		return true;
	}

	bool HashTable::Insert(const Pair& pair)
	{
		uint32_t index = mHash->GetHash(pair.GetFirst(), mElementSize) % mBucketCount;

		for (Pair& iterPair : mData[index])
		{
			if (Memory::Memcmp(pair.GetFirst(), iterPair.GetFirst(), mElementSize) == 0)
			{
				iterPair = pair;
				++mElementCount;
				return true;
			}
		}

		//mData[index].InsertBack(pair);
		mData[index].push_back(pair);
		++mElementCount;
		return true;
	}

	bool HashTable::Insert(Pair&& pair)
	{
		uint32_t index = mHash->GetHash(pair.GetFirst(), mElementSize) % mBucketCount;

		for (Pair& iterPair : mData[index])
		{
			if (Memory::Memcmp(pair.GetFirst(), iterPair.GetFirst(), mElementSize) == 0)
			{
				iterPair = std::move(pair);
				++mElementCount;
				return true;
			}
		}

		//mData[index].InsertBack(pair);
		mData[index].push_back(pair);
		++mElementCount;
		return true;
	}

	bool HashTable::Erase(const void* key)
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		//for (auto iter = mData[index].GetBeginIterator(); iter != mData[index].GetEndIterator(); ++iter)
		for (auto iter = mData[index].begin(); iter != mData[index].end(); ++iter)
		{
			if (Memory::Memcmp(key, iter->GetFirst(), mElementSize) == 0)
			{
				//mData[index].Delete(iter);
				mData[index].erase(iter);
				--mElementCount;
				return true;
			}
		}

		return false;
	}

	// lookup
	//constexpr void* HashTable::At(const void* key)
	void* HashTable::At(const void* key)
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (Pair& pair : mData[index])
		{
			if (Memory::Memcmp(key, pair.GetFirst(), mElementSize) == 0)
			{
				return pair.GetSecond();
			}
		}

		return nullptr;
	}

	//constexpr const void* HashTable::At(const void* key) const
	const void* HashTable::At(const void* key) const
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (const Pair& pair : mData[index])
		{
			if (Memory::Memcmp(key, pair.GetFirst(), mElementSize) == 0)
			{
				return pair.GetSecond();
			}
		}

		return nullptr;
	}

	//constexpr void* HashTable::operator[](void* key)
	void* HashTable::operator[](void* key)
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (Pair& pair : mData[index])
		{
			if (Memory::Memcmp(key, pair.GetFirst(), mElementSize) == 0)
			{
				return pair.GetSecond();
			}
		}

		Pair item(key, nullptr);

		//mData[index].InsertBack(item);
		mData[index].push_back(item);
		++mElementCount;

		return item.GetSecond();
	}

	void* HashTable::Find(const void* key)
	{
		uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (Pair& pair : mData[index])
		{
			if (Memory::Memcmp(key, pair.GetFirst(), mElementSize) == 0)
			{
				return pair.GetSecond();
			}
		}

		return nullptr;
	}

	const void* HashTable::Find(const void* key) const
	{
		/*uint32_t index = mHash->GetHash(key, mElementSize) % mBucketCount;

		for (const auto iter = mData[index].GetBeginConstIterator(); iter != mData[index].GetEndConstIterator(); ++iter)
		{
			if (Memory::Memcmp(key, *iter.GetFirst(), mElementSize) == 0)
			{
				return *iter.GetSecond();
			}
		}*/

		return nullptr;
	}

	constexpr bool HashTable::Contains(const void* key) const
	{
		return false;
	}

	constexpr size_t HashTable::GetBucketCount() const
	{
		return mBucketCount;
	}

	//constexpr size_t HashTable::GetBucketSize(size_t index) const
	size_t HashTable::GetBucketSize(size_t index) const
	{
		//assert(index < mData.GetSize());
		assert(index < mData.size());

		//return mData[index].GetSize();
		return mData[index].size();
	}

#ifdef CAVE_BUILD_DEBUG
#include "Utils/Crt.h"
#include "Debug/Log.h"

	export namespace HashTableTest
	{
		// DECLARATIONS

		void Main();
		void Constructor();
		void AssignmentOperator();
		void Iterator();
		void Capacity();
		void Modifiers();
		void Lookup();
		void BucketInterface();

		// DEFINITIONS
		void Main()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "======HashTable Test======");
			srand(time(nullptr));
			Constructor();
			AssignmentOperator();
			Iterator();
			Capacity();
			Modifiers();
			Lookup();
			BucketInterface();
			LOGD(eLogChannel::CORE_CONTAINER, "======HashTable Test Success======");
		}

		void Constructor()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Constructor Test====");
			{
				HashTable hashTable1(sizeof(int32_t));
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #1 Success");

				MemoryPool temp(1024);
				HashTable hashTable2(sizeof(int32_t), temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #2 Success");

				Hash tHash(eHashId::NORMAL_REPRESENTATION);
				HashTable hashTable3(sizeof(int32_t), tHash);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #3 Success");

				HashTable hashTable4(sizeof(int32_t), tHash, temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #4 Success");

				HashTable hashTable5(sizeof(int32_t), gPrimeNumberArray[20]);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #5 Success");

				HashTable hashTable6(sizeof(int32_t), gPrimeNumberArray[30], tHash);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #6 Success");

				HashTable hashTable7(sizeof(int32_t), gPrimeNumberArray[30], temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #7 Success");

				HashTable hashTable8(sizeof(int32_t), gPrimeNumberArray[40], tHash, temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #8 Success");

				HashTable hashTable9(hashTable1);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #9 Success");

				HashTable hashTable10(hashTable1, temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #10 Success");

				HashTable hashTable11(std::move(hashTable9));
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #11 Success");

				HashTable hashTable12(std::move(hashTable11), temp);
				LOGD(eLogChannel::CORE_CONTAINER, "\tConstructor #12 Success");
			}
		}

		void AssignmentOperator()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Assignment Operator Test====");
			{
				HashTable copiedHashTable(sizeof(int32_t));
				HashTable movedHashTable(sizeof(int32_t));
				HashTable hashTable1(sizeof(int32_t));

				copiedHashTable = hashTable1;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #1 Success");

				MemoryPool temp(1024);
				HashTable hashTable2(sizeof(int32_t), temp);
				copiedHashTable = hashTable2;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #2 Success");

				Hash tHash(eHashId::NORMAL_REPRESENTATION);
				HashTable hashTable3(sizeof(int32_t), tHash);
				copiedHashTable = hashTable3;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #3 Success");

				HashTable hashTable4(sizeof(int32_t), tHash, temp);
				copiedHashTable = hashTable4;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #4 Success");

				HashTable hashTable5(sizeof(int32_t), gPrimeNumberArray[20]);
				copiedHashTable = hashTable5;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #5 Success");

				HashTable hashTable6(sizeof(int32_t), gPrimeNumberArray[30], tHash);
				copiedHashTable = hashTable6;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #6 Success");

				HashTable hashTable7(sizeof(int32_t), gPrimeNumberArray[30], temp);
				copiedHashTable = hashTable7;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #7 Success");

				HashTable hashTable8(sizeof(int32_t), gPrimeNumberArray[40], tHash, temp);
				copiedHashTable = hashTable8;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #8 Success");

				HashTable hashTable9(hashTable1);
				copiedHashTable = hashTable9;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #9 Success");

				HashTable hashTable10(hashTable1, temp);
				copiedHashTable = hashTable10;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #10 Success");

				HashTable hashTable11(std::move(hashTable9));
				copiedHashTable = hashTable11;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #11 Success");

				HashTable hashTable12(std::move(hashTable11), temp);
				copiedHashTable = hashTable12;
				movedHashTable = std::move(copiedHashTable);
				LOGD(eLogChannel::CORE_CONTAINER, "\tAssignment Operator #12 Success");
			}
		}

		void Iterator()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Iterator Test====");
			{
				LOGD(eLogChannel::CORE_CONTAINER, "\tIterator Success");
			}
		}

		void Capacity()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Capacity Test====");
			{
				HashTable hashTable(sizeof(size_t));
				assert(hashTable.IsEmpty());

				size_t indices[256] = { 0, };
				int numbers[256] = { 0, };

				size_t index = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					if (index == 0 || index < 256 && rand() % 5 != 0)
					{
						numbers[index] = rand();
						indices[index] = index;
						//stack.Push(&numbers[index]);
						hashTable.Insert(&indices[index], &numbers[index]);
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
						assert(!hashTable.IsEmpty());
						++index;
						assert(hashTable.GetSize() == index);
					}
					else
					{
						--index;
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
						hashTable.Erase(&indices[index]);
						numbers[index] = 0;
						indices[index] = 0;
						assert(hashTable.GetSize() == index);
					}
				}

				LOGD(eLogChannel::CORE_CONTAINER, "\tCapacity Success");
			}
		}

		void Modifiers()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Modifiers Test====");
			{
				HashTable hashTable(sizeof(size_t));
				assert(hashTable.IsEmpty());

				size_t indices[256] = { 0, };
				int numbers[256] = { 0, };

				size_t index = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					if (index == 0 || index < 256 && rand() % 5 != 0)
					{

						numbers[index] = rand();
						indices[index] = index;

						if (numbers[index] % 3 == 0)
						{
							//stack.Push(&numbers[index]);
							hashTable.Insert(&indices[index], &numbers[index]);
							//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
						}
						else if (numbers[index] % 3 == 1)
						{
							Pair pair(&indices[index], &numbers[index]);
							hashTable.Insert(pair);
						}
						else
						{
							Pair pair(&indices[index], &numbers[index]);
							hashTable.Insert(std::move(pair));
						}
						assert(!hashTable.IsEmpty());
						++index;
						assert(hashTable.GetSize() == index);
					}
					else
					{
						--index;
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
						hashTable.Erase(&indices[index]);
						numbers[index] = 0;
						indices[index] = 0;
						assert(hashTable.GetSize() == index);
					}
				}
				hashTable.Clear();
				assert(hashTable.GetSize() == 0);
				assert(hashTable.IsEmpty());

				LOGD(eLogChannel::CORE_CONTAINER, "\tModifiers Success");
			}
		}

		void Lookup()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====Lookup Test====");
			{
				HashTable hashTable(sizeof(size_t));
				assert(hashTable.IsEmpty());

				size_t indices[256] = { 0, };
				int numbers[256] = { 0, };

				size_t index = 0;
				for (size_t i = 0; i < 131072; ++i)
				{
					if (index == 0 || index < 256 && rand() % 5 != 0)
					{

						numbers[index] = rand();
						indices[index] = index;

						if (numbers[index] % 3 == 0)
						{
							//stack.Push(&numbers[index]);
							hashTable.Insert(&indices[index], &numbers[index]);
							//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu: PUSH: stack[%lu] = %d", i, index, numbers[index]);
						}
						else if (numbers[index] % 3 == 1)
						{
							Pair pair(&indices[index], &numbers[index]);
							hashTable.Insert(pair);
						}
						else
						{
							Pair pair(&indices[index], &numbers[index]);
							hashTable.Insert(std::move(pair));
						}
						assert(!hashTable.IsEmpty());
						++index;
						assert(hashTable.GetSize() == index);
						assert(hashTable.Find(&indices[index - 1]) == &numbers[index - 1]);
						//assert(hashTable.Contains(&indices[index - 1]));
					}
					else
					{
						--index;
						//LOGDF(eLogChannel::CORE_CONTAINER, "%6lu:  POP: stack[%lu] = %d", i, index, numbers[index]);
						hashTable.Erase(&indices[index]);
						assert(hashTable.Find(&indices[index]) == nullptr);
						//assert(hashTable.Contains(&indices[index]));
						numbers[index] = 0;
						indices[index] = 0;
						assert(hashTable.GetSize() == index);
					}
				}
				hashTable.Clear();
				assert(hashTable.GetSize() == 0);
				assert(hashTable.IsEmpty());

				LOGD(eLogChannel::CORE_CONTAINER, "\tLookup Success");
			}
		}

		void BucketInterface()
		{
			LOGD(eLogChannel::CORE_CONTAINER, "====BucketInterface Test====");
			{

				LOGD(eLogChannel::CORE_CONTAINER, "BucketInterface Success");
			}
		}
	}
#endif
}