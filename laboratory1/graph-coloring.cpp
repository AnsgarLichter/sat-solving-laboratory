#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
    int count_vertices = 0;
    int count_edges = 0;
    std::vector<std::vector<int>> adjacency_matrix;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "p") {
            std::string format;
            iss >> format;
            if (format == "edge") {
                iss >> count_vertices >> count_edges;
                adjacency_matrix.assign(count_vertices, std::vector<int>(count_edges, 0));
            }
        } else if (token == "e") {
            int vertex1, vertex2;
            iss >> vertex1 >> vertex2;
            adjacency_matrix[vertex1 - 1][vertex2 - 1] = 1; // Assuming 1-based indexing
            adjacency_matrix[vertex2 - 1][vertex1 - 1] = 1; // Assuming an undirected graph
        }
    }

    file.close();

    for (int i = 0; i < count_vertices; ++i) {
        for (int j = 0; j < count_vertices; ++j) {
            std::cout << adjacency_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // TODO: Input File parsen

    // TODO: Create formulas

    // TODO: Call SAT Sovler

    // TODO: Print Result

    return 0;
}