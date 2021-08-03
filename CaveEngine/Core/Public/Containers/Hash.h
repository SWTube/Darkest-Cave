/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#pragma once

#include "CoreTypes.h"

#include "CoreGlobals.h"
#include "Memory/Memory.h"

namespace cave
{
    enum class eHashId : uint32_t
    {
        DEFAULT_ID = 0xEDB88320,
    };

    template <eHashId ID = eHashId::DEFAULT_ID>
    class Hashable
    {
    public:
        constexpr Hashable(uint8_t* bytes, size_t data);
        constexpr Hashable(const Hashable& other);
        constexpr Hashable(Hashable&& other);
        constexpr Hashable& operator=(const Hashable& other);
        constexpr Hashable& operator=(Hashable&& other);
        virtual ~Hashable();

        virtual uint32_t GetHash() const;
    protected:
        constexpr Hashable();
        virtual void update(uint8_t* bytes, size_t size);
        virtual void setSize(size_t size);

        size_t mSize;
        uint8_t* mBytes;
        constexpr static uint32_t TABLE_SIZE = 256u;
        static uint64_t msRefCount;
        static uint32_t* msTable;
    };

    template <eHashId ID>
    uint32_t* Hashable<ID>::msTable = nullptr;

    template <eHashId ID>
    uint64_t Hashable<ID>::msRefCount = 0ull;

    template <eHashId ID>
    constexpr Hashable<ID>::Hashable()
        : mSize(0u)
        , mBytes(nullptr)
    {
        ++msRefCount;
        if (msTable == nullptr)
        {
            msTable = reinterpret_cast<uint32_t*>(gCoreMemoryPool.Allocate(sizeof(uint32_t) * TABLE_SIZE));

            uint32_t k = 0ull;

            for (uint32_t i = 0; i < 256; ++i)
            {
                k = i;
                for (uint32_t j = 0; j < 8; ++j)
                {
                    if (k & 1)
                    {
                        k = (k >> 1) ^ static_cast<uint32_t>(ID);
                    }
                    else
                    {
                        k >>= 1;
                    }
                }
                msTable[i] = k;
            }
        }
    }

    template <eHashId ID>
    constexpr Hashable<ID>::Hashable(uint8_t* bytes, size_t size)
        : mSize(size)
        , mBytes(bytes)
    {
        ++msRefCount;
        if (msTable == nullptr)
        {
            msTable = reinterpret_cast<uint32_t*>(gCoreMemoryPool.Allocate(sizeof(uint32_t) * TABLE_SIZE));

            uint32_t k = 0ull;

            for (uint32_t i = 0; i < 256; ++i)
            {
                k = i;
                for (uint32_t j = 0; j < 8; ++j)
                {
                    if (k & 1)
                    {
                        k = (k >> 1) ^ static_cast<uint32_t>(ID);
                    }
                    else
                    {
                        k >>= 1;
                    }
                }
                msTable[i] = k;
            }
        }
    }

    template <eHashId ID>
    constexpr Hashable<ID>::Hashable(const Hashable& other)
        : mSize(other.mSize)
        , mBytes(other.mBytes)
    {
        ++msRefCount;
    }

    template <eHashId ID>
    constexpr Hashable<ID>::Hashable(Hashable&& other)
        : mSize(other.mSize)
        , mBytes(other.mBytes)
    {
        other.mSize = 0u;
        other.mBytes = nullptr;
    }

    template <eHashId ID>
    constexpr Hashable<ID>& Hashable<ID>::operator=(const Hashable& other)
    {
        if (this != &other)
        {
            mSize = other.mSize;
            mBytes = other.mBytes;
            ++msRefCount;
        }

        return *this;
    }

    template <eHashId ID>
    constexpr Hashable<ID>& Hashable<ID>::operator=(Hashable&& other)
    {
        if (this != &other)
        {
            mSize = other.mSize;
            mBytes = other.mBytes;
            other.mSize = 0u;
            other.mBytes = nullptr;
        }

        return *this;
    }

    template <eHashId ID>
    Hashable<ID>::~Hashable()
    {
        --msRefCount;

        if (msRefCount <= 0)
        {
            gCoreMemoryPool.Deallocate(msTable, sizeof(uint32_t) * TABLE_SIZE);
        }
    }

    template <eHashId ID>
    uint32_t Hashable<ID>::GetHash() const
    {
        uint32_t crc32 = 0xFFFFFFFF;
        size_t capacity = GetUpperPowerOfTwo(static_cast<size_t>(mSize));
        for (size_t i = 0; i < capacity; ++i)
        {
            // SPECTRE MITIGATION
            // https://docs.microsoft.com/en-us/cpp/security/developer-guidance-speculative-execution?view=msvc-160
            // https://en.wikipedia.org/wiki/Spectre_(security_vulnerability)#Mitigation
            i &= (capacity - 1);
            uint32_t index = (crc32 ^ mBytes[i]) & 0xFF;
            crc32 = (crc32 >> 8) ^ msTable[index];
        }

        crc32 ^= 0xFFFFFFFF;

        return crc32;
    }

    template <eHashId ID>
    void Hashable<ID>::update(uint8_t* bytes, size_t size)
    {
        mBytes = bytes;
        mSize = size;
    }

    template <eHashId ID>
    void Hashable<ID>::setSize(size_t size)
    {
        mSize = size;
    }

    // http://mwultong.blogspot.com/2006/05/c-c-crc32.html
    // uint64_t GetFileCrc(FILE*);
    // uint64_t CalculateCrc(const uint8_t*, int64_t, uint64_t, uint64_t*);
    // void MakeCrcTable(uint64_t* outTable, uint64_t id);
}