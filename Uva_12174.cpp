#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_num;
    cin >> case_num;
    while (case_num--){
        int s, n;
        cin >> s >> n;
        vector<int> ans(s, 1);
        vector<int> table(s, -1);
        for (int i = 0; i < n; i++)
        {
            int temp;
            int ans_now = (n - i - 1) % s;
            cin >> temp;
            temp -= 1; // from 0 begin;
            if (table[temp] != -1 && (i - table[temp] < s))
            {
                for (int j = 0; j < table[temp] + s - i;j++){
                    ans[(ans_now+s - j) % s] = 0;
                }
            }
            //cout << ans_now << " " << ans[ans_now] << endl;
            table[temp] = i;
        }

        int sum = 0;
        for (int i = 0; i < s; i++)
        {
            sum += ans[i];
        }
        cout << sum << endl;
    }
}