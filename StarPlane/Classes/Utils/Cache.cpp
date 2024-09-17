#include "Cache.h"


namespace Game
{
    inline namespace Utils
    {

        namespace
        {
            Cache *CACHE = nullptr;
        }

        Cache::Cache() :
            data_()
        {
        }

        Cache::DataSizeType Cache::Contains(const ByteType *key, const size_t size) const noexcept
        {
            for (const auto &data : data_)
            {
                if (memcmp(data.first, key, size) == 0)
                {
                    return data.second.second;
                }
            }
            return {nullptr, 0};
        }

        Cache::DataSizeType Cache::Contains(const ByteType *key) const noexcept
        {
            for (const auto &data : data_)
            {
                if (memcmp(data.first, key, data.second.first) == 0)
                {
                    return data.second.second;
                }
            }
            return {nullptr, 0};
        }

        void Cache::Push(const ByteType *key, const ByteType *data, size_t keySize, size_t dataSize) noexcept
        {
            if (!key || !data)
            {
                return;
            }

            ByteType *rKey = static_cast<ByteType *>(malloc(keySize * sizeof(ByteType)));
            ByteType *rData = static_cast<ByteType *>(malloc(dataSize * sizeof(ByteType)));

            if (!rKey || !rData)
            {
                return;
            }


            memcpy(rKey, key, sizeof(ByteType) * keySize);
            memcpy(rData, data, sizeof(ByteType) * dataSize);


            data_.insert({rKey,
                          {
                              keySize,
                              {rData,
                               dataSize
                              }
                          }
            });

        }

        Cache *Cache::ResolveCache() noexcept
        {
            if (!CACHE)
            {
                CACHE = ::new Cache();
            }
            return CACHE;
        }

        void Cache::Release()
        {
            ::delete CACHE;
            CACHE = nullptr;
        }


        Cache::~Cache()
        {
            for (const auto &item : data_)
            {
                void *pKey = item.first;
                void *pData = item.second.second.first;
                free(pKey);
                free(pData);
            }
        }


    }
}
