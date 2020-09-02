#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include <iomanip>
#include <fstream>

using namespace std;

bool judge_vector_zero(const  vector<int>& v)
{
    for (auto item:v){
        if  (item!=0){
            return false;
        }
    }
    return true;
}

void print_vector(const  vector<int>& v)
{
    for  (auto item:v)
    {
        cout << setw(3) << item;
    }
    cout << endl;
}

int main()
{
    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int case_num = 0;
    cin >> case_num;
    for (int case_i = 0; case_i < case_num;case_i++)
    {
        int size_tuple = 0;
        cin >> size_tuple;
        vector<int> tuple;
        for (int size_i = 0; size_i < size_tuple; size_i++)
        {
            int tuple_number;
            cin >> tuple_number;
            tuple.push_back(tuple_number);
        }

        set<vector<int> > find_ex;
        while (!judge_vector_zero(tuple) && find_ex.count(tuple)==0 )
        {
            find_ex.insert(tuple);
            int first_item = tuple[0];
            for (int i = 0; i < tuple.size()-1;i++)
            {
                tuple[i] = abs(tuple[i] - tuple[i + 1]);
            }
            tuple[tuple.size() - 1] = abs(tuple[tuple.size() - 1] - first_item);
        }

        if (judge_vector_zero(tuple)){
            cout << "ZERO" << endl;
        }
        else{
            cout << "LOOP" << endl;
        }
    }
}