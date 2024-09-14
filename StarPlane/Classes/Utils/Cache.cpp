#include "Cache.h"


namespace Game
{
    inline namespace Utils
    {

        namespace
        {
            Cache *cache = nullptr;
        }

        Cache::Cache() :
            data_()
        {
        }

        Cache::DataSizeType Cache::Contains(const ByteType *key, size_t size) const noexcept
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
            for (auto data : data_)
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

            ByteType *kKey = static_cast<ByteType *>(malloc(keySize * sizeof(ByteType)));
            ByteType *kData = static_cast<ByteType *>(malloc(dataSize * sizeof(ByteType)));

            if (!kKey || !kData)
            {
                return;
            }


            memcpy(kKey, key, sizeof(ByteType) * keySize);
            memcpy(kData, data, sizeof(ByteType) * dataSize);


            data_.insert({
                kKey,
                {
                    keySize,
                    {
                        kData,
                        dataSize
                    }
                }
            });

        }

        Cache *Cache::ResolveCache() noexcept
        {
            if (!cache)
            {
                cache = ::new Cache();
            }
            return cache;
        }

        void Cache::Release()
        {
            delete cache;
            cache = nullptr;
        }


        Cache::~Cache()
        {
            for (auto &item : data_)
            {
                void *pKey = item.first;
                void *pData = item.second.second.first;
                free(pKey);
                free(pData);
            }
        }


    }
}
