#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;
const int MaxN = 210;

char map[MaxN][MaxN];
int idx[MaxN][MaxN];

char h[6]={
    'W','A','K','J','S','D'
};

pair<int,int> dir[4]={
    make_pair(-1,0),make_pair(1,0),
    make_pair(0,1),make_pair(0,-1)
};

void  convert(char c,char* arr){
    int value=0;
    if (c >='0' && c<='9' ){
        value=c-'0';
    }
    else{
        value = c-'a'+10;
    }
    for (int i=0;i<4;i++){
        arr[3-i] = value % 2 +'0';
        value = value/2; 
    }
}

int dfs(int x,int y,int H,int W,int record){
    char c = record > 0 ? '1':'0';
    stack< pair<int,int> > s;
    s.push(make_pair(x,y));
    int black = 0;
    while (!s.empty()){
        auto now= s.top();
        s.pop(); 
        // if not c  or already visited
        if (map[now.first][now.second] != c || idx[now.first][now.second]!=0){
            //if white and already visited 
            if (record < 0 && black!=-1 && idx[now.first][now.second] >0){
                black = idx[now.first][now.second];
            }
            continue;
        }

        idx[now.first][now.second]=record; 
        // if visit arrive the border then black is -1
        if (record <0 && now.first==0 || now.first == H-1 || now.second==0 || now.second==W-1){
            black = -1;
        }
        // add next_point
        for (int d =0;d<4;d++){
            int next_x = now.first + dir[d].first;
            int next_y = now.second+ dir[d].second;
            if (next_x >=0 && next_x < H && next_y >=0 && next_y <W ){
                s.push(make_pair(next_x,next_y));
            }
        }
    }
    return black;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int H,W;
    int case_number=0;
    while (cin>> H >> W && H!=0 && W!=0){
        case_number++;
        memset(idx,0,sizeof(idx));
        string templine;
        //build map
        for (int i =0;i<H;i++){
            cin >> templine;
            for (int j=0;j<W;j++){
                convert(templine[j],&map[i][j*4]);
            }
        }

        int word_n=0;
        vector<int>  white_n;
        for (int i =0;i<H;i++){
            for (int j =0;j<W*4;j++){
                if (idx[i][j]==0){
                    if (map[i][j]=='0'){
                        int black = dfs(i,j,H,W*4,-1);                                                    
                        if (black>0){
                            white_n[black-1]++;
                        }
                        
                    }
                    else{
                        word_n++;
                        white_n.push_back(0);
                        dfs(i,j,H,W*4,word_n);
                    }
                }
            }
        }
        vector<char> ans;
        for (int i =0;i<white_n.size();i++){
            ans.push_back(h[white_n[i]]);
        }
        sort(ans.begin(),ans.end());
        printf("Case %d: ",case_number);
        for (int i =0;i<ans.size();i++){
            cout << ans[i];
        }
        cout << endl;
    }
}