#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <limits>
#include <functional>
#include <algorithm>
#include <unordered_map> 

#define green "\033[32m"
#define white "\033[0m"
#define red   "\033[31m"
#define blue  "\033[34m"
#define grey  "\033[90m"
#define yellow "\033[33m"

using namespace std;
namespace fs = std::filesystem;

struct account{
    string name;
    int win_count=0;
    string last_win_time;
    int total_time;
    int time_in_game;
    int game_counter=0;
}A;


int x,y,path_len,amount_u=3,amount_d=-3,block_u=5,block_d=2;



void print_menu();
void create_map_easy(string="");
void menu();
void write_map_to_file(string,string,string,string,string);
void print_file_names(string);
string print_selected_map(string,bool);
void creating_account();
void update_account();
void playground_easy(string);
void add_history(string,string);
void print_history();
void print_account_informations();
vector<vector<int>> readMazeFromFile(const string);
bool isValid (const vector<vector<int>>&,int,int,const vector<vector<int>>&);
bool dfs(const vector<vector<int>>&,int,int,int,int,int,const vector<vector<int>>&);
void displayMaze(const vector<vector<int>>&,const vector<vector<int>>&);  //for solve maze
void mazesolve(string);
void generatemazemap(vector<vector<int>>&,int,int,int,int,int,int&,int&);
bool DFS(vector<vector<int>>&,int,int,int,int,int,int);
bool findPath(vector<vector<int>>&,int,int,int,int,int,int,int);
void mazesolvehard(string);
vector<vector<int>> readMazeMap(const string);
void displayMazeMap(const vector<vector<int>>&,const vector<vector<int>>&);   // is for playground
string playMazeGame(vector<vector<int>>&);
void playgroundhard(string);
int count_txt_files(const string &);
void leaderboard();

int main(){
    // welcome message
    cout<<white<<"Hello welcome to this Game!\n"<<"We (Mahdi and Zeinab) hope to enjoy!";
    //account process
    string choice;
    cout<<"\nAre you a new user?(y/n)";
    cin>>choice;
    if(choice=="y"){
        cout<<"\nLets make your account\n";
        creating_account();
    }
    else{
        cout<<"please enter your username : ";
        cin>>A.name;
        cout<<endl;
    }
    menu();

}

void print_menu(){
    cout<<blue<<"1. Create a New Map\n\t"<<white<<"- 1.1 Easy\n\t- 1.2 Hard\n";
    cout<<blue<<"2. Playground\n\t"<<white<<"- 2.1 Choose from Existing Maps\n\t- 2.2 Import a Custom Map\n";
    cout<<blue<<"3. Solve a Maze\n\t"<<white<<"- 3.1 Choose from Existing Maps\n\t- 3.2 Import a Custom Map\n";
    cout<<blue<<"4. History\n";
    cout<<blue<<"5. Acount information\n";
    cout<<blue<<"6. Leaderboard\n";
    cout<<blue<<"7. Exit\n";
    cout<<red<<"Enter your option : ";
    cout<<white;

}

