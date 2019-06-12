#include <iostream>
#include <vector>
#include <cstdlib>
#include <zconf.h>

using namespace std;

vector<vector<bool> >Init(){
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

    vector<vector<bool>> mp({{0,0,0,0,0,0,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,1,0,1,0,0,0},
                             {0,0,0,0,0,0,0,0,0}});
    return mp;
}

void Show(vector<vector<bool> >& mp){
    int Size = (int)mp.size();
    for(int i = 0; i < Size; i++){
        for(int j = 0; j < Size; j++){
            if(mp[i][j]) printf("X");
            else printf(" ");
        }
        printf("\n");
    }
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
        sleep(10);
    }
}

int main() {
    vector<vector<bool> > mp = Init();
    Play(mp);
    return 0;
}
