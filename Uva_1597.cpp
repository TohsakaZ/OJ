#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>

using namespace std;

int main()
{
    ifstream fin;
    fin.open("input.txt");
    cin.rdbuf(fin.rdbuf());
}