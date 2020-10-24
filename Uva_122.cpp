#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>


using namespace std;

struct node;
typedef node* link;

struct node{
    node(){
        value=-1;
        left = nullptr;
        right = nullptr;
    }
    int value;
    link left;
    link right;
};


bool add_node(link head,int n,string& s){
    for (int i =0;i<s.length();i++){
        char dir = s[i];
        if (dir == 'L'){
            if (!head->left)  {
                head->left = new node();
            }
            head = head->left;
        }
        else{
            if (!head->right){
                head->right = new node();
            }
            head = head->right;
        }
    }
    
    if (head->value==-1){
        head->value = n;
    }
    else{
        return false;
    }
    return true;
}

bool bfs(link head){
    stringstream output;
    queue<link> node_list; 
    node_list.push(head);
    while (!node_list.empty()){
        head = node_list.front();
        node_list.pop();
        if (head->value == -1){
            return false;
        }
        if (head->left) node_list.push(head->left);
        if (head->right) node_list.push(head->right);
        output << head->value  << " ";
    }
    string out = output.str();
    out = out.substr(0,out.size()-1);
    cout << out << endl;
    return true;
}

void freze(link head){
    queue<link> node_list;
    node_list.push(head);
    while (!node_list.empty()){
        head = node_list.front();
        node_list.pop();
        if (head->left){
            node_list.push(head->left);
        }
        if (head->right){
            node_list.push(head->right);
        }
        delete(head);
    }
}

void str2ns(string& str,int& n,string& s){
    //cout << str << endl;
    stringstream temp_split(str.substr(1));
    temp_split >> n;
    temp_split >> s;
    //cout << n << " " << s << endl;
    if (s.length() == 2){
        s = "";
    }
    else{
        s = s.substr(1,s.length()-2);
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    string templine ;
    while (cin >> templine){
        link head = new node();
        int n;        
        string s;
        str2ns(templine,n,s);
        bool flag=true;
        if (!add_node(head,n,s)){
            flag = false; 
        }
        while (cin >> templine && templine!="()"){
            str2ns(templine,n,s);
            flag = flag?add_node(head,n,s):flag;
        }

        if (flag){
            if (!bfs(head)){
                cout << "not complete" << endl;
            }
        }
        else{
            cout << "not complete" << endl;
        }
        freze(head);
    }

    
}
