#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>

const int move_x[8]={-1,-2,-2,-1,1,2,2,1};
const int move_y[8]={2,1,-1,-2,-2,-1,1,2};
using namespace std;

int M[8][8];
int vis[8][8];
int beg_x,beg_y;
int end_x,end_y;

int bfs(){
    queue<pair<int,int> > q;
    q.push(make_pair(beg_x,beg_y));
    vis[beg_x][beg_y]=0;
    while (!q.empty()){
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        if (now_x == end_x && now_y == end_y){
            return vis[now_x][now_y];
        }
        for (int i =0;i<8;i++){
            int next_x = now_x + move_x[i];
            int next_y = now_y + move_y[i];
            if (next_x>=0 && next_x <8 && next_y >=0 && next_y < 8 && vis[next_x][next_y] ==-1){
                vis[next_x][next_y] = vis[now_x][now_y] + 1;
                q.push(make_pair(next_x,next_y));
            }
        }
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    string beg,end;
    while (cin >> beg >> end){
        memset(vis,-1,sizeof(vis));
        beg_x = beg[0] - 'a';
        beg_y = beg[1] -'1';
        end_x = end[0] - 'a';
        end_y = end[1] - '1';

        printf("To get from %s to %s takes %d knight moves.\n",beg.c_str(),end.c_str(),bfs());
    }
}