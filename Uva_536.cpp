#include <iostream>
#include <fstream>

using namespace std;

string pre_line,in_line;

void post_line(int pre_l,int pre_r,int in_l,int in_r){

    // find root in in line
    int idx=-1;
    for (int i =in_l;i<=in_r ;i++){
        if (in_line[i] == pre_line[pre_l]){
            idx = i;
            break;
        }
    }
    int left_size = idx - in_l;
    int right_size =in_r - idx; 
    
    // left
    if (left_size >0){
        post_line(pre_l+1,pre_l+1+left_size-1,in_l,in_l+left_size-1);
    }
    //  right
    if (right_size > 0){
        post_line(pre_l+left_size+1,pre_r,idx+1,in_r);
    }
    // root
    cout << pre_line[pre_l];
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    while (cin >> pre_line && cin >>in_line){
        post_line(0,pre_line.size()-1,0,in_line.size()-1);
        cout << endl;
    }
}
