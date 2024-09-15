#define USING_WINAPI
#include <Utils/Config.h>

#include "Support.h"

#include <Utils/Cache.h>

#include <fstream>

#include <GUI/Primitives/Rectangle.h>

#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

#include <GUI/Texture.h>

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
            file.close();
            Cache::ResolveCache()->Push(data, result, strlen(data), size);
            return result;
        }

        Node *CreateNode(const char *vertexShader, const char *fragmentShader, const char *texture)
        {
            Node *node = ::new Node(vertexShader, fragmentShader, GL_DYNAMIC_DRAW);

            node->LoadTexture(texture);

            glm::mat4x4 model = glm::mat4(1.0f);
            glm::mat4x4 projection = glm::ortho(-static_cast<float>(APP_WIDTH), static_cast<float>(APP_WIDTH),
                                                -static_cast<float>(APP_HEIGHT), static_cast<float>(APP_HEIGHT));
            node->SetModel(model);
            node->SetProjection(projection);
            return node;
        }


        Node *CreateRectangle(double width, double height)
        {
            Node *node = ::new Rectangle(width, height);

            glm::mat4x4 model = glm::mat4(1.0f);
            glm::mat4x4 projection = glm::ortho(-static_cast<float>(APP_WIDTH), static_cast<float>(APP_WIDTH),
                                                -static_cast<float>(APP_HEIGHT), static_cast<float>(APP_HEIGHT));
            node->SetModel(model);
            node->SetProjection(projection);
            return node;
        }


    }
}
