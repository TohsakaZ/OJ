#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>

using namespace std;

typedef int state[24];
const int MaxD = 1E6;
const int move_k[4][7]={
    {0,2,6,11,15,20,22},
    {1,3,8,12,17,21,23},
    {10,9,8,7,6,5,4},
    {19,18,17,16,15,14,13}
};
state end_s;
int end_num;
unordered_map<int,int> vis;
int ID(state s){
    int ans =0;
    for (int i =0;i<24;i++){
        if (s[i]){
            ans = ans | (1<<i);
        }
    }
    return ans;
}
void decode(int k,state s){
    for (int i =0;i<24;i++){
        s[i]  = 1 & (k >> i);
    }
}

void move_state(state s,int m){
    if (m<4){
        int temp=s[move_k[m][0]];
        for (int i =0;i<6;i++){
            s[move_k[m][i]] = s[move_k[m][i+1]];
        }
        s[move_k[m][6]] = temp;
    }
    else{
        if (m <=5){
            m = 5-m;
        }
        else{
            m = 9-m;
        }
        int temp=s[move_k[m][6]];
        for (int i=6;i>0;i--){
            s[move_k[m][i]] = s[move_k[m][i-1]];
        }
        s[move_k[m][0]] = temp;
    }
}

int lease_move(state s){
    const int r_loc[8]={
        6,7,8,11,12,15,16,17
    };
    int ans =0;
    for (int i =0;i<8;i++){
        if (s[r_loc[i]]) {
            ans++;
        }
    }
    return 8-ans;
}


bool dfs(int maxd,int d,int now,char* ans){
    if (d==maxd){
        if (now == end_num){
            return true;
        }
        else{
            return false;
        }
    }
    state s_now;
    decode(now,s_now);
    for (int m=0;m<8;m++){
        state next;
        memcpy(next,s_now,sizeof(s_now));
        // change next;    
        move_state(next,m);
        // cut useless
        if (lease_move(next) > (maxd - d -1)){
            continue;
        }
        int next_num = ID(next);
        if (vis.count(next_num)==0 || vis[next_num]> d+1){
            ans[d]='A'+m;
            vis[now] = d;
            if (dfs(maxd,d+1,next_num,ans)){
                return true;
            }
        }
    }
    return false;
}


bool update_ans(char* ans,char* ans_new,int n){
    for (int i =0;i<n;i++){
        if (ans_new[i]<ans[i]){
            memcpy(ans,ans_new,n);
            return true;
        }
        else if (ans_new[i] > ans[i]){
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    
    // init end result
    memset(end_s,0,sizeof(end_s));
    end_s[6] = end_s[7] = end_s[8] = 1;
    end_s[11] = end_s[12] = 1;
    end_s[15] = end_s[16] = end_s[17] =1;
    end_num=ID(end_s);

    state init;
    int temp;
    while (cin >> temp && temp!=0){
        init[0] = temp;
        for (int i =1;i<24;i++){
            cin >> init[i];
        }
        state beg[3];
        for (int j =1;j<=3;j++){
            for (int i =0;i<24;i++){
                beg[j-1][i] = (init[i]==j)?1:0;
            }
        }
        char result[MaxD];
        char ans[MaxD];
        result[0] = 'H'+1;
        int result_n = -1;
        int flag = 0;
        for (int maxd=0;maxd<1E6;maxd++){
            for (int j =0;j<3;j++){
                vis.clear();
                int beg_num =ID(beg[j]);
                vis[beg_num]=0;
                if (dfs(maxd,0,beg_num,ans) && update_ans(result,ans,maxd)){
                    flag = j+1; 
                }
            }
            if (flag){
                result_n = maxd;
                break;
            }
        }
        if (result_n){
            for (int i =0;i<result_n;i++){
                printf("%c",result[i]);
            }
            printf("\n");
        }
        else{
            printf("No moves needed\n");
        }
        printf("%d\n",flag);
    }
}