#include <iostream>
#include <fstream>
#include <stack>
#include <map>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int matrix_num=0; 
    cin >>  matrix_num;
    map<char,pair<int,int> > matrix_table;
    while (matrix_num--){
        char matrix_name;
        int row,col;
        cin >> matrix_name >> row >> col;
        matrix_table[matrix_name] = make_pair(row,col);
    }
    string templine;
    getline(cin,templine);
    while (getline(cin,templine)){
        int cnt = 0;
        stack<pair<int,int> > s;
        for (int i =0;i<templine.length();i++) {
            pair<int,int> right;
            if (templine[i] == '('){
                s.push(make_pair(-1,-1));
                continue;
            }
            else if (templine[i] == ')'){
                right = s.top();
                s.pop();
                s.pop(); // pop '('
            }
            else{
                right = matrix_table[templine[i]];
            }
            if (!s.empty() && s.top() !=make_pair(-1,-1)){
                pair<int,int> left = s.top();
                s.pop();
                if (left.second != right.first){
                    cout << "error" << endl;
                    cnt = -1;
                    break;
                }
                else{
                    cnt += left.first* left.second * right.second ;
                    s.push(make_pair(left.first,right.second));
                }
            }
            else{
                s.push(right);
            }
        }
        if (cnt>=0){
            cout << cnt << endl;
        }
    }
}