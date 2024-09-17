#pragma once

#include <type_traits>

namespace Game
{
    namespace GUI
    {

        class Node;
        class Rectangle;

        const char *ReadFile(const char *);

        Node *CreateNode(const char *vertexShader, const char *fragmentShader, const char *texture);


        Rectangle *CreateRectangle(double width, double height);
    }
}
