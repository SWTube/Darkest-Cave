/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

module;

#include "CoreTypes.h"

export module Hash;

import Memory;

namespace cave
{
    uint32_t DefaultHashFunction(const void* key, size_t size, uint32_t* table);

    export enum class eHashId : uint32_t
    {
        DEFAULT_ID = 0xEDB88320,
        NORMAL_REPRESENTATION = 0x04C11DB7,
    };

    export class Hash
    {
    public:
        constexpr Hash();
        constexpr Hash(uint32_t(*hashFunction)(const void*, size_t, uint32_t*));
        constexpr Hash(eHashId hashId);
        constexpr Hash(eHashId hashId, uint32_t(*hashFunction)(const void*, size_t, uint32_t*));
        constexpr Hash(const Hash& other) = default;
        constexpr Hash(Hash&& other) = default;
        constexpr Hash& operator=(const Hash& other) = default;
        constexpr Hash& operator=(Hash&& other) = default;
        ~Hash();

        constexpr void SetHashId(eHashId hashId);

        void SetHashFunction(uint32_t(*hashFunction)(const void*, size_t, uint32_t*));
        uint32_t GetHash(const void* key, size_t size);
    protected:
        constexpr void initialize();
        constexpr void initialize(uint32_t(*hashFunction)(const void*, size_t, uint32_t*));
        constexpr void initialize(eHashId hashId);
        constexpr void initialize(eHashId hashId, uint32_t(*hashFunction)(const void*, size_t, uint32_t*));

        static constexpr uint32_t TABLE_SIZE = 256u;
        eHashId mHashId = eHashId::DEFAULT_ID;
        uint32_t mTable[TABLE_SIZE] = { 0u, };
        uint32_t(*mHashFunction)(const void*, size_t, uint32_t*) = nullptr;
    };

    constexpr Hash::Hash()
        : Hash(eHashId::DEFAULT_ID, DefaultHashFunction)
    {
    }

    constexpr Hash::Hash(eHashId hashId)
        : Hash(hashId, DefaultHashFunction)
    {
    }

    constexpr Hash::Hash(uint32_t(*hashFunction)(const void*, size_t, uint32_t*))
        : Hash(eHashId::DEFAULT_ID, hashFunction)
    {
    }

    constexpr Hash::Hash(eHashId hashId, uint32_t(*hashFunction)(const void*, size_t, uint32_t*))
        : mHashId(hashId)
        , mHashFunction(hashFunction)
    {
        uint32_t k = 0ull;

        for (uint32_t i = 0; i < 256; ++i)
        {
            k = i;
            for (uint32_t j = 0; j < 8; ++j)
            {
                if (k & 1)
                {
                    k = (k >> 1) ^ static_cast<uint32_t>(mHashId);
                }
                else
                {
                    k >>= 1;
                }
            }
            mTable[i] = k;
        }
    }

    Hash::~Hash()
    {
        mHashFunction = nullptr;
    }

    constexpr void Hash::initialize()
    {
        initialize(eHashId::DEFAULT_ID, DefaultHashFunction);
    }

    constexpr void Hash::initialize(uint32_t(*hashFunction)(const void*, size_t, uint32_t*))
    {
        initialize(eHashId::DEFAULT_ID, hashFunction);
    }

    constexpr void Hash::initialize(eHashId hashId)
    {
        initialize(hashId, DefaultHashFunction);
    }

    constexpr void Hash::initialize(eHashId hashId, uint32_t(*hashFunction)(const void*, size_t, uint32_t*))
    {
        if (mHashFunction != nullptr)
        {
            mHashId = hashId;
            mHashFunction = hashFunction;
            uint32_t k = 0ull;

            for (uint32_t i = 0; i < 256; ++i)
            {
                k = i;
                for (uint32_t j = 0; j < 8; ++j)
                {
                    if (k & 1)
                    {
                        k = (k >> 1) ^ static_cast<uint32_t>(mHashId);
                    }
                    else
                    {
                        k >>= 1;
                    }
                }
                mTable[i] = k;
            }
        }
    }

    constexpr void Hash::SetHashId(eHashId hashId)
    {
        initialize(hashId);
    }

    void Hash::SetHashFunction(uint32_t(*hashFunction)(const void*, size_t, uint32_t*))
    {
        mHashFunction = hashFunction;
    }

    uint32_t Hash::GetHash(const void* key, size_t size)
    {
        return mHashFunction(key, size, mTable);
    }

    uint32_t DefaultHashFunction(const void* key, size_t size, uint32_t* table)
    {
        uint32_t crc32 = 0xFFFFFFFF;
        size_t capacity = GetUpperPowerOfTwo(static_cast<size_t>(size));
        for (size_t i = 0; i < capacity; ++i)
        {
            // SPECTRE MITIGATION
            // https://docs.microsoft.com/en-us/cpp/security/developer-guidance-speculative-execution?view=msvc-160
            // https://en.wikipedia.org/wiki/Spectre_(security_vulnerability)#Mitigation
            i &= (capacity - 1);
            uint32_t index = (crc32 ^ reinterpret_cast<const uint8_t*>(key)[i]) & 0xFF;
            crc32 = (crc32 >> 8) ^ table[index];
        }

        crc32 ^= 0xFFFFFFFF;

        return crc32;
    }

    // http://mwultong.blogspot.com/2006/05/c-c-crc32.html
    // uint64_t GetFileCrc(FILE*);
    // uint64_t CalculateCrc(const uint8_t*, int64_t, uint64_t, uint64_t*);
    // void MakeCrcTable(uint64_t* outTable, uint64_t id);
}