void menu(){
    const auto startTime = std::chrono::high_resolution_clock::now();
    print_menu();
    string option,name;
    cin>>option;
    if(option=="1.1"){
        cout<<"Choose a name : ";
        cin>>name;
        create_map_easy(name);
        menu();
    }

    if(option=="1.2"){
        cout<<"Choose a name : ";
        cin>>name;
        mazesolvehard(name);
        menu();
    }

    if(option=="2.1"){
        string chose,chose1;
        cout<<"hard or easy? ";
        cin>>chose;
        if(chose=="easy"){
            chose="Maps/"+chose+"/";
            print_file_names(chose);
            cout<<"\nEnter the file name you want : ";
            cin>>chose1;
            chose=chose+chose1;
            playground_easy(chose);
            menu();
        }
        else{
            chose="Maps/"+chose+"/";
            print_file_names(chose);
            cout<<"\nEnter the file name you want : ";
            cin>>chose1;
            chose=chose+chose1;
            playgroundhard(chose);
            menu();
        }
    }
    if(option=="2.2"){
        string choise;
        cout<<"hard or easy? ";
        cin>>choise;
        if(choise=="easy"){
            cout<<"Choose a name : ";
            cin>>choise;
            create_map_easy(choise);
            choise="Maps/easy/"+choise+".txt";
            playground_easy(choise);
            menu();
        }
        else{
            cout<<"Choose a name : ";
            cin>>choise;
            mazesolvehard(choise);
            choise="Maps/hard/"+choise+".txt";
            playgroundhard(choise);
            menu();
        }
    }
    if(option=="3.1"){
        string chose,chose1;
        cout<<"hard or easy? ";
        cin>>chose;
        if(chose=="easy"){
            chose="Maps/"+chose+"/";
            print_file_names(chose);
            cout<<"\nEnter the file name you want : ";
            cin>>chose1;
            chose=chose+chose1;
            mazesolve(chose);
            menu();
        }
        else{
            chose="Maps/"+chose+"/";
            print_file_names(chose);
            cout<<"\nEnter the file name you want : ";
            cin>>chose1;
            chose=chose+chose1;
            mazesolve(chose);
            menu();
        }
    }
    if(option=="3.2"){
        string choise;
        cout<<"hard or easy? ";
        cin>>choise;
        if(choise=="easy"){
            cout<<"Choose a name : ";
            cin>>choise;
            create_map_easy(choise);
            choise="Maps/easy/"+choise+".txt";
            mazesolve(choise);
            menu();
        }
        else{
            cout<<"Choose a name : ";
            cin>>choise;
            mazesolvehard(choise);
            choise="Maps/hard/"+choise+".txt";
            mazesolve(choise);
            menu();
        }
    }
    if(option=="4"){
        print_history();
        menu();
    }
    if(option=="5"){
        cout<<"Here is your account informations : \n";
        print_account_informations();
        menu();

    }
    if(option=="6"){
        cout<<yellow<<"Here is our TOP 3 players(name/win times/time spend) : \n";
        leaderboard();
        menu();
    }
    if(option=="7"){
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.total_time=duration.count();
        update_account();
        cout<<"Are you sure you wanna go?\n";
        Sleep(1000);
        cout<<"Really?\n";
        Sleep(1000);
        cout<<"OK  Hope to See you soon!\n";
        exit(0);
    }
    
}

void create_map_easy(string name){
    cout<<"Enter x(width) and y(hieght) : ";
    cin>>x>>y;
    path_len=x+y-2;

    int board[x][y];
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            board[i][j]=0;
        }
    }
    //specifing the path
    string path_map="",path="",path_elements="[0][0]\t";
    srand(0);
    for(int i=1;i<=x-1;i++){
        path_map+='d';
    }
    for(int i=1;i<=y-1;i++){
        path_map+='r';
    }

    int a=0,b=0,hold,sum=amount_u;
    board[0][0]=amount_u;
    while(true){
        hold=rand()%path_map.size();
        if(path_map[hold]=='r' and b==y-1)
            continue;
        if(path_map[hold]=='d' and a==x-1)
            continue;
    
        switch (path_map[hold]){
            case 'd':
                path+='d';
                a++;
                do {
                    board[a][b]=(rand()%7)-3;
                } while (board[a][b]==0);
                sum+=board[a][b];
                path_elements+='['+to_string(a)+']'+'['+to_string(b)+']'+"\t";
                break;
            case 'r':
                path+='r';
                b++;
                do {
                    board[a][b]=(rand()%7)-3;
                } while (board[a][b]==0);
                sum+=board[a][b];
                path_elements+='['+to_string(a)+']'+'['+to_string(b)+']'+"\t";   //adding element index of path to a string
                break;
        }
        if(a==x-1 and b==y-1)
            sum-=board[a][b];
        board[x-1][y-1]=sum;
        path_map.erase(path_map.begin()+hold);
        if(path_map.size()==0)
            break;
    }
    
    // adding block
    for(int i=1;i<=(x*y)-path_len-1-(rand()%4)-2;i++){
        do{
            a=rand()%3;
            b=rand()%6;
        }while(board[a][b]!=0);
        do {
            board[a][b]=(rand()%7)-3;
        }while(board[a][b]==0);
    }

    // for(int i=0;i<x;i++){
    //     for(int j=0;j<y;j++){
    //         cout<<board[i][j]<<"\t";
    //     }
    //     cout<<endl;
    // }
    cout<<"Map Created !\n";

    string board_into_string="";         //converting board into string form
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            board_into_string+=to_string(board[i][j])+"\t";
        }
        board_into_string+='\n';
    }
    write_map_to_file("easy",name,path,board_into_string,path_elements);
}

