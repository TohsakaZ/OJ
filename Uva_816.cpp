#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <cstring>
#include <deque>
#include <queue>

using namespace std;

map<char,int> idx_dir1={
    {'N',0},
    {'E',1},
    {'S',2},
    {'W',3}
};

map<char,int> idx_dir2={
    {'L',0},
    {'R',1},
    {'F',2},
};

struct node 
{
    node(){};
    node(int r,int c,int dir):r(r),c(c),dir(dir){};
    int r;
    int c;
    int dir;
};



pair<int,int> d[4][3]={
    {make_pair(0,-1),make_pair(0,1),make_pair(-1,0)},
    {make_pair(-1,0),make_pair(1,0),make_pair(0,1)},
    {make_pair(0,1),make_pair(0,-1),make_pair(1,0)},
    {make_pair(1,0),make_pair(-1,0),make_pair(0,-1)},
};

int change_dir(int dir1,int dir2){
    if (dir2==2){
        return dir1;
    }
    if (dir2==0){
        dir1--;
        if (dir1 < 0){
            dir1 =3;
        }
        return dir1;
    }
    if (dir2==1){
        dir1++;
        if (dir1>3){
            dir1 = 0;
        }
        return dir1;
    }
}

// N S W E 
int map_dir[10][10][4][3];
int idx[10][10][4];
int exist[10][10];
node father[10][10][4];

void print_ans(int beg_x,int beg_y, node n){
    vector<pair<int,int> >ans;
    ans.push_back(make_pair(n.r,n.c));
    while (true) {
         n = father[n.r][n.c][n.dir];
         ans.push_back(make_pair(n.r,n.c));
         if (n.r == beg_x && n.c == beg_y){
             break;
         }
    }
    int count =0;
    for (int i =ans.size()-1;i>=0;i--){
        if (count % 10 ==0){
           cout << endl << " "; 
        }
        printf(" (%d,%d)",ans[i].first,ans[i].second);
        count++;
    }
    cout << endl; 
}

bool bfs_map(int beg_x,int beg_y,node start,int end_x,int end_y){
    queue<node> q;
    q.push(start);
    idx[start.r][start.c][start.dir] = 1;
    while (!q.empty()){
        node n = q.front();
        q.pop();
        if (n.r == end_x && n.c==end_y){
            print_ans(beg_x,beg_y,n);
            return true;
        }
        // find next point
        for (int i =0;i<3;i++){
            // have this direction
            if (map_dir[n.r][n.c][n.dir][i]){
                int next_x,next_y,next_dir;
                next_x = n.r+ d[n.dir][i].first;
                next_y = n.c+ d[n.dir][i].second;
                next_dir = change_dir(n.dir,i);
                //next point is in map && next point did'n visited already
                if (exist[next_x][next_y] && idx[next_x][next_y][next_dir] == 0){
                    father[next_x][next_y][next_dir] = n;
                    q.push(node(next_x,next_y,next_dir));
                    idx[next_x][next_y][next_dir] = 1; 
                }
            }
        }
 
    }
    return false;
}

int main()
{
    //init direction
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    string maze_name;
    while (cin >> maze_name && maze_name != "END"){
        memset(map_dir,0,sizeof(map_dir)); 
        memset(idx,0,sizeof(idx));
        memset(exist,0,sizeof(exist));

        int beg_x,beg_y,end_x,end_y;
        char dir;
        cin >> beg_x >> beg_y >> dir >> end_x >> end_y;
        exist[beg_x][beg_y] = 1;
        exist[end_x][end_y] = 1;
        int row,col;
        // build map
        while (cin >> row && row !=0){
            cin >> col;
            exist[row][col] = 1;
            string templine;
            while (cin >> templine && templine !="*"){
                int dir1 = idx_dir1[templine[0]];
                for (int i =1;i<templine.length();i++) {
                    int dir2 = idx_dir2[templine[i]];
                    map_dir[row][col][dir1][dir2] = 1;
                }
            }
        }
        // find ans 
        int dir1 = idx_dir1[dir];
        int next_x,next_y,next_dir;
        next_x = beg_x + d[dir1][2].first;
        next_y = beg_y+ d[dir1][2].second;
        father[next_x][next_y][dir1] = node(beg_x,beg_y,-1);
        
        cout << maze_name ;
        if (!bfs_map(beg_x,beg_y,node(next_x,next_y,dir1),end_x,end_y)){
            cout << endl << "  No Solution Possible" << endl;
        }
    }
}