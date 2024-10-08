#pragma once

#include <string>

namespace Game
{
    namespace GUI
    {

        class Node;

        const char *ReadFile(const char *);

        Node *CreateNode(const char *vertexShader, const char *fragmentShader, const char *texture);


        Node *CreateRectangle(double width, double height);

        Node *CreateText(std::string &&fontName, std::string &&text, unsigned int fontSize);

    }
}
