#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;

const int MaxN=200000;

int64_t Arr[MaxN];
int vis_l[MaxN];
int vis_r[MaxN];

bool search(int left,int right)
{
    if (right-left<=0){
        return true;
    }
    int l=left,r=right;
    while (l<=r){
        if (vis_r[l]>right && vis_l[l] < left){
            return search(left,l-1) && search(l+1,right);
        }
        if (vis_l[r]<left && vis_r[r] > right){
            return search(left,r-1) && search(r+1,right);
        }
        l++;
        r--;
    }
    return false;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_n;
    cin >> case_n;
    while (case_n--){
        int n;
        cin >>  n;
        map<int64_t,int> loc;
        memset(vis_l,-1,sizeof(int)*n);
        memset(vis_r,n+1,sizeof(int)*n);
        for (int i =0;i<n;i++){
            cin >> Arr[i];
            if (loc.count(Arr[i])){
                vis_l[i] = loc[Arr[i]];
                vis_r[loc[Arr[i]]] = i;
            }
            loc[Arr[i]] = i;
        }
        loc.clear();
        if (search(0,n-1)){
            cout << "non-boring" << endl;
        }
        else{
            cout << "boring" << endl;
        }
    }
}