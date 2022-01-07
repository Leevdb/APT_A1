#include "PathSolver.h"
#include <iostream>

//initialized as nullptr
PathSolver::PathSolver()
{
    nodesExplored = nullptr;
}

//deconstructor
PathSolver::~PathSolver()
{
    delete nodesExplored;
    nodesExplored = nullptr;
}

void PathSolver::forwardSearch(Env env)
{
    //start and goal nodes
    Node *goalNode = nullptr;
    Node *startNode = nullptr;

    //Looping to find the start and goal node coordinates
    for (int row = 0; row < ENV_DIM; row++)
    {

        for (int col = 0; col < ENV_DIM; col++)
        {
            if (env[row][col] == SYMBOL_GOAL)
            {
                //Create the goal node
                goalNode = new Node(row, col, 0);
            }
            if (env[row][col] == SYMBOL_START)
            {
                //Create the start node
                startNode = new Node(row, col, 0);
            }
        }
    }
    
    //Intialize the explored nodes list of nodes to be used with the pathfinder
    nodesExplored = new NodeList();

    // create an empty list for open list (P)
    NodeList *openList = new NodeList();

    //intialise the currentNode
    Node *currentNode = nullptr;

    //adding startNode;
    openList->addElement(startNode);

    //select node P from openlist with smallest est distance from goal and is not in nodes explored.
    bool goalReached = false;
    do  {

        Node *tempNode = nullptr;
        int minDistance = 1000;
        for (int i = 0; i < openList->getLength(); ++i)
        {
            tempNode = openList->getNode(i);
            if (tempNode->getEstimatedDist2Goal(goalNode) < minDistance && !nodesExplored->checkIfExists(tempNode))
            {
                currentNode = tempNode;
                minDistance = currentNode->getEstimatedDist2Goal(goalNode);
            }
        }

        if (currentNode->isEqual(goalNode))
        {
            goalReached = true;
        }
        else
        {
            //adding the next open nodes
            //available node indexes
            int availableRow[4] = {+1, 0, -1, 0};
            int availableCol[4] = {0, -1, 0, +1};

            //check all neighbours and add to openlist if good
            for (int i = 0; i < 4; i++)

            {
                int tempRow = currentNode->getRow() + availableRow[i];
                int tempCol = currentNode->getCol() + availableCol[i];

                Node tempNode(tempRow, tempCol, currentNode->getDistanceTraveled() + 1);

                if (!openList->checkIfExists(&tempNode) && ((tempRow >= 0) && (tempRow < ENV_DIM) && (tempCol >= 0) && (tempCol < ENV_DIM)))
                {
                    if (env[tempRow][tempCol] == SYMBOL_GOAL || env[tempRow][tempCol] == SYMBOL_EMPTY)
                    {
                        openList->addElement(&tempNode);
                    }
                }
            }

            nodesExplored->addElement(currentNode);
        }
    } while (!goalReached);

    //cleaning up
    delete goalNode;
    delete startNode;
    delete openList;
}

NodeList *PathSolver::getNodesExplored()
{
    return new NodeList(*nodesExplored);
}

NodeList *PathSolver::getPath(Env env)
{
    //start is very similar to the forward search function.
    //available node indexes
    //int availableRow[4] = {+1, 0, -1, 0};
    //int availableCol[4] = {0, -1, 0, +1};

    Node *startNode = nullptr;
    Node *goalNode = nullptr;

    // read the start and goal
    // Looping to find the start and goal node coordinates
    for (int row = 0; row < ENV_DIM; row++)
    {

        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col] << " ";
            if (env[row][col] == SYMBOL_GOAL)
            {
                //Create the goal node
                goalNode = new Node(row, col, 0);
            }
            if (env[row][col] == SYMBOL_START)
            {
                //Create the start node
                startNode = new Node(row, col, 0);
            }
        }
    }

    //bool goalFound = false;

    NodeList *tempList = new NodeList();
    
    //this is as far as I got i ran out of time to complete milestone 3.    

    //clean up
   
    delete tempList;
    delete startNode;
    delete goalNode;

    return nullptr;

}

//-----------------------------