void write_map_to_file(string mode,string name,string path,string write,string path_index){
    name+=".txt";
    name="Maps/"+mode+"/"+name;
    ofstream f(name);
    f<<x<<" "<<y<<endl<<write<<"____"<<endl;
    f<<path<<endl<<path_index;
    f.close();
}

void print_file_names(string path){
    for (const auto& entry : fs::directory_iterator(path)){
            cout << entry.path().filename() << endl;
    }
}

string print_selected_map(string path,bool answer){
    ifstream f(path);
    string hold;
    int a,b;
    if(answer==false){
        f>>hold;
        a=stoi(hold);
        f>>hold;
        b=stoi(hold);
        getline(f,hold);
        int board[a][b];
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                f>>hold;
                board[i][j]=stoi(hold);
            }
            getline(f,hold);
        }
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                cout<<board[i][j]<<'\t';
            }
            cout<<endl;
        }
        getline(f,hold);
        getline(f,hold);
        f.close();
        return hold;
    }
    else{
        f>>hold;
        a=stoi(hold);
        f>>hold;
        b=stoi(hold);
        getline(f,hold);
        int board[a][b];
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                f>>hold;
                board[i][j]=stoi(hold);
            }
            getline(f,hold);
        }

        getline(f,hold);
        getline(f,hold);
        getline(f,hold);
        for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                if(hold.find('['+to_string(i)+']'+'['+to_string(j)+']')<=hold.size())
                    cout<<green<<board[i][j]<<'\t';
                else
                    cout<<white<<board[i][j]<<'\t';
            }
            cout<<endl;
        }
    }
    return "";
}

void creating_account(){
    cout<<"Please choose a username : ";
    cin>>A.name;
    string path="Users/"+A.name+".txt";
    ofstream p(path);
    p<<A.name<<endl<<0<<endl<<0<<endl<<0;
    p.close();
}

void update_account(){
    string path="Users/"+A.name+".txt";
    ifstream p(path);
    string hold;
    getline(p,hold);
    getline(p,hold);
    int total_t=stoi(hold)+A.total_time;
    getline(p,hold);
    int wins=stoi(hold)+A.win_count;
    getline(p,hold);
    int game_count=stoi(hold)+A.game_counter;
    getline(p,hold);
    string date_win=hold;
    p.close();
    ofstream p1(path);
    if(A.last_win_time.size()!=0)
        p1<<A.name<<endl<<total_t<<endl<<wins<<endl<<game_count<<endl<<A.last_win_time;
    else
        p1<<A.name<<endl<<total_t<<endl<<wins<<endl<<game_count<<endl<<date_win;
    p1.close();
}

