#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <filesystem>
#include <chrono>

using namespace std;
namespace fs = std::filesystem;

struct account{
    string name;
    int win_count=0;
    string last_win_time;
    int total_time;
}A;


int x,y,path_len,amount_u=3,amount_d=-3,block_u=5,block_d=2;



void print_menu();
void create_map_easy(string="");
void menu();
void write_map_to_file(string,string,string,string,string);
void print_file_names(string);
void print_selected_map(string);
void creating_account();
void update_account();


int main(){
    // welcome message
    cout<<"Hello welcome to this Game!\n"<<"We (Mahdi and Zeinab) hope to enjoy!";
    Sleep(2000);
    system("cls");
    //account process
    string choice;
    cout<<"Are you a new user?(y/n)";
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
    cout<<"1. Create a New Map\n\t- 1.1 Easy\n\t- 1.2 Hard\n";
    cout<<"2. Playground\n\t- 2.1 Choose from Existing Maps\n\t- 2.2 Import a Custom Map\n";
    cout<<"3. Solve a Maze\n\t- 3.1 Choose from Existing Maps\n\t- 3.2 Import a Custom Map\n";
    cout<<"4. History\n";
    cout<<"5. Leaderboard\n";
    cout<<"6. Exit\n";
    cout<<"Enter your option : \n";

}

void menu(){
    auto startTime = std::chrono::high_resolution_clock::now();
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
        string chose,chose1;
        cout<<"hard or easy? ";
        cin>>chose;
        chose="Maps/"+chose+"/";
        print_file_names(chose);
        cout<<"\nEnter the file name you want : ";
        cin>>chose1;
        chose=chose+chose1;
        print_selected_map(chose);
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
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        A.total_time=duration.count();
        update_account();
        cout<<"Are you sure you wanna go?";
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
    string path_map="",path,path_elements="";
    srand(0);
    for(int i=1;i<=x-1;i++){
        path_map+='d';
    }
    for(int i=1;i<=y-1;i++){
        path_map+='r';
    }
    path=path_map;
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
                a++;
                do {
                    board[a][b]=(rand()%7)-3;
                } while (board[a][b]==0);
                sum+=board[a][b];
                path_elements+='['+to_string(a)+']'+'['+to_string(b)+']'+"\t";
                break;
            case 'r':
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

    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            cout<<board[i][j]<<"\t";
        }
        cout<<endl;
    }

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
    f<<write;
    f<<path<<endl<<path_index;
    f.close();
}

void print_file_names(string path){
    for (const auto& entry : fs::directory_iterator(path)){
            cout << entry.path().filename() << endl;
    }
}

void print_selected_map(string path){
    ifstream f(path);
}

void creating_account(){
    string path="Users/"+A.name+".txt";
    cout<<"Please choose a username : ";
    cin>>A.name;
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
    p.close();
    ofstream p1(path);
    p1<<A.name<<endl<<total_t<<endl<<wins<<endl<<A.last_win_time;
    p1.close();
}
