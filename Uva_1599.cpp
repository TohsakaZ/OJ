#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

map<int, int> room[100010];
int len[100010];
int father[100010];

void print_output(int n)
{
    int i = 1;
    vector<int> path;
    while (i != n)
    {
        path.push_back(room[i][father[i]]);
        i = father[i];
    }
    int k = path.size();
    cout << k << endl;
    for (int i = 0; i < k-1; i++)
    {
        cout << path[i]<< " ";
    }
    cout << path[k-1] << endl;
}

void bfs(int n)
{
    queue<int> q;
    father[n] = -1;
    len[n] = 0;
    q.push(n);

    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        if (now == 1 ){
            print_output(n);
            return;
        }
        for (auto& next:room[now]){
            // already visited
            if (len[next.first] !=-1 && len[next.first] < len[now]+1 ){
                continue;
            }
            // len equal(just change father)
            else if (len[next.first]  == len[now]+1){
                int f1 = father[next.first];
                if (room[next.first][f1] < next.second)
                {
                    continue;
                }
                else if (room[next.first][f1] == next.second){
                    int f2 = now;
                    while (f1!=f2 && room[f1][father[f1]] == room[f2][father[f2]] ){
                        f1 = father[f1];
                        f2 = father[f2];
                    }
                    if (f1==f2 || room[f1][father[f1]] <= room[f2][father[f2]]){
                        continue;
                    }
                }
                father[next.first] = now;
            }
            else{
                len[next.first] = len[now] + 1;
                father[next.first] = now;
                q.push(next.first);
            }
        }
    }
}

int main(){

    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int n, m;
    while (cin >> n && cin >> m){
        memset(len, -1, sizeof(len));
        memset(father, -1, sizeof(father));
        for (auto& item: room){
            item.clear();
        }
        //build map
        for (int i = 0; i < m; i++)
        {
            string templine;
            int a, b , c;
            cin >> a >> b >> c;
            if (room[a].count(b) == 0 || room[a][b] > c)
            {
                room[a][b] = c;
                room[b][a] = c;
            }
       }
       bfs(n);
    }
}