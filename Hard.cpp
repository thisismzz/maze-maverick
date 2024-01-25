#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <limits>
#include <functional>
#include <chrono>
#include <ctime>



using namespace std;

// Function to generate a maze map

void generatemazemap(vector<vector<int>>& mazemap, int rows, int columns, int targetPathLength, int minHouseValue, int maxHouseValue, int& minBlockCount, int& maxBlockCount) {
   
   
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minHouseValue, maxHouseValue);

    int finalHouseValue = 0;

    if (maxBlockCount > (rows*columns - targetPathLength -1))
        maxBlockCount = (rows*columns - targetPathLength -1) ;

    uniform_int_distribution<> dar(minBlockCount , maxBlockCount);
    int blockCount = dar(gen) ;
    
    for (int i = 0; i < blockCount;) {
        
        int randomRow = rand() % rows;
        int randomColumn = rand() % columns ;
        
        if(mazemap[randomRow][randomColumn] != 2 && mazemap[randomRow][randomColumn] != 0 && randomRow != rows - 1 && randomColumn != columns - 1){
            mazemap[randomRow][randomColumn] = 0;
            i++;
        }
    }

    for (int i = 0; i < rows; i++) {
        for(int j = 0 ; j < columns ; j++){
            
            int num;
            do{
                num = dis(gen);
            }while(num == 0);

            if(mazemap[i][j] == 2){
                mazemap[i][j] = num ;
                finalHouseValue += num;                        
            }
            else if (mazemap[i][j] != 0 ){
                mazemap[i][j] = num ;
            }
        }
    }
    mazemap[rows - 1][columns - 1] = finalHouseValue ; 
}


// Function to find a path with the specified length

bool DFS(vector<vector<int>>& mazemap, int row, int col, int targetLength, int currentLength,int rows, int columns) {
   
   
    if (row < 0 || row >= rows || col < 0 || col >= columns || mazemap[row][col] == 2) {
        return false;
    }

    if (currentLength == targetLength && row == rows - 1 && col == columns -1) {
        return true;
    }

    mazemap[row][col] = 2;
     
    vector<int> numbers = {1, 2, 3, 4};
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // Shuffle the numbers
    shuffle(numbers.begin(), numbers.end(), default_random_engine(seed));
    for(int i = 0; i < 4 ; i++){
        switch(numbers[i]){
            case 1 : if (DFS(mazemap, row + 1, col, targetLength, currentLength + 1,rows,columns)) // پایین
                    return true;
            break;
            case 2 : if (DFS(mazemap , row - 1, col, targetLength, currentLength + 1 ,rows,columns)) // بالا
                    return true;
            break;
            case 3 :  if (DFS(mazemap , row, col + 1, targetLength, currentLength + 1,rows,columns)) // راست
                    return true;
            break;
            case 4 : if (DFS(mazemap , row, col - 1, targetLength, currentLength + 1,rows,columns)) // چپ
                    return true;
            break;
           

            }
    }
        
    mazemap[row][col] = 1;

    return false;
}

bool findPath(vector<vector<int>>& mazemap,int rows, int columns, int targetLength , int minHouseValue, int maxHouseValue, int minBlockCount, int maxBlockCount) {
  
    if (DFS(mazemap , 0 , 0 , targetLength, 0,rows,columns)){
        
        generatemazemap( mazemap, rows, columns, targetLength, minHouseValue, maxHouseValue,  minBlockCount,  maxBlockCount);
        return true;
    }
    return false;
}

int main() {

    int rows , columns , targetPathLength;
    int minHouseValue , maxHouseValue;
    int minBlockCount , maxBlockCount;
    string mapName;

    srand(time(0));
    // Step 1: Take the number of rows and columns from the user
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;
    cout << "Enter the target path length: ";
    cin >> targetPathLength;
    cout << "Enter the minimum allowed value for a house: ";
    cin >> minHouseValue;
    cout << "Enter the maximum allowed value for a house: ";
    cin >> maxHouseValue;
    cout << "Enter the minimum number of blocks: ";
    cin >> minBlockCount;
    cout << "Enter the maximum number of blocks: ";
    cin >> maxBlockCount;
    cout << "Enter the name for the map: ";
    cin >> mapName;

    // Step 2: Initialize the labyrinth map
    vector<vector<int>> mazemap(rows, vector<int>(columns, 0)) ;
    for (int i = 0 ; i < rows; i++)
    {
       for(int j = 0 ; j < columns ; j++){

            mazemap[i][j] = 1 ;
       }
    }
    
    if (findPath(mazemap , rows , columns , targetPathLength, minHouseValue,  maxHouseValue, minBlockCount, maxBlockCount)) {
        
        string fileName = "Maps/hard/" + mapName + ".txt";
        ofstream file(fileName);
        
        int mapnum = 0 ;
        if (file.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    file<<rows<<" "<<columns<<endl << mazemap[i][j] <<"\t";
                }
                file << endl;
            }
            file<<"____"<<endl;
            file.close();
            cout << "Map saved successfully!" << endl;
            mapnum ++ ;
        } else {
            cout << "Error: Unable to save the map." << endl;
        }
    }
    //     ofstream names("names.txt");
    //     if (names.is_open()) names << mapnum << "-"<< mapName <<endl;
    // return 0;
        // }
    else {
        cout << "Error: Unable to find a path with the specified length." << endl;
    }
    
}