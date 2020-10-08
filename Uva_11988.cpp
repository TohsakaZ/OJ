#include <iostream>
#include <fstream>

using namespace std;
const int MaxN = 100010;
char letters[MaxN];

struct node;
typedef node *point;
struct node{
    char letter;
    point next;
    point pre;
};

int main()
{
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());
    string line;
    while (getline(cin,line)){
        point head = new node;
        point tail = new node;
        head->next = tail;
        head->pre = nullptr;
        tail->next = nullptr;
        tail->pre = head;
        head->letter = '\0';
        tail->letter = '\0';
        point now = head;
        
        for (int i =0;i<line.length();i++){
            if (line[i]=='['){
                now = head;
            }
            else if (line[i] == ']'){
                now = tail->pre;
            }
            else{
                point newnode = new node;
                newnode->letter = line[i];
                newnode->next = now->next;  
                newnode->pre = now;
                now->next->pre = newnode;
                now->next = newnode;
                now = newnode;
            }
        }
        for (point i =head->next ; i !=tail;){
            cout << i->letter ; 
            i = i->next;
            delete i->pre;
        }
        delete head;
        delete tail; 
        cout << endl;
    }
}