#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;


char op(char c){
    if (c == '[' || c== ']'){
        return ']'+'[' - c;
    }
    else{
        return ')'+'(' - c;
    }

}

bool judge(string& input){
    stack<char> s;
    for (int i =0;i<input.size();i++){
        char c = input[i];
        if (c == ']' || c == ')'){
            if (s.empty() || c!=op(s.top())){
                return false;
            }
            s.pop();
        }
        else if (c== '[' || c == '(') {
            s.push(c);
        }
        else{
            return false;
        }
    }
    if (s.empty()){
        return true;
    }
    else{
        return false;
    }
}
int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    
    int n;
    cin >> n;
    string templine;
    getline(cin,templine);
    while (n--){
        getline(cin,templine);
        cout <<  (judge(templine) ? "Yes" : "No") << endl;
    }

}