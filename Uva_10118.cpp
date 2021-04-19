#include <iostream>
#include <cstring>

/*
这题的状态方程比较好想，而且每个状态之前的选择顺序是不影响后续状态的值
一定要通过记忆化的方式，因为有重叠子问题(也是动态规划高效的方面)
另外就是状态量的选取要保证无后效性，即能保证最优子问题的结构，保证状态转移有效性
这题巧妙地方在于可以在递归的时候采用DFS的编写方式，即不把状态通过参数传递 而是通过全局变量，调用完后恢复状态量
*/

using namespace std;

const int w=4;
const int MaxS=5;
const int maxH = 41;
typedef int mark[4];
int arr[maxH][5];
int H;
int dp[maxH][maxH][maxH][maxH];
int cnt[4];
int ans;

int dfs(int num,int status){
    int& ans = dp[cnt[0]][cnt[1]][cnt[2]][cnt[3]];
    if (ans > -1){
        return ans;
    }
    if (num==5){
        return (ans = 0);
    }
    ans=0;
    for (int i =0;i<w;i++){
        if (cnt[i]+1<=H)  {
            cnt[i]++;
            int st = 1<<arr[cnt[i]][i+1];
            if (status & st){
                ans = max(ans,dfs(num-1,status ^ st)+1);
            }
            else {
                ans = max(ans,dfs(num+1,status | st));
            }
            cnt[i]--;
        }
    }
    return ans;
}

int main()
{
    while (cin >> H && H >0){
        for (int i =1;i<=H;i++){
            for (int j=1;j<=4;j++){
                cin >> arr[i][j];
            }
        }
        memset(dp,-1,sizeof(dp));
        memset(cnt,0,sizeof(cnt));        
        cout << dfs(0,0) << endl;
    }
}