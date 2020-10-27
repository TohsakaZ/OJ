#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <cstring>


using namespace std;
const int MaxN = 110;
string map[MaxN];
int idx[MaxN][MaxN];

const pair<int,int> dir[8]={
    make_pair(-1,-1),make_pair(0,-1),make_pair(1,-1),
    make_pair(-1,0),make_pair(1,0),
    make_pair(-1,1),make_pair(0,1),make_pair(1,1)
};

void dfs(pair<int,int> beg,int cnt,int m,int n){
    stack<pair<int,int> > s;
    s.push(beg);
    while (!s.empty()){
        auto loc = s.top();        
        s.pop();
        idx[loc.first][loc.second] = cnt;
        for (int d = 0;d<8;d++){
            auto new_loc = make_pair(loc.first+dir[d].first,loc.second+dir[d].second);
            if (new_loc.first >=0 && new_loc.first< m && new_loc.second >=0 && new_loc.second <n 
                    && map[new_loc.first][new_loc.second] == '@' && idx[new_loc.first][new_loc.second] ==0) {
                    s.push(new_loc);
            }
        }
    }
}

void bfs(pair<int,int> beg,int cnt,int m,int n){
    queue<pair<int,int> >q; 
    q.push(beg);
    while (!q.empty()){
        auto loc = q.front();        
        q.pop();
        idx[loc.first][loc.second] = cnt;
        for (int d = 0;d<8;d++){
            auto new_loc = make_pair(loc.first+dir[d].first,loc.second+dir[d].second);
            if (new_loc.first >=0 && new_loc.first< m && new_loc.second >=0 && new_loc.second <n 
                    && map[new_loc.first][new_loc.second] == '@' && idx[new_loc.first][new_loc.second] ==0) {
                    q.push(new_loc);
            }
        }
    }

}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int m,n;
    int cnt=0;
    while (cin >> m >> n &&  m!=0){
        cnt = 0;
        memset(idx,0,sizeof(idx));
        for (int i =0;i<m;i++){
            cin >> map[i];
        }
        for (int i =0;i<m;i++){
            for (int j =0;j<n;j++){
                if (map[i][j] == '@' && idx[i][j] ==0){
                    cnt++;
                    //dfs(make_pair(i,j),cnt,m,n);   
                    bfs(make_pair(i,j),cnt,m,n);   
                }
            }
        }
        cout << cnt << endl;
    }
}