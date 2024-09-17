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
            friend class Application;

            using ByteType = char;
            using KeyType = ByteType *;
            using DataType = ByteType *;
            using DataSizeType = std::pair<DataType, size_t>;
            using ValueType = std::pair<size_t, DataSizeType>;

            ~Cache();
            static Cache *ResolveCache() noexcept;
            DataSizeType Contains(const ByteType *, size_t) const noexcept;
            DataSizeType Contains(const ByteType *) const noexcept;
            void Push(const ByteType *, const ByteType *, size_t, size_t) noexcept;

        private:
            static void Release();

            Cache();
            std::unordered_map<KeyType, ValueType> data_;
        };

    } // namespace Utils

} // namespace Game
