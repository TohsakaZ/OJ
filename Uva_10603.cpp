#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>

using namespace std;

const int max_cap=200;
int full[3],d;
int vis[max_cap][max_cap][max_cap];

class water
{
public:
    water(){
        cur[0] = 0;
        cur[1] = 0;
        cur[2] = 0;
        pour_warter=0;
    }

    int cur[3];
    int pour_warter=0;
    
    bool operator<(const water& Other) const{
        return this->pour_warter > Other.pour_warter;
    }
};


int ans_pour;
int ans_d;

void bfs(water init)
{
    priority_queue<water> q;
    q.push(init); 
    while (!q.empty()){
        water now =q.top(); q.pop();
        if (vis[now.cur[0]][now.cur[1]][now.cur[2]]){
            continue;
        }
        for (int i =0;i<3;i++){
            if (now.cur[i] == d){
                ans_pour = now.pour_warter;
                ans_d = d;
                return;
            }
            else if (now.cur[i] < d && now.cur[i] > ans_d ){
                ans_d = now.cur[i];
                ans_pour = now.pour_warter;
            }
        }
        vis[now.cur[0]][now.cur[1]][now.cur[2]] = 1;
        for (int i =0;i<3;i++){
            for (int j=0;j<3;j++){
                if (i==j){
                    continue;
                }
                int pour = min(full[j]-now.cur[j],now.cur[i]);
                if (pour == 0){
                    continue;
                }
                water next(now);
                next.cur[i]-=pour;
                next.cur[j]+=pour;
                next.pour_warter+=pour;
                q.push(next); 
            }
        }
    }

}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_num;
    cin >> case_num;
    while (case_num--){
        cin >> full[0] >> full[1] >> full[2] >> d;
        memset(vis,0,sizeof(vis));
        ans_d = -1;
        water init;
        init.cur[2] = full[2];
        bfs(init);
        printf("%d %d\n",ans_pour,ans_d);
    }

}