#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    //setting all values in array to null 
   // for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE ; i++) {
   //     nodes[i] = nullptr;
   // }
    //current array length is zero
    length = 0;
}

NodeList::~NodeList(){
   for(int i = 0; i < length; i++){
        nodes[i] = nullptr;
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
   for (int i = 0; i < this->length; ++i){
        delete this->nodes[i];
    }

    this->length = other.length;

    for(int i = 0; i < other.getLength(); ++i){
        if(other.getNode(i)!=nullptr){
            nodes[i] = new Node (*other.nodes[i]);
        }
    }
    
}

void NodeList::setLength(int i){
    length = i;
}

int NodeList::getLength(){
     return length;
}

void NodeList::addElement(Node* newPos){
   if(length < NODE_LIST_ARRAY_MAX_SIZE){
        nodes[length] = newPos;
        length++;
    }
}

Node* NodeList::getNode(int i){
   if(i < 0 || i >= length){
        return nullptr;
    }
    return nodes[i];
}