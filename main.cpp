#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

int x,y,path_len,amount_u=3,amount_d=-3,block_u=5,block_d=2;

void print_menu();
void create_map_easy(string="");
void menu();


int main(){
    menu();
    while(true){
        create_map_easy("Easy");
        cout<<endl;
        Sleep(3000);
    }

}

void print_menu(){
    cout<<"1. Create a New Map\n\t- 1.1 Easy\n\t- 1.2 Hard\n";
    cout<<"2. Playground\n\t- 2.1 Choose from Existing Maps\n\t- 2.2 Import a Custom Map\n";
    cout<<"3. Solve a Maze\n\t- 3.1 Choose from Existing Maps\n\t- 3.2 Import a Custom Map\n";
    cout<<"4. History\n";
    cout<<"5. Leaderboard\n";
    cout<<"6. Exit\n";

}

void menu(){
    print_menu();
    string option,name;
    cin>>option;
    if(option=="1.1"){
        cout<<"Choose a name : ";
        cin>>name;
        create_map_easy(name);
    }

    if(option=="1.2"){

    }
    if(option=="1.2"){

    }
    if(option=="2.1"){

    }
    if(option=="2.2"){

    }
    if(option=="3.1"){

    }
    if(option=="3.2"){

    }
    if(option=="4"){

    }
    if(option=="5"){

    }
    if(option=="6"){

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
    string path_map="";
    srand(0);
    for(int i=1;i<=x-1;i++){
        path_map+='d';
    }
    for(int i=1;i<=y-1;i++){
        path_map+='r';
    }
    
    int a=0,b=0,hold,hold1=0,sum=amount_u;
    board[0][0]=amount_u;
    while(true){
        hold=rand()%path_map.size();
        if(path_map[hold]=='r' and b==y-1)
            continue;
        if(path_map[hold]=='d' and a==x-1)
            continue;
    
        switch (path_map[hold]){
            case 'd':
                a++;
                do {
                    board[a][b]=(rand()%7)-3;
                } while (board[a][b]==0);
                sum+=board[a][b];
                break;
            case 'r':
                b++;
                hold1++;
                do {
                    board[a][b]=(rand()%7)-3;
                } while (board[a][b]==0);
                sum+=board[a][b];
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

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl;
    }

}

void add_to_map_file(string mode,string name,string path,int board[100][100]){
    name+=".txt";
    name="Maps/"+mode+name;
    ofstream f(name);
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            f<<board[i][j]<<"\t";
        }
        f<<endl;
    }
    f<<path;
    f.close();
}