#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    

    int case_num = 0;
    string  templine; 
    while (getline(cin,templine) && templine!="0")
    {
        stringstream n_temp(templine);
        int n=0;
        n_temp >> n;
        while (getline(cin,templine) && templine !="0")
        {
            stringstream temp_split(templine);
            int idx = 1; 
            stack<int> s;
            bool flag = true;
            for (int i =0;i<n;i++){
                int next_train;
                temp_split >> next_train;
                if (next_train < 1 || next_train > n){
                    flag = false;
                    break;
                }
                if (next_train < idx ){
                   if (s.empty() || s.top() != next_train ){
                      flag = false; 
                      break;
                   } 
                   else{
                       s.pop();
                   }
                }
                else{
                    while (idx < next_train && idx <= n){
                        s.push(idx++);
                    }
                    if (idx != next_train){
                        flag = false;
                        break;
                    }
                    else{
                        idx++ ;
                    }
                }
            }

            if (flag){
                cout << "Yes"<< endl;
            }
            else{
                cout << "No" << endl;
            }
        }
        cout << endl;
    }
}