#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define NUM (8)
#define BLACK (1)
#define WHITE (-1)

// １:黒が置かれている
// ０：何も置かれていない
//−１：白が置かれている
int board[NUM][NUM];

bool judgeBlackWin(int * black, int * white ){
    int n_black = 0;
    int n_white = 0;
    int i,j;
    for(int i = 0; i < NUM; i++){
        for(int j = 0; j < NUM; j++){
            if(board[j][i] == BLACK) n_black++;
            else if(board[j][i] == WHITE) n_white++;
        }
    }
    *black = n_black;
    *white = n_white;
    return  n_black > n_white ? true:false;
}

void initboard(){
    board[3][3] = WHITE;
    board[4][4] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    return;
}

void putstone(int x, int y, int var){
    int i, cx, cy, tx, ty;
    int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    
    //step1：石を置く
    if(var == BLACK) board[x][y] = BLACK;
    else board[x][y] = WHITE;
    
    //step2：石を反転する
    for(i = 0 ; i < 8; i++){
        cx = x + dx[i], cy = y + dy[i];
        while(0 <= cx && cx < NUM && 0 <= cy && cy < NUM && (board[cx][cy] == (-1)*var)){
            cx += dx[i],cy += dy[i];
        }
        if(board[cx][cy] == 0) continue;
        
        //移動後のcx/cyが盤面の中かつ、cx/cyとx/yの間に石が存在する場合には、石を反転する
        if(0 <= cx && cx < NUM && 0 <= cy && cy < NUM){
            tx = x, ty = y;
            while(!(tx == cx && ty == cy)){
                board[tx][ty] = var;
                tx += dx[i], ty += dy[i];
            }
        }
    }
}


int main(void){
    int i, n, x, y, nb, nw;
    char var;
    bool BlackWin;
    
    //盤面の初期化
    initboard();
    
    cin >> n;
    for(i = 0; i< n; i++){
        cin >> var;
        cin >> x >> y;
        if(var == 'B'){
            putstone(x-1, y-1, BLACK);
        }else{
            putstone(x-1, y-1, WHITE);
        }
    }
    
    BlackWin = judgeBlackWin(&nb, &nw);
    
    if(BlackWin){
        printf("%02d-%02d The black won!\n", nb, nw);
    }else{
        printf("%02d-%02d The white won!\n", nb, nw);
    }
    
    return 0;
}

