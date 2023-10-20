#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "../cadical/src/ipasir.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Please enter only the path to your dicmas graph file!" << std::endl;
        return 0;
    }

    std::string pathToDimacsGraph = argv[1];
    std::ifstream file(pathToDimacsGraph);
    if (!file.is_open())
    {
        std::cout << "Failed to open the file at the path '" << pathToDimacsGraph << "'!" << std::endl;
        return 1;
    }

    std::string line;
    int countOfVertices = 0;
    int countOfEdges = 0;
    std::vector<std::vector<int>> adjacencyMatrix;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "p")
        {
            std::string format;
            iss >> format;
            if (format == "edge")
            {
                iss >> countOfVertices >> countOfEdges;
                adjacencyMatrix.assign(countOfVertices, std::vector<int>(countOfEdges, 0));
            }
        }
        else if (token == "e")
        {
            int vertex1, vertex2;
            iss >> vertex1 >> vertex2;
            adjacencyMatrix[vertex1 - 1][vertex2 - 1] = 1; // Assuming 1-based indexing
            adjacencyMatrix[vertex2 - 1][vertex1 - 1] = 1; // Assuming an undirected graph
        }
    }

    file.close();

    for (int i = 0; i < countOfVertices; ++i)
    {
        for (int j = 0; j < countOfVertices; ++j)
        {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // TODO: Create formulas
    void *solver = ipasir_init();

    // TODO: Call SAT Sovler

    // TODO: Print Result

    return 0;
}

void adjacentNodesHaveDifferentColors(void *solver, int colorCodeFirstNode, int colorCodeSecondNode)
{
    ipasir_add(solver, colorCodeFirstNode * -1);
    ipasir_add(solver, colorCodeSecondNode * -1);
    ipasir_add(solver, 0);
}

void everyNodeGetsAColor(void *solver, const std::vector<int> &colorCodesOfNode)
{
    int length = sizeof(colorCodesOfNode) / sizeof(int);
    for (const int &colorCode : colorCodesOfNode)
    {
        ipasir_add(solver, colorCode);
    }
    ipasir_add(solver, 0);
}

void atMostOneColorPerNode(void *solver, const std::vector<int> &colorCodesOfNode)
{
    for (size_t i = 0; i < colorCodesOfNode.size(); ++i)
    {
        for (size_t j = i + 1; j < colorCodesOfNode.size(); ++j)
        {
            ipasir_add(solver, -colorCodesOfNode[i]);
            ipasir_add(solver, -colorCodesOfNode[j]);
            ipasir_add(solver, 0);
        }
    }

    ipasir_add(solver, 0);
}