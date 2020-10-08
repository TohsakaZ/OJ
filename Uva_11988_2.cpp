#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
const int MaxN = 100010;
char letters[MaxN];

int main()
{
    int next[MaxN];
    //ifstream fin("input.txt");
    //cin.rdbuf(fin.rdbuf());
    string templine;
    while (getline(cin,templine)){
        int head = 0;
        int tail = 0;
        int now = 0;
        next[head] = -1;
        for (int i =0;i<templine.length();i++){
            if (templine[i] == '['){
                now = head;
            }
            else if (templine[i] ==']'){
                now = tail;
            }
            else{
                next[i+1] = next[now];
                next[now] = i+1;
                if (now ==  tail){
                    tail =i+1;
                }
                now = i+1;
            }
        }
        for (int i =next[head];i!=-1;i=next[i]){
            cout << templine[i-1];
        }
        cout << endl;
    }
}