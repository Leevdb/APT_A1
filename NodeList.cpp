#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i)
    {
        nodes[i] = nullptr;
    }
    length = 0;
}

NodeList::~NodeList()
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i)
    {
        delete nodes[i];
        nodes[i] = nullptr;
    }
}

NodeList::NodeList(NodeList &other)
{
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i)
    {
        delete this->nodes[i];
        nodes[i] = nullptr;
    }
    this->length = other.length;
    for (int i = 0; i < length; ++i)
    {
        nodes[i] = new Node(*other.nodes[i]);
    }
}

int NodeList::getLength()
{
    return length;
}

void NodeList::addElement(Node *newPos)
{
    Node* tempNode = new Node(*newPos);
    if (length < (NODE_LIST_ARRAY_MAX_SIZE - 1))
    {
        nodes[length] = tempNode;
        ++length;
    }
    else
    {
        throw std::runtime_error("Computer says no.");
    }
}

Node *NodeList::getNode(int i)
{
    if (i < 0 || i >= length)
    {
        return nullptr;
    }
    return nodes[i];
}

bool NodeList::checkIfExists(Node *node)
{

    for (int i = 0; i < length; i++)
    {
        if (nodes[i]->isEqual(node))
        {
            return true;
        }
    }
    return false;
}