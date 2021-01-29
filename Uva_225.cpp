#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <set>

using namespace std;
const int MaxW= 300;
const int MaxN=20;
const int mx[4]={1,0,0,-1};
const int my[4]={0,1,-1,0};
const int mc[4]={'e','n','s','w'};
map<char,int> md={
    {'e',0},{'n',1},{'s',2},{'w',3}
};
const int ms[2][2]={{0,3},{1,2}};
int distance[MaxN][MaxN];
int n;
int ans_num;
char dir[MaxN];

map<int, vector<int> > block_x;
map<int, vector<int> > block_y;

void print_ans(vector<string>& result){
    string ans(n,' ');
    for (int i =0;i<n;i++){
        ans[i] = dir[i];
    }
    result.push_back(ans);
}

void sum(){
    for (int i=0;i<MaxN;i++){
        for (int j =0;j<MaxN;j++){
            
        }
    }
}

bool confilct(int x1,int y1,int x2,int y2){
    int min_bound,max_bound;
    if (x1==x2){
        int min_y = min(y1,y2);
        int max_y = max(y1,y2);
        min_bound = lower_bound(block_x[x1].begin(),block_x[x1].end(),min_y) - block_x[x1].begin();
        max_bound = upper_bound(block_x[x1].begin(),block_x[x1].end(),max_y) - block_x[x1].begin();
    }
    else if( y1==y2){
        int min_x = min(x1,x2);
        int max_x = max(x1,x2);
        min_bound = lower_bound(block_y[y1].begin(),block_y[y1].end(),min_x) - block_y[y1].begin();
        max_bound = upper_bound(block_y[y1].begin(),block_y[y1].end(),max_x) - block_y[y1].begin();
       
    }
    if (max_bound-min_bound >0){
        return true;
    }
    else{
        return false; 
    }
}

void dfs(int x,int y,set<pair<int,int> >& table,int d,int num,vector<string>& result){
    if (num==n){
        if (x==0&&y==0) {
            ans_num++;
            print_ans(result);
        }
        return;
    }
    for (int s=0;s<2;s++) 
    {
        int i = ms[d][s];
        int next_x = x+mx[i]*(num+1);
        int next_y = y+my[i]*(num+1);
        if (table.count(make_pair(next_x,next_y))!=0){
            continue;
        }
        
        dir[num]=mc[i]; 
        table.insert(make_pair(next_x,next_y));
        dfs(next_x,next_y,table,1-d,num+1,result);
        table.erase(make_pair(next_x,next_y));
    }
}

bool serach(string s){
    int x=0,y=0;
    for (int i =0;i<s.size();i++){
        int next_x=x+mx[md[s[i]]]*(i+1);
        int next_y=y+my[md[s[i]]]*(i+1);
        if (confilct(next_x,next_y,x,y)){
            return false;
        }
        x = next_x;
        y = next_y;
    }
    return true;
}

int main()
{
     
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    clock_t beg = clock();
    set<int> sovle_num={7,8,15,16};
    vector<string>  sovle_result[MaxN];  
    for (auto item:sovle_num){
        n = item;
        set<pair<int,int> > table;
        for (int i =0;i<4;i++){
            table.clear();
            int beg_x = mx[i];
            int beg_y = my[i];
            table.insert(make_pair(beg_x,beg_y));
            int d=(i%3?1:0);
            dir[0] = mc[i];
            dfs(beg_x,beg_y,table,1-d,1,sovle_result[n]);
        }
    }

    int case_num;
    cin >> case_num;
    for (int i =0;i<case_num;i++){
        ans_num=0;
        block_x.clear();
        block_y.clear();
        int k;
        cin >> n >> k;
        for (int j =0;j<k;j++){
            int x,y;
            cin >> x >> y;
            block_x[x].push_back(y);
            block_y[y].push_back(x);
        }
        for (auto& item:block_x){
            sort(item.second.begin(),item.second.end());
        }
        for (auto& item:block_y){
            sort(item.second.begin(),item.second.end());
        }
        
        for (int i =0;i<sovle_result[n].size();i++){
            if (serach(sovle_result[n][i])){
                ans_num++;
                printf("%s\n",sovle_result[n][i].c_str());
            }
        }
        printf("Found %d golygon(s).\n\n",ans_num);
    }
    clock_t end=clock();
    //printf("Spend %lf s\n",(double)(end-beg)/CLOCKS_PER_SEC);
}