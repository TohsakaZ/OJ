#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>

using namespace std;
class state{
public:
    state(int x,int y,int k):x(x),y(y),k(k){};
    int x,y,k;
};

const int move_x[4]={-1,0,1,0};
const int move_y[4]={0,-1,0,1};

const int MaxR = 20;
const int MaxC = 20;
const int MaxK = 20;

int M[MaxR][MaxC];
int vis[MaxR][MaxC][MaxK];

int row,col;
int k;

int bfs()
{
    queue<state> q;
    q.push(state(0,0,0));
    vis[0][0][0] = 0; 
    while (!q.empty()){
        auto now = q.front();
        q.pop();
        if (now.x == row-1 && now.y == col-1){
            return vis[now.x][now.y][now.k];
        }
        
        for (int i =0;i<4;i++){
            // update x y 
            auto next = state(now.x+move_x[i],now.y+move_y[i],now.k);
            if (next.x >=0 && next.x < row && next.y >=0 && next.y< col){
                // update k
                if (M[next.x][next.y] == 1){
                    next.k ++; 
                }
                else{
                    next.k = 0;
                }
                // if not visited
                if (next.k <= k && vis[next.x][next.y][next.k] == -1 ){
                    vis[next.x][next.y][next.k] = vis[now.x][now.y][now.k] +1;
                    q.push(next);
                }
            }
        }
    }

    return -1;

}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    while (case_n--){
        memset(vis,-1,sizeof(vis));
        cin >> row >> col >> k;
        for (int i =0;i<row;i++){
            for (int j=0;j<col;j++){
                cin >> M[i][j];
            }
        }
        printf("%d\n",bfs());
    }

}