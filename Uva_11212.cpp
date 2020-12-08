#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

int n;
int num[10];

int ID(int*arr){
    int ans=0;
    for (int i =0;i<n;i++){
        ans = ans*10+arr[i];
    }
    return ans;
}

void decode(int num,vector<int>& arr){
    int count=n;
    while (count--){
        arr[count]=num%10;
        num/=10;
    }
}

int reverse_num(const vector<int>& arr){
    int ans =0;
    for (int i =0;i<arr.size()-1;i++){
        if (arr[i]>arr[i+1]){
            ans ++;
        }
    }
    return ans;
}

unordered_map<int,int> vis;

int result;
bool dfs(int maxd,int d,int beg){
    vis[beg] = d;
    if (d==maxd){
        if(beg == result){
            return true;
        }
        else{
            return false;
        }
    }
    vector<int> now(n);
    decode(beg,now);
    int r_num = reverse_num(now);
    if (r_num > 3*(maxd-d)){
        return false;
    }
    vector<int> next(n);
    for (int beg_loc=0;beg_loc<n-1;beg_loc++){
        for (int len=1;len<n-beg_loc;len++) {
           for (int insert_loc=beg_loc+len+1;insert_loc<=n;insert_loc++) {
                for (int i =0;i<n;i++){
                    if (i<beg_loc){
                        next[i] = now[i];
                    }
                    else if (i>=beg_loc && i<beg_loc+len){
                        next[insert_loc-len+i-beg_loc] = now[i];
                    }
                    else if (i>=beg_loc+len && i < insert_loc){
                        next[beg_loc+i-beg_loc-len]  = now[i];
                    }
                    else{
                        next[i]=now[i];
                    }
                }
                int next_num = ID(&next[0]);
                if ((vis.count(next_num)==0 || (d+1) < vis[next_num]) &&  dfs(maxd,d+1,next_num)){
                    return true;
                }
           }
        }
    }
    return false;
}

int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int final[9];
    for (int i=0;i<9;i++){
       final[i] =i+1;
    }
    int case_num=0;
    while (cin >> n && n!=0){
        case_num++;
        for (int i =0;i<n;i++){
            cin >> num[i]; 
        }
        int ok=-1;
        int beg = ID(num);
        result = ID(final);
        for (int maxd=0;maxd<n;maxd++){
            vis.clear();
            if (dfs(maxd,0,beg)){
                ok=maxd; break;
            }
        }
        if (ok>-1){
            printf("Case %d: %d\n",case_num,ok);
        }
        else{
            printf("Case %d: %d\n",case_num,n);
        }
    }
}