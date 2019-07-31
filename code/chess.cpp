#define CHESSSIZE 8
//国际象棋棋子
class ChessPiece:public Piece{
    public:
    //设置棋子属性
    void setPiece(char type,int x,int y){
        setType(type);
        setPosition(x,y);
    }
    //输出棋子属性
    string printPiece(){
        string info="";
        char type=getType();
        vector<int> position=getPosition();
        if(type=='P')
            info="Pawn";
        else if(type=='N')
            info="Knight";
        else if(type=='B')
            info="Bishop";
        else if(type=='R')
            info="Rock";
        else if(type=='Q')
            info="Queen";
        else
            info="King";
        info+="("+to_string(position[0])+","+to_string(position[1])+")";
        return info;
    }
};
//国际象棋棋手
class ChessPlayer:public Player{
    public:
    void init(){
        pieces.clear();
        int color=getPlayerColor();
        ChessPiece piece;
        if(color>0){
            for(int i=0;i<8;i++){
                piece.setPiece('P',i,1);
                pieces.push_back(piece);
            }
            piece.setPiece('N',1,0);
            pieces.push_back(piece);
            piece.setPiece('N',6,0);
            pieces.push_back(piece);
            piece.setPiece('B',2,0);
            pieces.push_back(piece);
            piece.setPiece('B',5,0);
            pieces.push_back(piece);
            piece.setPiece('R',0,0);
            pieces.push_back(piece);
            piece.setPiece('R',7,0);
            pieces.push_back(piece);
            piece.setPiece('K',4,0);
            pieces.push_back(piece);
            piece.setPiece('Q',3,0);
            pieces.push_back(piece);
        }
        else{
            for(int i=0;i<8;i++){
                piece.setPiece('P',i,6);
                pieces.push_back(piece);
            }
            piece.setPiece('N',1,7);
            pieces.push_back(piece);
            piece.setPiece('N',6,7);
            pieces.push_back(piece);
            piece.setPiece('B',2,7);
            pieces.push_back(piece);
            piece.setPiece('B',5,7);
            pieces.push_back(piece);
            piece.setPiece('R',0,7);
            pieces.push_back(piece);
            piece.setPiece('R',7,7);
            pieces.push_back(piece);
            piece.setPiece('Q',4,7);
            pieces.push_back(piece);
            piece.setPiece('K',3,7);
            pieces.push_back(piece);
        }
    }
    //获取玩家棋子
    vector<ChessPiece> getPieces(){
        return pieces;
    }
    //更改玩家拥有的棋子
    void setPieces(vector<ChessPiece> p){
        pieces=p;
    }
    protected:
    //玩家拥有的棋子
    vector<ChessPiece> pieces;
};
//国际象棋玩家行动
class ChessAction:public Action{
    public:
    //获取玩家下一步的行动
    int getAction(string playerName){
        string input="";
        while(input!="1"&&input!="2"&&input!="3"&&input!="4"&&input!="5"){
            cout<<endl;
            cout<<playerName<<" enter the serial number to select the action to be taken:"<<endl;
            cout<<"1.Move a piece."<<endl;
            cout<<"2.Check position."<<endl;
            cout<<"3.Calculate the number of pieces on the chessboard."<<endl;
            cout<<"4.Skip."<<endl;
            cout<<"5.Give up."<<endl;
            cin>>input;
        }
        return input[0]-'0';
    }
    //检查位置是否合法
    bool checkPosition(vector<int> position){
        if(position[0]<0||position[0]>=CHESSSIZE||position[1]<0||position[1]>=CHESSSIZE){
            cout<<"Position out of chessboard range."<<endl;
            return false;
        }
        return true;
    }
    //检查该位置是否有棋子
    bool checkPiece(vector<int> position,vector<ChessPiece> pieces){
        for(ChessPiece piece:pieces){
            vector<int> piecePosition=piece.getPosition();
            if(piecePosition[0]==position[0]&&piecePosition[1]==position[1]){
                cout<<"This place has your own chess."<<endl;
                return false;
            }
        }
        return true;
    }
    //检查是否需要删除棋子
    string deletePiece(vector<int> position,vector<ChessPiece> &pieces){
        string record="";
        for(decltype(pieces.size()) i=0;i<pieces.size();i++){
            ChessPiece piece=pieces[i];
            vector<int> piecePosition=piece.getPosition();
            if(piecePosition[0]==position[0]&&piecePosition[1]==position[1]){
                record=" and remove a ";
                record+=piece.printPiece();
                record+=" of opponent";
                pieces.erase(pieces.begin()+i);
                break;
            }
        }
        return record;
    }
    //移动棋子
    string moveAPiece(ChessPlayer &player,ChessPlayer &otherPlayer){
        int index=0;
        string record="";
        vector<ChessPiece> pieces=player.getPieces();
        decltype(player.getPieces().size()) piecesSize=player.getPieces().size();
        while(index<1||index>piecesSize){
            cout<<"Input the serial number to choose a chess piece:"<<endl;
            for(decltype(piecesSize) i=0;i<piecesSize;i++){
                cout<<(i+1)<<". ";
                cout<<pieces[i].printPiece()<<endl;
            }
            cin>>index;
        }
        record=" moves "+pieces[index-1].printPiece()+" to ";
        bool isSuccess=false;
        vector<int> position;
        while(!isSuccess){
            position=getPosition();
            if(checkPosition(position)&&checkPiece(position,pieces))
                isSuccess=true;
        }
        pieces[index-1].setPosition(position[0],position[1]);
        player.setPieces(pieces);
        record+="("+to_string(position[0])+","+to_string(position[1])+")";
        pieces=otherPlayer.getPieces();
        record+=deletePiece(position,pieces);
        otherPlayer.setPieces(pieces);
        return record;
    }
    //输出位置情况
    void printPosition(vector<ChessPiece> pieces1,vector<ChessPiece> pieces2){
        vector<int> position=getPosition();
        bool isFind=false;
        for(ChessPiece p:pieces1){
            if(p.getPosition()==position){
                cout<<p.printPiece()<<" of white at this position."<<endl;
                isFind=true;
                break;
            }
        }
        if(!isFind){
            for(ChessPiece p:pieces2){
                if(p.getPosition()==position){
                    cout<<p.printPiece()<<" of black at this position."<<endl;
                    isFind=true;
                    break;
                }
            }
        }
        if(!isFind)
            cout<<"This position has no chess."<<endl;
    }
};
//国际象棋游戏
class ChessGame:public Game,public ChessAction{
    public:
    ChessGame(string p1,string p2){
        player1.setPlayer(p1,1);
        player1.init();
        player2.setPlayer(p2,-1);
        player2.init();
        setMovePlayer(player1);
        board.setBoard(CHESSSIZE,CHESSSIZE);
        int act=0;
        while(act!=5){
            act=getAction(getMovePlayer().getPlayerName());
            ChessPlayer player=getMovePlayer();
            ChessPlayer otherPlayer=(getMovePlayer().getPlayerColor()==player1.getPlayerColor())?player2:player1;
            string record=getMovePlayer().getPlayerName();
            switch(act){
                case 1:
                    record+=moveAPiece(player,otherPlayer);
                    record+=".";
                    if(player.getPlayerColor()==player1.getPlayerColor()){
                        player1=player;
                        player2=otherPlayer;
                    }
                    else{
                        player1=otherPlayer;
                        player2=player;
                    }
                    addRecord(record);
                    cout<<record<<endl;
                    changeMovePlayer();
                    break;
                case 2:
                    printPosition(player1.getPieces(),player2.getPieces());
                    break;
                case 3:
                    cout<<"Number of white pieces on the chessboard:"<<to_string(player1.getPieces().size())<<endl;
                    cout<<"Number of black pieces on the chessboard:"<<to_string(player2.getPieces().size())<<endl;
                    break;
                case 4:
                    record+=" skip this round.";
                    addRecord(record);
                    changeMovePlayer();
                    break;
                case 5:
                    record+=" give up!";
                    addRecord(record);
                    changeMovePlayer();
                    break;
                default:
                    break;
            }
        }
        cout<<endl;
        cout<<getMovePlayer().getPlayerName()<<" Success!!!"<<endl;
        cout<<endl;
        cout<<"Chess game record:"<<endl;
        printRecords();
    }
    //设置当前行动玩家
    void setMovePlayer(ChessPlayer p){
        movePlayer=p;
    }
    //获取当前行动玩家
    ChessPlayer getMovePlayer(){
        return movePlayer;
    }
    void changeMovePlayer(){
        if(movePlayer.getPlayerColor()==player1.getPlayerColor())
            movePlayer=player2;
        else
            movePlayer=player1;
    }
    protected:
    //玩家1
    ChessPlayer player1;
    //玩家2
    ChessPlayer player2;
    //棋盘
    Board board;
    //当前行动玩家
    ChessPlayer movePlayer;
};