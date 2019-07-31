//一局游戏的基类
#include <iostream>
#include <vector>
using namespace std;
//棋手
class Player{
    public:
    //设置玩家属性
    void setPlayer (string s,int c){
        name=s;
        color=c;
    }
    //获取玩家姓名
    string getPlayerName(){
        return name;
    }
    //获取玩家颜色
    int getPlayerColor(){
        return color;
    }
    protected:
    //玩家姓名
    string name;
    //执子颜色，-1代表黑，1代表白
    int color;
};
//一局游戏
class Game{
    public:
    //添加棋局记录
    void addRecord(string record){
        records.push_back(record);
    }
    //输出本局游戏记录
    void printRecords(){
        int i=1;
        for(string record:records)
            cout<<"Round "<<i++<<" : "<<record<<endl;
    }
    protected:
    //游戏记录
    vector<string> records;
    
};
//位置
class Position{
    public:
    //设置棋子位置
    void setPosition(int row,int col){
        x=row;
        y=col;
    }
    //获取棋子位置
    vector<int> getPosition(){
        vector<int> position;
        position.push_back(x);
        position.push_back(y);
        return position;
    }
    protected:
    //横坐标
    int x;
    //纵坐标
    int y;
};
//棋子
class Piece:public Position{
    public:
    //设置棋子类型
    void setType(char c){
        type=c;
    }
    //获取棋子类型
    char getType(){
        return type;
    }
    protected:
    //棋子类型
    char type;
    //棋子位置
    Position position;
};
//棋盘
class Board{
    public:
    //设置棋盘大小
    void setBoard(int w,int l){
        width=w;
        length=l;
        b.clear();
        //初始化棋盘,0代表空
        for(int i=0;i<length;i++){
            vector<int> row(width,0);
            b.push_back(row);
        }
    }
    //获取棋盘中棋子数量
    void getPiecesNum(){
        int white=0,black=0;
        for(vector<int> row:b){
            for(int p:row){
                if(p>0)
                    white++;
                else if(p<0)
                    black++;
            }
        }
        cout<<"Number of white pieces on the chessboard:"<<white<<endl;
        cout<<"Number of black pieces on the chessboard:"<<black<<endl;
    }
    //在指定位置落子
    void addPiece(vector<int> position,int color){
        b[position[1]][position[0]]=color;
    }
    protected:
    //棋盘宽度
    int width=0;
    //棋盘长度
    int length=0;
    //棋盘
    vector<vector<int>> b;
};
//行动
class Action{
    public:
    //获取输入坐标
    vector<int> getPosition(){
        string x,y;
        int xPosition=0,yPosition=0;
        cout<<"Please enter the position."<<endl;
        bool isX=false;
        while(!isX){
            cout<<"x=";
            cin>>x;
            if(x.size()>0&&x.size()<3){
                isX=true;
                for(char c:x)
                    if(c<'0'||c>'9')
                        isX=false;
            }
        }
        for(char c:x)
            xPosition=xPosition*10+(c-'0');
        bool isY=false;
        while(!isY){
            cout<<"y=";
            cin>>y;
            if(y.size()>0&&y.size()<3){
                isY=true;
                for(char c:y)
                    if(c<'0'||c>'9')
                        isY=false;
            }
        }
        for(char c:y)
            yPosition=yPosition*10+(c-'0');
        vector<int> position;
        position.push_back(xPosition);
        position.push_back(yPosition);
        return position;
    }
};
