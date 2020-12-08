#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <cstring>
#include <math.h>
#include <queue>
#include <map>

const int MaxW = 16;
const int MaxH = 16;
const int MaxP = MaxW*MaxH;
const int MaxN = 3;

using namespace std;


char M[MaxW*MaxH];
vector<int> edge[MaxW*MaxH+2];
int vis1[MaxP*MaxP*MaxP];
int vis2[MaxP*MaxP*MaxP];
int w,h,n;

void decode(int loc,vector<int>& p){
    int count=n;
    while (count--){
        p[count] = loc%(w*h);
        loc = loc / (w*h);
    }
    return;
}

int code(vector<int> p){
    int ans =0;
    for (int i =0;i<n;i++){
        ans= ans*w*h+p[i]; 
    }
    return ans;
}

class point
{
public:
    point();
    point(int l,int b,int e){
       loc =l;
       begf=b;
       endf=e; 
    }
    int loc=0;
    int begf=0;
    int endf=0;

    bool operator<(const point& Other) const{
        return begf+endf > Other.begf+Other.endf;
    }

};

bool conflict(int x1,int x2 ,int y1,int y2){
    if (x1==x2 || x1==y2 && x2 == y1){
        return true;
    }
    else{
        return false;
    }
}

int extend_bfs(priority_queue<point>& q,int*vis,int*vis_other){
    point now_p = q.top(); q.pop();
    int now=now_p.loc;
    if (vis_other[now]!=-1){
        return vis_other[now] + vis[now];
    }
    if (now_p.begf > vis[now]){
        return -1;
    }
    vector<int> p(n);
    decode(now,p);
    vector<int> next(n);
    for (int i =0;i<edge[p[0]].size();i++){
        next[0] = edge[p[0]][i];
        for (int j =0;j<edge[p[1]].size();j++){
            next[1] = edge[p[1]][j];
            if (conflict(next[1],next[0],p[1],p[0])) continue;
            for (int k=0;k<edge[p[2]].size();k++){
                next[2] = edge[p[2]][k];
                if (conflict(next[2],next[1],p[2],p[1])) continue;
                if (conflict(next[2],next[0],p[2],p[0])) continue;
                int next_loc =code(next);
                if (vis[next_loc]==-1 || vis[next_loc] > vis[now]+1){
                    vis[next_loc] = vis[now]+1;                
                    q.push(point(next_loc,now_p.begf+1,0));
                }
            }
        }
    }
    return -1;
}

int bfs_Astar(int beg,int end){
    // set move
    vector<int> end_loc(n);
    decode(end,end_loc);
    priority_queue<point> q1;
    priority_queue<point> q2;
    q1.push(point(beg,0,0)); vis1[beg] = 0;
    q2.push(point(end,0,0)); vis2[end] = 0;
    while (true){
        int ans=-1;
        if (q1.size() < q2.size()){
            ans =extend_bfs(q1,vis1,vis2);
        }
        else{
            ans = extend_bfs(q2,vis2,vis1);
        }
        if (ans >=0 ){
            return ans;
        }
    }
}
int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while(cin>>w >> h >>n && w!=0 && h!=0 && n!=0){
        vector<int> move;
        move.push_back(0); 
        move.push_back(-1);
        move.push_back(+1);
        move.push_back(+w);
        move.push_back(-w);
        memset(vis1,-1,sizeof(vis1));
        memset(vis2,-1,sizeof(vis2));
        vector<char> point;
        map<char,int > beg,end;
        // build map
        string templine;
        getline(cin,templine);
        for (int i =0;i<h;i++) {
            getline(cin,templine);
            for (int j=0;j<w;j++){
                int loc = i*w+j;
                M[loc]=templine[j];
                if ('A'<=M[loc] && M[loc] <= 'Z'){         
                    end[M[loc]+'a'-'A'] = loc;
                    M[loc] = ' ';
                }
                else if ('a' <= M[loc] && M[loc] <= 'z'){
                    beg[M[loc]] = loc;
                    point.push_back(M[loc]);
                }
            }
        }
        for (int i =0;i<h;i++){
            for (int j=0;j<w;j++){
                int loc =i*w+j;
                edge[loc].clear();
                if (M[loc]!='#'){
                    for (int k =0;k<5;k++){
                        if (M[loc+move[k]]!='#'){
                            edge[loc].push_back(loc+move[k]);
                        }
                    }
                }
            }
        }
        vector<int> p_loc1,p_loc2;
        for (int i =0;i<n;i++){
            p_loc1.push_back(beg[point[i]]);
            p_loc2.push_back(end[point[i]]);
        }
        if (n<=2){
            p_loc1.push_back(w*h-1);
            p_loc2.push_back(w*h-1);
            edge[w*h-1].push_back(w*h-1);
        }
        if (n<=1){
            p_loc1.push_back(w*h-2);
            p_loc2.push_back(w*h-2);
            edge[w*h-2].push_back(w*h-2);
        }
        n = 3;
        int beg_loc = code(p_loc1);
        int end_loc = code(p_loc2);
        //clock_t beg_t = clock();
        printf("%d\n",bfs_Astar(beg_loc,end_loc));
        //clock_t end_t = clock();
        //printf("Spend time: %lf s\n",(double)(end_t-beg_t)/CLOCKS_PER_SEC);
    }
}