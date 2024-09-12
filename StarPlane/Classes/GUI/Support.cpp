#include "Support.h"

#include <Utils/Cache.h>

#include <fstream>

namespace Game
{
    namespace GUI
    {
        const char* ReadFile(const char *data)
        {
            auto cachedData = Cache::ResolveCache()->Contains(data);
            if (cachedData.first != nullptr)
            {
                return cachedData.first;
            }

            std::ifstream file(data);
            if (!file.is_open())
            {
                return "";
            }

            auto size = file.tellg();
            file.seekg(0, std::ios::beg);
            char *result = ::new char[size]();
            file.read(result, size);
            Cache::ResolveCache()->Push(data, result, strlen(data), size);
            return data;
        }

    }
}