void playground_easy(string map_path){
    auto startTime = std::chrono::high_resolution_clock::now();
    string answer;
    answer=print_selected_map(map_path,false);
    cout<<"\nEnter your path (example : ddrulud)";
    string user_ans;
    cin>>user_ans;
    if(user_ans==answer){
        cout<<"\ncongratulations! you answer is correct\n";
        A.win_count++;
        A.game_counter++;
        //adding win time to struct
        time_t currentTime = std::time(nullptr);
        tm* timeInfo = localtime(&currentTime);
        stringstream ss;
        ss<<put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
        A.last_win_time=ss.str();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.time_in_game=duration.count();
        answer=print_selected_map(map_path,true);
        add_history(map_path,"win");
    }

    else{
        A.game_counter++;
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.time_in_game=duration.count();
        cout<<"sorry your answer is incorrect :(\nthe right answer is "<<answer<<endl;
        answer=print_selected_map(map_path,true);
        add_history(map_path,"lose");
    }
}

void add_history(string map_name,string status){
    string data,hold,time;
    ifstream his("history.txt");
    getline(his,hold);
    while(!his.eof()){
        data+=hold+'\n';
        getline(his,hold);
    }
    his.close();
    ofstream his1("history.txt");
    //calculating time
    time_t currentTime = std::time(nullptr);
    tm* timeInfo = localtime(&currentTime);
    stringstream ss;
    ss<<put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
    time=ss.str();
    his1<<time<<'\t'<<A.name<<'\t'<<map_name<<'\t'<<A.time_in_game<<'\t'<<status<<'\n';
    his1<<data;
    his1.close();
}

void print_history(){
    string hold;
    ifstream f("history.txt");
    cout<<"The last 10 games : \n";
    for(int i=1;i<=10;i++){
        if(!f.eof()){
            getline(f,hold);
            cout<<hold<<'\n';
        }
    }
    f.close();
}

void print_account_informations(){
    string hold="Users/"+A.name+".txt";
    ifstream f(hold);
    getline(f,hold);
    getline(f,hold);
    cout<<grey<<"Your total time of games you have played : "<<red<<hold<<'\n';
    getline(f,hold);
    cout<<grey<<"Your total number of wins : "<<red<<hold<<'\n';
    getline(f,hold);
    cout<<grey<<"Your total number of games you have played : "<<red<<hold<<'\n';
    getline(f,hold);
    cout<<grey<<"Your last win date is : "<<red<<hold<<'\n';
    f.close();


}

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
    int row = maze.size()-1;
    int col = maze[0].size()-1;
    if(x == row && y == col)
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && !visited[x][y] ;
    else
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
                     cout << green<< maze[i][j]<<'\t';
                 else
                     cout <<white << maze[i][j]<<'\t';
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

}

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
    // if (currentLength == targetLength && row != rows - 1 && col != columns -1) {
    //     return false;
    // }
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

void mazesolvehard(string choice) {

    int rows , columns , targetPathLength;
    int minHouseValue , maxHouseValue;
    int minBlockCount , maxBlockCount;
    string mapName;
    mapName = choice ;
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
            file << rows << " " << columns << endl ; 
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    file << mazemap[i][j] << " ";
                }
                file << endl;
            }
            file.close();
            cout << "Map saved successfully!" << endl;
            mapnum ++ ;
        } else {
            cout << "Error: Unable to save the map." << endl;
        }}
    else {
        cout << "Error: Unable to find a path with the specified length." << endl;
    }
    }


vector<vector<int>> readMazeMap(const string filename) {
    ifstream file(filename);
    vector<vector<int>> mazeMap;
    int rows, columns;

    if (file.is_open()) {
        file >> rows >> columns;
        mazeMap.resize(rows, vector<int>(columns));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                file >> mazeMap[i][j];
            }
        }

        file.close();
    }

    return mazeMap;
}

// Function to display the maze map with color
void displayMazeMap(const vector<vector<int>>& mazeMap, const vector<pair<int, int>>& visitedHouses) {
    int rows = mazeMap.size();
    int columns = mazeMap[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            // Check if the house is visited
            if (find(visitedHouses.begin(), visitedHouses.end(), make_pair(i, j)) != visitedHouses.end()) {
                // Highlight the visited houses with color
                cout << green<< mazeMap[i][j]<<'\t';
            } else {
                // Display other elements normally
                cout<< white << mazeMap[i][j]<<'\t';
            }
        }
        cout << endl;
    }
}

