#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class big_int
{
public:
    big_int(string s){
        value = "";
        for (int i =s.size()-1;i>=0;i--){
            value += s[i];
        }
    };

    void double_v(){
        int add = 0;
        for (int i = 0; i < value.size(); i++)
        {
            int next = 2 * (value[i] - '0') + add;
            value[i] = '0' + (next % 10);
            add = next / 10;
        }
        if (add!=0){
            value += '0' + add;
        }
    }

    
    string value;
};

map<string, int> Count;
string Line;
int idx;

void dfs(int d)
{
    if (Line[idx] == '['){
        // left
        idx++;
        dfs(d+1);
        
        // ,
        idx++;

        //right
        dfs(d+1);
        // ]
        idx++;
    }
    else{
        string temp = "";
        while (Line[idx] != ',' && Line[idx] !=']' && idx < Line.size())
        {
            temp = temp + Line[idx];
            idx++;
        }
        big_int v(temp);
        while (d--)
        {
            v.double_v();
        }
        //cout << temp << " is " << v.value << endl;
        Count[v.value]++;
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_n;
    cin >> case_n;
    while (case_n--)
    {
        Count.clear();
        idx = 0;
        cin >> Line;
        dfs(0);
        int max = -1;
        int total = 0;
        for (auto &item : Count)
        {
            if (item.second > max){
                max = item.second;
            }
            total += item.second;
        }
        cout << total - max << endl;
    }
}