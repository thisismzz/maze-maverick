#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <limits>
#include <functional>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

#define RESET   "\033[0m"
#define YELLOW  "\033[33m"

// Function to read maze from file
vector<vector<int>> readMazeFromFile(const string mappath ) {
    ifstream file(mappath);
    vector<vector<int>> maze;

    if (file.is_open()) {
    
        int rows, cols;
        file >> rows >> cols;

        
        maze.resize(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                file >> maze[i][j];
            }
        }

        file.close();
        return maze;
    }
    return maze;
}

// Function to check if a house is valid and not visited
bool isValid(const vector<vector<int>>& maze, int x, int y, vector<vector<bool>>& visited) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && !visited[x][y] && maze[x][y] != 0;
}

// Depth-First Search algorithm
bool dfs(vector<vector<int>>& maze, int x, int y, int targetLength, int currentLength, int targetValue, vector<vector<bool>>& visited) {
    visited[x][y] = true;

    // Check if we reached the target length and the sum condition
    if (currentLength == targetLength && targetValue == 0 && x == maze.size() - 1 && y == maze[0].size() - 1) {
        return true;
    }

   
    
    vector<int> numbers = {1, 2, 3, 4};
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Shuffle the numbers
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));

    for(int i = 0; i < 4 ; i++){
        switch(numbers[i]){
            case 1 : if (isValid(maze , x + 1 , y , visited) && dfs(maze , x + 1 , y , targetLength , currentLength + 1 , targetValue - maze[x][y] , visited)) 
                    {// color the valid path
                        // maze[x][y] = -maze[x][y];
                        return true;
                    }break;
            case 2 :if (isValid(maze , x - 1 , y , visited) && dfs(maze , x - 1 , y , targetLength , currentLength + 1 , targetValue - maze[x][y] , visited)) 
                    {// color the valid path
                        // maze[x][y] = -maze[x][y];
                        return true;
                    }break;
            case 3 :if (isValid(maze , x , y + 1 , visited) && dfs(maze , x , y + 1 , targetLength , currentLength + 1 , targetValue - maze[x][y] , visited)) 
                    {// color the valid path
                        // maze[x][y] = -maze[x][y];
                        return true;
                    }break;
            case 4 :if (isValid(maze , x , y - 1 , visited) && dfs(maze , x , y - 1 , targetLength , currentLength + 1 , targetValue - maze[x][y] , visited)) 
                    {// color the valid path
                        // maze[x][y] = -maze[x][y];
                        return true;
                    }break;
            
        }
    }
    visited[x][y] = false;
    return false;
}
// Function to display the maze
void displayMaze(const vector<vector<int>> maze , vector<vector<bool>>& visited) {
    for(int i = 0; i < maze.size(); i++){
             for(int j = 0; j < maze[0].size(); j++)
             {
                 if(visited[i][j])
                     cout << YELLOW << setw(5)<< maze[i][j] << RESET;
                 else
                     cout << maze[i][j] << " ";
            }
             cout << endl;
         }
}



void mazesolve (string choice) {
    // Get input from the user
    //string fileName , level;
    int targetLength;

    // cout << "Enter the file name: ";
    // cin >> fileName;
    // cout << "Enter the maze level: " ;
    // cin >> level ;
    // Read maze from file
    vector<vector<int>> maze = readMazeFromFile(choice);
    cout << "Enter the target path length: ";
    cin >> targetLength;

    // Initialize visited matrix
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));

    // Find a path using DFS
    bool pathFound = dfs(maze, 0, 0, targetLength, 0, maze[maze.size() - 1][maze[0].size() - 1], visited);

    // Display the result
    if (pathFound) {
        cout << "Path found!\n";
        displayMaze(maze,visited);
   
    } else {
        cout << "No valid path found.\n";
    }

    return 0;
}
