#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    //setting all values in array to null 
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE ; i++) {
        nodes[i] = nullptr;
    }
    //current array length is zero
    length = 0;
}

NodeList::~NodeList(){
    for (int i = 0; i < length; i++){
        delete nodes[i];
        nodes[i] = nullptr;
    }
}

NodeList::NodeList(NodeList& other){
   for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE ; i++){
        nodes[i] = nullptr;
    }

    length = other.length;
    for (int i = 0; i < length; i++)
    {
        nodes[i] = new Node(*other.nodes[i]);
    }
    
}

int NodeList::getLength(){
     return length;
}

void NodeList::addElement(Node* newPos){
      Node* tempNode = new Node(*newPos);

    if(length < NODE_LIST_ARRAY_MAX_SIZE - 1){
        nodes[length] = tempNode;
        length++;
    }
}

Node* NodeList::getNode(int i){
    Node* node = nullptr;
    //checking that not going out of array bounds, if ok return the node at the point.
    if (i >=0 && i < length){
        node = nodes[i];
    }
    return node;
}