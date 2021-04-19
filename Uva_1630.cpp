/*
这题主要注意一下状态转移 类似切分链路的思路 除了遍历所有可能的分成两个子序列的情况外，还需要判断一下周期的情况
另外注意DP数组的给的大小。。这题给MaxL=100爆了
*/
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <cstring>
using namespace std;
const int maxL=101;
unordered_map<string,string> dtable;
int dp[maxL][maxL];
string templine;
int len_digit(int k){
    if (k<10){
        return 1;
    }
    else if (k < 100){
        return 2;
    }
    else{
        return 3;
    }
}
int DP(int beg,int end){
    string cnt_s = templine.substr(beg,end-beg);
    int& ans=dp[beg][end];
    if (ans >0){
        return ans;
    }
    if (dtable.count(cnt_s)!=0){
        ans = dtable[cnt_s].length();
        return ans;
    }
    ans = end-beg;
    dtable[cnt_s]=cnt_s;
    if (ans == 1) {
        return ans;
    }
    int max_div = ceil((end-beg)/2);
    int len = end-beg;
    for (int div=1;div<=max_div;div++){
        if (len % div ==0){
            int k = len / div;
            bool flag = true;
            string temp = templine.substr(beg,div);
            for (int idx=1;idx<k;idx++){
                if (templine.substr(beg+idx*div,div)!=temp){
                    flag = false;
                    break;
                }
            }
            if (flag){
                int kn = DP(beg,beg+div)+2+len_digit(k);
                if (kn < ans){
                    ans  = kn;
                    dtable[cnt_s]=to_string(k)+"("+dtable[templine.substr(beg,div)]+")";
                }
            }
        }
    }
    for (int idx=beg+1;idx<end;idx++){
        int kn = DP(beg,idx)+DP(idx,end);
        if (kn < ans ){
            ans = kn;
            dtable[cnt_s] = dtable[templine.substr(beg,idx-beg)]+dtable[templine.substr(idx,end-idx)];
        }
    }
    return ans;
}
int main()
{
    while (cin >> templine){
        memset(dp,0,sizeof(dp));
        dtable.clear();
        DP(0,templine.length());
        cout << dtable[templine] << endl;
    }
}