#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


struct mobile
{
    int Wl;
    int Dl;
    int Wr;
    int Dr;
};
int top = 0;
int judge(int head){
    mobile new_m;
    cin >> new_m.Wl >> new_m.Dl >> new_m.Wr >> new_m.Dr;

    if (!new_m.Wl) {
        top++;
        new_m.Wl = judge(top);
    }
    if (!new_m.Wr){
        top++;
        new_m.Wr = judge(top);
    }
    
    if (new_m.Wl == -1 || new_m.Wr == -1 || new_m.Wl*new_m.Dl != new_m.Wr * new_m.Dr){
        return -1;
    }
    else{
        return new_m.Wl+ new_m.Wr;     
    }
}

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int case_number;
    cin >> case_number;
    for (int i =0;i<case_number;i++){
        int top=0;
        if (judge(top)==-1){
            cout << "NO" << endl;    
        }
        else{
            cout << "YES" << endl;
        }
        if (i != case_number-1){
            cout << endl;
        }
    }
}