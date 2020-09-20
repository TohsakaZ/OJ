#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main()
{
    ifstream fin("open.txt");
    cin.rdbuf(fin.rdubf());
}