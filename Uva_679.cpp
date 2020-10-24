#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());

    int case_number;
    cin >> case_number;
    for (int i =0;i<case_number;i++){
        int D,I;
        cin >> D >> I;
        //cout << D << " " << I << endl;
        int deep = 1;
        int loc = 1;
        while (deep < D ){
            //cout << loc << I << endl;
            loc = (I%2==0)?(loc*2+1):loc*2; 
            I = (I%2==0)?(I/2):(I+1)/2;
            deep++;
        }
        cout << loc << endl;
    }


}
