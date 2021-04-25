#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int total_scord(int i,vector<int> a){
    int cnt = 0;
    int total= 0;
    while (cnt < 3)
    {
        if (i % 2){
            total+= a[cnt];
        }
        i = i / 2;
        cnt++;
    }
    return total;
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_cnt = 0;
    int n;
    while (cin >> n && n!=0){
        case_cnt++;
        vector<vector<int> > arr(n);
        for (int i = 0; i < n; i++)
        {
            double a,b,c;
            cin >> a >> b >> c;
            vector<int> s;
            s.push_back(round(100.0 * a));
            s.push_back(round(100.0 * b));
            s.push_back(round(100.0 * c));
            for (int k = 0; k < 8; k++)
            {
                arr[i].push_back(total_scord(k, s));
            }
            sort(arr[i].begin(), arr[i].end());
        }
        vector<int> rank(n);
        int last_score = 100000*3+10;
        int last_rank = -1;
        bool flag = true;
        for (int i = 0; i < n; i++)
        {
            cin >> rank[i];
            if (!flag){
                continue;
            }
            rank[i]--;
            bool edit = false;
            for (int k = arr[rank[i]].size() - 1; k >= 0; k--)
            {
                if (arr[rank[i]][k] < last_score || (arr[rank[i]][k] == last_score && rank[i] > last_rank)){
                    last_score = arr[rank[i]][k];
                    last_rank = rank[i];
                    edit = true;
                    //cout << last_score << " " << last_rank << endl;
                    break;
                }
            }
            if (!edit){
                flag = false;
            }
        }
        if (flag){
            printf("Case %d: %.2f\n", case_cnt, last_score / 100.0);
        }
        else{
            printf("Case %d: No solution\n", case_cnt);
        }
    }
}