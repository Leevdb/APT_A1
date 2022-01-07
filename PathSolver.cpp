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

    //available node indexes
    int availableRow[4] = {+1, 0, -1, 0};
    int availableCol[4] = {0, -1, 0, +1};

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

    Node *currentNode = nullptr;
    bool goalFound = false;

    // find the goal node in nodesExplored list
    for (int i = 0; i < nodesExplored->getLength() && !goalFound; ++i)
    {
        Node *tempNode = nodesExplored->getNode(i);
        if (tempNode->isEqual(goalNode))
        {
            currentNode = tempNode;
            goalFound = true;
        }
    }

    NodeList *tempList = new NodeList();
    
    while (!currentNode->isEqual(startNode))
    {
        tempList->addElement(currentNode);

        //check the neighbours to see if there is a node with dist_traveled
        // that is one less than that of current node
        bool foundNode = false;
        for (int i = 0; i < 4; ++i)
        {
            if (foundNode == false)
            {
                //get the neighbour
                int exploredRow = currentNode->getRow() + availableRow[i];
                int exploredCol = currentNode->getCol() + availableCol[i];

                //check if it is inside the env
                if ((exploredRow >= 0) && (exploredRow < ENV_DIM) && (exploredCol >= 0) && (exploredCol < ENV_DIM))
                {
                    Node* checkNode = new Node(exploredRow, exploredCol, 0);

                    int j = 0;
                    //check if the neighbout is in the nodesExplored list
                    while (j < nodesExplored->getLength())
                    {
                        if (foundNode == false)
                        {
                            Node *tempNode = nodesExplored->getNode(j);
                            if (tempNode->isEqual(checkNode) && tempNode->getDistanceTraveled() ==currentNode->getDistanceTraveled() - 1)
                            {
                                foundNode = true;
                                currentNode = tempNode;
                            }
                        }
                        ++j;
                    }
                    delete checkNode;
                }
            }
        }
    }
    //adding start loop last    
    tempList->addElement(startNode);

    // flipping list order
    NodeList *path = new NodeList();
    for (int i = tempList->getLength() - 1; i >= 0; i--)
    {
        path->addElement(tempList->getNode(i));
    }

    NodeList *returnPath = new NodeList(*path);

    //clean up
    delete path;
    delete tempList;
    delete startNode;
    delete goalNode;

    return returnPath;

}

//-----------------------------