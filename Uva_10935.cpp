#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

int main()
{

    //ifstream fin;
    //fin.open("input.txt");
    //cin.rdbuf(fin.rdbuf());

    int card_number;
    while (cin >> card_number and card_number!=0)
    {
        queue<int> cards;
        for (int i = 1; i <= card_number;i++)
        {
            cards.push(i);
        }
        cout << "Discarded cards:";
        while (true)
        {
            int first_number = cards.front();
            cards.pop();
            if (cards.empty()){
                cout << endl;
                cout << "Remaining card: " << first_number << endl;
                break;
            }
            int second_number = cards.front();
            cards.pop();
            if (cards.empty()){
                cout << " " << first_number ;
            }
            else{
                cout << " " << first_number << ",";
            }
            cards.push(second_number);
        }
    }
}