// Function to play the maze game
string playMazeGame(vector<vector<int>>& mazeMap) {
    int row = 0;
    int col = 0;
    int sum = mazeMap[0][0];
    vector<pair<int, int>> visitedHouses = {make_pair(row, col)}; // Include starting house

    while (true) {
        // Display the maze map with color
        displayMazeMap(mazeMap, visitedHouses);

        // Check if the player has reached the last house
        if (row == mazeMap.size() - 1 && col == mazeMap[0].size() - 1) {
            sum-=mazeMap[row][col];
            if(sum == mazeMap[row][col])  {
                cout << "Congratulations! You have reached the last house and won the game!" << endl;
                return "win";
            }
            else{
                cout<<"You lost the game :("<<endl;
                return "lose";
            }    
        }
        // Check if the house is valid
        else if(mazeMap [row][col] == 0 && row != mazeMap.size() - 1 && col != mazeMap[0].size() - 1) {
            cout << "You hit the block" << endl;
            return "lose";
        }
        
        // Get the player's move
        char move;
        cout << "Enter your move (R/L/U/D for right/left/up/down): ";
        cin >> move;

        // Update the player's position, sum, and mark the house as visited
        if (move == 'R' && col < mazeMap[0].size() - 1) {
            col++;
        } else if (move == 'L' && col > 0) {
            col--;
        } else if (move == 'U' && row > 0) {
            row--;
        } else if (move == 'D' && row < mazeMap.size() - 1) {
            row++;
        }

        sum += mazeMap[row][col];
        visitedHouses.push_back(make_pair(row, col));
    }
}

void playgroundhard(string mappath){
    auto startTime = std::chrono::high_resolution_clock::now();
    vector<vector<int>> mazeMap = readMazeMap(mappath);

    // Play the maze game
    string status=playMazeGame(mazeMap);

    if(status=="win"){
        A.win_count++;
        A.game_counter++;
        //adding time play to struct
        time_t currentTime = std::time(nullptr);
        tm* timeInfo = localtime(&currentTime);
        stringstream ss;
        ss<<put_time(timeInfo, "%Y-%m-%d %H:%M:%S");
        A.last_win_time=ss.str();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.time_in_game=duration.count();
        add_history(mappath,"win");
    }

    else{
        A.game_counter++;
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.time_in_game=duration.count();
        add_history(mappath,"lose");
    }

   
}

void leaderboard(){
    string holder;   
    int player; 
    vector <string> names;
    vector <int> win_games;
    vector <int> time_spend;
    ofstream top_player("top-player.txt");
    for (const auto& entry : fs::directory_iterator("Users/")){
            ifstream f(entry.path().filename());
            cout<<entry.path().filename()<<endl;
            getline(f,holder);
            cout<<holder<<endl;
            // names.push_back(holder);
            getline(f,holder);
            cout<<holder<<endl;
            // time_spend.push_back(stoi(holder));
            getline(f,holder);
            cout<<holder<<endl;
            // win_games.push_back(stoi(holder));
            f.close();
    }
    
    for(int i=1;i<=3;i++){
        for(int j=0;j<win_games.size()-1;j++){
            if(win_games[i]>win_games[i+1]){
                player=i;
            }
            if(win_games[i]==win_games[i+1]){
                if(time_spend[i]<time_spend[i+1]){
                    player=i;
                }
                else{
                    player=i+1;
                }
            }
            else{
                player=i+1;
            }
        }
        top_player<<names[player]<<'\t'<<win_games[player]<<'\t'<<time_spend[player]<<endl;
        names.erase(names.begin()+player);
        win_games.erase(win_games.begin()+player);
        time_spend.erase(time_spend.begin()+player);
    }
    top_player.close();

    ifstream f1("top-player.txt");
    getline(f1,holder);
    while(!f1.eof()){
        cout<<red<<holder<<endl;
        getline(f1,holder);
    }
    f1.close();
}