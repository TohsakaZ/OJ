#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

double average_vector(const vector<int>& v)
{
    int sum=0;
    for (auto item : v)
    {
        sum += item;
    }
    return sum / double(v.size());
}

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int case_number = 0;
    cin >> case_number;
    for (int case_i = 0; case_i < case_number;case_i++)
    {
        int dots_number = 0;
        cin >> dots_number;
        map<int, vector<int> > dot_table;
        for (int dot_i = 0; dot_i < dots_number;dot_i++)
        {
            int x, y;
            cin >> x >> y;
            dot_table[y].push_back(x);
        }
        double middle_value = average_vector(dot_table.begin()->second);
        bool flag = true;
        for (auto item : dot_table)
        {
            sort(item.second.begin(), item.second.end());
            double average = average_vector(item.second);
            if ( (item.second.size()%2!=0 and item.second[item.second.size()/2] != average)
                || (average!=middle_value) )
            {
                flag = false;
                break;
            }
        }

        cout << (flag ? "YES" : "NO") << endl;
    }
}