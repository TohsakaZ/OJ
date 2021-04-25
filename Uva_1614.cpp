#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int maxN = 1000000 + 10;

int arr[maxN];
int id[maxN];
int flg[maxN];

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int n;
    while (cin >> n)
    {
        int64_t  sum = 0;
        memset(flg, 0, sizeof(flg));
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            id[i] = i;
            sum += arr[i];
        }
        if (sum % 2 == 1){
            cout << "No" << endl;
            continue;
        }
        sum = sum / 2;
        for (int i = n - 1; i >= 0;i--){
            if (sum >= arr[i]){
                sum -= arr[i];
                flg[i] = 1;
            }
        }
        cout << "Yes" << endl;
        for (int i = 0; i < n; i++)
        {
            if (i){
                cout << ' ';
            }
            if (flg[i]) {
                cout << 1;
            }
            else{
                cout << -1;
            }
        }
        cout << endl;
    }
}