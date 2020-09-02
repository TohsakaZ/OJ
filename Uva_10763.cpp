#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());
    int number = 0;
    while (cin >> number && number != 0)
    {
        map<pair<int, int>,int> table;
        for (int i = 0; i < number; i++)
        {
            int orig=0, target=0;
            cin >> orig >> target;
            if (number%2!=0)
            {
                continue;
            }
            if (table.count(make_pair(target,orig))==0){
                table[make_pair(orig, target)] += 1;
            }
            else{
                table[make_pair(target, orig)] -= 1;
                if (table[make_pair(target,orig)] == 0 ){
                    table.erase(make_pair(target, orig));
                }
            }
        }
        if (number%2!=0){
            cout << "NO" << endl;
            continue;
        }
        if (table.size()!=0){
            cout << "NO" << endl;
        }
        else{
            cout << "YES" << endl;
        }
    }
}