#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <queue>

using namespace std;

const int MaxN = 10000000;

int Value[MaxN];
int left_node[MaxN];
int right_node[MaxN];

int top = 0;

void str2ns(string& str,int& n,string& s){
    stringstream temp_split(str.substr(1));
    temp_split >> n;
    temp_split >> s;
    if (s.length() == 2){
        s = "";
    }
    else{
        s = s.substr(1,s.length()-2);
    }
}


bool add_node(int n,string&s){
    int head = 0;
    for (int i =0;i<s.length();i++){
        if (s[i] == 'L'){
            if (left_node[head] == -1){
                left_node[head] = ++top;
            }
            head = left_node[head];
        }
        else if (s[i] == 'R'){
            if (right_node[head] == -1){
                right_node[head] = ++top;
            }
            head = right_node[head];
        }
    }
    if (Value[head] == -1){
        Value[head] = n;
    }
    else{
        return false;
    }
    return true;
}

bool bfs(){
    stringstream output;
    int head = 0;
    queue<int> q;
    q.push(head);
    while (!q.empty()){
        head = q.front();
        q.pop();
        if (left_node[head] !=-1){
            q.push(left_node[head]);
        }
        if (right_node[head] !=-1){
            q.push(right_node[head]);
        }
        if (Value[head]==-1){
            return false;
        }
        output << Value[head] << " ";
    }
    cout << output.str() << endl;
    return true;
}


int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    string templine;
    while (cin>> templine){
        memset(Value,-1,sizeof(Value));
        memset(left_node,-1,sizeof(left_node));
        memset(right_node,-1,sizeof(right_node));
        int n;
        string s;
        str2ns(templine,n,s);
        bool flag = true;
        flag = add_node(n,s);
        while (cin >> templine && templine!="()") {
            str2ns(templine,n,s); 
            if (flag){
                flag = add_node(n,s);
            }
        }
        if (flag){
            flag = bfs(); 
        }
        if (!flag){
            cout << "not complete" << endl;
        }
    }
}
