#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int N, D;
    while (cin >> N && cin >> D && N!=0 && D!=0){
        D = N - D;
        string ans;
        string templine;
        cin >> templine;
        deque<char> q;
        for (int i = 0; i < N - D+1;i++){
            char now = templine[i];
            while (!q.empty() && q.back() < now)
                q.pop_back();
            q.push_back(now);
        }
        ans += q.front();
        q.pop_front();
        for (int i = N - D +1; i < N;i++){
            char now = templine[i];
            while (!q.empty() && q.back() < now){
                q.pop_back();
            }
            q.push_back(now);
            ans += q.front();
            q.pop_front();
        }
        cout << ans << endl;
    }
}