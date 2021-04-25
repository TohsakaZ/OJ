#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int  case_n;
    cin >> case_n;
    for (int i =0;i<case_n;i++){
        if (i){
            cout << endl;
        }
        int num;
        cin >> num;
        vector<pair<int,int> > arr;
        for (int i =0;i<num;i++){
            int q,d;            
            cin >> q >> d;
            arr.push_back(make_pair(q,d));
        }
        sort(arr.begin(),arr.end(),[] (pair<int,int> x,pair<int,int> y) -> bool { return x.second < y.second || (x.second == y.second && x.first < y.first);});
        priority_queue<pair<int, int> > select;
        int now_t = 0;
        for (auto &item : arr)
        {
            if (now_t+ item.first <=item.second){
                select.push(item);
                now_t += item.first;
            }
            else{
                if (!select.empty() && item.first < select.top().first){
                    now_t +=  item.first - select.top().first;
                    select.pop();
                    select.push(item);
                }
            }
        }
        cout << select.size() << endl;
    }

}