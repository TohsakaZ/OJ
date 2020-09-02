#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int case_number = 0;
    cin >> case_number;
    while (case_number--)
    {
        int queue_size = 0, pos = 0;
        int priority_pos = 0;
        cin >> queue_size >> pos;
        map<int, vector<int > > table;
        for (int queue_i = 0; queue_i < queue_size;queue_i++)
        {
            int priority;
            cin >> priority;
            table[priority].push_back(queue_i);
            if (queue_i==pos) {
                priority_pos = priority;
            }
        }

        int sum_minutes = 0;
        int last_loc = 0;
        for (int priority_i = 9; priority_i > priority_pos;priority_i--)
        {
            if (table[priority_i].size()==0){
                continue;
            }
            auto  find_loc = lower_bound(table[priority_i].begin(), table[priority_i].end(), last_loc);
            if  (find_loc==table[priority_i].begin()){
                last_loc = table[priority_i][table[priority_i].size() - 1];
            }
            else{
                last_loc = *(--find_loc);
            }
            sum_minutes += table[priority_i].size();
        }

        auto find_loc = lower_bound(table[priority_pos].begin(), table[priority_pos].end(), last_loc);
        if (find_loc == table[priority_pos].end())
        {
            find_loc=table[priority_pos].begin();
        }
        auto pos_loc = lower_bound(table[priority_pos].begin(), table[priority_pos].end(), pos);
        auto minutes = pos_loc - find_loc;
        sum_minutes += (minutes < 0 ? minutes + table[priority_pos].size() : minutes) + 1;
        cout << sum_minutes << endl;
    }
}