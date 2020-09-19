#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <map>
#include <set>

using namespace std;


class buy_trade
{
public:
    buy_trade(int size,int price,int number):
        size(size),
        price(price),
        number(number)
    {
    }
    int price=0;
    int size=0;
    int number =0;

    bool operator> (const buy_trade& Other){
        return (price > Other.price || (price == Other.price && number < Other.number));
    }
};

class sell_trade 
{
public:
    sell_trade(int size,int price,int number):
        size(size),
        price(price),
        number(number)
    {
    }
    int price=0;
    int size=0;
    int number =0;

    bool operator> (const sell_trade& Other){
        return (price < Other.price || (price == Other.price && number < Other.number));
    }
};




int main()
{
    ifstream fin("input.txt");
    cin.rdbuf(fin.rdbuf());
    int cnt=0;
    int number_message=0;
    while (cin >> number_message){
        if (cnt!=0){
            cout << endl;
        }
        set<int> unvalid_map;
        priority_queue<buy_trade> buy_list;
        priority_queue<sell_trade> sell_list;

        while (number_message--){
            string templine;
            getline(cin,templine);
            stringstream line_split(templine);
            string key_word;
            line_split >> key_word;
            if (key_word == "BUY"){
                int size,price;
                line_split >> size >> price;
                while (size > 0){
                    while (!sell_list.empty() and unvalid_map.count(sell_list.top().number)!=0 ){
                        sell_list.pop();
                    }

                    if (sell_list.empty() || price < sell_list.top().price){
                        break;
                    }
                    
                    int common_size = min(size,sell_list.top().size);
                    size -= common_size;

                }
            }
            else if (key_word == "SELL"){
                int size,price;
                line_split >> size >> price;
                trade_info* new_trade = new trade_info(size,true);
                message_list.push_back(new_trade);
                sell_table.push(price);
                sell_list[price].push(new_trade);
            }
            else if (key_word == "CANCEL"){
                int number;
                line_split >> number;
                unvalid_map.isnert(number);
            }

            // cout quote
        }
        string empty_line;
        getline(cin,empty_line);
    }

}