/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "Containers/Hash.h"

namespace cave
{
    /*uint64_t GetFileCrc(FILE* s)
    {
        uint8_t buf[32768];
        uint64_t crc = 0;
        uint64_t table[256];
        size_t len;


        MakeCrcTable(table, 0xEDB88320);

        while ((len = fread(buf, 1, sizeof(buf), s)) != 0ul)
        {
            crc = CalculateCrc(buf, static_cast<int64_t>(len), crc, table);
        }

        return crc;
    }


    uint64_t CalculateCrc(const uint8_t* mem, int64_t size, uint64_t crc, uint64_t* outTable)
    {
        crc = ~crc;

        while (size--)
        {
            crc = outTable[(crc ^ *(mem++)) & 0xFF] ^ (crc >> 8);
        }

        return ~crc;
    }


    void MakeCrcTable(uint64_t* outTable, uint64_t id) {
        uint64_t k = 0ull;

        for (uint64_t i = 0; i < 256; ++i)
        {
            k = i;
            for (uint64_t j = 0; j < 8; ++j)
            {
                if (k & 1)
                {
                    k = (k >> 1) ^ id;
                }
                else
                {
                    k >>= 1;
                }
            }
            outTable[i] = k;
        }
    }*/
}