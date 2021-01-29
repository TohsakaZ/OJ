#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MaxN = 1000000;

int n;
int fl[MaxN];
int ce[MaxN];
int level[MaxN];

int judge_height(int height,int i){
    if (height > ce[i]){
        height = ce[i];
    }
    else if (height<fl[i]){
        height = fl[i];
    }
    return height;
}

void search_L(int left,int right){
    int height = ce[left];
    for (int i = left; i <= right;i++){
        height = judge_height(height, i);
        level[i] = height;
    }
}

void search_R(int left,int right){
    int height = ce[right];
    for (int i = right; i >= left;i--){
        height = judge_height(height, i);
        level[i] = min(height,level[i]);
    }
}

int sovle_ans(int left,int right){
    int ans = 0;
    for (int i = left; i <=right; i++)
    {
        ans += level[i] - fl[i];
    }
    return ans;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    while (case_n--){
        cin >> n;
        for (int i = 0; i < n;i++){
            cin >> fl[i];
        }
        for (int i = 0;i<n;i++){
            cin >> ce[i];
        }
        search_L(0, n - 1);
        search_R(0, n - 1);
        cout << sovle_ans(0, n - 1) << endl;
    }
}