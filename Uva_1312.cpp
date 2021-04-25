#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int N,W,H;
const int MaxN=100;
int tree_x[MaxN];
int tree_y[MaxN];

int cal_ans(int x,int y)
{
    int min_v = min(H-y,W-x);
    for (int i =0;i<N;i++){
        if (tree_x[i] <= x || tree_y[i] <= y){
            continue;
        }
        min_v = min(min_v,max(tree_x[i]-x,tree_y[i]-y));
    }
    return min_v;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    for (int case_i =0;case_i<case_n;case_i++){
        if (case_i){
            cout << endl;
        }
        cin >> N >> W >> H;
        set<int> xx,yy;
        for (int i =0;i<N;i++)
        {
            cin >> tree_x[i];
            cin >> tree_y[i];
            xx.insert(tree_x[i]);
            yy.insert(tree_y[i]);
        }
        xx.insert(0);
        yy.insert(0);
        vector<int> x_l(xx.begin(),xx.end()); 
        vector<int> y_l(yy.begin(),yy.end());
        int ans=0;
        int ans_x,ans_y;
        for (int yi=0;yi<y_l.size();yi++){
            for (int xi=0;xi<x_l.size();xi++)
            {
                int v = cal_ans(x_l[xi],y_l[yi]);
                if (v > ans){
                    ans = v;
                    ans_x = x_l[xi];
                    ans_y = y_l[yi];
                }
            }
        }
        cout << ans_x << " " << ans_y << " " << ans << endl;
    }

}