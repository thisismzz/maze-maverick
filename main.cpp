#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void print_menu();

int main(){
    print_menu();

}

void print_menu(){
    cout<<"1. Create a New Map\n\t- 1.1 Easy\n\t- 1.2 Hard\n";
    cout<<"2. Playground\n\t- 2.1 Choose from Existing Maps\n\t- 2.2 Import a Custom Map\n";
    cout<<"3. Solve a Maze\n\t- 3.1 Choose from Existing Maps\n\t- 3.2 Import a Custom Map\n";
    cout<<"4. History\n";
    cout<<"5. Leaderboard\n";
    cout<<"6. Exit";

}