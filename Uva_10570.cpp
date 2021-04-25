#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;

const int MaxN = 500;
int n;
int arr[MaxN];
int arr_bak[MaxN];
int loc[MaxN+1];
int loc_bak[MaxN+1];


int solve(int l,int d)
{
    memcpy(arr_bak,arr,sizeof(int) * n);
    memcpy(loc_bak,loc,sizeof(int) * n);
    int cnt=0;
    int dest_num = l;
    for (int i = 0; i < n; i++)
    {
        int j = loc_bak[dest_num];
        if (i != j) {
            swap(arr_bak[i],arr_bak[j]);
            swap(loc_bak[arr_bak[i]], loc_bak[arr_bak[j]]);
            cnt++;
        }

        dest_num += d;
        if (dest_num < 0){
            dest_num += n;
        }
        if (dest_num >= n){
            dest_num -= n;
        }
    }
    return cnt;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    while (cin >> n && n!=0){
        for (int i=0;i<n;i++){
            cin >> arr[i];
            arr[i]--;
            loc[arr[i]]=i;
        }
        int ans = INT32_MAX;
        for (int i = 0; i < n; i++)
        {
            ans = min(ans,solve(i,1));
            ans = min(ans,solve(i,-1));
        }
        cout << ans << endl;
    }
}