#pragma once

#include <unordered_map>
#include <utility>

namespace Game
{

    inline namespace Utils
    {

        class Cache final
        {
        public:
            using ByteType = char;
            using KeyType = ByteType *;
            using DataType = ByteType *;
            using DataSizeType = std::pair<DataType, size_t>;
            using ValueType = std::pair<size_t, DataSizeType>;

            ~Cache();
            static Cache *ResolveCache() noexcept;
            DataSizeType Contains(const ByteType *, size_t size) const noexcept;
            DataSizeType Contains(const ByteType *) const noexcept;
            void Push(const ByteType *, const ByteType *, size_t keySize, size_t dataSize) noexcept;

            static void Release();

        private:
            Cache();
            std::unordered_map<KeyType, ValueType> data_;
        };

    } // namespace Utils

} // namespace Game
