//Hi Ali, comments as required from the assignment spec below:
/*
NOTES ON THE APPROACH USED:
I've only been able to complete milestone 3, I didn't attempt milestone 4.
the classes for Node and Nodelist are pretty standard stuff that was 
shown in class and the sample vidoes nothing new there.  The bulk of work is contained in the two pathsolver methods
Forwardsearch and getPath.

Forwardsearch method can be outlined as followed:
- locate the start and goal nodes, create a current node pointer.
- create the nodes explored list and add the start node
- a big do while loop to 
    -select the P nodes for the open list (current node) based on lowest distance
    -add the next open nodes to the open list
    -current node added to the explored list .
    -check if goal reached and if not keep going.
    -exits the do while once the goal reached.
GetPath essentially works as follows:
- initialises a temp list to hold the correct path nodes 
- get the goal and start nodes from the returned explorednodelist
- find each node that has a distance travelled of less than 1 from the goal node and add to tempList
- once list is completed, order is flipped and returned
- the print out method replaces these coords with the solution sumbols in the env.


ISSUES ENCOUNTERED:
My biggest issues in approaching this assignment was my time was very limited and I probably could have finished it 
if it had not been end of year and having kids, and another subject.  
Aside from that, It was difficult to test things as I was going, I would
get a lot of 'seg fault' errors but i found it hard to debug things spent heaps of time trying to find the errors.
I attempted milestone 4 but didn't get very far, so none of that code is contained here i deleted it all
Creating the main loop in the pathsolver forward search was very difficult
and took me a long time to get working, the problem was very complex.
Definetly a challenging assignment.  I wish i had given myself more time to complete it but 
I also was very slow in my progress throught the two main methods in the pathsolver file.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
//void testNode();
//void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    //std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    //testNode();
    //testNodeList();
    //std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment
    Env env;
    readEnvStdin(env);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    //NodeList* exploredPositions = nullptr;
    //exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList *solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete solution;
}

void readEnvStdin(Env env)
{
    int charsRead = 0;

    //nested for loops to read in env
    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            if (std::cin.good())
            {
                std::cin >> env[row][col];
                charsRead++;
            }
        }
    }

    if (charsRead != (ENV_DIM * ENV_DIM))
    {
        std::cerr << "ERROR: Only read " << charsRead << " characters," << (ENV_DIM * ENV_DIM) << "charaters required, check input file." << std::endl;
        ;
    }
}

void printEnvStdout(Env env, NodeList *solution)
{

    //replace all the path nodes with symbols (except forthe last and first ones) in the
    //env, then print the env.
    for (int i = 1; i < solution->getLength() - 1; i++)
    {
        if (solution->getNode(i)->getCol() < solution->getNode(i + 1)->getCol())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '>';
        }
        else if (solution->getNode(i)->getCol() > solution->getNode(i + 1)->getCol())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '<';
        }
        else if (solution->getNode(i)->getRow() > solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = '^';
        }
        else if (solution->getNode(i)->getRow() < solution->getNode(i + 1)->getRow())
        {
            env[solution->getNode(i)->getRow()][solution->getNode(i)->getCol()] = 'V';
        }
    }

    for (int row = 0; row < ENV_DIM; row++)
    {
        for (int col = 0; col < ENV_DIM; col++)
        {
            std::cout << env[row][col];
        }
        std::cout << std::endl;
    }
}

/*void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}*/