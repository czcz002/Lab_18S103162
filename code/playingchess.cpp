#include <iostream>
#include "game.cpp"
#include "chess.cpp"
#include "go.cpp"
using namespace std;
string chooseGame(){
    string s="";
    while(s!="Go"&&s!="Chess"){
        cout<<"Please enter the name to select a game:"<<endl<<"1.Go"<<endl<<"2.Chess"<<endl;
        cin>>s;
    }
    return s;
}
void startGame(){
    string choose=chooseGame();
    string p1Name="",p2Name="";
    while(p1Name.size()==0){
        cout<<"Please enter the name of Player1:";
        cin>>p1Name;
    }
    while(p2Name.size()==0){
        cout<<"Please enter the name of Player2:";
        cin>>p2Name;
    }
    if(choose=="Go")
        GoGame gg(p1Name,p2Name);
    else
        ChessGame cg(p1Name,p2Name);
}
int main(){
    bool isStart=true;
    while(isStart){
        startGame();
        string choose="";
        while(choose!="Y"&&choose!="N"){
            cout<<"Whether to continue the game or not? Y/N"<<endl;
            cin>>choose;
        }
        if(choose=="N")
            isStart=false;
    }
    return 0;
}