#include "Node.h"
#include <iostream>

Node::Node(int row, int col, int dist_traveled) : row(row), col(col), dist_traveled(dist_traveled) {}

Node::~Node()
{
    // TODO
}

int Node::getRow()
{
    return row;
}

int Node::getCol()
{
    return col;
}

int Node::getDistanceTraveled()
{
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node *goal)
{
    int goalRow = goal->getRow();
    int goalCol = goal->getCol();
    int currentRow = this->row;
    int currentCol = this->col;

    //calculate  manhattan distance for current node
    int manhattanDistance = (currentRow - goalRow) + (currentCol - goalCol);

    //returns manhattan +dis traveled
    return manhattanDistance + dist_traveled;
}

bool Node::isEqual(Node *node)
{

    return (this->row == node->row && this->col == node->col);
}

//--------------------------------