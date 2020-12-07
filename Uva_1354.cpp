#include <iostream>
#include <fstream>

using namespace std;




int main(){
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
}