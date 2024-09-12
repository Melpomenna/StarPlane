#pragma once

#include <unordered_map>
#include <memory>
#include <utility>

namespace Game
{

    inline namespace Utils
    {

        class Cache final
        {
        public:
            using ByteType = char;
            using KeyType = const ByteType *;
            using DataType = const ByteType *;
            using DataSizeType = std::pair<DataType, size_t>;
            using ValueType = std::pair<size_t, DataSizeType>;

            ~Cache();
            static Cache *ResolveCache() noexcept;
            DataSizeType Contains(KeyType, size_t size) const noexcept;
            DataSizeType Contains(KeyType) const noexcept;
            void Push(KeyType, DataType, size_t keySize, size_t dataSize) noexcept;

			static void Release();

        private:
            Cache() = default;
            std::unordered_map<KeyType, ValueType> data_;
        };

    } // namespace Utils

} // namespace Game
