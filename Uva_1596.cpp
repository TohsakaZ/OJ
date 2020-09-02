#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <fstream>

using namespace std;
typedef map<char, pair<int, map<int, int> > > arr_table;


int exper(string str,arr_table& table)
{
    stack<char> list;
    for (int i = 0; i < str.length();)
    {
        if ( str[i] <'0' || str[i]>'9'){
            list.push(str[i]);
            i += 2;
            continue;
        }
        else{
            int number = 0;
            while (i < str.length() and str[i] != ']')
            {
                number = 10 * number + (str[i] - '0');
                i++;
            }
            while (!list.empty())
            {
                char arr_name = list.top();
                list.pop();
                if (table[arr_name].second.find(number) == table[arr_name].second.end()){
                    return -1;
                }
                else{
                    number = table[arr_name].second[number];
                }
            }
            return number;
        }
    }
    return -1;
}

int main()
{
    ifstream fin;
    fin.open("input.txt");
    cin.rdbuf(fin.rdbuf());

    string templine;
    while (getline(cin,templine) and templine!=".")
    {
        arr_table table;
        int error_flag = 0;
        int line_count = 0;
        while (templine != ".")
        {
            line_count++;
            if (error_flag == 0)
            {
                if (templine.find('=')== string::npos){
                    char arr_name = templine[0];
                    int exper_value = exper(templine.substr(2, templine.size() - 3), table);
                    if (exper_value < 0){
                        error_flag = line_count;
                        continue;
                    }
                    else{
                        table[arr_name] = make_pair(exper_value, map<int, int>());
                    }
                }
                else{
                    int idx = templine.find('=');
                    char arr_name = templine[0];
                    int exper_v1 = exper(templine.substr(2, idx - 3), table);
                    int exper_v2 = exper(templine.substr(idx + 1, templine.size() - idx - 1), table);
                    if (exper_v1 < 0 || exper_v2 < 0 || exper_v1>=table[arr_name].first)
                    {
                        error_flag = line_count;
                        continue;
                    }
                    else{
                        table[arr_name].second[exper_v1] = exper_v2;
                    }
                }
            };
            getline(cin, templine);
        }
        cout << error_flag << endl;
    }
}