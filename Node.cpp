#include "Node.h"
#include <iostream>

//parameter constructor
Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    this->dist_traveled = dist_traveled;// TODO
}

Node::Node(int row, int col){
    this->row = row;
    this->col = col;
}

//deconstructor
Node::~Node(){
   delete this;
}

Node::Node(Node& other){
    this->row = other.row;
    this->col = other.col;
    this->dist_traveled = other.dist_traveled;
	
}

int Node::getRow(){
    return row;
}
int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled =dist_traveled;
}
void Node::setExplorable(bool explorable){
    this->explorable = explorable;
}

bool Node::getExplorable(){
    return explorable;
}

int Node::getEstimatedDist2Goal(Node* goal){
    int goalRow = goal->getRow();
    int goalCol = goal->getCol();
    int currentRow = this->row;
    int currentCol = this->col;

    //calculate  manhattan distance for current node    
    int manhattanDistance = (currentRow - goalRow )+(currentCol - goalCol);
    
    //returns manhattan +dis traveled
    return manhattanDistance+dist_traveled;
}
    
//--------------------------------                             