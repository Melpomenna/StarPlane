#include "Support.h"

#include <Utils/Cache.h>

#include <fstream>

#include <GUI/Node.h>

namespace Game
{
    namespace GUI
    {
        const char *ReadFile(const char *data)
        {
            auto cachedData = Cache::ResolveCache()->Contains(data);
            if (cachedData.first != nullptr)
            {
                return cachedData.first;
            }

            std::ifstream file(data);
            if (!file.is_open())
            {
                return nullptr;
            }

            file.seekg(0, std::ios::end);
            auto size = file.tellg();
            file.seekg(0, std::ios::beg);
            char *result = ::new char[size]();
            file.read(result, size);
            Cache::ResolveCache()->Push(data, result, strlen(data), size);
            return result;
        }

        Node *CreateNodeFromObjFile(const char *file)
        {
            auto data = ReadFile(file);
            if (data == nullptr)
            {
                return nullptr;
            }

            auto cacheData = Cache::ResolveCache()->Contains(data);
            if (cacheData.first != nullptr)
            {
                Node *node = static_cast<Node *>(malloc(sizeof(Node)));
                Node *cached = reinterpret_cast<Node *>(const_cast<char *>(cacheData.first));
                ::new(node) Node(*cached);
                return node;
            }

            // Logic for import

            Node *node = ::new Node();

            // cache data

            return node;
        }


    }
}
