#pragma once

#include <type_traits>

namespace Game
{
    namespace GUI
    {

        class Node;

        const char *ReadFile(const char *);

        Node *CreateNodeFromObjFile(const char *);


    }
}
