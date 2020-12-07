#include <iostream>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, int> table;

int get_idx(char a){
    if (table.count(a)==0){
        table[a] = table.size();
    }
    return table[a];
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    string templine;
    while (cin >> templine && templine !="#"){
        table.clear();
        map<char , set<char> > edge;
        int idx = 0;
        while (idx < templine.length())
        {
            char x = templine[idx];
            idx += 2;
            while (idx < templine.length() && templine[idx] != ';'){
                char y = templine[idx];
                edge[x].insert(y);
                edge[y].insert(x);
                idx++;
            }
            idx++;
        }

        vector<int> arr;
        vector<char> char_table;
        int count = 0;
        for (auto iter = edge.begin(); iter != edge.end(); iter++)
        {
            arr.push_back(count++);
            char_table.push_back(iter->first);
        }

        int min = 10;
        vector<int> min_ans;
        do
        {
            int max = 0;
            for (int i = 0; i < arr.size() - 1; i++)
            {
                for (int j = i+1; j < arr.size();j++){
                    if (edge[char_table[arr[i]]].count(char_table[arr[j]])!=0 && j-i > max){
                        max = j - i;
                    }
                }
            }

            if (max < min ){
                min = max;
                min_ans = arr;
            }

        } while (next_permutation(arr.begin(), arr.end()));

        for (int i = 0; i < min_ans.size(); i++)
        {
            printf("%c ", char_table[min_ans[i]]);
        }
        printf("-> %d\n", min);
    }
}