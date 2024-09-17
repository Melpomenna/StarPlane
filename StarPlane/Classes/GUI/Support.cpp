#include "Support.h"

#include <Utils/Cache.h>

#include <fstream>

#include <GUI/Primitives/Rectangle.h>

#include <glm/gtc/matrix_transform.hpp>

#include <GUI/Render.h>

#include <GUI/Texture.h>


namespace Game
{
    namespace GUI
    {
        const char *ReadFile(const char *data)
        {
            const auto kCachedData = Cache::ResolveCache()->Contains(data);
            if (kCachedData.first != nullptr)
            {
                return kCachedData.first;
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

            const auto render = Render::ResolveRender();

            glm::mat4x4 model = glm::mat4(1.0f);
            glm::mat4x4 projection = glm::ortho(-render->GetWidth(), render->GetWidth(), -render->GetHeight(),
                                                render->GetHeight());
            node->SetModel(model);
            node->SetProjection(projection);

            return node;
        }


        Rectangle *CreateRectangle(const double width, const double height)
        {
            Rectangle *node = ::new Rectangle(width, height);

            const auto render = Render::ResolveRender();

            glm::mat4x4 model = glm::mat4(1.0f);
            glm::mat4x4 projection =
                glm::ortho(-render->GetWidth(), render->GetWidth(), -render->GetHeight(), render->GetHeight());

            node->SetModel(model);
            node->SetProjection(projection);

            return node;
        }


    }
}
