#include <iostream>
#include <vector>
#include <cstdlib>
#include <zconf.h>
#include <termios.h>

using namespace std;

static struct termios initial_settings, new_settings;
static int peek_character = -1;
void init_keyboard(void);
void close_keyboard(void);
int kbhit(void);
int readch(void);
void init_keyboard()
{
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag |= ICANON;
    new_settings.c_lflag |= ECHO;
    new_settings.c_lflag |= ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
    unsigned char ch;
    int nread;

    if (peek_character != -1) return 1;
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
////////////////////////////////////////////////////////////////////////////////////////
static int Time = 500000;
static const int L = 33;
vector<vector<bool> >Init(int mode){
//    int Size;
//    scanf("%d", &Size);
//    vector<vector<bool> > mp(Size, vector<bool>(Size, false));
//    for(int i = 0; i < Size; i++){
//        for(int j = 0; j < Size; j++){
//            int op;
//            scanf("%1d", &op);
//            if(op == 1) mp[i][j] = true;
//            else mp[i][j] = false;
//        }
//    }

    vector<vector<bool>> mp0({{0,0,0,0,0,0,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,1,0,1,0,0,0},
                              {0,0,0,0,0,0,0,0,0}});

    vector<vector<bool>> mp(L,vector<bool>(L, false));
    switch (mode){
        case 1:
            for(int i=1;i<mp.size()-1;++i){
                mp[i][mp.size()/2-1]=true;
                mp[i][mp.size()/2+1]=true;
            }
            return mp;
        case 2:
            return vector<vector<bool>>({{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,1,0,0,0,0,1,0,1,0,0,0,0,1,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                {0,0,0,1,1,1,0,0,0,1,1,1,0,0,0},
                {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}});
        default:
            break;
    }

    return mp0;
}

void Show(vector<vector<bool> >& mp){
    int Size = (int)mp.size();
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size; j++){
            if(mp[i][j]) printf("国");
            else printf("..");
        }
        printf("\n");
    }

    //printf("\n\n\n按回车键返回");
}

int getAliveCnt(int x, int y, vector<vector<bool> >& mp){
    int cnt = 0;
    int Size = (int)mp.size();
    for(int dx = -1; dx <= 1; ++dx){
        for(int dy = -1; dy <= 1; ++dy) {
            int nxtX = x + dx;
            int nxtY = y + dy;
            if (dx == 0 && dy == 0) continue;
            if (nxtX < 0 || nxtX >= Size || nxtY < 0 || nxtY >= Size)continue;
            if (mp[nxtX][nxtY]) cnt++;
        }
    }
    return cnt;
}

vector<vector<bool> > nextStep(vector<vector<bool> >& mp,bool &IfAlive){
    int Size = (int)mp.size();

    vector<vector<bool> > nxt(Size, vector<bool>(Size, false));
    for(int row = 0; row < Size; row++){
        for(int col = 0; col < Size; col++){
            if(!IfAlive&&mp[row][col]) IfAlive = true;
            int AliveCnt = getAliveCnt(row, col, mp);

            if(AliveCnt == 3) nxt[row][col]=true;
            else if(AliveCnt != 2) nxt[row][col] = false;
            else if(AliveCnt == 2) nxt[row][col] = mp[row][col];
        }
    }

    return nxt;
}

void Play(vector<vector<bool> >& mp){
    int loopTime = 0;
    int Size = (int)mp.size();
    while(true){
        bool IfAlive = false;
        system("clear");
        Show(mp);
        mp = nextStep(mp,IfAlive);
        loopTime++;
        if(!IfAlive||loopTime >= 1000000) break;
        usleep(Time);

        if(kbhit()){
            char ch = readch();
            if(ch == 10) break;
        }
    }
}

int main() {
    int mode = 1;
    vector<vector<bool> > mp;
    while(true){
        printf("*****生命游戏*****\n");
        printf("1.开始游戏\n");
        printf("2.设置模式\n");
        printf("3.设置速度\n");
        printf("4.游戏介绍\n");
        printf("5.退出游戏\n");
        printf(">>");

        int choose = 0;
        scanf("%d",&choose);

        switch (choose){
            case 1:
                mp = Init(mode);
                Play(mp);
                break;
            case 2:
                system("clear");
                printf("1.法式长棍\n");
                printf("2.脉冲星\n");
                printf(">>");

                while(true){
                    int getMode = 0;
                    scanf("%d",&getMode);
                    if(getMode>0&&getMode<3){
                        mode = getMode;
                        break;
                    }
                }

                break;
            case 3:
                system("clear");
                printf("输入速度(100～1000ms):");


                scanf("%d",&Time);
                if(Time < 100) Time = 100;
                if(Time > 1000) Time = 1000;
                Time *= 1000;
                break;
            case 4:
                system("clear");
                printf("生命游戏是John Conway 发现的一种游戏。\n");
                printf("游戏规则如下：\n");
                printf("1.如果一个细胞周围有3个细胞为生（一个细胞周围共有8个细胞），则该细胞为生；\n");
                printf("2.如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；\n");
                printf("3.在其它情况下，该细胞为死。\n");
                printf("\n\n按回车退出\n");

                while(true){
                    if(kbhit()){
                        char ch = readch();
                        if(ch == 10) break;
                    }
                }
                break;
            case 5:
                return 0;
            default:
                break;
        }

        system("clear");
    }
    return 0;
}
