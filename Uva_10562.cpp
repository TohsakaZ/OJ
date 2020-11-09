#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class node;
typedef node *link;
class node{
public:
    node(){};
    node(char c):c(c){};

public:
    char c;
    vector<int>  next;
};

node node_list[40000];
int top=0;

void pre_transver(int n)
{
    cout << node_list[n].c << '(';
    for (int i =0;i<node_list[n].next.size();i++){
        pre_transver(node_list[n].next[i]);
    }
    cout << ')';
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_number;
    cin >> case_number;
    string templine;
    //empty line
    getline(cin,templine);
    while (case_number--){
        top = 0;
        vector<pair<int,int > > before;
        vector<int> now;
        vector<pair<int,bool> > now_loc;
        
        // build tree
        while (getline(cin,templine) && templine[0] !='#'){
            now.clear();
            now_loc.clear();
            char c;
            int pre = before.size() > 0 ? 0 :-1;
            for (int i =0;i<templine.size();i++){
                char c = templine[i];
                if (c == ' '){
                    continue;
                }
                node_list[top].c = c;
                node_list[top].next.clear();
                now.push_back(top);
                if (pre!=-1){
                    if (i > before[pre].second){
                        pre++;
                    }
                    node_list[before[pre].first].next.push_back(top);    
                }
                top++;

                now_loc.push_back(make_pair(i,false));
            }
            // child list
            getline(cin,templine);
            if (templine[0]=='#') break;

            for (int i =0 ;i<now_loc.size();i++){
                if (templine[now_loc[i].first] == '|'){
                    now_loc[i].second = true;
                }
            }
            // set before list
            getline(cin,templine);
            before.clear();
            for (int i =0;i<now_loc.size();i++){                    
                if (now_loc[i].second){                        
                    int end=now_loc[i].first;
                    while (templine[end] == '-'){
                        end++;
                    }
                    before.push_back(make_pair(now[i],end));
                }
            }
        
        }
        
        cout << '(';
        if (top >0){
            pre_transver(0);           
        }
        cout << ')';
        
        cout << endl;
    }
}