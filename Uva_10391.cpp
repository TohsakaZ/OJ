#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());
    string word;
    vector<string> words;
    set<string>  word_table;
    while (cin >> word)
    {
        words.push_back(word);
        word_table.insert(word);
    }

    for (auto item:words)
    {
        for (int i = 0; i < item.length()-1;i++)
        {
            if (word_table.count(item.substr(0,i+1))!=0 and word_table.count(item.substr(i+1))!=0)
            {
                cout << item << endl;
                break;
            }
        }
    }
    
}