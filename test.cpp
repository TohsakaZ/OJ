#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

using namespace std;

void print_vec(vector<int>& vec)
{
    for (int i = 0; i < vec.size();i++)
    {
        cout << setw(10) << vec[i] << endl;
    }
}

int main()
{
    map<string, vector<double> > test_map;
    vector<int> test_vec(10, 0);
    print_vec(test_vec);
    int j = 0;
    for (int i = 0; i < 10;i++)
    {
        j += i;
    }
    cout << j << endl;
    cout << "hello worldd" << endl;
}