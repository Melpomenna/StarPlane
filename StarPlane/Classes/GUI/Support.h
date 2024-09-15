#pragma once

#include <type_traits>

namespace Game
{
    namespace GUI
    {

        class Node;

        const char *ReadFile(const char *);

        Node *CreateNode(const char *vertexShader, const char *fragmentShader, const char *texture);


        Node *CreateRectangle(double width, double height);
    }
}
