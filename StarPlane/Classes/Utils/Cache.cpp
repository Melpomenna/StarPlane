#include "Cache.h"


namespace Game
{
    inline namespace Utils
    {

        namespace
        {
            Cache *cache = nullptr;
        }

        Cache::DataSizeType Cache::Contains(KeyType key, size_t size) const noexcept
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

        Cache::DataSizeType Cache::Contains(KeyType key) const noexcept
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

        void Cache::Push(KeyType key, DataType data, size_t keySize, size_t dataSize) noexcept
        {
            KeyType kKey = ::new ByteType[keySize]();
            DataType kData = ::new ByteType[dataSize]();


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
            delete[] cache;
            cache = nullptr;
        }


        Cache::~Cache()
        {
            for (const auto &item : data_)
            {
                delete[] item.first;
                delete[] item.second.second.first;
            }
        }


    }
}
