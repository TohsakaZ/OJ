#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;

const int Max_line = 1010;
const int Max_word = 300;

int main()
{
    ifstream fin;
    fin.open("input.txt");
    cin.rdbuf(fin.rdbuf());
 
    vector<string> line_array[Max_line];
    int  max_word_array[Max_word];
    string templine;
    int line_count = 0;
    while (getline(cin, templine))
    {
        stringstream temp(templine);
        string tempword;
        int word_num = 0;
        while (temp >> tempword)
        {
            line_array[line_count].push_back(tempword);
            if (tempword.length() > max_word_array[word_num]){
                max_word_array[word_num] = tempword.length();
            }
            word_num++;
        }
        line_count++;
    }

    for (int i = 0; i < line_count;i++)
    {
        for (int j = 0; j < line_array[i].size()-1;j++)
        {
            cout << left << setw(max_word_array[j]+1) << setfill(' ') <<line_array[i][j];
        }
        cout << line_array[i][line_array[i].size() - 1];
        cout << endl;
    }
}