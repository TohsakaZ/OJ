#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    for (int case_i = 0; case_i < case_n; case_i++)
    {
        printf("Case %d: ",case_i+1);

        string temp1, temp2;
        cin >> temp1 >> temp2;
        vector<int> table_0, table_1, table_2, table_3;
        int s1 = 0, s2 = 0;
        for (int i = 0; i < temp1.length(); i++)
        {
            if (temp1[i] == temp2[i]){
                continue;
            }
            if (temp1[i] == '1')
            {
                table_1.push_back(i);
                s1++;
            }
            else if (temp1[i] == '0'){
                table_0.push_back(i);
            }
            else{
                if (temp2[i] == '0'){
                    table_2.push_back(i);
                }
                else{
                    table_3.push_back(i);
                }
            }
            if (temp2[i] == '1'){
                s2++;
            }
        }
        // IMPOSSIBLE
        int ans = 0;
        int one_n = s2 - s1;
        if (one_n < 0){
            cout << -1 << endl;
            continue;
        }
        if (one_n <= table_3.size()){
            ans += table_0.size() + table_1.size() + table_3.size() - one_n;
            cout << ans / 2 + table_2.size() + table_3.size() << endl;
        }
        else{
            ans += table_0.size() - (one_n - table_3.size()) + table_1.size();
            cout << ans / 2 + table_2.size() + table_3.size() + (one_n - table_3.size()) << endl;
        }
    }
}