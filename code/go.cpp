#include <iostream>
#define GOSIZE 19
//围棋棋盘
class GoBoard:public Board{
    public:
    //检查位置棋子情况
    int checkPosition(vector<int> position){
        if(position[0]<0||position[0]>width-1||position[1]<0||position[1]>length-1){
            cout<<"Position out of chessboard range."<<endl;
            return 2;
        }
        return (b[position[1]][position[0]]);
    }
};
//围棋玩家行动
class GoAction:public Action{
    public:
    //获取玩家下一步的行动
    int getAction(string playerName){
        string input="";
        while(input!="1"&&input!="2"&&input!="3"&&input!="4"&&input!="5"&&input!="6"){
            cout<<endl;
            cout<<playerName<<" enter the serial number to select the action to be taken:"<<endl;
            cout<<"1.Add a piece."<<endl;
            cout<<"2.Delete a piece."<<endl;
            cout<<"3.Check position."<<endl;
            cout<<"4.Calculate the number of pieces on the chessboard."<<endl;
            cout<<"5.Skip."<<endl;
            cout<<"6.Give up."<<endl;
            cin>>input;
        }
        return input[0]-'0';
    }
    //落子
    vector<int> addAPiece(GoBoard &board,int color){
        bool isSuccess=false;
        vector<int> position;
        while(!isSuccess){
            position=getPosition();
            int piece=board.checkPosition(position);
            if(piece==0){
                board.addPiece(position,color);
                isSuccess=true;
            }
            else if(piece!=2)
                cout<<"This position has a piece."<<endl;
        }
        return position;
    }
    //输出位置信息
    void printPosition(GoBoard board){
        int piece=2;
        while(piece==2){
            vector<int> position=getPosition();
            piece=board.checkPosition(position);
            switch(piece){
                case 0:
                    cout<<"This position has no piece."<<endl;
                    break;
                case 1:
                    cout<<"This position has a white piece."<<endl;
                    break;
                case -1:
                    cout<<"This position has a black piece."<<endl;
                    break;
                default:
                    break;
            }
        }
    }
    //提子
    string deleteAPiece(GoBoard &board,int color){
        string record="";
        bool isSuccess=false;
        while(!isSuccess){
            vector<int> position=getPosition();
            int piece=board.checkPosition(position);
            if(piece==0)
                cout<<"This position has no chess to remove."<<endl;
            else if(piece==color)
                cout<<"You can't remove your own chess."<<endl;
            else if(piece==-color){
                record=" removed a chess of ("+to_string(position[0])+","+to_string(position[1])+").";
                board.addPiece(position,0);
                isSuccess=true;
            }
        }
        return record;
    }
};
//围棋游戏
class GoGame:public Game,public GoAction{
    public:
    //构建一局围棋游戏
    GoGame(string p1,string p2){
        board.setBoard(19,19);
        player1.setPlayer(p1,1);
        player2.setPlayer(p2,-1);
        setMovePlayer(player2);
        int act=0;
        while(act!=6){
            act=getAction(getMovePlayer().getPlayerName());
            vector<int> position;
            string record=getMovePlayer().getPlayerName();
            switch(act){
                case 1:
                    position=addAPiece(board,getMovePlayer().getPlayerColor());
                    cout<<"Successful addition of chess pieces"<<endl;
                    record+=" placed a ";
                    if(getMovePlayer().getPlayerColor()==1)
                        record+="white";
                    else
                        record+="black";
                    record+=" chess in (";
                    record+=to_string(position[0]);
                    record+=",";
                    record+=to_string(position[1]);
                    record+=") position.";
                    addRecord(record);
                    changeMovePlayer();
                    break;
                case 2:
                    record+=deleteAPiece(board,getMovePlayer().getPlayerColor());
                    cout<<record<<endl;
                    addRecord(record);
                    changeMovePlayer();
                    break;
                case 3:
                    printPosition(board);
                    break;
                case 4:
                    board.getPiecesNum();
                    break;
                case 5:
                    record+=" skips this round.";
                    addRecord(record);
                    cout<<record<<endl;
                    changeMovePlayer();
                    break;
                case 6:
                    record+=" give up!";
                    addRecord(record);
                    cout<<record<<endl;
                    changeMovePlayer();
                    break;
                default:
                    break;
            }
        }
        cout<<endl;
        cout<<getMovePlayer().getPlayerName()<<" Success!!!"<<endl;
        cout<<endl;
        cout<<"Go game record:"<<endl;
        printRecords();
    }
    //更换当前行动玩家
    void changeMovePlayer(){
        if(getMovePlayer().getPlayerColor()==player1.getPlayerColor())
            setMovePlayer(player2);
        else
            setMovePlayer(player1);
    }
    //设置当前行动玩家
    void setMovePlayer(Player p){
        movePlayer=p;
    }
    //获取当前行动玩家
    Player getMovePlayer(){
        return movePlayer;
    }
    protected:
    //棋盘
    GoBoard board;
    //玩家1
    Player player1;
    //玩家2
    Player player2;
    //当前行动玩家
    Player movePlayer;
};